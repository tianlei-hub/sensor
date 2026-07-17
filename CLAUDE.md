# CLAUDE.md — sensor (STM32F407)

基于 STM32CubeMX 生成的 STM32F407xx 传感器项目，使用 CMake + Ninja + ARM GCC 在 VS Code 中开发。

## 构建命令

```bash
# 配置（Debug）
cmake --preset Debug

# 编译
cmake --build build/Debug

# 编译并下载到开发板（CMSIS-DAP）
cmake --build build/Debug --target flash

# 配置（Release）
cmake --preset Release
cmake --build build/Release
```

- CMake 预设定义在 [CMakePresets.json](CMakePresets.json) 中
- 工具链文件：[cmake/gcc-arm-none-eabi.cmake](cmake/gcc-arm-none-eabi.cmake)（`arm-none-eabi-gcc`，需在 PATH 中）
- 构建产物：`build/Debug/sensor.elf`、`.map`、`.hex`、`.bin`
- VS Code 中通过 `cmake` 和 `stm32cube-ide-clangd` 扩展可直接构建

## 项目架构

```
sensor/
├── Core/
│   ├── Inc/           # 用户头文件（外设初始化声明）
│   │   ├── main.h     # 主头文件 + GPIO pin 宏定义
│   │   ├── adc.h      # ADC3 句柄声明
│   │   ├── gpio.h     # GPIO 初始化声明
│   │   ├── i2c.h      # I2C1/I2C2 句柄声明
│   │   ├── tim.h      # TIM12 句柄声明
│   │   ├── stm32f4xx_hal_conf.h  # HAL 模块开关
│   │   └── stm32f4xx_it.h        # 中断处理声明
│   └── Src/           # 用户源码
│       ├── main.c     # 入口 main() + 时钟配置（168MHz, HSE+PLL）
│       ├── adc.c / gpio.c / i2c.c / tim.c  # 外设初始化
│       ├── stm32f4xx_hal_msp.c  # HAL MSP（外设底层初始化）
│       ├── stm32f4xx_it.c       # 中断服务例程
│       └── syscalls.c / sysmem.c  # 底层系统调用
├── Drivers/
│   ├── CMSIS/              # ARM CMSIS 核心 + STM32F4xx 设备头
│   └── STM32F4xx_HAL_Driver/  # STM32 HAL 驱动（按需编译的源文件）
├── cmake/
│   ├── gcc-arm-none-eabi.cmake  # ARM GCC 工具链配置
│   ├── starm-clang.cmake        # STM32CubeIDE clang 工具链（备选）
│   └── stm32cubemx/
│       └── CMakeLists.txt       # CubeMX 生成的模块（源文件/宏/头文件路径）
├── sensor.ioc             # STM32CubeMX 项目文件
├── STM32F407XX_FLASH.ld   # 链接脚本
├── CMakeLists.txt         # 顶层 CMake（项目定义，用户扩展点）
├── CMakePresets.json      # CMake 预设（Debug / Release）
└── .vscode/               # VS Code 配置（cmake + clangd）
```

## 外设配置

| 外设 | 实例 | 用途 |
|------|------|------|
| ADC | ADC3 | 模数采集 |
| I2C | I2C1, I2C2 | I2C 通信 |
| TIM | TIM12 | PWM 输出（PB14） |
| GPIO EXTI | PE2 (LIGHT), PE3 (SPEED), PE4 (SWITCH) | 外部中断输入 |

## 关键 Pin 定义

| 宏 | Pin | 端口 | 说明 |
|----|-----|------|------|
| `LIGHT_Pin` | PE2 | GPIOE | 光传感器，EXTI2 中断 |
| `SPEED_Pin` | PE3 | GPIOE | 速度传感器，EXTI3 中断 |
| `SWITCH_Pin` | PE4 | GPIOE | 开关，EXTI4 中断 |
| `LS1_Pin` | PF7 | GPIOF | — |
| `LED_GREEN_Pin` | PF10 | GPIOF | 绿色 LED |
| `PWM_Pin` | PB14 | GPIOB | PWM 输出 (TIM12) |
| `BI_Pin` | PB15 | GPIOB | — |

定义位于 [Core/Inc/main.h](Core/Inc/main.h#L60-L77)。

## 开发注意事项

### CubeMX 代码生成规则
- CubeMX 重新生成时只覆盖 **`USER CODE BEGIN`/`USER CODE END`** 块之外的内容
- 用户代码应放在这些标记块内：`USER CODE BEGIN Includes`、`USER CODE BEGIN PV`、`USER CODE BEGIN 2` 等
- `cmake/stm32cubemx/CMakeLists.txt` 由 CubeMX 管理，不要手动修改
- 顶层 `CMakeLists.txt` 仅生成一次，允许用户自由修改
- `.mxproject` 由 CubeMX IDE 使用，不要手动编辑

### CubeMX 后需检查
- 如果在 CubeMX 中添加/移除外设，需要检查 `cmake/stm32cubemx/CMakeLists.txt` 中的源文件列表是否同步
- GPIO pin 宏在 [Core/Inc/main.h](Core/Inc/main.h) 中，CubeMX 会维护
- HAL 模块开关在 [Core/Inc/stm32f4xx_hal_conf.h](Core/Inc/stm32f4xx_hal_conf.h)，按需启用/禁用

### 工具链
- **编译器**: `arm-none-eabi-gcc`（工具链文件: `cmake/gcc-arm-none-eabi.cmake`）
- **架构**: Cortex-M4 + FPU (`-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard`)
- **精简库**: 使用 `--specs=nano.specs`
- **语言标准**: C11
- **调试符号表**: Debug 用 `-O0 -g3`，Release 用 `-Os -g0`

### VS Code 设置
- `.clangd` 指定编译命令数据库路径为 `build/Debug`
- VS Code `settings.json` 使用 `cube-cmake`（STM32CubeIDE 绑定的 cmake）和 `starm-clangd`
- 如果脱离 CubeIDE 环境，需要自行安装 `arm-none-eabi-gcc` 工具链并确保在 PATH 中

### 中断服务
- 中断处理函数在 [Core/Src/stm32f4xx_it.c](Core/Src/stm32f4xx_it.c) 中
- EXTI2/3/4 回调可在 `HAL_GPIO_EXTI_Callback()` 中处理
- `Error_Handler()` 在 [main.c](Core/Src/main.c#L164-L173) 中，发生 HAL 错误时调用

### 内存
- 链接脚本 [STM32F407XX_FLASH.ld](STM32F407XX_FLASH.ld) 定义 Flash/RAM 布局
- 构建后 `--print-memory-usage` 会输出 Flash/RAM 使用统计
