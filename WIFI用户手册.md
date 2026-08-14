|     | ATK-MB026 | 模块用户手册  |     |
| --- | --------- | ------- | --- |

User
|     | WIFI & BLE 模块  |     |     |
| --- | -------------- | --- | --- |
Manual
用户手册
修订历史
| 版本    | 日期          |                  | 原因  |
| ----- | ----------- | ---------------- | --- |
| V1.0  | 2024/11/20  | 第一次发布            |     |
| V1.1  | 2025/11/03  | 修正特性参数值以及引脚丝印描述  |     |
|       |             |                  |     |
|       |             |                  |     |

ATK-MB026 模块用户手册
WIFI & BLE模块
目 录
1，特性参数 .................................................................................................................. 1
2，使用说明 .................................................................................................................. 3
2.1 模块引脚说明 .................................................................................................................... 3
2.2 ATK-MWC3介绍 ............................................................................................................... 3
2.3 AT指令简介 ....................................................................................................................... 4
2.3.1 功能说明 ................................................................................................................. 5
2.3.2 AT指令说明 ............................................................................................................ 5
2.3.3 基础AT指令 .......................................................................................................... 6
2.3.4 WIFI功能AT指令 ................................................................................................. 7
2.3.5 TCP/IP相关AT指令 ............................................................................................ 17
2.3.6 Bluetooth® Low Energy AT指令 .......................................................................... 26
2.3.7 常用AT指令实例 ................................................................................................ 35
2.4 连接旧版原子云服务器 .................................................................................................. 38
2.4.1 创建设备 ............................................................................................................... 38
2.4.2 连接原子云 ........................................................................................................... 40
2.5 连接新版原子云服务器 .................................................................................................. 43
2.5.1 创建设备 ............................................................................................................... 43
2.5.2 连接新版原子云 ................................................................................................... 44
2.6 配置Bluetooth LE ........................................................................................................... 46
2.6.1 Bluetooth LE协议架构 ......................................................................................... 46
2.6.2 Bluetooth LE角色划分 ......................................................................................... 47
2.6.3 Bluetooth LE服务端配置 ..................................................................................... 47
2.6.4 Bluetooth LE客户端配置 ..................................................................................... 49
2.6.5 Bluetooth LE手机APP配置 ................................................................................ 51
2.7 一键配网 .......................................................................................................................... 54
2.7.1 ESP-TOUCH .......................................................................................................... 54
2.8 固件烧写 .......................................................................................................................... 56
3，结构尺寸 ................................................................................................................ 59
4，其他 ........................................................................................................................ 60
用户手册 www.alientek.com
1

ATK-MB026 模块用户手册

WIFI & BLE模块
1，特性参数
| ATK-MB026 | 模块是正点原子推出的一款高性能 | WIFI & BLE（无线-蓝牙）模块， |
| --------- | --------------- | -------------------- |
ATK-MB026模块板载了正点原子公司自主研发的ATK-MWC3模块，该模块通过FCC、CE、
SRRC、RoHS认证，可直接用于出口欧美地区的产品。
ATK-MB026模块采用串口（TTL）与MCU（或其他串口设备）通讯，内嵌Wi-Fi子系
统，遵循IEEE 802.11 b/g/n Wi-Fi MAC协议栈，同时还兼具低功耗蓝牙子系统，支持Bluetooth
5和Bluetooth mesh，能够实现串口与WIFI以及蓝牙之间的转换，在WIFI功能运作时能同
时使用蓝牙功能。通过ATK-MB026模块，传统的串口设备只需要简单的串口配置，即可通
过网络（WIFI）传输自己的数据。
ATK-MB026模块支持TTL串口，兼容5V单片机系统，可以很方便得与其他产品进行
连接。同时，该模块支持还多种工作模式：Station模式、SoftAP模式、SoftAP + Station模
式和混杂模式，从而能够快速地构建串口-WIFI的数据传输方案，方便其他设备使用互联网
传输数据。
ATK-MB026模块的各项基本参数，如下表所示：
| 项目      |                                           | 说明  |
| ------- | ----------------------------------------- | --- |
| WIFI协议  | 支持IEEE 802.11b、IEEE 802.11g、IEEE 802.11n  |     |
IEEE 802.11b：最高可达11Mbps
| WIFI传输速率  | IEEE 802.11g：最高可达54Mbps  |     |
| --------- | ------------------------ | --- |
IEEE 802.11b：最高可达HT40（MCS7）
| WIFI频率范围  | 2.412GHz~2.484GHz                               |     |
| --------- | ----------------------------------------------- | --- |
| WIFI发射功率  | 18.5dBm~20.5dBm                                 |     |
| 蓝牙LE      | 低功耗蓝牙(Bluetooth LE)：Bluetooth 5、Bluetooth mesh  |     |
| 蓝牙传输速率    | 支持125Kbps、500Kbps、1Mbps、2Mbps                   |     |
| 蓝牙频率范围    | 2.402GHz~2.480GHz                               |     |
| 蓝牙发射功率    | -24.00dBm~20.00dBm（各种传输速率下）                     |     |
| 通信接口      | TTL电平                                           |     |
| 天线        | 板载PCB天线                                         |     |
| 工作温度      | -40℃~85℃                                        |     |
| 工作湿度      | 10%RH~90%RH                                     |     |
| 外形尺寸      | 32.50mm*19.00mm                                 |     |
表1.1 ATK-MB026模块基本参数
ATK-MB026模块的功能特性，如下表所示：
| 项目        |                                             | 说明  |
| --------- | ------------------------------------------- | --- |
| WIFI工作模式  | Station模式、SoftAP模式、SoftAP + Station模式和混杂模式  |     |
WPA2-PSK/WPA3-PSK、WPA2-Enterprise/WPA3-Enterprise、链路层加密
无线安全
（BLE）
支持广播扩展、多广播、同时广播和扫描、多连接、自适应跳频和信道选择
低功耗蓝牙链路控制器
等
| 用户配置   | AT指令集、Web页面、Android、iOS终端、Smart Link智能配置APP  |     |
| ------ | -------------------------------------------- | --- |
| 串口波特率  | 110bps~4608000bps，默认115200bps                |     |
用户手册                                                                    www.alientek.com

1

ATK-MB026 模块用户手册
WIFI & BLE模块
TCP客户端连接数量 5个
固件升级 本地串口、OTA远程升级
表1.2 ATK-MB026模块功能特性
用户手册 www.alientek.com
2

ATK-MB026 模块用户手册

WIFI & BLE模块
2，使用说明
2.1  模块引脚说明
ATK-MB026模块非常小巧（32.50mm*19.00mm），模块通过6个2.54mm间距的排针与
外部相连接，方便用户安装到自己的设备里，模块外观，如下图所示：

图2.1.1 ATK-MB026模块实物图
ATK-MB026模块的各个引脚的详细描述，如下表所示：
| 序号  | 名称         |     | 说明  |
| --- | ---------- | --- | --- |
| 1   | VCC  5V电源  |     |     |
| 2   | GND  电源地   |     |     |
模块串口发送引脚（TTL电平，不能直接接RS232电平！），可接单片机的
| 3   | TXD  |     |     |
| --- | ---- | --- | --- |
RXD
模块串口接收引脚（TTL电平，不能直接接RS232电平！），可接单片机的
| 4   | RXD  |     |     |
| --- | ---- | --- | --- |
TXD
| 5   | RST  复位（低电平有效）                            |     |     |
| --- | ----------------------------------------- | --- | --- |
| 6   | IO_9  用于进入固件烧写模式，低电平：固件烧写模式；高电平：运行模式（默认）  |     |     |
表2.1.1 ATK-MB026模块引脚说明
2.2 ATK-MWC3 介绍
| ATK- MWC3 | 模组是ATK-MB026 | 模块的核心部件，ATK-MB026模块是正点原子团队 |     |
| --------- | ------------ | -------------------------- | --- |
自主研发的高性能WIFI & BLE模块，通过FCC、CE、SRRC、RoHS认证，可直接用于出
| 口。模块内嵌 | TCP/IP 协议栈，可以实现串口、WIFI |     | 以及蓝牙之间的数据转换传输。ATK-  |
| ------ | ---------------------- | --- | ------------------- |
MWC3模组的尺寸图，如下图所示：
用户手册                                                                    www.alientek.com

3

ATK-MB026 模块用户手册

WIFI & BLE模块

图2.2.1 ATK-MWC3模组实物图
ATK-MWC3模组的各个引脚的详细描述，如下表所示：
| 序号  | 名称                              | 说明  |
| --- | ------------------------------- | --- |
| 1   | IO0  GPIO0、ADC1_CH0、XTAL_32K_P  |     |
| 2   | IO1  GPIO1、ADC1_CH1、XTAL_32K_N  |     |
高电平：芯片使能；
| 3   | EN  低电平：芯片关闭；  |     |
| --- | -------------- | --- |
注意：不能让该管脚浮空。
| 4   | IO2  GPIO2、ADC1_CH2、 FSPIQ       |     |
| --- | -------------------------------- | --- |
| 5   | IO3  GPIO3、ADC1_CH3              |     |
| 6   | IO4  GPIO4、ADC1_CH4、FSPIHD、MTMS  |     |
| 7   | IO5  GPIO5、ADC2_CH0、FSPIWP、MTDI  |     |
建议3.3V/500mA供电
| 8     | VCC                    |     |
| ----- | ---------------------- | --- |
| 9~11  | NC  未连接                |     |
| 12    | IO6  FSPICLK、MTCK      |     |
| 13    | IO7  GPIO7、FSPID、MTDO  |     |
未连接
| 14  | NC          |     |
| --- | ----------- | --- |
| 15  | GND  接地     |     |
| 16  | IO8  GPIO8  |     |
GPIO10、FSPICS0
当eFuse位EFUSE_JTAG_SEL_ENABLE的值为0时，JTAG信号无法使用。
| 17  | IO10  |     |
| --- | ----- | --- |
如果IO10为0，JTAG信号来自芯片引脚；如果IO10为1，则无法使用JTAG
信号
| 18  | IO9  GPIO9           |     |
| --- | -------------------- | --- |
| 19  | IO18  GPIO18、USB_D-  |     |
| 20  | IO19  GPIO19、USB_D+  |     |
| 21  | RX0  GPIO20、U0RXD    |     |
GPIO21、U0TXD
| 22  | TX0  |     |
| --- | ---- | --- |
表2.2.1 ATK-MWC3模块引脚说明
指令简介
2.3 AT
| ATK-MB026 | 模块可以使用乐鑫官方提供的 | SDK 进行二次开发，也可以使用出厂提供 |
| --------- | ------------- | -------------------- |
的固件，直接使用AT指令配置模块进行使用。在本文档中，仅介绍在使用出厂提供的固件
用户手册                                                                    www.alientek.com

4

|     |     |     |     |     | ATK-MB026 |     | 模块用户手册 |     |
| --- | --- | --- | --- | --- | --------- | --- | ------ | --- |

WIFI & BLE模块
的情况下，使用AT指令配置和使用ATK-MB026模块。如有需要，用户自行可使用乐鑫官
| 方 提 供 | 的 SDK | 进   | 行 二 次 | 开 发 ， 有 | 关 乐 鑫 官 | 方 SDK | 的   | 介 绍 ， 请 点 击 |
| ----- | ----- | --- | ----- | ------- | ------- | ----- | --- | ----------- |
https://www.espressif.com.cn/zh-hans/support/download/sdks-demos?keys=&field_type_tid%5B
%5D=785获取相关资料。
| ATK-MB026模块出厂默认为AT |     |     |     | 指令状态，可通过UART与模块进行通讯，UART通 |     |     |     |     |
| ------------------ | --- | --- | --- | ------------------------- | --- | --- | --- | --- |
讯的默认配置参数，如下表所示：
| 参数   |     |            |     |     | 参数值  |     |     |     |
| ---- | --- | ---------- | --- | --- | ---- | --- | --- | --- |
| 波特率  |     | 115200bps  |     |     |      |     |     |     |
| 数据位  |     | 8          |     |     |      |     |     |     |
| 停止位  |     | 1          |     |     |      |     |     |     |
| 校验位  |     | 无          |     |     |      |     |     |     |
表2.3.1 ATK-MB026模块默认UART通讯配置参数
| 在本节中将介绍 |     | ATK-MB026 |     | 模块常用的 | AT 指令，更详细的 |     | AT  | 指令介绍请参考 |
| ------- | --- | --------- | --- | ----- | ---------- | --- | --- | ------- |
《ESP_AT指令集V2.1.0》。
2.3.1 功能说明
ATK-MB026模块支持三种工作模式，分别为：Station、SoftAP、Station+SoftAP。
1.  Station模式
| 在此模式下，ATK-MB026 |     |     |     | 模块可连接其他设备提供的无线网络，例如通过 |     |     |     | WIFI 连接 |
| --------------- | --- | --- | --- | --------------------- | --- | --- | --- | ------- |
至路由器，从而可以访问互联网，进而实现手机或电脑通过互联网实现对设备的远程控制。
2.  SoftAP模式
| AP 模式为默认的模式，在此模式下，ATK-MB026 |     |     |     |     |     | 模块将作为热点供其他设备连接， |     |     |
| --------------------------- | --- | --- | --- | --- | --- | --------------- | --- | --- |
从而让手机或电脑直接与模块进行通讯，实现局域网的无线控制。
3.  Station+SoftAP模式
| 该模式为Station |     | 模式与SoftAP |     | 模式共存的一种模式，ATK-MB026 |     |     |     | 模块既能连接至其 |
| ----------- | --- | --------- | --- | ------------------- | --- | --- | --- | -------- |
他设备提供的无线网络，又能作为热点，供其他设备连接，以实现广域网与局域网的无缝切
换，方便操作使用。
| 除了上述的三种工作模式外，ATK-MB026 |     |     |     |     | 模块在进行UDP | 连接或作为 |     | TCP客户端连 |
| ---------------------- | --- | --- | --- | --- | -------- | ----- | --- | ------- |
接时，能够进入透传模式，进入透传模式后，ATK-MB026将会原封不动地把从TCP服务器
或其他UDP终端接收到的消息，通过UART发送至与之连接的设备。
2.3.2 AT指令说明
AT指令可以细分为四种类型，如下表所示：
| 类型    |               | 指令格式  |     |                              |     | 描述  |     |     |
| ----- | ------------- | ----- | --- | ---------------------------- | --- | --- | --- | --- |
| 测试指令  | AT+<CMD>=?    |       |     | 该命令用于查询设置指令的参数以及取值范围         |     |     |     |     |
| 查询指令  | AT+<CMD>?     |       |     | 该命令用于返回参数的当前值                |     |     |     |     |
| 设置指令  | AT+<CMD>=<…>  |       |     | 该命令用于设置用户自定义的参数值             |     |     |     |     |
| 执行指令  | AT+<CMD>      |       |     | 该命令用于执行受模块内部程序控制，且参数不可变的的功能  |     |     |     |     |
表2.3.2.1 AT指令分类
注意：
不是每条AT指令都具有以上四种指令格式的命令。
1.
2.  中括号（[ ]）内的参数为缺省值，不必填写或者可能不显示
3.  使用双引号表示字符串数据，例如：AT+CWJAP=”ALIENTEK”,”15902020353”。
4.  ATK-MB026模块的UART通讯波特率为115200bps。
用户手册                                                                    www.alientek.com

5

