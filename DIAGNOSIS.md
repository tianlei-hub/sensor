# 调试笔记：OLED 黑屏 + 按键无反应 + 风扇不受控

> 更新：2026-08-14。**问题已解决**，根因与修复方案记录如下，供后续维护参考。

## 结论摘要

**症状**：改动（加 WiFi/MQTT 云任务）后 OLED 黑屏、按键（EXTI）无反应、风扇不受控、绿灯常亮。

**根因（gdb 实证）**：`App_Entry()` 在 `osKernelStart()` **之前**调用 `DataModel_Init()` →
`osMutexNew()`。FreeRTOS 的 `uxCriticalNesting` 毒值（`0xaaaaaaaa`，port.c:146）只在
`xPortStartScheduler()` 里初始化为 0（port.c:370）。启动前调用 FreeRTOS API 会进/出临界区，
但嵌套计数永远不为 0 → `vPortExitCritical()` 里的 `portENABLE_INTERRUPTS()` 永不执行 →
**BASEPRI 永久残留 0x50** → 屏蔽优先级 ≥5 的所有中断（含 TIM6 HAL 时基）→ uwTick 冻结 →
`BSP_AHT20_Init()` 的 `HAL_Delay(40)` 死循环 → App_Entry 永不返回 → 调度器永不启动。

基线（TICK_INT_PRIORITY=0）没暴露此 bug：TIM6 优先级 0 不受 BASEPRI=0x50 屏蔽，
uwTick 照常运行。改为 15（CubeMX 推荐值）后 TIM6 被屏蔽 → 问题暴露。

**修复**：`App_Entry()` 移入 `AppInitTask`（freertos.c，调度器启动后的首个用户任务，
执行完自动退出）。TICK_INT_PRIORITY 保持 15。这符合 FreeRTOS 官方规范：
**调度器启动前不要调用 FreeRTOS API**。

## 调试过程中的实证数据

gdb 断点跟踪（TICK_INT_PRIORITY=15 时）：

| 断点位置 | BASEPRI | uwTick |
| --- | --- | --- |
| App_Entry 入口（OLED_Init 前） | 0x00 | 正常增长 |
| DataModel_Init 入口（osMutexNew 前） | 0x00 | 正常增长 |
| DataModel_Init 返回后 | **0x50** | **冻结** |

卡死点：`BSP_AHT20_Init` 的 `HAL_Delay(40)`（bsp_aht20.c:31）。
TIM6 状态：CR1=1（计数中）、DIER=1（中断使能）、SR UIF=1（更新挂起未服务）、
NVIC ISER bit22=1（使能）——中断被 BASEPRI 屏蔽的铁证。

## 后续联调中解决的次要问题（WiFi/MQTT 链路）

| 问题 | 现象 | 解决 |
| --- | --- | --- |
| 模块 TX/RX 直连 | STM32 收不到任何数据（CLD:INIT） | **交叉接线**：模块 TXD→PB11，RXD→PB10 |
| 模块 IO_9 接 LED 接口（低电平） | boot 日志显示 `boot:0x5 (DOWNLOAD...)`，模块进固件烧写模式，AT 无应答 | IO_9 **悬空**（高电平=运行模式） |
| RST 引脚 | 用户接线改为 PA4 | WIFI_RST 宏改为 GPIOA Pin4（main.h） |
| WiFi 连接偶发超时 | CLD:WIFI | JoinWifi 失败后隔 2s 重试一次 |
| MQTT 域名 | CONNACK 返回码 4（鉴权失败） | 改为产品级域名 `{产品ID}.mqtts.acc.cmcconenet.cn` |
| token 复制含 `%0A`（网页折行） | 仍返回码 4 | 去掉 %0A |
| access_key 与 token 不配对 | 仍返回码 4（本地重算 sign 与平台显示 sign 不匹配） | **用设备密钥（非产品 access_key）按官方算法本地生成 token**：`msg = et+"\n"+method+"\n"+res+"\n"+version`，`sign = base64(hmac_sha1(base64decode(device_key), msg))`，sign 需 URL 编码 |

**OneNET token 生成要点**（后续换设备/密钥时参考）：

- 设备接入必须用**设备级密钥**（设备详情页的 Device Key），不是产品级 access_key
- res = `products/{产品ID}/devices/{设备名}`（未 URL 编码形式参与签名）
- et 为过期时间 Unix 时间戳；token 各 value 需 URL 编码（`/`→%2F，`=`→%3D）
- 平台网页显示 token 时的 `%0A` 是折行符号，复制时必须去掉

## 遗留 TODO

1. **安全**：WiFi 密码（bsp_mb026.h）与 Token（mqtt_client.h）硬编码，仓库公开前提取到
   gitignore 的配置文件
2. 清理 `sensor-baseline` worktree（C:/Users/tianlei/Desktop/test/cubemx-vscode/sensor-baseline）
3. 提交时注意未跟踪文件：Core/Src/usart.c、dma.c、hal_uart 等（CubeMX 生成）、
   访问云服务器参数.txt（凭据，勿提交或先 gitignore）
4. 云状态显示（CLD:xxx 一行）与 cloud_detail 已保留为正式功能（OLED 底部显示云连接状态）
