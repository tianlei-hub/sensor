# ATK-MB026 WIFI & BLE 模块用法总结
> 适配平台：正点原子 STM32F407 探索者 + STM32CubeMX + Keil + HAL库

---

## 1. 模块概述

ATK-MB026 是正点原子的高性能 WIFI & BLE 模块，核心芯片为 **ESP32-C3**（乐鑫）。

| 项目 | 说明 |
|------|------|
| WIFI协议 | IEEE 802.11 b/g/n |
| 蓝牙 | Bluetooth 5 (BLE) + Bluetooth mesh |
| 通信接口 | TTL串口（115200bps, 8N1） |
| 工作模式 | Station / SoftAP / Station+SoftAP |
| 供电 | 5V |
| 尺寸 | 32.5mm × 19.0mm |
| TCP客户端连接数 | 最多5个 |

模块出厂自带AT固件，通过AT指令即可完成所有配置，不需要自己烧写ESP32-C3固件。

---

## 2. 模块引脚说明

模块共6个2.54mm排针引脚：

| 引脚 | 说明 | 接F407探索者 |
|------|------|-------------|
| VCC | 5V电源 | 5V |
| GND | 电源地 | GND |
| TXD | 模块串口发送(TTL)，接MCU的RX | F407的UART RX引脚 |
| RXD | 模块串口接收(TTL)，接MCU的TX | F407的UART TX引脚 |
| RST | 复位，低电平有效 | F407的GPIO输出引脚 |
| IO_9 | 固件烧写模式控制，正常运行不接 | 不接（悬空即可） |

**注意：TXD/RXD是TTL电平（3.3V），不能直接接RS232电平！**

---

## 3. 硬件连接方案（F407探索者）

原厂例程基于STM32F103，引脚映射如下。F407探索者建议用同样的逻辑，选一组空闲UART即可：

### 推荐连接方案

| ATK-MB026引脚 | F407探索者引脚 | 说明 |
|---------------|---------------|------|
| VCC | 5V | 供电 |
| GND | GND | 共地 |
| TXD | PB11 (USART3_RX) | 模块→MCU |
| RXD | PB10 (USART3_TX) | MCU→模块 |
| RST | PA4 (GPIO推挽输出) | 硬件复位控制 |
| IO_9 | 不接 | 运行模式下不需要 |

> 如果USART3(PB10/PB11)已被占用，可换用其他UART（如USART2: PA2/PA3，或UART4/UART5）。原则：选一组空闲的UART，波特率能配到115200即可。

---

## 4. STM32CubeMX 配置步骤

### 4.1 时钟配置
- 外部HSE晶振 25MHz（探索者板载晶振）
- 系统时钟配置为 168MHz（HCLK）

### 4.2 USART3配置（与模块通讯）
1. `Connectivity` → `USART3` → Mode选 `Asynchronous`
2. Parameter Settings:
   - Baud Rate: `115200`
   - Word Length: `8 Bits (including Parity)`
   - Parity: `None`
   - Stop Bits: `1`
3. DMA Settings（推荐）: 添加USART3_RX的DMA接收
   - Direction: `Peripheral To Memory`
   - Priority: `Low`
   - Mode: `Normal`
   - Data Width: Peripheral=`Byte`, Memory=`Byte`
4. NVIC Settings:
   - 勾选 `USART3 global interrupt` → Enable
   - 勾选 `USART3 RX DMA interrupt` → Enable

### 4.3 GPIO配置（RST复位引脚）
- 选择 `PA4`，设为 `GPIO_Output`
- Output Push Pull，默认电平 `High`（上电时RST为高，模块正常运行）
- User Label: `WIFI_RST`

### 4.4 USART1（调试串口，可选）
- 如果需要printf调试输出，配置USART1(PA9/PA10)，115200，8N1
- 勾选 `Asynchronous`

### 4.5 生成代码
- Project Manager → Toolchain选 `MDK-ARM`
- Code Generator → 勾选 `Generate peripheral initialization as a pair of .c/.h`
- 点击 `GENERATE CODE`

---

## 5. 软件驱动框架（HAL库）

### 5.1 文件结构