ATK-MB026 模块用户手册
WIFI & BLE模块
5. AT指令必须大写，且每条指令都需以回车换行符结尾“\r\n”。
2.3.3 基础AT指令
基础AT指令，如下表所示：
指令 描述
AT 测试AT启动
AT+RST 重启模块
AT+GMR 查看版本信息
ATE 开关回显功能
AT+RESTORE 恢复出厂设置
AT+UART UART配置
表2.3.3.1 基础AT指令
1. AT——测试AT启动
执行指令 AT
响应 OK
参数说明 -
表2.3.3.2 AT——测试AT启动
2. AT+RST——重启模块
执行指令 AT+RST
响应 OK
参数说明 -
表2.3.3.3 AT+RST——重启模块
3. AT+GMR——查询版本信息
执行指令 AT+GMR
<AT version info>
<SDK version info>
响应 <compile time>
OK
⚫ <AT version info>：AT版本信息
参数说明 ⚫ <SDK version info>：SDK版本信息
⚫ <compile time>：固件编译生成时间
表2.3.3.4 AT+GMR——查询版本信息
4. ATE——开关回显功能
执行指令 ATE
响应 OK
⚫ ATE0：关闭回显功能
参数说明
⚫ ATE1：开启回显功能
表2.3.3.5 ATE——开关回显功能
5. AT+RESTORE——恢复出厂设置
执行指令 AT+RESTORE
响应 OK
恢复出厂设置后，将所有保存的参数恢复到出厂的默认参数值。
说明
恢复出厂设置会重启模块
用户手册 www.alientek.com
6

ATK-MB026 模块用户手册
WIFI & BLE模块
表2.3.3.6 ATE——开关回显功能
6. AT+UART——UART配置
查询指令 设置指令
AT+UART? AT+UART=<baudrate>,<databits>,<stopbits>,
指令
<parity>,<flow control>
+UART:<baudrate>,<databits>,<stopbits>,<par OK
响应 ity>,<flow control>
OK
⚫ <baudrate>：UART波特率
⚫ <databits>：数据位
 5：5bit数据位
 6：6bit数据位
 7：7bit数据位
 8：8bit数据位
⚫ <stopbits>：停止位
 1：1bit停止位
 2：1.5bit停止位
参数说明  3：2bit停止位
⚫ <parity>：校验位
 0：None
 1：Odd
 2：Even
⚫ <flow control>：流控
 0：不使能流控
 1：使能RTS
 2：使能CTS
 3：同时使能RTS和CTS
查询返回的响应是UART实际参数值，与设 ⚫ 本设置将保存在Flash的用户区，重新上
置值有一定误差，是正常情况。 电后仍生效。
例如：设置UART波特率为115200bps时， ⚫ 使用流控需要硬件支持流控：
注意
查询实际波特率为115273bps。  MTCK为UART0 CTS
 MTDO为UART0 RTS
 波特率支持范围：110bps~115200*40bps
示例 - AT+UART=115200,8,1,0,0
表2.3.3.7 AT+UART——UART配置
2.3.4 WIFI功能AT指令
WIFI功能AT指令，如下表所示：
指令 描述
AT+CWMODE 设置WIFI模式（Station、SoftAP、Station+SoftAP）
AT+CWJAP 连接AP
AT+CWLAP 扫描附近的AP信息
AT+CWQAP 与AP断开连接
AT+CWSAP 设置AP模式的配置
用户手册 www.alientek.com
7

|     |     |     |     |     | ATK-MB026 |     | 模块用户手册 |
| --- | --- | --- | --- | --- | --------- | --- | ------ |

WIFI & BLE模块
| AT+CWLIF  |     |     | 获取已接入设备的信息  |     |     |     |     |
| --------- | --- | --- | ----------- | --- | --- | --- | --- |
设置DHCP
AT+CWDHCP
| AT+CWAUTOCONN  |     |     | 设置上电时是否自动连接AP   |     |     |     |     |
| -------------- | --- | --- | --------------- | --- | --- | --- | --- |
| AT+CIPSTAMAC   |     |     | 设置STA模式下的MAC地址  |     |     |     |     |
| AT+CIPAPMAC    |     |     | 设置AP模式下的MAC地址   |     |     |     |     |
| AT+CIPSTA      |     |     | 设置STA模式下的IP地址   |     |     |     |     |
设置AP模式下的IP地址
AT+CIPAP
| AT+CWSTARTSMART  |     |     | 开始SmartConfig  |     |     |     |     |
| ---------------- | --- | --- | -------------- | --- | --- | --- | --- |
| AT+CWSTOPSMART   |     |     | 停止SmartConfig  |     |     |     |     |
| AT+WPS           |     |     | 设置WPS功能        |     |     |     |     |
设置MDNS功能
AT+MDNS
| AT+CWHOSTNAME  |     |     | 设置主机名  |     |     |     |     |
| -------------- | --- | --- | ------ | --- | --- | --- | --- |
表2.3.4.1 WIFI功能AT指令
1.  AT+CWMODE——查询/设置Wi-Fi模式（Station、SoftAP、Station+SoftAP）
|     |     | 测试指令  |     |     | 查询指令  |     | 设置指令  |
| --- | --- | ----- | --- | --- | ----- | --- | ----- |
AT+CWMODE=<mode>[,<au
| 指令  |     | AT+CWMODE=?  |     |     | AT+CWMODE?  |     |     |
| --- | --- | ------------ | --- | --- | ----------- | --- | --- |
to_connect>]
|     | +CWMODE:<mode>取值列 |     |     | +CWMODE:<mode>  |     | OK  |     |
| --- | ----------------- | --- | --- | --------------- | --- | --- | --- |
| 响应  | 表                 |     |     | OK              |     |     |     |
OK
⚫ <mode>：
 0：无Wi-Fi模式，并且关闭Wi-Fi RF
 1：Station模式
 2：SoftAP模式
 3：Station模式+SoftAP模式
⚫ <auto_connect>：
参数说明  切换 ESP32-C3 设备的Wi-Fi模式时（例如，从 SoftAP 或无Wi-Fi 模式切换为Station
模式或SoftAP+Station模式），是否启用自动连接AP的功能，默认值：1。参数缺省时，使
用默认值，也就是能自动连接。
 0：禁用自动连接AP的功能
 1：启用自动连接AP的功能，若之前已经将自动连接AP的配置保存到flash中，则
ESP32-C3设备将自动连接AP

| 注意  | -   |     |     | -   |     | 本设置保存在Flash的系统区  |     |
| --- | --- | --- | --- | --- | --- | ---------------- | --- |
| 示例  | -   |     |     | -   |     | AT+CWMODE=3      |     |
表2.3.4.2 AT+CWMODE——设置WIFI模式（STA、AP、STA+AP）
2.  AT+CWJAP——连接AP
|     |            |     | 查询指令  |     |                                                 | 设置指令  |     |
| --- | ---------- | --- | ----- | --- | ----------------------------------------------- | ----- | --- |
|     | AT+CWJAP?  |     |       |     | AT+CWJAP=[<ssid>],[<pwd>][,<bssid>][,<pc        |       |     |
| 指令  |            |     |       |     | i_en>][,<reconn_interval>][,<listen_interval>][ |       |     |
,<scan_mode>][,<jap_timeout>][,<pmf>]
|     | +CWJAP:<ssid>,<bssid>,<channel>,<rssi>,<pc |     |     |     | WIFI CONNECTED  |     |     |
| --- | ------------------------------------------ | --- | --- | --- | --------------- | --- | --- |
响应
|     | i_en>,<reconn_interval>,<listen_interval>,<sca |     |     |     | WIFI GOT IP  |     |     |
| --- | ---------------------------------------------- | --- | --- | --- | ------------ | --- | --- |
用户手册                                                                    www.alientek.com

8

ATK-MB026 模块用户手册
WIFI & BLE模块
n_mode>,<pmf> OK
OK [WIFI GOT IPv6 LL]
[WIFI GOT IPv6 GL]
或
+CWJAP:<error code>
ERROR
⚫ <ssid>：目标AP的SSID
1.如果SSID和密码中有等特殊字符，需转义。
2.AT支持连接SSID为中文的AP，但是某些路由器或者热点的中文SSID不是
UTF-8编码格式。您可以先扫描SSID，然后使用扫描到的SSID进行连接。
⚫ <pwd>：密码最长63字节ASCII
⚫ <bssid>：目标AP的MAC地址，当多个AP有相同的SSID时，该参数不可省略
⚫ <channel>：信道号
⚫ <rssi>：信号强度
⚫ <pci_en>：PCI认证
⚫ 0：ESP32-C3 station可与任何一种加密方式的AP连接，包括OPEN和WEP
⚫ 1：ESP32-C3 station可与除OPEN和WEP之外的任何一种加密方式的AP连接
⚫ <reconn_interval>：Wi-Fi重连间隔，单位：秒，默认值：1，最大值：7200
⚫ 0：断开连接后，ESP32-C3 station不重连AP
⚫ [1,7200]：断开连接后，ESP32-C3 station每隔指定的时间与AP重连
⚫ <listen_interval>：监听AP beacon的间隔，单位为AP beacon间隔，默认值：3，范围：
[1,100]
参数说明
⚫ <scan_mode>：扫描模式
⚫ 0：快速扫描，找到目标AP后终止扫描，ESP32-C3 station与第一个扫描到的AP连接
⚫ 1：全信道扫描，所有信道都扫描后才终止扫描，ESP32-C3 station与扫描到的信号最强的
AP连接
⚫ <jap_timeout>：AT+CWJAP命令超时的最大值，单位：秒，默认值：15，范围：[3,600]
⚫ <pmf>：PMF（ProtectedManagement Frames，受保护的管理帧），默认值1
⚫ 0表示禁用PMF
⚫ bit 0：具有PMF功能，提示支持PMF，如果其他设备具有PMF功能，则ESP32-C3设备
将优先选择以PMF模式连接
⚫ bit 1：需要PMF，提示需要PMF，设备将不会关联不支持PMF功能的设备
⚫ <error code>：错误码，仅供参考
⚫ 1：连接超时
⚫ 2：密码错误
⚫ 3：无法找到目标AP
⚫ 4：连接失败
⚫ 其它值：发生未知错误
⚫ 回复OK代表IPv4网络已经准备就绪，而不代表IPv6网络准备就绪。当前ESP-AT以
IPv4网络为主，IPv6网络为辅。
注意 ⚫ WIFI GOT IPv6 LL代表已经获取到本地链路IPv6地址，这个地址是通过EUI-64本地
计算出来的，不需要路由器参与。由于并行时序，这个打印可能在OK之前，也可能
在OK之后。
用户手册 www.alientek.com
9

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ WIFI GOT IPv6 GL 代表已经获取到全局IPv6地址，该地址是由AP下发的前缀加上
内部计算出来的后缀进行组合而来的，需要路由器参与。由于并行时序，这个打印可
能在OK之前，也可能在OK之后；也可能由于AP不支持IPv6而不打印。
示例 - AT+CWJAP=”ALIENTEK”,”15902020353”
表2.3.4.3 AT+CWJAP——连接AP
3. AT+CWLAP——扫描当前可用的AP信息
设置指令 执行指令
AT+CWLAP=[<ssid>,<mac>,<channel>,<scan AT+CWLAP
指令
_type>,<scan_time_min>,<scan_time_max>]
+CWLAP:<ssid>,<mac>,<channel>,<scan_typ +CWLAP:(<ecn>,<ssid>,<rssi>,<mac>,<chann
e>,<scan_time_min>,<scan_time_max> el>,<freq_offset>,<freqcal_val>,<pairwise_cip
响应 OK her>,<group_cipher>,<bgn>,<wps>)
或 OK
ERROR
⚫ <ecn>：加密方式
0：OPEN
1：WEP
2：WPA_PSK
3：WPA2_PSK
4：WPA_WPA2_PSK
5：WPA2_ENTERPRISE
6：WPA3_PSK
7：WPA2_WPA3_PSK
8：WAPI_PSK
9：OWE
⚫ <ssid>：AP的SSID
⚫ <rssi>：信号强度
⚫ <mac>：AP的MAC地址
⚫ <channel>：信道号
参数说明
⚫ <scan_type>：Wi-Fi扫描类型，默认值为：0
0：主动扫描
1：被动扫描
⚫ <scan_time_min>：每个信道最短扫描时间，单位：毫秒，范围：[0,1500]，如果扫描类
型为被动扫描，本参数无效
⚫ <scan_time_max>：每个信道最长扫描时间，单位：毫秒，范围：[0,1500]，如果设为0，
固件采用参数默认值，主动扫描为120ms，被动扫描为360ms
⚫ <freqoffset>：AP频偏，单位kHz。此数值除以2.4，可得到ppm值
⚫ <freqcal_val>：频率校准值（保留项目）
⚫ <pairwise_cipher>：成对加密类型
0：None
1：WEP40
2：WEP104
3：TKIP
4：CCMP
用户手册 www.alientek.com
10

ATK-MB026 模块用户手册
WIFI & BLE模块
5：TKIP and CCMP
6：AES-CMAC-128
7：未知
⚫ <group_cipher>：组加密类型，与<pairwise_cipher>参数的枚举值相同
⚫ <bgn>：802.11 b/g/n，若bit设为1，则表示使能对应模式，若设为0，则表示禁用对应
模式
bit 0：是否使能802.11b模式
bit 1：是否使能802.11g模式
bit 2：是否使能802.11n模式
⚫ <wps>：wps flag
0：不支持WPS
1：支持WPS
AT+CWLAP=”ALIENTEK”,”e4:0e:ee:f2:11:1 -
4”,6
示例
或者查找指定SSID的AP：
AT+CWLAP=”ALIENTEK”
表2.3.4.4 AT+CWLAP——扫描当前可用的AP信息
4. AT+CWQAP——与AP断开连接
执行指令 AT+CWQAP
响应 OK
参数说明 -
表2.3.4.5 AT+CWQAP——与AP断开连接
5. AT+CWSAP——配置ESP32-C3 SoftAP参数
查询指令 设置指令
AT+CWSAP? AT+CWSAP=<ssid>,<pwd>,<chl>,<ecn>[,<m
指令
ax conn>][,<ssid hidden>]
+CWSAP:<ssid>,<pwd>,<channel>,<ecn>,<m OK
响应 ax conn>,<ssid hidden> 或
OK ERROR
⚫ <ssid>：字符串参数，接入点名称
⚫ <pwd>：字符串参数，密码，范围8~63字节ASCII
⚫ <channel>：信道号
⚫ <ecn>：加密方式，不支持WEP
 0：OPEN
 2：WPA_PSK
参数说明
 3：WPA2_PSK
 4：WPA_WPA2_PSK
⚫ [<max conn>]（选填参数）：允许连入ESP32-C3 SoftAP的最大station数量
⚫ [<ssid hidden>]（选填参数）：是否广播AP的SSID
 0：广播SSID（默认）
 1：不广播SSID
⚫ 本命令只有当AT+CWMODE=2或者AT+CWMODE=3时才有效
注意
⚫ 若AT+SYSSTORE=1，配置更改将保存在NVS分区
用户手册 www.alientek.com
11

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ 默认SSID因设备而异，因为它由设备的MAC地址组成。可以使用AT+CWSAP?查询
默认的SSID。
示例 - AT+CWSAP=”ATK-MB026”,”12345678”,6,4
表2.3.4.6 AT+CWSAP——配置ESP32-C3 SoftAP参数
6. AT+CWLIF——查询连接到ESP32-C3 SoftAP的station信息
执行指令 AT+CWLIF
+CWLIF:<ip addr>,<mac>
响应
OK
⚫ <ipaddr>：连接到ESP32-C3 SoftAP的station的IP地址
参数说明
⚫ <mac>：连接ESP32-C3 SoftAP的MAC地址
⚫ 本指令无法查询静态IP
注意
⚫ 本指令仅在ESP32-C3 SoftAP和接入的station DHCP均使能的情况下有效
表2.3.4.7 AT+CWLIF——查询连接到ESP32-C3 SoftAP的station信息
7. AT+CWDHCP——启用/禁用DHCP
查询指令 设置指令
指令 AT+CWDHCP? AT+CWDHCP=<operate>,<mode>
+CWDHCP:<state> OK
响应
OK
⚫ <state>DHCP的状态Bit0： ⚫ <operate>：
 0：禁用Station的DHCP  0：禁用
 1：启用Station的DHCP  1：启用
