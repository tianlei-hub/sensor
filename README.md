# sensor — 智能环境监测与控制系统

基于 **STM32F407ZG（正点原子探索者）** 的多传感器环境监测系统，采集温湿度与光照，OLED 本地显示，按键控制 PWM 风扇。软件基于 **CMSIS-RTOS v2 (FreeRTOS)** 四层模块化架构。

```
AHT20 温湿度 ─┐
              ├─▶ SensorTask ─▶ DataModel ─▶ DisplayTask ─▶ OLED
光敏传感器 ───┘        │                          │
                     滤波                       风扇动画
                                                  │
按键 ──EXTI──▶ 消息队列 ──▶ FanCtrlTask ─▶ 状态机 ─▶ PWM 风扇
```

---

## 一、硬件接线（外设接哪个口）

> 所有接线均在开发板的排针上完成，按 **GPIO 端口+引脚号** 对应即可。

### 传感器/外设接线表

| 外设 | 接口 | 引脚 | 说明 |
|------|------|------|------|
| **AHT20 温湿度传感器** | I2C2 | **PF0 = SDA，PF1 = SCL** | 7 位地址 `0x38`，需外接 4.7kΩ 上拉电阻 |
| **SSD1306 OLED (128×64)** | I2C1 | **PB6 = SCL，PB7 = SDA** | 7 位地址 `0x3C`，模块自带 I2C 接口 |
| **光敏传感器模块** | ADC3 通道5 | **PF7** | 模块 AO 模拟输出接 PF7，VCC 接 3.3V |
| **风扇（PWM 调速）** | TIM12_CH1 | **PB14** | 驱动需三极管/MOS 管，MCU 输出 20kHz PWM |
| **按键 SWITCH（风扇开关）** | EXTI2 | **PE2** | 一端接 PE2，**另一端接 GND** |
| **按键 SPEED（风扇调速）** | EXTI3 | **PE3** | 一端接 PE3，**另一端接 GND** |
| **按键 LIGHT（OLED开关）** | EXTI4 | **PE4** | 一端接 PE4，**另一端接 GND** |
| **绿色 LED** | GPIO | **PF10** | 低电平点亮，运行指示灯 |

### 接线注意事项

1. **按键必须接到 GND**：代码配置为下降沿触发 + 内部上拉。接 VCC 按键将无反应。
2. **I2C 上拉电阻**：
   - OLED 模块一般自带上拉；
   - AHT20 裸模块通常**不带**上拉，需要在 PF0/PF1 上各接 4.7kΩ 到 3.3V。
3. **风扇驱动**：PB14 是 3.3V 信号，**不能直接接风扇**。需经过 NPN 三极管（如 S8050）或 MOS 管（如 AO3400）放大驱动，风扇电源单独供电。
4. **光敏传感器**：若使用光敏电阻模块，AO 输出接 PF7；电压越高代表越暗（代码中做了反相）。

### 电源与调试

| 项目 | 连接 |
|------|------|
| 调试器 | SWD（PA13=SWDIO, PA14=SWCLK），CMSIS-DAP / ST-Link |
| 串口烧录 | 不需要，OpenOCD 经 SWD 下载 |

---

## 二、软件架构

```
sensor/
├── Core/                    # STM32CubeMX 生成（HAL + 外设初始化）
│   ├── Src/main.c           # 精简入口：硬件初始化 → 启动调度器
│   ├── Src/freertos.c       # RTOS 初始化（挂载 App_Entry）
│   └── Src/oled.c, font.c   # OLED 底层驱动
├── App/                     # 应用层（任务）
│   ├── app_entry.c          # 初始化 + 创建任务 + 事件队列
│   ├── task_sensor.c        # 500ms 周期采集，滤波后发布
│   ├── task_display.c       # 等通知刷新 OLED
│   └── task_fan.c           # 按键事件 → 状态机 → PWM
├── BSP/                     # 驱动层（可复用，句柄参数化）
│   ├── bsp_aht20.c          # AHT20 温湿度
│   ├── bsp_fan.c            # PWM 风扇
│   └── bsp_lightsensor.c    # 光敏 ADC
├── Services/                # 服务层（纯逻辑）
│   ├── data_model.c         # 共享数据 + 互斥锁
│   ├── fan_sm.c             # 风扇状态机 OFF/HALF/FULL
│   └── data_filter.c        # 滑动平均滤波
└── Middlewares/FreeRTOS/    # FreeRTOS + CMSIS-RTOS v2
```

### 任务与通信

| 任务 | 优先级 | 周期 | 职责 |
|------|--------|------|------|
| task_sensor | Normal | 500ms | 采集 AHT20+光敏 → 滤波 → DataModel → 通知显示 |
| task_display | Low | 通知驱动 | 读 DataModel → 刷新 OLED |
| task_fan | Normal | 事件驱动 | 队列收按键 → 状态机 → PWM |

- **按键链路**：EXTI ISR（消抖+入队）→ `osMessageQueuePut` → task_fan（状态机+输出）
- **数据链路**：SensorTask 写、DisplayTask 读，`osMutexId_t` 保护

### 风扇状态机

```
        SWITCH按下
  OFF ───────────▶ FULL
   ▲      SPEED     │
   │  OFF──▶HALF    │ SPEED
   │  HALF──▶FULL   │
   └── HALF ◀───────┘
```

---

## 三、按键功能

| 按键 | 功能 |
|------|------|
| **SWITCH (PE2)** | 风扇开（全速）/ 关 |
| **SPEED (PE3)** | 风扇 半速 ↔ 全速 循环（关状态按下=半速启动） |
| **LIGHT (PE4)** | OLED 显示 开/关 |

---

## 四、构建与烧录

### 环境要求

- STM32CubeIDE 的捆绑工具链（`CUBE_BUNDLE_PATH` 指向 `stm32cube/bundles`）或独立 `arm-none-eabi-gcc`（需在 PATH 中）
- CMake ≥ 3.22 + Ninja
- OpenOCD（CMSIS-DAP 调试器）

### 构建

```bash
# 配置（自动查找 ARM GCC：PATH → CubeIDE 捆绑工具链）
cmake --preset Debug

# 编译
cmake --build build/Debug

# 烧录到开发板（CMSIS-DAP）
cmake --build build/Debug --target flash

# 擦除芯片
cmake --build build/Debug --target erase
```

编译输出：`build/Debug/sensor.elf` / `.hex` / `.bin` / `.map`

### 内存占用（当前）

```
RAM:   22.4 KB / 128 KB  (17.07%)
FLASH: 46.4 KB / 1 MB    (4.43%)
```

---

## 五、Git 分支

| 分支 | 内容 |
|------|------|
| `main` | v1.0 裸机版本（无 RTOS） |
| `freertos-upgrade` | FreeRTOS 模块化重构（当前开发） |

```bash
git checkout main               # 回到裸机版
git checkout freertos-upgrade   # 回到 RTOS 版
```

---

## 六、路线图

- [x] 裸机多传感器采集与显示
- [x] CMSIS-RTOS v2 四层架构重构
- [ ] IWDG 硬件看门狗
- [ ] USART1 CLI 调试命令行
- [ ] ESP8266 (ATK-MB026) WiFi 远程访问
- [ ] Web 仪表盘 + 微信小程序