```
Drivers/BSP/
├── atk_mb026_uart.c    // UART驱动（收发、不定长数据接收）
├── atk_mb026_uart.h
├── atk_mb026.c          // 模块驱动（AT指令封装）
└── atk_mb026.h
```

### 5.2 UART不定长接收方案

ESP32-C3通过UART回传的数据长度不固定。推荐两种方案：

**方案A：DMA + 空闲中断（推荐，F407支持）**

```c
// 在main中启动DMA接收
HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, RX_BUF_SIZE);

// 空闲中断回调
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART3) {
        // Size即为本次接收到的数据长度
        // 将数据拷贝到帧缓冲区，标记帧完成
        memcpy(frame_buf, rx_buf, Size);
        frame_len = Size;
        frame_ready = 1;
        // 重新启动DMA接收
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, RX_BUF_SIZE);
    }
}
```

**方案B：定时器超时分包（通用，不依赖空闲中断）**

原理：每收到1个字节重置定时器，如果定时器超时（如50ms无新数据），则认为一帧接收完成。

### 5.3 核心驱动函数

#### 发送AT指令并等待响应

```c
/**
 * @brief  发送AT指令并等待期望响应
 * @param  cmd:  AT指令字符串（不含\r\n，函数自动添加）
 *         ack:  期望的响应关键字，如"OK"；传NULL则不等待
 *         timeout: 超时时间(ms)
 * @retval 0:成功  1:超时失败
 */
uint8_t atk_mb026_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    uint32_t tickstart = HAL_GetTick();

    // 清空接收缓冲区，重新开始接收
    atk_mb026_uart_rx_restart();

    // 发送指令（自动加\r\n）
    HAL_UART_Transmit(&huart3, (uint8_t *)cmd, strlen(cmd), 1000);
    uint8_t newline[] = "\r\n";
    HAL_UART_Transmit(&huart3, newline, 2, 100);

    if (ack == NULL || timeout == 0) {
        return 0;  // 不需要等待响应
    }

    // 等待期望响应
    while ((HAL_GetTick() - tickstart) < timeout) {
        ret = atk_mb026_uart_rx_get_frame();
        if (ret != NULL) {
            if (strstr((const char *)ret, ack) != NULL) {
                return 0;  // 收到期望响应
            }
            atk_mb026_uart_rx_restart();  // 不是期望响应，继续等
        }
        HAL_Delay(1);
    }
    return 1;  // 超时
}
```

#### 模块初始化

```c
/**
 * @brief  ATK-MB026初始化
 * @param  baudrate: 串口波特率(固定115200)
 * @retval 0:成功  1:失败
 */
uint8_t atk_mb026_init(uint32_t baudrate)
{
    // 1. 硬件复位：拉低RST再拉高
    HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(500);  // 等待模块启动

    // 2. 启动UART DMA接收
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, RX_BUF_SIZE);

    // 3. AT指令测试（重试10次）
    for (uint8_t i = 0; i < 10; i++) {
        if (atk_mb026_send_at_cmd("AT", "OK", 500) == 0) {
            return 0;  // 通讯正常
        }
    }
    return 1;  // 通讯失败
}
```

---

## 6. 三种典型应用场景

### 场景一：Station模式 + TCP透传（最常用）