⚫ <state>DHCP的状态Bit1： ⚫ <mode>：
 0：禁用SoftAP的DHCP  Bit0：Station的DHCP
参数说明
 1：启用SoftAP的DHCP  Bit1：SoftAP的DHCP
⚫ <state>DHCP的状态Bit2：
 0：禁用Ethernet的DHCP
 1：启用Ethernet的DHCP
- ⚫ 若 AT+SYSSTORE=1，配置更改将保存到
NVS 分区
⚫ 本设置命令与设置静态 IPv4 地址的命令
会相互影响：AT+CIPSTA 和 AT+CIPAP
注意
⚫ 若启用 DHCP，则静态 IPv4 地址会被禁
用
⚫ 若启用静态 IPv4，则 DHCP 会被禁用
⚫ 最后一次配置会覆盖上一次配置
表2.3.4.8 AT+CWHDCP——启用/禁用DHCP
8. AT+CWAUTOCONN——设置上电时是否自动连接AP
查询指令 设置指令
指令 AT+CWAUTOCONN? AT+CWAUTOCONN=<enable>
+CWAUTOCONN:<enable> OK
响应
OK
参数说明 ⚫ <enable>：
用户手册 www.alientek.com
12

ATK-MB026 模块用户手册
WIFI & BLE模块
 0：上电不自动连接AP
 1：上电自动连接AP（默认）
注意 - 本设置保存到NVS区域
示例 AT+CWAUTOCONN=1
表2.3.4.9 AT+CWAUTOCONN——设置上电时是否自动连接AP
9. AT+CIPSTAMAC——查询/设置ESP32-C3 Station的MAC地址
查询指令 设置指令
指令 AT+CIPSTAMAC? AT+CIPSTAMAC=<mac>
+CIPSTAMAC:<mac> OK
响应
OK
参数说明 ⚫ <mac>：字符串参数，表示ESP32-C3 Station的MAC地址
- ⚫ 若AT+SYSSTORE=1，配置更改将保存到
NVS分区
⚫ ESP32-C3 Station的MAC地址与
ESP32-C3 SoftAP不同，不要为二者设置
注意 同样的MAC地址
⚫ MAC地址的Bit 0不能为1，例如，MAC
地址可以是“1a:…”，但不可以是“15:…”
⚫ FF:FF:FF:FF:FF:FF和00:00:00:00:00:00是
无效地址，不能设置
示例 AT+CIPSTAMAC=”1a:fe:35:98:d3:7b”
表2.3.4.10 AT+CIPSTAMAC——查询/设置ESP32-C3 Station的MAC地址
10. AT+CIPAPMAC——查询/设置ESP32-C3 SoftAP的MAC地址
查询指令 设置指令
指令 AT+CIPAPMAC? AT+CIPAPMAC=<mac>
+CIPAPMAC:<mac> OK
响应
OK
参数说明 ⚫ <mac>：字符串参数，表示ESP32-C3 SoftAP的MAC地址
- ⚫ 若AT+SYSSTORE=1，配置更改将保存到
NVS分区
⚫ ESP32-C3 SoftAP的MAC地址与
ESP32-C3 Station不同，不要为二者设置
注意 同样的MAC地址
⚫ MAC地址的Bit 0不能为1，例如，MAC
地址可以是“18:…”，但不可以是“15:…”
⚫ FF:FF:FF:FF:FF:FF和00:00:00:00:00:00是
无效地址，不能设置
示例 AT+CIPAPMAC=”18:fe:36:97:d5:7b”
表2.3.4.11 AT+CIPAPMAC——查询/设置ESP32-C3 SoftAP的MAC地址
11. AT+CIPSTA——查询/设置ESP32-C3 Station的IP地址
查询指令 设置指令
指令 AT+CIPSTA? AT+CIPSTA=<ip>[,<gateway>,<netmask>]
+CIPSTA:ip:<"ip"> OK
响应
+CIPSTA:gateway:<"gateway">
用户手册 www.alientek.com
13

ATK-MB026 模块用户手册
WIFI & BLE模块
+CIPSTA:netmask:<"netmask">
+CIPSTA:ip6ll:<"ipv6 addr">
+CIPSTA:ip6gl:<"ipv6 addr">
OK
⚫ <ip>：字符串参数，表示ESP32-C3 station的IPv4地址
⚫ [<gateway>]：网关
参数说明
⚫ [<netmask>]：子网掩码
⚫ [<ipv6 addr>]：ESP32-C3 station的IPv6地址
使用查询命令时，只有在ESP32-C3 station连 ⚫ 若AT+SYSSTORE=1，配置更改将保存到
接上AP或者配置过静态IP地址后，才能查 NVS分区
询到它的IP地址。 ⚫ 本设置命令与设置DHCP的命令相互影
注意 响，如AT+CWDHCP：
 若启用静态IPv4地址，则禁用DHCP
 若启用DHCP，则禁用静态IPv4地址
 最后一次配置会覆盖上一次配置
- AT+CIPSTA="192.168.6.100","192.168.6.1","
示例
255.255.255.0"
表2.3.4.12 AT+CIPSTA——查询/设置ESP32-C3 Station的IP地址
12. AT+CIPAP——查询/设置ESP32-C3 SoftAP的IP地址
查询指令 设置指令
指令 AT+CIPAP? AT+CIPAP=<ip>[,<gateway>,<netmask>]
+CIPAP:ip:<"ip"> OK
+CIPAP:gateway:<"gateway">
响应 +CIPAP:netmask:<"netmask">
+CIPAP:ip6ll:<"ipv6 addr">
OK
⚫ <ip>：字符串参数，表示ESP32-C3 SoftAP的IPv4地址
⚫ [<gateway>]：网关
参数说明
⚫ [<netmask>]：子网掩码
⚫ [<ipv6 addr>]：ESP32-C3 SoftAP的IPv6地址
⚫ 本设置命令仅适用于IPv4网络，不适用
IPv6网络
⚫ 若AT+SYSSTORE=1，配置更改将保存到
NVS分区
注意 ⚫ 本设置命令与设置DHCP的命令相互影
响，如AT+CWDHCP：
 若启用静态IPv4地址，则禁用DHCP
 若启用DHCP，则禁用静态IPv4地址
 最后一次配置会覆盖上一次配置
- AT+CIPAP="192.168.5.1","192.168.5.1","255.
示例
255.255.0"
表2.3.4.13 AT+CIPAP——查询/设置ESP32-C3 SoftAP的IP地址
13. AT+CWSTARTSMART——开始SmartConfig
执行指令 设置指令
用户手册 www.alientek.com
14

ATK-MB026 模块用户手册
WIFI & BLE模块
AT+CWSTARTSMART AT+CWSTARTSMART=<type>[,<auth
指令
floor>][,<"esptouch v2 key">]
响应 OK
⚫ <type>：
 1：ESP-TOUCH
 2：AirKiss
 3：ESP-TOUCH+AirKiss
 4：ESP-TOUCH v2
⚫ <auth floor>：Wi-Fi认证模式阈值，ESP-AT不会连接到authmode低于此阈值的AP
 0：OPEN（默认）
 1：WEP
参数说明
 2：WPA_PSK
 3：WPA2_PSK
 4：WPA_WPA2_PSK
 5：WPA2_ENTERPRISE
 6：WPA3_PSK
 7：WPA2_WPA3_PSK
⚫ <”esptouch v2 key”>：ESP-TOUCH v2的解密秘钥，用于解密Wi-Fi密码和自定义数据。
长度应为16字节。
⚫ 用户可以参考《ESP-TOUCH用户指南》来了解SmartConfig的详细介绍
⚫ SmartConfig仅支持在ESP32-C3 Station模式下调用；
⚫ 消息Smart get Wi-Fi info表示SmartConfig成功获取到AP信息，之后ESP32-C3尝试连
接AP；
⚫ 消息+SCRD:<length>,<rvd data>表示ESP-Touch v2成功获取到自定义数据；
注意
⚫ 消息Smartconfig connected Wi-Fi表示成功连接到AP；
⚫ 因为ESP32-C3设备需要将SmartConfig配网结果同步给手机端，所以建议在消息
Smartconfig connected Wi-Fi输出后延迟超过6秒再调用AT+CWSTOPSMART；
⚫ 可调用AT+CWSTOPSMART停止SmartConfig，然后再执行其他命令。注意，在
SmartConfig过程中请勿执行其他命令。
- AT+CWMODE=1
示例
AT+CWSTARTSMART
表2.3.4.14 AT+CWSTARTSMART——开始SmartConfig
14. AT+CWSTOPSMART——停止SmartConfig
执行指令 AT+CWSTOPSMART
响应 OK
参数说明 -
无论SmartConfig成功与否，都请调用AT+CWSTOPSMART释放快连占用的
注意
内存
AT+CWMODE=1
示例 AT+CWSTARTSMART
AT+CWSTOPSMART
表2.3.4.15AT+CWSTOPSMART——停止SmartConfig
15. AT+WPS——设置WPS功能
设置指令 AT+WPS=<enable>[,<auth floor>]
用户手册 www.alientek.com
15

ATK-MB026 模块用户手册
WIFI & BLE模块
响应 OK
⚫ <enable>：
 1：开启PBC类型的WPS
 0：关闭PBC类型的WPS
⚫ <auth floor>:Wi-Fi认证模式阈值，ESP-AT不会连接到authmode低于此阈
值的AP
 0：OPEN（默认）
 1：WEP
参数说明
 2：WPA_PSK
 3：WPA2_PSK
 4：WPA_WPA2_PSK
 5：WPA2_ENTERPRISE
 6：WPA3_PSK
 7：WPA2_WPA3_PSK
⚫ WPS功能必须在 ESP32-C3 Station 模式下再能开启
注意
⚫ WPS功能不支持WEP加密方式
AT+CWMODE=1
示例
AT+WPS=1
表2.3.4.16 AT+WPS——设置WPS功能
16. AT+MDNS——设置MDNS功能
AT+MDNS=<enable>[,<"hostname">,<"service_type">,<port>]
设置指令
[,<"instance">][,<"proto">][,<txt_number>][,<"key">,<"value">][...]
OK
响应 或
ERROR
⚫ <enable>：
 1：开启mDNS功能，后续参数需要填写
 0：关闭mDNS功能，后续参数无需填写
⚫ <”hostname”>：mDNS主机名称。
⚫ <”service_type”>：mDNS服务类型。
⚫ <port>：mDNS服务端口。
参数说明
⚫ <”instance”>：mDNS实例名称。默认值：<"hostname">。
⚫ <”proto”>：mDNS服务协议。建议值：_tcp或_udp，默认值：_tcp。
⚫ <txt_number>：mDNS TXT记录的数量。范围：[1,10]。
⚫ <”key”>：TXT记录的键。
⚫ <”value”>：TXT记录的值。
⚫ […]：根据<txt_number>继续填写TXT记录的键值对。
⚫ MDNS主机名和MDNS服务器名不能包含特殊字符，或设置为协议名（如：
注意
http）
开启mDNS功能：主机名为"espressif"，服务类型为"_iot"，端口为8080
示例 AT+MDNS=1,"espressif","_iot",8080
关闭mDNS功能：AT+MDNS=0
表2.3.4.17 AT+MDNS——设置MDNS功能
用户手册 www.alientek.com
16

ATK-MB026 模块用户手册

WIFI & BLE模块
17. AT+CWHOSTNAME——查询/设置ESP32-C3 Station主机名
|     | 查询指令  | 设置指令  |
| --- | ----- | ----- |
指令
AT+CWHOSTNAME?  AT+CWHOSTNAME=<hostname>
+CWHOSTNAME:<hostname>  OK
响应  OK  若未使能Station模式，则返回
ERROR
参数说明  ⚫ <hostname>：ESP32-C3 Station的主机名称，最大长度：32 字节
⚫ 本设置不保存到Flash，重启后将恢复默认
-
值
注意  ⚫ STA模式的默认主机名为“ATK_”+STA
模式下的MAC地址的低3字节，例如，
“+CWHOSTNAME:ATK_98D37B”
-  AT+CWMODE=3
示例
AT+CWHOSTNAME=”ALIENTEK”
表2.3.4.18 AT+CWHOSTNAME——查询/设置ESP32-C3 Station主机名
2.3.5 TCP/IP相关AT指令
TCP/IP相关AT指令，如下表所示：
| 指令  | 描述  |     |
| --- | --- | --- |
查询网络连接信息，官方弃用，但指令的基本功能还能运行，这里
AT+CIPSTATUS(官方弃用)
仅做了解
| AT+CIPDOMAIN   | 域名解析功能               |     |
| -------------- | -------------------- | --- |
| AT+CIPSTART    | 建立TCP连接、UDP传输或SSL连接  |     |
| AT+CIPSSLSIZE  | 设置SSL缓冲大小            |     |
| AT+CIPSEND     | 发送数据                 |     |
| AT+CIPCLOSE    | 关闭TCP连接、UDP传输或SSL连接  |     |
| AT+CIFSR       | 查询本地IP地址             |     |
| AT+CIPMUX      | 设置多连接模式              |     |
设置TCP服务器
AT+CIPSERVER
| AT+CIPMODE        | 设置透传模式         |     |
| ----------------- | -------------- | --- |
| AT+SAVETRANSLINK  | 保存透传连接到Flash   |     |
| AT+CIPSTO         | 设置TCP服务器的超时时间  |     |
| AT+PING           | Ping功能         |     |
| AT+ATKCLDSTA      | 连接旧版原子云服务器     |     |
| AT+ATKNEWCLDSTA   | 连接新版原子云服务器     |     |
| AT+ATKCLDCLS      | 关闭原子云服务器连接     |     |
表2.3.5.1 TCP/IP相关AT指令
1.  AT+CIPSTATUS——查询网络连接信息
| 执行指令  | AT+CIPSTATUS  |     |
| ----- | ------------- | --- |
STATUS:<stat>
响应
+CIPSTATUS:<link ID>,<type>,<remote IP>,<remote port>,<local port>,<tetype>
⚫ <stat>：ESP32-C3 station接口的连接状态
| 参数说明  |  0：ESP32-C3 station为未初始化状态  |     |
| ----- | ---------------------------- | --- |
 1：ESP32-C3 station为已初始化状态，但还未开始连接Wi-Fi
用户手册                                                                    www.alientek.com

17

ATK-MB026 模块用户手册
WIFI & BLE模块
 2：ESP32-C3 station已连接AP，获得IP地址
 3：ESP32-C3 station已建立TCP连接或UDP、SSL传输
 4：ESP32-C3 station设备所有的TCP、UDP和SSL均断开
 5：ESP32-C3 station开始过Wi-Fi连接，但尚未连上AP或从AP断开
⚫ <link ID>：网络连接ID（0~4），用于多连接的情况
⚫ <type>：“TCP”或“UDP”
⚫ <remote IP>：远端IP地址
⚫ <remote port>：远端端口值
⚫ <local port>：本地端口值
⚫ <tetype>：
 0：ESP32-C3设备作为客户端
 1：ESP32-C3设备作为服务器
表2.3.5.2 AT+CIPSTATUS——查询网络连接信息
2. AT+CIPDOMAIN——域名解析功能
执行指令 AT+CIPDOMAIN=<domain name>
+CIPDOMAIN:<IP address>
响应
OK
⚫ <domain name>：待解析的域名
⚫ <ip network>：首选IP网络。默认值：1
 1：首选解析为IPv4地址
 2：只解析为IPv4地址