```c
#define DEMO_WIFI_SSID       "your_wifi_name"
#define DEMO_WIFI_PWD        "your_wifi_password"
#define DEMO_TCP_SERVER_IP   "192.168.1.100"
#define DEMO_TCP_SERVER_PORT "8080"

void wifi_tcp_demo(void)
{
    uint8_t ret;
    char ip_buf[64] = {0};

    // 1. 初始化模块
    ret = atk_mb026_init(115200);
    if (ret) { printf("init failed!\r\n"); return; }

    // 2. 恢复出厂设置 + AT测试
    atk_mb026_send_at_cmd("AT+RESTORE", "OK", 2000);
    HAL_Delay(1000);
    atk_mb026_send_at_cmd("AT", "OK", 500);

    // 3. 设为Station模式
    atk_mb026_send_at_cmd("AT+CWMODE=1", "OK", 1000);
    atk_mb026_send_at_cmd("AT+RST", "OK", 2000);
    HAL_Delay(500);

    // 4. 关闭回显
    atk_mb026_send_at_cmd("ATE0", "OK", 500);

    // 5. 连接WIFI
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"", DEMO_WIFI_SSID, DEMO_WIFI_PWD);
    ret = atk_mb026_send_at_cmd(cmd, "OK", 15000);  // 连WIFI可能需要较长时间
    if (ret) { printf("WiFi connect failed!\r\n"); return; }
    printf("WiFi connected!\r\n");

    // 6. 获取IP地址
    atk_mb026_send_at_cmd("AT+CIFSR", "OK", 2000);

    // 7. 连接TCP服务器
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",%s",
             DEMO_TCP_SERVER_IP, DEMO_TCP_SERVER_PORT);
    ret = atk_mb026_send_at_cmd(cmd, "OK", 5000);
    if (ret) { printf("TCP connect failed!\r\n"); return; }
    printf("TCP connected!\r\n");

    // 8. 进入透传模式
    atk_mb026_send_at_cmd("AT+CIPMODE=1", "OK", 500);
    atk_mb026_send_at_cmd("AT+CIPSEND", ">", 1000);  // 收到">"表示可发送数据
    printf("Entered transparent mode!\r\n");

    // 9. 此后直接通过UART发送/接收的数据即为TCP透传数据
    //    退出透传：发送"+++"（前后各1秒不发送其他数据）
}
```

### 场景二：SoftAP模式（模块做热点）

```c
void wifi_ap_demo(void)
{
    atk_mb026_init(115200);
    atk_mb026_send_at_cmd("AT+RESTORE", "OK", 2000);
    HAL_Delay(1000);

    // 设为SoftAP模式
    atk_mb026_send_at_cmd("AT+CWMODE=2", "OK", 1000);
    atk_mb026_send_at_cmd("AT+RST", "OK", 2000);
    HAL_Delay(500);

    // 设置AP参数：SSID=ATK-MB026, 密码=12345678, 信道=1, WPA_WPA2_PSK
    atk_mb026_send_at_cmd("AT+CWSAP=\"ATK-MB026\",\"12345678\",1,4", "OK", 1000);

    // 开启多连接
    atk_mb026_send_at_cmd("AT+CIPMUX=1", "OK", 500);

    // 开启TCP服务器，端口8086
    atk_mb026_send_at_cmd("AT+CIPSERVER=1,8086", "OK", 1000);

    // 之后手机/电脑连上ATK-MB026热点，即可TCP连接 192.168.4.1:8086
}
```

### 场景三：BLE透传（模块做蓝牙服务端）

```c
#define BLE_NAME   "ATK-MB026"
#define BLE_UUID   "A002"
#define BLE_DATA   "0102030405"
#define BLE_POWER   1

void ble_demo(void)
{
    atk_mb026_init(115200);
    atk_mb026_send_at_cmd("AT+RESTORE", "OK", 2000);
    HAL_Delay(1000);
    atk_mb026_send_at_cmd("AT", "OK", 500);

    // BLE初始化为server角色
    atk_mb026_send_at_cmd("AT+BLEINIT=2", "OK", 1000);

    // GATTS创建服务
    atk_mb026_send_at_cmd("AT+BLEGATTSSRVCRE", "OK", 1000);

    // GATTS开启全部服务
    atk_mb026_send_at_cmd("AT+BLEGATTSSRVSTART", "OK", 1000);

    // 设置广播数据
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+BLEADVDATAEX=\"%s\",\"%s\",\"%s\",%d",
             BLE_NAME, BLE_UUID, BLE_DATA, BLE_POWER);
    atk_mb026_send_at_cmd(cmd, "OK", 1000);

    // 关闭回显
    atk_mb026_send_at_cmd("ATE0", "OK", 500);

    // 获取BLE地址
    atk_mb026_send_at_cmd("AT+BLEADDR?", "OK", 1000);

    // 开启广播
    atk_mb026_send_at_cmd("AT+BLEADVSTART", "OK", 1000);

    // 设置BLE SPP参数
    atk_mb026_send_at_cmd("AT+BLESPPCFG=1,1,7,1,5,1", "OK", 1000);

    // 等待主设备连接后，进入SPP透传模式
    // atk_mb026_send_at_cmd("AT+BLESPP", "OK", 1000);
}
```

---

## 7. 常用AT指令速查表

### 7.1 基础指令

| 指令 | 说明 | 示例 |
|------|------|------|
| AT | 测试AT是否就绪 | `AT` → `OK` |
| AT+RST | 重启模块 | `AT+RST` |
| AT+GMR | 查询版本信息 | `AT+GMR` |
| ATE0 | 关闭回显 | `ATE0` |
| ATE1 | 开启回显 | `ATE1` |
| AT+RESTORE | 恢复出厂设置（会重启） | `AT+RESTORE` |
| AT+UART | 配置串口参数 | `AT+UART=115200,8,1,0,0` |

### 7.2 WIFI指令

| 指令 | 说明 | 示例 |
|------|------|------|
| AT+CWMODE | 设置WIFI模式 | `AT+CWMODE=1` (Station) |
| AT+CWJAP | 连接AP | `AT+CWJAP="SSID","password"` |
| AT+CWLAP | 扫描附近AP | `AT+CWLAP` |
| AT+CWQAP | 断开AP | `AT+CWQAP` |
| AT+CWSAP | 设置AP参数 | `AT+CWSAP="ATK-MB026","12345678",1,4` |
| AT+CIFSR | 查询本地IP/MAC | `AT+CIFSR` |
| AT+CWDHCP | 设置DHCP | `AT+CWDHCP=1,1` |
| AT+CIPSTA | 设置STA静态IP | `AT+CIPSTA="192.168.1.100"` |

### 7.3 TCP/IP指令

| 指令 | 说明 | 示例 |
|------|------|------|
| AT+CIPSTART | 建立TCP/UDP/SSL连接 | `AT+CIPSTART="TCP","192.168.1.100",8080` |
| AT+CIPSEND | 发送数据 | `AT+CIPSEND=25` 或透传模式 `AT+CIPSEND` |
| AT+CIPCLOSE | 关闭连接 | `AT+CIPCLOSE` |
| AT+CIPMUX | 多连接模式 | `AT+CIPMUX=1` (多连接) / `=0` (单连接) |
| AT+CIPSERVER | 建立TCP服务器 | `AT+CIPSERVER=1,8086` |
| AT+CIPMODE | 透传模式 | `AT+CIPMODE=1` (透传) / `=0` (普通) |
| AT+CIPSTO | 服务器超时时间 | `AT+CIPSTO=1200` |
| AT+PING | Ping功能 | `AT+PING="192.168.1.1"` |
| AT+CIPDOMAIN | 域名解析 | `AT+CIPDOMAIN="www.baidu.com"` |

### 7.4 BLE指令

| 指令 | 说明 | 示例 |
|------|------|------|
| AT+BLEINIT | BLE初始化 | `AT+BLEINIT=2` (server) / `=1` (client) |
| AT+BLEGATTSSRVCRE | GATTS创建服务 | `AT+BLEGATTSSRVCRE` |
| AT+BLEGATTSSRVSTART | GATTS开启服务 | `AT+BLEGATTSSRVSTART=1` |
| AT+BLEADDR | 查询BLE地址 | `AT+BLEADDR?` |
| AT+BLEADVPARAM | 设置广播参数 | `AT+BLEADVPARAM=50,50,0,0,4` |
| AT+BLEADVDATA | 设置广播数据 | `AT+BLEADVDATA="1122334455"` |
| AT+BLEADVDATAEX | 设置广播数据(扩展) | `AT+BLEADVDATAEX="ATK-MB026","A002","0102030405",1` |
| AT+BLEADVSTART | 开始广播 | `AT+BLEADVSTART` |
| AT+BLECONN | 建立BLE连接 | `AT+BLECONN=0,"24:0a:c4:09:34:23"` |
| AT+BLESPPCFG | 设置BLE SPP参数 | `AT+BLESPPCFG=1,1,7,1,5,1` |
| AT+BLESPP | 进入BLE透传 | `AT+BLESPP` |

---

## 8. 透传模式使用要点