参数说明  3：只解析为IPv6地址
⚫ <”IP address”>：解析后的IPv4地址或IPv6地址
⚫ <timeout>：命令超时。单位：毫秒。默认值：0。范围：[0,60000]。设置为
0时，命令的超时依赖于网络和lwIP协议栈；设置为非0时，命令会在指定
超时内返回，但会多消耗约5KB的堆空间。
AT+CWMODE=1
示例 AT+CWJAP=”SSID”,”password”
AT+CIPDOMAIN=”www.openedv.com”
表2.3.5.3 AT+CIPDOMAIN——域名解析功能
3. AT+CIPSTART——建立TCP连接、UDP传输或SSL连接（建立TCP传输）
TCP单连接（AT+CIPMUX=0） TCP多连接（AT+CIPMUX=1）
AT+CIPSTART=<"type">,<"remote host">,<r AT+CIPSTART=<link ID>,<"type">,<"remote
设置指令 emote port>[,<keep_alive>][,<"local IP">][,<t host">,<remote port>[,<keep_alive>][,<"loca
imeout>] l IP">][,<timeout>]
CONNECT <link ID>,CONNECT
响应
OK OK
⚫ <link ID>：网络连接ID（0~4），用于多连接的情况
⚫ <type>：连接类型，“TCP”、“UDP”或“SSL”
⚫ <”remote host”>：字符串参数，表示远端IPv4地址、IPv6地址，或域名。
参数说明 ⚫ <remote port>：远端端口号
⚫ <keep alive>：配置套接字的SO_KEEPALIVE选项（参考：SO_KEEPALIVE介绍），单
位：秒。范围：[0,7200]。
 0：关闭keep-alive功能
用户手册 www.alientek.com
18

ATK-MB026 模块用户手册
WIFI & BLE模块
 1~7200：开启keep-alive功能
⚫ 本命令中的<keep_alive>参数与AT+CIPTCPOPT命令中的<keep_alive>参数相同，最终值
由后设置的命令决定。如果运行本命令时不设置<keep_alive>参数，则默认使用上次配置
的值。
⚫ <”local IP”>：本地的IPv4地址或IPv6地址，用于绑定连接。使用多个网络接口或多个IP
地址时，此参数非常有用。默认为禁用。如需使用请先自行设置。可设置为空。
⚫ <timeout>：命令超时。单位：毫秒。默认值：0。范围：[0,60000]。设置为0时，命令的
超时依赖于网络和lwIP协议栈；设置为非0时，命令会在指定超时内返回，但会多消耗
约5KB的堆空间。
⚫ 如果您想基于IPv6网络建立一个TCP连接，请执行以下操作：
 确保AP支持IPv6
注意  设置AT+CIPV6=1
 通过AT+CWJAP命令获取到一个IPv6地址
 （可选）通过AT+CIPSTA?命令检查ESP32-C3是否获取到IPv6地址
AT+CIPSTART=”TCP”,”www.openedv.com”, -
示例 8080
AT+CIPSTART=”TCP”,”47.111.11.73”,8080
表2.3.5.4 AT+CIPSTART——建立TCP连接
4. AT+CIPSTART——建立UDP传输
单连接模式（AT+CIPMUX=0） 多连接模式（AT+CIPMUX=1）
AT+CIPSTART=<type>,<remote IP>,<remote AT+CIPSTART=<link ID>,<type>,<remote I
设置指令 port>[,(<UDP local port>),(<UDP mode>)] P>,<remote port>[,(<UDP local port>),(<UD
P mode>)]
OK
或
响应 ERROR
若连接已存在，则返回
ALREADY CONNECT
⚫ <link ID>：网络连接ID（0~4），用于多连接的情况
⚫ <type>：连接类型，“TCP”、“UDP”或“SSL”
⚫ <remote IP>：远端IP地址
⚫ <remote port>：远端端口号
参数说明 ⚫ [<UDP local port>]：UDP传输时，设置本地端口号
⚫ [<UDP mode>]：UDP传输的属性，若透传，则必须为0
 0：收到数据后，不更改远端目标（默认）
 1：收到数据后，改变以此远端目标
 2：收到数据后，改变远端目标
AT+CIPSTART=”UDP”,”192.168.101.110”,10 -
示例
00,1002,2
表2.3.5.5 AT+CIPSTART——建立UDP传输
5. AT+CIPSTART——建立SSL连接
设置指令 AT+CIPSTART=[<link ID>,]<type>,<remote IP>,<remote port>[,<TCP keep ali
用户手册 www.alientek.com
19

ATK-MB026 模块用户手册
WIFI & BLE模块
ve>]
OK
或
响应 ERROR
若连接已存在，则返回
ALREADY CONNECT
⚫ <link ID>：网络连接ID（0~4），用于多连接的情况
⚫ <type>：连接类型，“TCP”、“UDP”或“SSL”
⚫ <remote IP>：远端IP地址
参数说明 ⚫ <remote port>：远端端口号
⚫ [<TCP keep alive>]：TCP keep-alive侦测时间，默认关闭此功能
 0：关闭TCP keep-alive功能
 1~7200：侦测时间，单位为1S
⚫ ATK-MB026模块最多仅支持建立1个SSL连接
⚫ SSL连接不支持透传
注意
⚫ SSL需要占用较多空间，如果空间不足，会导致系统重启，用户可以使用指
令AT+CIPSSLSIZE=<size>增大SSL缓存
AT+CIPSSLSIZE=4096
示例
AT+CIPSTART=”SSL”,”www.openedv.com”,8443
表2.3.5.6 AT+CIPSTART——建立SSL连接
6. AT+CIPSEND——发送数据
设置指令 执行指令
⚫ 单连接时（AT+CIPMUX=0） AT+CIPSEND
 AT+CIPSEND=<length>
⚫ 多连接时（AT+CIPMUX=1）
 AT+CIPSNED=<link ID>,<length>
指令
⚫ 如果时UDP传输，可以设置远端IP和端
口
 AT+CIPSEND=[<link ID>,]<length>[,<r
emote host>,<remote port>]
发送指令长度的数据。 收到此命令后先换行返回“>”。
收到此命令后先换行返回“>”，然后开始接 进入Wi-Fi透传模式发送数据，ESP32-C3设
收串口数据，当数据长度满<length>时，发送 备每次最大接收8192字节，最大发送2920
数据，回到普通指令模式，等待下一条AT 字节，数据会立即被分为每2920字节一组的
指令。 块进行发送，否则会等待20毫秒或等待接收
如果未建立连接或连接被断开，返回： 到的数据大于等于2920字节再发送数据。当
响应 ERROR 输入单独一包“+++”时，返回普通AT指令
如果数据发送成功，返回： 模式。发送“+++”退出透传时，请至少间隔
SEND OK 1秒再发下一条AT指令。
本指令必须在开启透传模式及单连接下使
用。
若为UDP透传，指令“AT+CIPSEND”的参
数<mode>必须为0
参数说明 ⚫ <link ID>：网络连接ID（0~4），用于多 -
用户手册 www.alientek.com
20

ATK-MB026 模块用户手册
WIFI & BLE模块
连接的情况
⚫ <length>：发送数据的长度，最大长度为
8192字节
⚫ [<remote host>]：UDP传输可以指定对端
主机：IPv4地址、IPv6地址或者域名
⚫ [<remote port>]：UDP传输可以设置对端
端口号
表2.3.5.7 AT+CIPSEND——发送数据
7. AT+CIPCLOSE——关闭TCP/UDP/SSL连接
设置指令 执行指令
指令 AT+CIPCLOSE=<link ID> AT+CIPCLOSE
<link ID>,CLOSED CLOSED
响应
OK OK
<link ID>：需要关闭的连接ID号。当ID号 -
参数说明
为5时，关闭所有连接
表2.3.5.8 AT+CIPCLOSE——关闭TCP/UDP/SSL连接
8. AT+CIFSR——查询本地IP地址和MAC地址
执行指令 AT+CIFSR
+CIFSR:APIP,<"APIP">
+CIFSR:APIP6LL,<"APIP6LL">
+CIFSR:APIP6GL,<"APIP6GL">
+CIFSR:APMAC,<"APMAC">
+CIFSR:STAIP,<"STAIP">
+CIFSR:STAIP6LL,<"STAIP6LL">
响应 +CIFSR:STAIP6GL,<"STAIP6GL">
+CIFSR:STAMAC,<"STAMAC">
+CIFSR:ETHIP,<"ETHIP">
+CIFSR:ETHIP6LL,<"ETHIP6LL">
+CIFSR:ETHIP6GL,<"ETHIP6GL">
+CIFSR:ETHMAC,<"ETHMAC">
OK
⚫ <”APIP”>:ESP32-C3 SoftAP的IPv4地址
⚫ <”APIP6LL”>：ESP32-C3 SoftAP的IPv6本地链路地址
⚫ <”APIP6GL”>：ESP32-C3 SoftAP的IPv6全局地址
⚫ <”APMAC”>：ESP32-C3 SoftAP的MAC地址
⚫ <”STAIP”>：ESP32-C3 station的IPv4地址
⚫ <”STAIP6LL”>：ESP32-C3 station的IPv6本地链路地址
参数说明
⚫ <”STAIP6GL”>：ESP32-C3 station的IPv6全局地址
⚫ <”STAMAC”>：ESP32-C3 station的MAC地址
⚫ <”ETHIP”>：ESP32-C3 ethernet的IPv4地址
⚫ <”ETHIP6LL”>：ESP32-C3 ethernet的IPv6本地链路地址
⚫ <”ETHIP6GL”>：ESP32-C3 ethernet的IPv6全局地址
⚫ <”ETHMAC”>：ESP32-C3 ethernet的MAC地址
注意 ⚫ 通过“AT+CWMODE”指令进入对应模式后，才会显示当前模式下的IP地
用户手册 www.alientek.com
21

ATK-MB026 模块用户手册
WIFI & BLE模块
址和MAC地址信息
⚫ Station模式下的IP地址和MAC地址信息，需在Station模式下连接上AP
后，才可以查询
表2.3.5.9 AT+CIFSR——查询本地IP地址和MAC地址
9. AT+CIPMUX——启用/禁用多连接模式
查询指令 设置指令
指令 AT+CIPMUX? AT+CIPMUX=<mode>
+CIPMUX:<mode> OK
响应
OK
⚫ <mode>：
参数说明  0：单连接模式
 1：多连接模式