### WiFi透传
1. 必须是**单连接**（`AT+CIPMUX=0`）+ **TCP Client** 或 **UDP固定对端**
2. 设置 `AT+CIPMODE=1` 进入透传
3. 执行 `AT+CIPSEND`（不带参数），收到 `>` 后进入透传
4. 透传模式下UART收发的数据直接透传到TCP/UDP
5. 退出透传：发送 `+++`，注意前后各空1秒不发其他数据
6. **进入WiFi透传后，蓝牙功能不可用**

### BLE透传
1. 配置BLE SPP参数：`AT+BLESPPCFG=1,1,7,1,5,1`
2. 执行 `AT+BLESPP` 进入SPP透传
3. 退出：发送 `+++`

### 保存开机自动透传
```bash
# WiFi透传开机自启
AT+SAVETRANSLINK=1,"192.168.1.100",8080,"TCP"

# BLE透传开机自启
AT+SAVETRANSLINK=2,2,1,7,1,5,"aa:bb:cc:dd:ee:ff"
```

---

## 9. 调试要点 & 常见问题

### 9.1 模块无响应
- 检查VCC是否5V供电
- 检查TXD/RXD是否**交叉连接**（模块TXD接MCU RX，模块RXD接MCU TX）
- 检查波特率是否115200
- 检查RST引脚是否为高电平（低电平会持续复位）

### 9.2 AT指令返回ERROR
- AT指令必须**大写**
- 每条指令必须以 `\r\n` 结尾
- 回显模式下（ATE1）指令会回显，解析响应时注意过滤

### 9.3 连接WiFi失败
- 确认SSID和密码正确
- 密码用双引号包裹
- 2.4G WiFi，不支持5G
- `AT+CWJAP` 超时建议设15秒以上
- 用 `AT+CWLAP` 先扫描确认AP存在

### 9.4 TCP连接失败
- 确认服务器和模块在同一局域网
- 先连WiFi再建TCP连接
- 确认服务器防火墙放行对应端口

### 9.5 透传退出失败
- 发送 `+++` 时前后必须各空闲1秒以上
- 不要在发送 `+++` 前后紧跟其他数据

### 9.6 BLE搜索不到设备
- 确认执行了 `AT+BLEADVSTART` 开启广播
- 确认BLE初始化为正确角色（server: `AT+BLEINIT=2`）

---

## 10. 原厂例程移植说明

原厂提供三个例程（针对M48Z-M3 STM32F103版），移植到F407探索者需要修改：

| 修改项 | F103原厂 | F407探索者 |
|--------|---------|-----------|
| UART | PB10/PB11 (USART3) | 可保持，或改用其他UART |
| RST | PA4 | 可保持，或改用其他GPIO |
| HAL库 | F1的HAL | F4的HAL |
| 时钟 | 72MHz | 168MHz |
| delay | delay_ms() | HAL_Delay() |
| printf重定向 | USART1 | USART1 (PA9/PA10) |

### 移植步骤
1. 在CubeMX中配置USART3(115200,8N1) + DMA RX + 空闲中断
2. 配置RST对应的GPIO为推挽输出
3. 配置USART1做printf调试输出（可选）
4. 将原厂 `atk_mb026_uart.c/h` 和 `atk_mb026.c/h` 复制到工程
5. 修改UART句柄引用（`huart3` → 你的UART）
6. 修改RST引脚宏定义
7. 修改 `delay_ms()` → `HAL_Delay()`
8. 修改不定长接收逻辑：用 `HAL_UARTEx_ReceiveToIdle_DMA` 替代原厂的超时定时器方案
9. 修改 `demo.c` 中的WiFi SSID/密码、TCP服务器IP/端口

---

## 11. 参考文档

| 文档 | 路径 |
|------|------|
| 用户手册（AT指令详解） | ATK-MB026 WIFI & BLE模块用户手册_V1.1.pdf |
| 使用说明（例程解读） | ATK-MB026 WIFI & BLE模块使用说明_V1.0.pdf |
| ESP-AT指令集 | 参考资料/ESP-AT 用户指南.pdf |
| ESP32-C3数据手册 | 参考资料/esp32-c3_datasheet_cn.pdf |
| ESP32-C3技术参考 | 参考资料/esp32-c3_technical_reference_manual_cn.pdf |
| 原理图 | 2，原理图/ATK-MB026_V1.0.pdf |