⚫ 默认为单连接模式
⚫ 只有当所有连接都断开时才可更改连接模式
注意 ⚫ 只有非透传模式（AT+CIPMODE=0），才能设置为多连接
⚫ 如果建立了TCP服务器，想切换为单连接，必须关闭服务器（AT+CIPSERVER=0）,服务
器仅支持多连接
示例 - AT+CIPMUX=1
表2.3.5.10 AT+CIPMUX——启用/禁用多连接模式
10. AT+CIPSERVER——建立/关闭TCP或SSL服务器
查询指令 设置指令
AT+CIPSERVER? AT+CIPSERVER=<mode>[,<param2>][,<"typ
指令
e">][,<CA enable>]
+CIPSERVER:<mode>[,<port>,<"type">][,<C OK
响应 A enable>]
OK
⚫ <mode>：
 0：普通传输模式
 1：透传模式，仅支持TCP单连接和UDP固定通信对端的情况
⚫ <port>：服务器端口
⚫ <param2>：参数<mode>不同，则此参数意义不同：
 如果<mode>是1，<param2>代表端口号。默认值：333
参数说明  如果<mode>是0，<param2>代表服务器是否关闭所有客户端。默认值：0
 0：关闭服务器并保留现有客户端连接
 1：关闭服务器并关闭所有连接
⚫ <”type”>：服务器类型：”TCP”，”TCPv6”，”SSL”，或“SSLv6”.默认值：”TCP”
⚫ <CA enable>：
 0：不使用CA认证
 1：使用CA认证
- ⚫ 多连接情况下 (AT+CIPMUX=1)，才能开
启服务器。
注意
⚫ 创建服务器后，自动建立服务器监听，最
多只允许创建一个服务器。
用户手册 www.alientek.com
22

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ 当有客户端接入，会自动占用一个连接
ID。
⚫ 如果您想基于 IPv6 网络创建一个
TCP/SSL 服务器，请首先设
置 AT+CIPV6=1，并获取一个IPv6地址。
⚫ 关闭服务器时参数<” type”>和
< CA enable >必须省略。
- ⚫ 建立 TCP 服务器：
 AT+CIPMUX=1
 AT+CIPSERVER=1,80
⚫ 建立 SSL 服务器
 AT+CIPMUX=1
示例  AT+CIPSERVER=1,443,"SSL",1
⚫ 基于 IPv6 网络，创建 SSL 服务器
 AT+CIPMUX=1
 AT+CIPSERVER=1,443,"SSLv6",0
⚫ 关闭服务器并且关闭所有连接
 AT+CIPSERVER=0,1
表2.3.5.11 AT+CIPSERVER——设置TCP服务器
11. AT+CIPMODE——设置透传模式
查询指令 设置指令
指令 AT+CIPMODE? AT+CIPMODE=<mode>
+CIPMODE:<mode> OK
响应
OK
⚫ <mode>：
参数说明  0：普通传输模式
 1：Wi-Fi透传模式，仅支持TCP单连接和UDP固定通信对端、SSL单连接的情况
- ⚫ 本设置不保存到Flash
注意 ⚫ 在ESP32-C3进入Wi-Fi透传接收模式后，
任何蓝牙功能将无法使用
示例 - AT+CIPMODE=1
表2.3.5.12 AT+CIPMODE——设置透传模式
12. AT+SAVETRANSLINK——设置开机Wi-Fi/Bluetooth LE透传模式信息
AT+SAVETRANSLINK=<mode>,<"remote host">,<remote port>[,<"type">,<keep_
设置指令
alive>]
响应 OK
⚫ <mode>：
 0：关闭ESP32-C3上电进入Wi-Fi透传模式
 1：开启ESP32-C3上电进入Wi-Fi透传模式
参数说明 ⚫ <remote host>：字符串参数，表示远端IP地址或域名，最长为64字节
⚫ <remote port>：远端端口号值
⚫ [<type>]（选填参数）：字符串参数，表示传输类型：TCP、SSL或SSLv6，缺
省默认为TCP
用户手册 www.alientek.com
23

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ [<keep alive>]（选填参数）：keep alive侦测，缺省默认关闭此功能
 0：关闭keep-alive功能
 1~7200：侦测时间，单位为秒
本设置将Wi-Fi开机透传模式信息保存在NVS区，若参数<mode>为1，下次上电
注意
自动进入透传模式。需重启生效。
AT+SAVETRANSLINK=1,"192.168.6.110",1002,"TCP"
AT+SAVETRANSLINK=1,"www.baidu.com",443,"SSL"
示例
AT+SAVETRANSLINK=1,"240e:3a1:2070:11c0:55ce:4e19:9649:b75",8080,"TCPv6"
AT+SAVETRANSLINK=1,"240e:3a1:2070:11c0:55ce:4e19:9649:b75",8080,"SSLv6
表2.3.5.13 AT+SAVETRANSLINK——设置开机进入TCP/SSL透传模式信息
13. AT+SAVETRANSLINK——设置开机Wi-Fi/Bluetooth LE透传模式信息
设置指令 AT+SAVETRANSLINK=<mode>,<remote IP>,<remote port>,<type>[,<UDP local port>]
响应 OK
⚫ <mode>：
 0：关闭ESP32-C3上电进入Wi-Fi透传模式
 1：开启ESP32-C3上电进入Wi-Fi透传模式
参数说明 ⚫ <remote host>：字符串参数，表示远端IP地址或域名，最长为64字节
⚫ <remote port>：远端端口号值
⚫ [<type>]（选填参数）：字符串参数，表示传输类型：UDP或UDPv6，默认为TCP
⚫ [<UDP local port>]：开机进入UDP传输时，使用本地端口
⚫ 本设置将Wi-Fi开机透传模式信息保存在NVS区，若参数<mode>为1，下次上电自
动进入透传模式。需重启生效。
⚫ 如果您想基于IPv6网络建立一个UDP传输，请执行以下操作：
注意  确保AP支持IPv6
 设置AT+CIPV6=1
 通过AT+CWJAP命令获取到一个IPv6地址
 （可选）通过AT+CIPSTA?命令检查ESP32-C3是否获取到IPv6地址
AT+SAVETRANSLINK=1,"192.168.6.110",1002,"UDP",1005
示例
AT+SAVETRANSLINK=1,"240e:3a1:2070:11c0:55ce:4e19:9649:b75",8081,"UDPv6",1005
表2.3.5.14 AT+SAVETRANSLINK——设置开机进入UDP透传模式信息
14. AT+SAVETRANSLINK——设置开机Wi-Fi/Bluetooth LE透传模式信息
AT+SAVETRANSLINK=<mode>,<role>,<tx_srv>,<tx_char>,<rx_srv>,<rx_char>,<pe
设置指令
er_addr>
响应 OK
⚫ mode>：
 0：关闭ESP32-C3上电进入BLE透传模式
 2：开启ESP32-C3上电进入BLE透传模式
⚫ <role>：
 1：client角色
参数说明
 2：server角色
⚫ <tx_srv>：tx服务序号
⚫ <tx_char>：tx服务特征序号
⚫ <rx_srv>：rx服务序号
⚫ <rx_char>：rx服务特征序号
用户手册 www.alientek.com
24

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ <peer_addr>：对方Bluetooth LE地址
本设置将Wi-Fi开机透传模式信息保存在NVS区，若参数<mode>为2，下次上电
注意
自动进入透传模式。需重启生效。
示例 AT+SAVETRANSLINK=2,2,1,7,1,5,"26:a2:11:22:33:88"
表2.3.5.15 AT+SAVETRANSLINK——设置开机进入BLE透传模式信息
15. AT+CIPSTO——查询/设置本地TCP/SSL服务器的超时时间
查询指令 设置指令
指令 AT+CIPSTO? AT+CIPSTO=<time>
+CIPSTO:<time> OK
响应
OK
参数说明 ⚫ <time>：TCP/SSL服务器的超时时间，取值范围0s~7200s
- ⚫ 当TCP/SSL客户端在<time>时间内未发生
数据通讯时，ESP32-C3服务器会断开此连
接。
⚫ 如果设置参数<time>为0，则连接永远不
注意 会超时，不建议这样设置。
⚫ 在设定的时间内，当客户端发起与服务器
的通信或者服务器发起与客户端的通信
时，计时器将重新计时。超时后，客户端
被关闭。
- AT+CIPMUX=1
示例 AT+CIPSERVER=1,1001
AT+CIPSTO=10
表2.3.5.16 AT+CIPSTO——设置TCP服务器的超时时间
16. AT+PING——Ping功能
设置指令 AT+PING=<””””host”>
+<time>
OK
或
响应
+PING:TIMEOUT (注：只有在域名解析失败或 PING 超时情况下，才会有这
个回复)
ERROR
⚫ <IP>：IP地址
参数说明
⚫ <time>：ping响应时间，单位：毫秒
⚫ 如果您想基于IPv6网络Ping对端主机，请执行以下操作：
 确保AP支持IPv6
 设置AT+CIPV6=1
注意  通过AT+CWJAP命令获取到一个IPv6地址
 （可选）通过AT+CIPSTA?命令检查ESP32-C3是否获取到IPv6地址
⚫ 如果远端主机是域名字符串，则ping将先通过DNS进行域名解析（优先解
析IPv4地址），再ping对端主机IP地址
AT+PING=”192.168.1.1”
示例
AT+PING=”www.openedv.com”
用户手册 www.alientek.com
25

ATK-MB026 模块用户手册
WIFI & BLE模块
表2.3.5.17 AT+PING——Ping功能
17. AT+ATKCLDSTA——连接到旧版原子云服务器
指令 AT+ATKCLDSTA=<id>,<password>
CLOUD CONNECTED
响应
OK
⚫ <id>：设备编号，固定20字节
参数说明
⚫ <password>：设备密码，固定8字节
表2.3.5.18 AT+ATKCLDSTA——连接到原子云服务器
18. AT+ATKNEWCLDSTA——连接到新版原子云服务器
指令 AT+ATKCLDSTA=<id>,<password>
CLOUD CONNECTED
响应
OK
⚫ <id>：设备编号，固定20字节
参数说明
⚫ <password>：设备密码，固定8字节
表2.3.5.19 AT+ATKMEWCLDSTA——连接到原子云服务器
19. AT+ATKCLDCLS——关闭原子云服务器连接
指令 AT+ATKCLDCLS
OK
响应
CLOUD DISCONNECT
表2.3.5.20 AT+ATKCLDCLS——关闭原子云服务器连接
2.3.6 Bluetooth® Low Energy AT指令
文档仅介绍常用的Bluetooth® Low Energy AT指令，如下表所示：
指令 描述
AT+BLEINIT 设置Bluetooth LE初始化
AT+BLEGATTSSRVCRE GATTS（Generic Attributes Server）创建Bluetooth LE服务
AT+BLEGATTSSRVSTART GATTS开启全部服务
AT+BLEADDR 查询Bluetooth LE设备的公共地址
AT+BLEADVPARAM 查询广播参数
AT+BLEADVDATA 设置Bluetooth LE广播数据
AT+BLESECPARAM 查询Bluetooth LE SMP加密参数
AT+BLEADVSTART 开始Bluetooth LE 广播
AT+BLEENC 发起Bluetooth LE加密请求
AT+BLESCAN 使能Bluetooth LE 扫描
AT+BLECONN 建立Bluetooth LE连接
AT+BLEGATTCPRIMSRV GATTC发现基本服务
AT+BLEGATTCCHAR GATTC发现服务特征
AT+BLESPPCFG 设置Bluetooth LE SPP参数
AT+BLESPP 进入Bluetooth LE SPP模式
表2.3.6.1 Bluetooth® Low Energy AT指令
1. AT+ BLEINIT——查询/设置Bluetooth LE初始化
查询指令 设置指令
用户手册 www.alientek.com
26

ATK-MB026 模块用户手册
WIFI & BLE模块
指令 AT+BLEINIT? AT+BLEINIT=<init>
+BLEINIT:<role> OK
响应
OK
⚫ <init>:
 0：注销Bluetooth LE
参数说明
 1：client角色
 2：server角色
- ⚫ 为获得更好的性能，建议在使用Bluetooth
LE功能前，先发送AT+CWMODE=0/1命
令禁用SoftAP。如您想了解更多细节，请
阅读RF共存文档。
⚫ 使用其它BluetoothLE命令之前，请先调
用本命令，初始化BluetoothLE角色。
⚫ Bluetooth LE角色初始化后，不能直接切
注意
换。如需切换角色，需要先调用AT+RST
命令重启系统，再重新初始化BluetoothLE
角色。
⚫ 建议在注销Bluetooth LE之前，停止正在
进行的广播、扫描并断开所有的连接。
⚫ 如果Bluetooth LE已初始化，则
AT+CIPMODE无法设置为1。
示例 - AT+BLEINIT=1
表2.3.6.2 AT+ BLEINIT——Bluetooth LE初始化
2. AT+ BLEGATTSSRVCRE——GATTS创建服务
执行指令 AT+BLEGATTSSRVCRE
响应 OK
⚫ 使用ESP32-C3作为Bluetooth LE server创建服务，需烧录带有GATTS配置
的mfg_nvs.bin文件到flash中。
⚫ Bluetooth LE server初始化后，请及时调用本命令创建服务；如果先建立
Bluetooth LE连接，则无法创建服务。
⚫ 如果Bluetooth LE client已初始化成功，可以使用此命令创建服务；也可以
使用其他一些相应的GATTS命令，例如启动和停止服务、设置服务特征值
和notification/indication，具体命令如下：
注意
 AT+BLEGATTSSRVCRE(建议在Bluetooth LE连接建立之前使用)
 AT+BLEGATTSSRVSTART(建议在Bluetooth LE连接建立之前使用)
 AT+BLEGATTSSRV
 AT+BLEGATTSCHAR
 AT+BLEGATTSNTFY
 AT+BLEGATTSIND
 AT+BLEGATTSSETATTR
AT+BLEINIT=2 （详细参数介绍请看上一小节）
示例
AT+BLEGATTSSRVCRE
表2.3.6.3 AT+ BLEGATTSSRVCRE——GATTS创建服务
3. AT+ BLEGATTSSRVSTART——GATTS开启服务
用户手册 www.alientek.com
27

ATK-MB026 模块用户手册
WIFI & BLE模块
执行指令 AT+BLEGATTSSRVSTART=<srv_index>
响应 OK
参数说明 <srv_index>：服务序号，从1开始递增
AT+BLEINIT=2 （详细参数介绍请看上一小节）
示例
AT+BLEGATTSSRVCRE
表2.3.6.4 AT+ BLEGATTSSRVSTART——GATTS开启服务
4. AT+ BLEADDR——查询/设置Bluetooth LE设备地址
查询指令 设置指令
指令 AT+BLEADDR? AT+BLEADDR=<addr_type>[,<random_addr>]
+BLEADDR:<BLE_public_addr> OK
响应
OK
⚫ <addr_type>:
 0：公共地址 (Public Address)
参数说明
 1：随机地址 (Random Address)
- ⚫ 静态地址(Static Address)应满足以下条件
 地址最高两位应为1
注意  随机地址部分至少有1位为0
 随机地址部分至少有1位为1
 设置的静态地址不会被保存在NVS区
- AT+BLEADDR=1,"f8:7f:24:87:1c:7b"
示例 AT+BLEADDR=1
AT+BLEADDR=0
表2.3.6.5 AT + BLEADDR——查询/设置Bluetooth LE设备地址
5. AT+ BLEADVPARAM——查询/设置Bluetooth LE广播参数
查询指令 设置指令
AT+BLEADVPARAM? AT+BLEADVPARAM=<adv_int_min>,<adv_i
nt_max>,<adv_type>,<own_addr_type>,<chann
指令 el_map>[,<adv_filter_policy>][,<peer_addr_typ
e>,<peer_addr>][,<primary_PHY>,<secondary_
PHY>]
+BLEADVPARAM:<adv_int_min>,<adv_int OK
_max>,<adv_type>,<own_addr_type>,<chann
el_map>,<adv_filter_policy>,<peer_addr_typ
响应
e>,<peer_addr>,<primary_PHY>,<secondary
_PHY>
OK
⚫ <adv_int_min>：最小广播间隔。参数范围：[0x0020,0x4000]。广播间隔等于该参数乘以
0.625毫秒，所以实际的最小广播间隔范围为[20,10240]毫秒。本参数值应小于等于
<adv_int_max>参数值。
参数说明 ⚫ <adv_int_max>：最大广播间隔。参数范围：[0x0020,0x4000]。广播间隔等于该参数乘以
0.625毫秒，所以实际的最大广播间隔范围为[20,10240]毫秒。本参数值应大于等于
<adv_int_min>参数值。
⚫ <adv_type>:
用户手册 www.alientek.com
28

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ 0：ADV_TYPE_IND
⚫ 1：ADV_TYPE_DIRECT_IND_HIGH
⚫ 2：ADV_TYPE_SCAN_IND
⚫ 3：ADV_TYPE_NONCONN_IND
⚫ 4：ADV_TYPE_DIRECT_IND_LOW
⚫ 5：ADV_TYPE_EXT_NOSCANNABLE_IND
⚫ 6：ADV_TYPE_EXT_CONNECTABLE_IND
⚫ 7：ADV_TYPE_EXT_SCANNABLE_IND
 当设置广播类型为0-4，则使用AT+BLEADVDATA命令设置广播参数最多只能设置
31字节，如果需要设置更长的广播参数，请调用AT+BLESCANRSPDATA命令来设置。
 当设置广播类型为5-7，则使用AT+BLEADVDATA命令设置广播参数最多只能设置
119字节。
⚫ <own_addr_type>：Bluetooth LE地址类型
⚫ 0：BLE_ADDR_TYPE_PUBLIC
⚫ 1：BLE_ADDR_TYPE_RANDOM
⚫ <channel_map>：广播信道
⚫ 1：ADV_CHNL_37
⚫ 2：ADV_CHNL_38
⚫ 4：ADV_CHNL_39
⚫ 7：ADV_CHNL_ALL
⚫ [<adv_filter_policy>]：广播过滤器规则
⚫ 0：ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY
⚫ 1：ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY
⚫ 2：ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST
⚫ 3：ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST
⚫ [<peer_addr_type>]：对方Bluetooth LE地址类型
⚫ 0：PUBLIC
⚫ 1：RANDOM
⚫ [<peer_addr>]：对方Bluetooth LE地址
⚫ [<primary_phy>]：广播primary PHY。默认值：1M PHY。
 1：1M PHY
 3：Coded PHY
⚫ [<secondary_phy>]：广播secondary PHY。默认值：1M PHY。
 1：1M PHY
 2：2M PHY
 3：Coded PHY
- ⚫ 如果从未设置过peer_addr,那么查询出来
的结果会是全零。
注意 ⚫ primary_phy和secondary_phy需要一起
设置，如果不设置，那么未设置的参数会使
用默认1M PHY。
- AT+BLEINIT=2
示例 AT+BLEADDR=1,"c2:34:45:78:66:89"
AT+BLEADVPARAM=50,50,0,1,4,0,1,"12:34:
用户手册 www.alientek.com
29

ATK-MB026 模块用户手册
WIFI & BLE模块
45:78:66:88"
表2.3.6.6 AT + BLEADVPARAM——查询/设置Bluetooth LE广播参数
6. AT+ BLEADVDATA——设置Bluetooth LE广播参数
设置指令 AT+BLEADVDATA=<adv_data>
响应 OK
<adv_data>：广播数据，为HEX字符串。例如，若想设置广播数据为“0x11 0x22
参数说明 0x33 0x44 0x55”，则命令为AT+BLEADVDATA="1122334455"。最大长度：
119字节。
⚫ 如果之前已经使用命令
AT+BLEADVDATAEX=<dev_name>,<uuid>,<manufacturer_data>,<include_pow
er>设置了广播数据，则会被本命令设置的广播数据覆盖。
⚫ 如果您想使用本命令修改设备名称，则建议在执行完该命令之后执行
AT+BLENAME命令将设备名称设置为同样的名称。
⚫ 在使用AT+BLEADVDATA命令之前，必须先通过AT+BLEADVPARAM命令
注意
设置广播参数。
⚫ 当调用AT+BLEADVPARAM命令设置广播类型为0-4，则使用
AT+BLEADVDATA命令设置广播数据最多只能设置31字节，如果需要设置
更长的广播数据，请调用AT+BLESCANRSPDATA命令来设置。
⚫ 当调用AT+BLEADVPARAM命令设置广播类型为5-7，则使用
AT+BLEADVDATA命令设置广播数据最多只能设置119字节。
AT+BLEINIT=2
示例
AT+BLEADVDATA="1122334455"
表2.3.6.7 AT+ BLEADVDATA——设置Bluetooth LE广播参数
7. AT+ BLESECPARAM——查询/设置Bluetooth LE加密参数
查询指令 设置指令
AT+BLESECPARAM? AT+BLESECPARAM=<auth_req>,<iocap>,<en
指令 c_key_size>,<init_key>,<rsp_key>[,<auth_optio
n>]
+BLESECPARAM:<auth_req>,<iocap>,<enc OK
_key_size>,<init_key>,<rsp_key>,<auth_opti
响应
on>
OK
⚫ <auth_req>：认证请求。
 0：NO_BOND
 1：BOND
 4：MITM
 8：SC_ONLY
 9：SC_BOND
参数说明
 12：SC_MITM
 13：SC_MITM_BOND
⚫ <iocap>：输入输出能力。
 0：DisplayOnly
 1：DisplayYesNo
 2：KeyboardOnly
用户手册 www.alientek.com
30

ATK-MB026 模块用户手册
WIFI & BLE模块
 3：NoInputNoOutput
 4：Keyboard display
⚫ <enc_key_size>：加密密钥长度。参数范围：[7,16]。单位：字节。
⚫ <init_key>：多个比特位组成的初始密钥。
⚫ <rsp_key>：多个比特位组成的响应密钥。
⚫ <auth_option>：安全认证选项：
 0：自动选择安全等级
 1：如果无法满足之前设定的安全等级，则会断开连接。
注意 - -
示例 - AT+BLESECPARAM=1,4,16,3,3,0
表2.3.6.8 AT + BLEADDR——查询/设置Bluetooth LE加密参数
8. AT+ BLEADVSTART——开始Bluetooth LE广播
执行指令 AT+BLEADVSTART
响应 OK
参数说明 -
⚫ 若未使用命令AT+BLEADVPARAM=<adv_parameter>设置广播参数，则使用默
认广播参数。
⚫ 若未使用命令AT+BLEADVDATA=<adv_data>设置广播数据，则发送全0数据
包。
⚫ 若之前已经使用命令AT+BLEADVDATA=<adv_data>设置过广播数据，则会被
注意
AT+BLEADVDATAEX=<dev_name>,<uuid>,<manufacturer_data>,<include_pow
er>设置的广播数据覆盖，相反，如果先使用AT+BLEADVDATAEX，则会被
AT+BLEADVDATA设置的广播数据覆盖。
⚫ 开启Bluetooth LE广播后，如果没有建立Bluetooth LE连接，那么将会一直保
持广播；如果建立了连接，则会自动结束广播。
AT+BLEINIT=2
示例
AT+BLEADVSTART
表2.3.6.9 AT+ BLEENC——开始Bluetooth LE广播
9. AT+ BLEENC——发起Bluetooth LE加密请求
设置指令 AT+BLEENC=<conn_index>,<sec_act>
响应 OK
⚫ <conn_index>：Bluetooth LE 连接号，范围：[0,2]。
⚫ <sec_act>：
 0： SEC_NONE
参数说明
 1： SEC_ENCRYPT
 2： SEC_ENCRYPT_NO_MITM
 3： SEC_ENCRYPT_MITM
注意 使用本命令前，请先设置安全参数、建立与对方设备的连接。
AT+RESTORE
AT+BLEINIT=2
AT+BLEGATTSSRVCRE
示例
AT+BLEGATTSSRVSTART
AT+BLEADDR?
AT+BLESECPARAM=1,0,16,3,3
用户手册 www.alientek.com
31

ATK-MB026 模块用户手册
WIFI & BLE模块
AT+BLESETKEY=123456
AT+BLEADVSTART
AT+BLEENC=0,3
表2.3.6.10 AT+ BLEENC——发起Bluetooth LE加密请求
10. AT+BLESCAN——使能Bluetooth LE扫描
设置指令 AT+BLESCAN=<enable>[,<duration>][,<filter_type>,<filter_param>]
+BLESCAN：<addr>,<rssi>,<adv_data>,<scan_rsp_data>,<addr_type>
响应 OK
+BLESCANDONE
⚫ <enable>：
 1：开始持续扫描
 0：停止持续扫描
⚫ [<duration>]：扫描持续时间，单位：秒。
 若设置停止扫描，无需设置本参数；
 若设置开始扫描，需设置本参数：
 本参数设为0时，则表示开始持续扫描；
 本参数设为非0值时，例如AT+BLESCAN=1,3，则表示扫描3秒后自动结束
扫描，然后返回扫描结果。
参数说明
⚫ [<filter_type>]：过滤选项
 1：“MAC”
 2：“NAME”
⚫ <filter_param>：过滤参数，表示对方设备MAC地址或名称
⚫ <addr>：Bluetooth LE地址
⚫ <rssi>：信号强度
⚫ <adv_data>：广播数据
⚫ <scan_rsp_data>：扫描响应数据
⚫ <addr_type>：广播设备地址类型
注意 在服务端广播开启后使用
AT+BLEINIT=1
AT+BLESCAN=1
示例 AT+BLESCAN=0
AT+BLESCAN=1,3,1,"24:0A:C4:96:E6:88"
AT+BLESCAN=1,3,2,"ESP-AT"
表2.3.6.11 AT+BLESCAN——使能Bluetooth LE扫描
11. AT+ BLECONN——建立Bluetooth LE连接
设置指令 AT+BLECONN=<conn_index>,<remote_address>[,<addr_type>,<timeout>]
若建立连接成功，则提示：
+BLECONN:<conn_index>,<remote_address>
OK
响应
若建立连接失败，则提示：
+BLECONN:<conn_index>,-1
ERROR
用户手册 www.alientek.com
32

ATK-MB026 模块用户手册
WIFI & BLE模块
若是因为参数错误或其它的原因导致连接失败，则提示：
ERROR
⚫ <conn_index>：Bluetooth LE 连接号，范围：[0,2]。
⚫ <remote_address>：对方 Bluetooth LE 设备地址。
⚫ [<addr_type>]：广播设备地址类型：
参数说明
 0：公共地址 (Public Address)
 1：随机地址 (Random Address)
⚫ [<timeout>]：连接超时时间，单位：秒。范围：[3,30]。
在建立新的连接之前先运行AT+BLESCAN命令扫描设备，确保目标设备处于广播
注意
状态。
AT+BLEINIT=1
示例
AT+BLECONN=0,"24:0a:c4:09:34:23",0,10
表2.3.6.12 AT+BLECONN——建立Bluetooth LE连接
12. AT+ BLEGATTCPRIMSRV——GATTC发现基本服务
查询指令 AT+BLEGATTCPRIMSRV=<conn_index>
+BLEGATTCPRIMSRV:<conn_index>,<srv_index>,<srv_uuid>,<srv_type>
响应
OK
⚫ <conn_index>：Bluetooth LE连接号，范围：[0,2]。
⚫ <srv_index>：服务序号，从1开始递增。
⚫ <srv_uuid>：服务的UUID。
参数说明
⚫ <srv_type>：服务的类型：
 0：次要服务；
 1：首要服务。
注意 使用本命令，需要先建立 Bluetooth LE 连接
AT+BLEINIT=1
示例 AT+BLECONN=0,"24:12:5f:9d:91:98"
AT+BLEGATTCPRIMSRV=0
表2.3.6.13 AT+BLEGATTCPRIMSRV——GATTC发现基本服务
13. AT+BLEGATTCCHAR——GATTC发现服务特征
设置指令 AT+BLEGATTCCHAR=<conn_index>,<srv_index>
对于服务特征信息，响应如下：
+BLEGATTCCHAR:"char",<conn_index>,<srv_index>,<char_index>,
<char_uuid>,<char_prop>
响应 对于描述符信息，响应如下：
+BLEGATTCCHAR:"desc",<conn_index>,<srv_index>,<char_index>,
<desc_index>,<desc_uuid>
OK
⚫ <conn_index>：Bluetooth LE连接号，范围：[0,2]。
⚫ <srv_index>：服务序号，可运行AT+BLEGATTCPRIMSRV=<conn_index>查询。
⚫ <char_index>：服务特征的序号，从1开始递增。
参数说明 ⚫ <char_uuid>：服务特征的UUID。
⚫ <char_prop>：服务特征的属性。
⚫ <desc_index>：特征描述符序号。
⚫ <desc_uuid>：特征描述符的UUID。
用户手册 www.alientek.com
33

ATK-MB026 模块用户手册
WIFI & BLE模块
注意 使用本命令，需要先建立Bluetooth LE连接
AT+BLEINIT=1
AT+BLECONN=0,"24:12:5f:9d:91:98"
示例
AT+BLEGATTCPRIMSRV=0
AT+BLEGATTCCHAR=0,1
表2.3.6.14 AT+ BLEGATTCCHAR——GATTC发现服务特征
14. AT+BLESPPCFG——设置Bluetooth LE SPP参数
AT+BLESPPCFG=<cfg_enable>[,<tx_service_index>,<tx_char_index>,<rx_service_in
设置指令
dex>,<rx_char_index>][,<auto_conn>]
响应 OK
⚫ <cfg_enable>：
 0：重置所有SPP参数，后面参数无需填写；
 1：后面参数需要填写。
⚫ <tx_service_index>：tx服务序号，可运行
AT+BLEGATTCPRIMSRV=<conn_index>和AT+BLEGATTSSRV?查询。
⚫ <tx_char_index>：tx服务特征序号，可运行
AT+BLEGATTCCHAR=<conn_index>,<srv_index>和AT+BLEGATTSCHAR?查
询。
参数说明
⚫ <rx_service_index>：rx服务序号，可运行
AT+BLEGATTCPRIMSRV=<conn_index>和AT+BLEGATTSSRV?查询。
⚫ <rx_char_index>：rx服务特征序号，可运行
AT+BLEGATTCCHAR=<conn_index>,<srv_index>和AT+BLEGATTSCHAR?查
询。
⚫ <auto_conn>：自动重连标志位，默认情况下，自动重连功能被使能。
 0：禁止Bluetooth LE透传自动重连功能。
 1：使能Bluetooth LE透传自动重连功能。
注意 -
AT+BLESPPCFG=0
示例 AT+BLESPPCFG=1,3,5,3,7
AT+BLESPPCFG?
表2.3.6.15 AT+BLESPPCFG——设置Bluetooth LE SPP参数
15. AT+BLESPP——进入Bluetooth LE SPP模式
执行指令 AT+BLESPP
OK
>
上述响应表示 AT 已经进入 Bluetooth LE SPP 模式，可以进行数据的
响应
发送和接收。
若 Bluetooth LE SPP 状态错误 ( 对端在 Bluetooth LE 连接建立后未
使能 Notifications )，则返回：
用户手册 www.alientek.com
34

ATK-MB026 模块用户手册
WIFI & BLE模块
ERROR
⚫ 在SPP传输中，若未设置AT+SYSMSG Bit0为1，则AT不会提示任何退出SPP
透传模式的信息。
⚫ 在SPP传输中，若未设置AT+SYSMSG Bit2为1，则AT不会提示任何连接状
参数说明
态变更的信息。
⚫ 当系统收到只含有+++的包时，设备返回到普通命令模式，请至少等待一秒再发
送下一个AT命令。
注意 -
示例 AT+BLESPP
表2.3.6.16 AT+ BLESPP——进入Bluetooth LE SPP模式
2.3.7 常用AT指令实例
1. SoftAP模式下作TCP服务器
发送指令 作用
AT+CWMODE=2 设置为SoftAP模式
AT+RST 重启生效
AT+CWSAP=”ATK-MB026”, 设置 AP 参数。SSID 为ATK-MB026、密码为 12345678、
”12345678”,1,4 通道为1、加密方式为WPA_WPA2_PSK
AT+CIPMUX=1 开启多连接
AT+CIPSERVER=1,8086 开启SERVER模式，端口号为8086
AT+CIPSEND=0,25 向ID0发送25字节数据包
表2.3.7.1 SoftAP模式下作TCP服务器
2. SoftAP模式下作TCP客户端
发送指令 作用
AT+CWMODE=2 设置为SoftAP模式
AT+RST 重启生效
AT+CWSAP=”ATK-MB026”, 设置 AP 参数。SSID 为ATK-MB026、密码为 12345678、
”12345678”,1,4 通道为1、加密方式为WPA_WPA2_PSK
AT+CIPMUX=0 开启单连接
AT+CIPSTART=”TCP”,
建立TCP连接到192.168.4.XXX:8086
”192.168.4.XXX”,8086
AT+CIPMODE=1 开启透传模式（仅单连接Client时支持）
AT+CIPSEND 开始发送数据
表2.3.7.2 SoftAP模式下作TCP客户端
3. SoftAP模式下UDP连接
发送指令 作用
AT+CWMODE=2 设置为SoftAP模式
AT+RST 重启生效
AT+CWSAP=”ATK-MB026”, 设置SoftAP参数。SSID为ATK-MB026、密码为12345678、
”12345678”,1,4 通道为1、加密方式为WPA_WPA2_PSK
AT+CIPMUX=0 开启单连接
用户手册 www.alientek.com
35

ATK-MB026 模块用户手册
WIFI & BLE模块
AT+CIPSTART=”UDP”,
建立UDP连接到192.168.4.XXX:8086
“192.168.4.XXX”,8086
AT+CIPSEND=25 向目标UDP发送25字节数据
表2.3.7.3 SoftAP模式下UDP连接
4. Station模式下作TCP服务器
发送指令 作用
AT+CWMODE=1 设置为Station模式
AT+RST 重启生效
AT+CWJAP=” ALIENTEK”,
加入WiFi热点。SSID：ALIENTEK、密码：12345678
”12345678”
AT+CIPMUX=1 开启多连接
AT+CIPSERVER=1,8086 开启SERVER模式，端口号为8086
AT+CIPSEND=0,25 向ID0发送25字节数据包
表2.3.7.4 Station模式下作TCP服务器
5. Station模式下作TCP客户端
发送指令 作用
AT+CWMODE=1 设置为Station模式
AT+RST 重启生效
AT+CWJAP=” ALIENTEK”,
加入WiFi热点。SSID：ALIENTEK、密码：12345678
”12345678”
AT+CIPMUX=0 开启单连接
AT+CIPSTART=”TCP”,
建立TCP连接到192.168.4.XXX:8086
”192.168.4.XXX”,8086
AT+CIPMODE=1 开启透传模式（仅单连接Client时支持）
AT+CIPSEND 开始发送数据
表2.3.7.5 Station模式下作TCP客户端
6. Station模式下UDP连接
发送指令 作用
AT+CWMODE=1 设置为Station模式
AT+RST 重启生效
AT+CWJAP=” ALIENTEK”,
加入WiFi热点。SSID：ATK-MB026、密码：12345678
”12345678”
AT+CIPMUX=0 开启单连接
AT+CIPSTART=”UDP”,
建立UDP连接到192.168.4.XXX:8086
“192.168.4.XXX”,8086
AT+CIPSEND=25 向目标UDP发送25字节数据
表2.3.7.6 Station模式下UDP连接
7. SoftAP+Station模式下作TCP服务器
发送指令 作用
AT+CWMODE=3 设置为SoftAP+Station模式
AT+RST 重启生效
AT+CWSAP=”ATK-MB026”, 设置SoftAP参数。SSID为ATK-MB026、密码为12345678、
”12345678”,1,4 通道为1、加密方式为WPA_WPA2_PSK
用户手册 www.alientek.com
36

ATK-MB026 模块用户手册
WIFI & BLE模块
AT+CWJAP=”ALIENTEK”,
加入WiFi热点。SSID：ALIENTEK、密码：12345678
”12345678”
AT+CIPMUX=1 开启多连接
AT+CIPSERVER=1,8086 开启SERVER模式，端口号为8086
AT+CIPSTO=1200 设置服务器超时时间1200s
AT+CIPSEND=0,25 向ID0发送数据
AT+CIPSEND=1,25 向ID1发送数据
表2.3.7.7 SoftAP+Station模式下作TCP服务器
8. SoftAP+Station模式下作TCP客户端
发送指令 作用
AT+CWMODE=3 设置为SoftAP+Station模式
AT+RST 重启生效
AT+CWSAP=”ATK-MB026”, 设置 AP 参数。SSID 为ATK-MB026、密码为 12345678、
”12345678”,1,4 通道为1、加密方式为WPA_WPA2_PSK
AT+CWJAP=”ALIENTEK”,
加入WiFi热点。SSID：ALIENTEK、密码：12345678
”12345678”
AT+CIPMUX=1 开启多连接
AT+CIPSTART=0,”TCP”,
建立TCP连接到192.168.4.XXX:8086
”192.168.4.XXX”,8086
AT+CIPSEND=0,25 向ID0发送数据
AT+CIPSEND=1,25 向ID1发送数据
表2.3.7.8 SoftAP+Station模式下作TCP客户端
9. SoftAP+Station模式下UDP连接
发送指令 作用
AT+CWMODE=3 设置为SoftAP+Station模式
AT+RST 重启生效
AT+CWSAP=”ATK-MB026”, 设置SoftAP参数。SSID为ATK-MB026、密码为12345678、
”12345678”,1,4 通道为1、加密方式为WPA_WPA2_PSK
AT+CWJAP=”ALIENTEK”,
加入WiFi热点。SSID：ALIENTEK、密码：12345678
”12345678”
AT+CIPMUX=1 开启多连接
AT+CIPSERVER=1,8086 开启服务器，端口号8086
AT+CIPSTO=1200 设置服务器超时时间1200s
AT+CIPSTART=0,”UDP”,
STA作为ID0连接到192.168.1.XXX:8086
“192.168.1.XXX”,8086
AT+CIPSEND=0,25 向ID0发送数据
AT+CIPSEND=1,25 向ID1发送数据
表2.3.7.9 SoftAP+Station模式下UDP连接
10. Bluetooth LE连接
发送指令 作用
AT+BLEINIT=2 初始化蓝牙，将设备初始化为server
AT +BLEGATTSSRVCRE GATTS创建服务
AT +BLEGATTSSRVSTART GATTS开启服务
用户手册 www.alientek.com
37

ATK-MB026 模块用户手册
WIFI & BLE模块
AT+BLEADDR? 查询Bluetooth LE设备地址
设置Bluetooth LE广播参数，
最小广播间隔50，
最大广播间隔50，
AT +BLEADVPARAM=50, 50, 0, 0, 4 设置广播类型为0：ADV_TYPE_IND；
Bluetooth LE地址类型设置为：
0：BLE_ADDR_TYPE_PUBLIC；
设置广播信道为：4:：ADV_CHNL_39
设置Bluetooth LE广播数据，将设备名称
设置为：ATK-MB026
AT+BLEADVDATAEX="ATK-MB026","A002","00",1 uuid设置为：A002
制造商数据设置为：00
包含TX功率
设置 Bluetooth LE SMP 加密参数，
设置认证请求为：13: SC_MITM_BOND
设置输入输出能力：2: KeyboardOnly
AT +BLESECPARAM=13, 2, 16, 3, 3
设置加密密钥长度：16字节
设置用于交换初始密钥和响应密钥的
link密钥
开启广播（这一步很重要，若未发送该
AT+BLEADVSTART
指令，将搜索不到该设备）
AT+BLEENC=0, 3 发起配对请求
表2.3.7.10 Bluetooth LE连接
值得一提的是，ESP32-C3芯片由于其强大的功能，可以同时支持Wi-Fi与Bluetooth LE
连接。也就是说在连接 Wi-Fi 后与其它 TCP/IP 协议的上位机进行数据传输的过程中，仍然
可以通过其它蓝牙设备发送数据给ESP32-C3。那么Wi-Fi和Bluetooth LE的配置方式已经
在上面列出来了，笔者建议的配置顺序为：先进行Wi-Fi功能的配置再进行Bluetooth LE功
能的配置，具体请参考:5.Station模式下作TCP客户端->10. Bluetooth LE连接。
2.4 连接旧版原子云服务器
原子云即原子云服务器，是正点原子推出的互联网云服务平台，它可以实现数据的远程
监控、转发和管理等功能，在未来也会持续更新更多的功能以满足用户的需求。原子云域名
为：cloud.alientek.com，端口号为：59666。
2.4.1 创建设备
在创建设备之前，需登入原子云的网址https://cloud.alientek.com/创建并登入账号。创建
和登入账号的过程比较简单，这里不做过多介绍，登入原子云后，如下图所示：
用户手册 www.alientek.com
38

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.4.1.1 原子云首页
建议第一次使用原子云的用户，点击原子云首页左下角的“帮助文档”，快速了解原子
云服务器。
在原子云平台创建设备，首先点击原子云首页左侧导航栏中的“设备管理”，随后在出
现的页面中，点击“新增设备”，如下图所示：
图2.4.1.2 新增设备
接着在弹出的窗口中，根据ATK-MB026模块的设备类型选择“ESP8266”，随后根据个
人喜好填入“设备名称”和“密码”（这里的密码在就是ATK-MB026模块通过AT指令连接
原子云时需要的密码），如下图所示：
用户手册 www.alientek.com
39

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.4.1.3 新增ESP8266设备
最后，点击“新增”按钮，即可创建设备，设备创建好后，如下图所示：
图2.4.1.4 设备创建完成
创建好设备后，系统会自动为设备生成编号，这个设备编号就是ATK-MB026模块使用
AT指令连接原子云时需要的设备ID。
2.4.2 连接原子云
创建好设备后，就能后根据设备的编号和密码并通过AT指令操作ATK-MB026模块连
接原子云了。具体的AT指令如下所示：
/* 使能ATK-MB026模块的STA模式，以连接路由器的AP */
AT+CWMODE=1
/* 连接路由器的AP，以访问互联网 */
AT+CWJAP=”ALIENTEK-YF”,”15902020353”
/* 连接原子云服务器 */
AT+ATKCLDSTA=”58762000827114330285”,”12345678”
实际在串口调试助手中的操作，如下图所示：
用户手册 www.alientek.com
40

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.4.2.1 ATK-MB026模块使用AT指令连接原子云
当串口调试助手显示“CLOUD CONNECTED”后，说明已成功连接上原子云服务器，
此时在原子云的设备管理界面，也能够看到对应的设备显示为“已连接”的连接状态，如下
图所示：
图2.4.2.2 原子云设备已连接状态
当ATK-MB026模块成功连接原子云服务器后，即进入了透传模式，此时就能够在原子
云的对应设备的“消息收发”操作界面通过原子云服务器发送消息至ATK-MB026模块，同
时，也能后在该界面下，查看到接收自ATK-MB026模块的消息，如下图所示：
用户手册 www.alientek.com
41

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.4.2.3 ATK-MB026模块接收到来自原子云服务器的消息
图2.4.2.4 原子云服务器接收到来自ATK-MB026模块的消息
用户手册 www.alientek.com
42

ATK-MB026 模块用户手册
WIFI & BLE模块
2.5 连接新版原子云服务器
原子云即原子云服务器，是正点原子 2024 年推出的互联网云服务平台，它可以实现数
据的远程监控、转发和管理等功能，在未来也会持续更新更多的功能以满足用户的需求。原
子云域名为：zdyz.alientek.com，端口号为：6666。
2.5.1 创建设备
在创建设备之前，需登入原子云的网址https://zdyz.alientek.com/home创建并登入账号。
创建和登入账号的过程比较简单，这里不做过多介绍，登入原子云后，如下图所示：
图2.5.1.1 新版原子云首页
新版原子云的使用方法与旧版原子云差别不大，对于第一次使用新版原子云的用户可以
在首页右下角点击“上云流程”进行初步的了解。再者，本次ATK-MB026模块连接新版原
子云所用到的节点不多，跟着笔者接下所介绍的步骤进行操作即可：
首先，在新版原子云平台左侧导航栏的“设备管理-设备列表”中创建设备，随后在出
现的页面中，点击“添加设备”，如下图所示：
图2.5.1.2 添加设备
接着在弹出的窗口中，根据ATK-MB026模块的设备类型选择“ESP8266”，随后根据个
用户手册 www.alientek.com
43

ATK-MB026 模块用户手册
WIFI & BLE模块
人喜好填入“设备名称”和“设备密钥”（这里的密钥在就是ATK-MB026模块通过AT指令
连接原子云时需要的密码），如下图所示：
图2.5.1.3 新增ESP32-C3设备
最后，点击“保存”按钮，即可创建设备，其它选项可以不用管，将标有红色标记的必
填选项填好即可。设备创建好后，如下图所示：
图2.5.1.4 设备创建完成
创建好设备后，系统会自动为设备生成编号，这个设备编号就是ATK-MB026模块使用
AT指令连接原子云时需要的设备ID。
2.5.2 连接新版原子云
创建好设备后，就能后根据设备的编号和密码并通过AT指令操作ATK-MB026模块连
接原子云了。具体的AT指令如下所示：
/* 使能ATK-MB026模块的Station模式，以连接路由器的AP */
AT+CWMODE=1
/* 连接路由器的AP，以访问互联网 */
AT+CWJAP=”ALIENTEK-YF”,”15902020353”
/* 连接原子云服务器 */
AT+ATKNEWCLDSTA=”18617699302953533447”,”12345678”
实际在串口调试助手中的操作，如下图所示：
用户手册 www.alientek.com
44

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.4.2.1 ATK-MB026模块使用AT指令连接新版原子云
当串口调试助手显示“CLOUD CONNECTED”后，说明已成功连接上原子云服务器，
此时在原子云的“设备列表”界面，能够看到对应的设备显示为“在线”的连接状态，如下
图所示：
图2.4.2.2 原子云设备已连接状态
当ATK-MB026模块成功连接原子云服务器后，即进入了透传模式，此时就能够在原子
云的对应设备的“消息收发”操作界面通过原子云服务器发送消息至ATK-MB026模块，同
时，也能后在该界面下，查看到接收自ATK-MB026模块的消息，如下图所示：
用户手册 www.alientek.com
45

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.5.2.3 ATK-MB026模块接收到来自新版原子云服务器的消息
图2.5.2.4 新版原子云服务器接收到来自ATK-MB026模块的消息
2.6 配置 Bluetooth LE
这一节主要介绍Bluetooth LE的配置方法，本节中的描述仅适用于Bluetooth LE protocol
4.2协议规范。在开始配置前我们先简单了解一下Bluetooth LE协议的架构以及角色划分。
2.6.1 Bluetooth LE协议架构
Bluetooth LE协议栈从下至上分为几个层级：Physical Layer(PHY)、Link Layer(LL)、Host
Controller Interface(HCI)、Logical Link Control and Adaptation Protocol Layer(L2CAP)、
Attribute Protocol(ATT)、Security Manager Protocol(SMP)、Generic Attribute Profile(GATT)、
用户手册 www.alientek.com
46

ATK-MB026 模块用户手册

WIFI & BLE模块
Generic Access Profile(GAP)。
⚫  PHY：PHY层主要负责在物理信道上发送和接收信息包。Bluetooth LE使用40个
射频信道。频率范围：2402MHz到2480MHz。
⚫  LL：LL层主要负责创建、修改和释放逻辑链路（以及，如果需要，它们相关的逻
辑传输），以及与设备之间的物理链路相关的参数的更新。它控制链路层状态机处
于准备、广播、监听/扫描、发起连接、已连接五种状态之一。
⚫  HCI：HCI层向主机和控制器提供一个标准化的接口。该层可以由软件API实现或
者使用硬件接口UART、SPI、USB来控制。
| ⚫  L2CAP：L2CAP | 层负责对主机和协议栈之间交换的数据进行协议复用能力、分段 |     |
| -------------- | ---------------------------- | --- |
和重组操作。
| ⚫  ATT：ATT | 层实现了属性服务器和属性客户端之间的点对点协议。ATT | 客户端向 |
| ---------- | --------------------------- | ---- |
ATT服务端发送命令、请求和确认。ATT服务端向客户端发送响应、通知和指示。
| ⚫  SMP：SMP | 层用于生成加密密钥和身份密钥。SMP还管理加密密钥和身份密钥的 |     |
| ---------- | ------------------------------- | --- |
存储，并负责生成随机地址并将随机地址解析为已知设备身份。
| ⚫  GATT：GATT | 层表示属性服务器和可选的属性客户端的功能。该配置文件描述了 |     |
| ------------ | ----------------------------- | --- |
属性服务器中使用的服务、特征和属性的层次结构。该层提供用于发现、读取、写
入和指示服务特性和属性的接口。
| ⚫  GAP：GAP | 层代表所有蓝牙设备通用的基本功能，例如传输、协议和应用程序配 |     |
| ---------- | ------------------------------ | --- |
置文件使用的模式和访问程序。GAP 服务包括设备发现、连接模式、安全、身份
验证、关联模型和服务发现。
2.6.2 Bluetooth LE角色划分
在Bluetooth LE协议栈中不同的层级有不同的角色划分。这些角色划分互不影响。
⚫  LL：设备可以划分为主机和从机，从机广播，主机可以发起连接。
⚫  GAP：定义了4种特定角色：广播者、观察者、外围设备和中心设备。
⚫  GATT：设备可以分为服务端和客户端。
关于Bluetooth LE更详细的内容介绍请参考《[ESP32C3-AT][v3.3.0.0]用户指南.pdf》，那
么接下来笔者将介绍具体的配置步骤与方法。
2.6.3 Bluetooth LE服务端配置
配置步骤分两部分讲解，一部分面向Bluetooth LE服务端，另一部分面向Bluetooth LE
客户端。其中客户端包含了在串口助手上对另一个ATK-MB026模块的配置，此时，该模块
| 将作为主设备（也就是客户端）与服务端进行通信；另外，还包含了手机 | APP | 的配置，此 |
| -------------------------------- | --- | ----- |
时手机设备将作为主设备（也是客户端）与服务端进行通信。注意：以下介绍仅限于两个设
备之间的透传功能，其它功能不做介绍，有感兴趣的读者可自行了解。
1.  初始化Bluetooth LE功能
ESP32-C3 Bluetooth LE服务端：
| 指令  | AT+BLEINIT=2  |     |
| --- | ------------- | --- |
| 响应  | OK            |     |
表2.6.3.1 AT+ BLEINIT——初始化Bluetooth LE功能
2.  Bluetooth LE服务端创建GATTS服务
ESP32-C3 Bluetooth LE服务端：
| 指令  | AT+BLEGATTSSRVCRE  |     |
| --- | ------------------ | --- |
| 响应  | OK                 |     |
用户手册                                                                    www.alientek.com

47

ATK-MB026 模块用户手册
WIFI & BLE模块
当发送这条命令后提示：ERROR，需要输入AT+RESTORE后从初始
说明
化开始重新配置
表2.6.3.2 AT+ BLEGATTSSRVCRE——Bluetooth LE服务端创建服务
3. Bluetooth LE服务端开启GATTS服务
ESP32-C3 Bluetooth LE服务端：
指令 AT+BLEGATTSSRVSTART
响应 OK
表2.6.3.3 AT+ BLEGATTSSRVSTART——Bluetooth LE服务端开启服务
4. Bluetooth LE服务端获取其MAC地址
ESP32-C3 Bluetooth LE服务端：
指令 AT+BLEADDR?
+BLEADDR:"e4:b0:63:c4:62:2e"
响应
OK
说明 请记住该地址，因为客户端配置时会用到
表2.6.3.4 AT+ BLEADDR?——Bluetooth LE服务端获取其MAC地址
5. 设置Bluetooth LE广播数据（即设备名称等参数）
ESP32-C3 Bluetooth LE服务端：
指令 AT+BLEADVDATAEX="ATK-MB026","A002","0102030405",1
响应 OK
还有一条指令：AT+BLEADVDATA=<adv_data>可以设置设备名称，但是传入
的配置参数是十六进制的字符串，也就意味着你需要将你的设备名称（前提是不包
含中文）由ASCII码转换为十六进制表示，同时还要对照相应的蓝牙广播数据类
型定义的描述添加完整的字段，比如：
AT+BLEADVDATA="0201060A09414C49454E54454B"这一命令中我们可知：
02 01 06 字段设置广播模式为BLE only
0A 09 414C49454E54454B字段表示：
说明 0A：此字段数据长度为10
09：完整的设备名称
414C49454E54454B：设备名称ALIENTEK的十六进制表示
在配置过程中我们推荐使用AT+BLEADVDATAEX这一命令进行配置，这样配置
设备名称错误率低且不需要ASCII码与十六进制数值之间的转换，使用起来更方
便。如果使用AT+BLEADVDATA这一命令进行配置那么服务端很有可能会无法
正确显示你所要配置的设备名称（一旦配置失败会显示默认的设备名称：
ESP-AT），因此笔者推荐使用AT+BLEADVDATAEX这一命令进行配置。
表2.6.3.5 AT+ BLEADVDATAEX——设置Bluetooth LE广播数据
6. Bluetooth LE服务端开始广播
ESP32-C3 Bluetooth LE服务端：
指令 AT+BLEADVSTART
响应 OK
表2.6.3.6 AT+ BLEADVSTART——Bluetooth LE服务端开始广播
7. Bluetooth LE服务端配置Bluetooth LE SPP
ESP32-C3 Bluetooth LE服务端：
指令 AT+BLESPPCFG=1,1,7,1,5,1
响应 OK
用户手册 www.alientek.com
48

ATK-MB026 模块用户手册
WIFI & BLE模块
表2.6.3.7 AT+ BLESPPCFG——Bluetooth LE服务端配置Bluetooth LE SPP
8. Bluetooth LE使能Bluetooth LE SPP（进入透传模式）
ESP32-C3 Bluetooth LE服务端：
指令 AT+BLESPP
OK
响应
>
有上述相应，表示已经进入Bluetooth LE SPP模式，但需要服务端设备
说明
与客户端设备连接成功后才能使用该命令进入该模式（透传）
表2.6.3.8 AT+ BLESPP——Bluetooth LE使能Bluetooth LE SPP
2.6.4 Bluetooth LE客户端配置
1. 初始化Bluetooth LE功能
ESP32-C3 Bluetooth LE客户端：
指令 AT+BLEINIT=1
响应 OK
表2.6.4.1 AT+ BLEINIT——初始化Bluetooth LE功能
2. Bluetooth LE客户端开始扫描，持续3秒
ESP32-C3 Bluetooth LE客户端：
指令 AT+BLESCAN= 1,3
OK
+BLESCAN:"24:0a:c4:d6:e4:46",-78,0201060a09457370726573736966030302a0,,0
响应
+BLESCAN:"45:03:cb:ac:aa:a0",-62,0201060aff4c001005441c61df7d,,1
+BLESCAN:"24:0a:c4:d6:e4:46",-26,0201060a09457370726573736966030302a0,,0
表2.6.4.2 AT+ BLESCAN——Bluetooth LE客户端开始扫描，持续3秒
3. 建立Bluetooth LE连接
ESP32-C3 Bluetooth LE客户端：
指令 AT+BLECONN=0," e4:b0:63:c4:62:2e "
OK
+BLESCAN:"24:0a:c4:d6:e4:46",-78,0201060a09457370726573736966030302a0,,0
响应
+BLESCAN:"45:03:cb:ac:aa:a0",-62,0201060aff4c001005441c61df7d,,1
+BLESCAN:"24:0a:c4:d6:e4:46",-26,0201060a09457370726573736966030302a0,,0
命令中的地址是服务端的MAC地址，我们在配置服务端时就已经获取到了，
说明
此时将其填入。
表2.6.4.3 AT+ BLECONN——建立Bluetooth LE连接
4. Bluetooth LE客户端发现服务
ESP32-C3 Bluetooth LE客户端：
指令 AT+BLEGATTCPRIMSRV=0
+BLEGATTCPRIMSRV:0,1,0x1801,1
+BLEGATTCPRIMSRV:0,2,0x1800,1
+BLEGATTCPRIMSRV:0,3,0xA002,1
响应
+BLEGATTCPRIMSRV:0,4,0xA003,1
OK
用户手册 www.alientek.com
49

ATK-MB026 模块用户手册
WIFI & BLE模块
表2.6.4.4 AT+ BLEGATTCPRIMSRV——Bluetooth LE客户端发现服务
5. Bluetooth LE客户端发现特征
ESP32-C3 Bluetooth LE客户端：
指令 AT+BLEGATTCCHAR=0,3
+BLEGATTCCHAR:"char",0,3,1,0xC300,0x02
+BLEGATTCCHAR:"desc",0,3,1,1,0x2901
+BLEGATTCCHAR:"char",0,3,2,0xC301,0x02
+BLEGATTCCHAR:"desc",0,3,2,1,0x2901
+BLEGATTCCHAR:"char",0,3,3,0xC302,0x08
+BLEGATTCCHAR:"desc",0,3,3,1,0x2901
+BLEGATTCCHAR:"char",0,3,4,0xC303,0x04
+BLEGATTCCHAR:"desc",0,3,4,1,0x2901
响应 +BLEGATTCCHAR:"char",0,3,5,0xC304,0x08
+BLEGATTCCHAR:"char",0,3,6,0xC305,0x10
+BLEGATTCCHAR:"desc",0,3,6,1,0x2902
+BLEGATTCCHAR:"char",0,3,7,0xC306,0x20
+BLEGATTCCHAR:"desc",0,3,7,1,0x2902
+BLEGATTCCHAR:"char",0,3,8,0xC307,0x02
+BLEGATTCCHAR:"desc",0,3,8,1,0x2901
OK
表2.6.4.5 AT+ BLEGATTCCHAR——Bluetooth LE客户端发现特征
6. Bluetooth LE使能Bluetooth LE SPP（进入透传模式）
ESP32-C3 Bluetooth LE客户端：
指令 AT+BLESPP
OK
响应
>
有上述相应，表示已经进入Bluetooth LE SPP模式，但需要服务端设备
说明
与客户端设备连接成功后才能使用该命令进入该模式（透传）
表2.6.3.6 AT+ BLESPP——Bluetooth LE使能Bluetooth LE SPP
以上所介绍服务端和客户端的 AT 指令均在串口助手上实现，配套的开发板例程在
《ATK-MB026 WIFI & BLE使用说明》中有讲解，以下是串口助手的具体实现过程：
用户手册 www.alientek.com
50

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.6.3.1 串口助手实现过程
2.6.5 Bluetooth LE手机APP配置
手机 APP 我们可以认为是一个客户端设备，那么我们只需要将服务端的设备按照上面
所提到的配置步骤，将服务端配置好即可。那么在这里，笔者建议用到的手机APP是：nRF
Connet。
图2.6.4.1 APP发现设备广播 图2.6.4.2 APP连接设备成功并打开设备监听
用户手册 www.alientek.com
51

ATK-MB026 模块用户手册
WIFI & BLE模块
首先，根据图 2.6.4.1 所示内容，在 APP 界面搜索到了设备名称，我们点击右上角的
“Connect”按钮进行连接。根据图 2.6.4.2 所示内容，我们看到了界面底部连接成功标识，
然后分别点击界面上半部分的两个红色框内的箭头按钮打开监听。执行到这一步，笔者需要
说明几点可能出现的情况：
1，当如图2.6.4.1界面所示没有正常出现设备名称时，我们可以尝试下滑屏幕刷新界面，
目的在于刷新设备。
2，如果使用第一点的操作，发现无效后可以查看该设备列表界面，是否存在“ESP-AT”
字样的设备名称。若出现，那就证明前面配置服务端的步骤不正确。配置步骤请看：5.设置
Bluetooth LE广播数据（即设备名称等参数）。
3，如果前面两点都无法解决无法发现设备的问题，那么可以考虑服务端是否开启了广
播，上述图片中所涉及到的步骤均是基于服务端设备已经开启的前提下进行，这点尤为重
要！！！
图2.6.4.3 APP接收到数据 图2.6.4.4 切换数据格式
如图 2.6.4.3 所示，我们已经接收到了来自服务端设备的数据，不过此时显示的是十六
进制的数据格式，那么我们点击图 2.6.4.3 中位于十六进制数据左下角的按钮进行数据格式
的转换，由十六进制数据格式转换为UTF-8格式进行显示，如图2.6.4.4所示。
用户手册 www.alientek.com
52

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.6.4.5 得见庐山真面目 图2.6.4.6 发送数据
经过数据格式转换后，我们看见了数据的真面目“This is information from the server”。
至此证明，服务端设备发送数据至APP（客户端）的步骤是没有问题了，如图2.6.4.5所示。
接收数据没有问题了，那么我们来看看发送数据。
如图 2.6.4.6 所示，我们点击红色方框中右下角的箭头按钮进入命令与数据发送界面，
如图 2.6.4.7 所示。在弹出的操作界面中，我们填入要发送的数据，并切换发送数据的格式
为 UTF-8，否则，在服务端一侧的串口助手中，有大概率显示乱码数据或者接收不到数据。
完成上述步骤我们可以在串口助手中看到来自APP的数据，如图2.6.4.8所示。
图2.6.4.7 APP发送数据
用户手册 www.alientek.com
53

|     |     |     |     |     | ATK-MB026 | 模块用户手册 |     |
| --- | --- | --- | --- | --- | --------- | ------ | --- |

WIFI & BLE模块

 图2.6.4.8 服务端接收到APP（客户端）发来的数据
以上内容，便是服务端与客户端设备之间实现透传模式的几种连接方法的介绍。具体的
方式方法也可以参考官方给出的方式进行操作：
https://docs.espressif.com/projects/esp-at/zh_CN/latest/esp32c3/AT_Command_Examples/bluetoo
th_le_at_examples.html
一键配网
2.7
2.7.1 ESP-TOUCH
| ESP-TOUCH |     | 是乐鑫官方提供的用于配置乐鑫 |     |     | ESP 设备连接 | AP 的 APP，能够实现 |     |
| --------- | --- | -------------- | --- | --- | -------- | ------------- | --- |
ATK-MB026模块的一键配网。
7.  手机端APP配置
要使用ESP-TOUCH，必须先访问乐鑫官方的APP下载网址，下载并安装ESP-TOUCH，
乐鑫官方的APP下载网址为：https://www.espressif.com.cn/zh-hans/support/download/apps。
安装并打开ESP-TOUCH APP后，出现选择EspTouch版本的界面，这里选择“EspTouch”，
切记不能选择“EspTouch V2”，者两者是不相兼容的 。
选择“EspTouch”版本后，会出现当前手机所连接AP的SSID和BSSID，ESP-TOUCH
| 会将当前手机所连接         |                     | AP 的信息发送至 |        | ATK-MB026                | 模块，让其连接与手机相同的   |                | AP，但 |
| ----------------- | ------------------- | --------- | ------ | ------------------------ | --------------- | -------------- | ---- |
| 因为 ATK-MB026      |                     | 模块仅支持     | 2.4GHz | 频段的 AP，所以手机要连接           |                 | 2.4GHz 频段的AP。接 |      |
| 下来根据提示，输入手机所连接    |                     |           | AP     | 的密码，因为本文档介绍使用            |                 | ESP-TOUCH      | 实现   |
| ATK-MB026         | 模块的一键配网仅做测试，因此设备数量为 |           |        |                          | 1，且选择通过组播的方式进行一 |                |      |
| 键配网，配置好以上参数后，即可点击 |                     |           |        | APP 下方的“确认”按钮，进行一键配网，此时， |                 |                |      |
如果处于SmartConfig状态的ATK-MB026模块成功完成一键配网，那么ESP-TOUCH将会
有相应的提示。
手机端APP一键配网的操作，如下图所示：
用户手册                                                                    www.alientek.com

54

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.7.1.1 ESP-TOUCH一键配网操作
8. 开始SmartConfig
在手机端进行一键配网的过程中，ATK-MB026模块须开始SmartConfig，才能够接收到
手机端传来的 AP 信息，进而根据信息连接 AP，实现一键配网。ATK-MB026 模块开始
SmartConfig的AT指令如下所示：
/* 使能ATK-MB026模块的STA模式，以通过一键配网连接AP */
AT+CWMODE=1
/* 开始SmartConfig */
AT+CWSTARTSMART=1
实际在串口调试助手中的操作，如下图所示：
用户手册 www.alientek.com
55

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.7.1.2 ATK-MB026模块使用AT指令一键配网
从上图可以看出，ATK-MB026模块在一键配网的过程中，会获取手机端发送过来的AP
信息，其中就包括AP的SSID和密码，通过AP的SSID和密码就能够连接AP，实现一键
配网。
2.8 固件烧写
ATK-MB026模块须进入下载模式，才能够进行固件的烧写。ATK-MB026模块的“IO_9”
引脚控制ATK-MB026模块的启动模式，具体的说明，如下表所示：
模块上电时IO_9引脚电平 模块启动模式
低电平 下载模式
高电平 运行模式
表2.8.1 ATK-MB026模块启动模式
ATK-MB026模块的固件烧写可以借助PC端的固件烧写软件（flash_download_tool）进
行烧写，在对ATK-MB026模块进行固件烧写前，需要通过USB转TTL将ATK-MB026模
块与PC连接，ATK-MB026模块与USB转TTL的连接示例，如下表所示：
ATK-MB026模块 USB转TTL
VCC VCC（5V）
GND GND
TXD RXD
RXD TXD
RST -
IO_9 GND（使ATK-MB026模块上电后进入下载模式）
表2.8.2 ATK-MB026模块与USB转TTL连接示例
对于上表的连接示例，需要注意以下几点：
用户手册 www.alientek.com
56

ATK-MB026 模块用户手册
WIFI & BLE模块
⚫ 在上表的连接示例中，ATK-MB026 模块由 USB 转 TTL 供电，若用户使用额外的
电源给ATK-MB026模块供电，则需保证ATK-MB026模块与PC共地。
⚫ ATK-MB026模块的RST引脚可以悬空，因为ATK-MB026模块内部已对RST引脚
进行上拉，默认为非复位状态。
⚫ ATK-MB026 模块的 IO_9 需连接至 GND，使 ATK-MB026 模块上电后进入下载模
式，而非运行模式。
连接好ATK-MB026模块后，打开PC端的“flash_download_tool”软件，随后在弹出的
窗口中，选择“chip Type（芯片类型）”为“ESP32C3”、“workMode（工作模式）”为“develop”，
如下图所示：
图2.8.1 烧录软件模式配置
配置好模式并进入软件后，选择待烧录固件的bin文件，并设置好bin文件烧录至芯片
的地址信息和其他的一些信息，即可点击软件左下方的“START”按钮进行固件烧写，如下
图所示：
用户手册 www.alientek.com
57

ATK-MB026 模块用户手册
WIFI & BLE模块
图2.8.2 固件烧录配置
若固件烧录失败，可通过配置软件右下方的串口通讯波特率配置项，适当降低串口通讯
波特率。
用户手册 www.alientek.com
58

ATK-MB026 模块用户手册
WIFI & BLE模块
3，结构尺寸
ATK-MB026模块的尺寸结构，如下图所示：
图3.1 ATK-MB026模块尺寸图
用户手册 www.alientek.com
59

ATK-MB026 模块用户手册
WIFI & BLE模块
4，其他
1、 购买地址：
天猫：https://zhengdianyuanzi.tmall.com
淘宝：https://openedv.taobao.com
2、 资料下载
模块资料下载地址：http://www.openedv.com/docs/modules/iot/atk-esp.html
3、 技术支持
公司网址 ：www.alientek.com
技术论坛 ：http://www.openedv.com/forum.php
在线教学 ：www.yuanzige.com
B站视频 ：https://space.bilibili.com/394620890
传真：020-36773971
电话：020-38271790
用户手册 www.alientek.com
60