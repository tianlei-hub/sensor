|     | ATK-MB026 | 模块使用说明  |     |
| --- | --------- | ------- | --- |

Application
|     | 高性能 WIFI & BLE | 模块  |     |
| --- | -------------- | --- | --- |
Note

使用说明
修订历史
| 版本    | 日期          |        | 原因  |
| ----- | ----------- | ------ | --- |
| V1.0  | 2022/11/20  | 第一次发布  |     |
|       |             |        |     |
|       |             |        |     |

ATK-MB026 模块使用说明
WIFI & BLE模块
目 录
1，硬件连接 .................................................................................................................. 1
2，实验功能 .................................................................................................................. 2
2.1 ATK-MB026模块TCP透传实验 ..................................................................................... 2
2.1.1 功能说明 ................................................................................................................. 2
2.1.2 源码解读 ................................................................................................................. 2
2.1.3 实验现象 ................................................................................................................. 7
2.2 ATK-MB026模块原子云连接实验 ................................................................................. 10
2.2.1 功能说明 ............................................................................................................... 10
2.2.2 源码解读 ............................................................................................................... 10
2.2.3 实验现象 ............................................................................................................... 13
2.3 ATK-MB026模块Bluetooth LE透传实验 ..................................................................... 16
2.3.1 功能说明 ............................................................................................................... 16
2.3.2 源码解读 ............................................................................................................... 16
2.3.3 实验现象 ............................................................................................................... 19
3，其他 ........................................................................................................................ 23
使用说明 www.alientek.com
1

|     |     |     |     | ATK-MB026 | 模块使用说明 |     |
| --- | --- | --- | --- | --------- | ------ | --- |

WIFI & BLE模块
1，硬件连接
| 这里以正点原子 | M48Z-M3 | 最小系统板 | STM32F103 | 版为例，给大家介绍一下模块和板 |     |     |
| ------- | ------- | ----- | --------- | --------------- | --- | --- |
卡的连接方法。其它板卡与模块的硬件连接方法，请大家在“ATK-MB026 WIFI & BLE模
块\3，程序源码相应板卡例程文件夹\readme.txt”路径下查看。
WIFI & BLE模块可通过杜邦线与正点原子M48Z-M3最小系统板STM32F103版进行连
接，具体的连接关系，如下表所示：
| 模块对应开发板       |     |      |      | 连接关系      |      |       |
| ------------- | --- | ---- | ---- | --------- | ---- | ----- |
| WIFI & BLE模块  |     | VCC  | GND  | TXD  RXD  | RST  | IO_9  |
M48Z-M3最小系统板
|     |     | 5V  | GND  | PB11  PB10  | PA4  | -   |
| --- | --- | --- | ---- | ----------- | ---- | --- |
STM32F103版
表1.1.1 WIFI & BLE模块与M48Z-M3最小系统板STM32F103版连接关系
|     |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- |
使用说明                                                                    www.alientek.com

1

ATK-MB026 模块使用说明
WIFI & BLE模块
2，实验功能
2.1 ATK-MB026 模块 TCP 透传实验
2.1.1 功能说明
在本实验中，开发板主控芯片通过串口与ATK-MB026模块进行通讯，并在上电后自动
根据配置信息，配置 ATK-MB026 模块连接 WIFI、TCP 服务器（与 ATK-MB026 模块所连
接 WIFI 在同一局域网的电脑作为 TCP 服务器），成功连接 WIFI 后，将在串口调试助手和
LCD 上显示 ATK-MB026 模块的 IP 地址，随后便可通过按键对 ATK-MB026 模块进行 AT
指令测试和配置其进入或退出透传模式，AT指令测试的测试结果将显示在串口调试助手上，
当模块进入透传模式后，可通过按键发送数据至TCP服务器，同时也可接收来自TCP服务
器的数据，并实时显示在串口调试助手上。
2.1.2 源码解读
打开本实验的工程文件夹，能够在./Drivers/BSP目录下看到ATK_MB026子文件夹，该
文件夹中就包含了ATK-MB026模块的驱动文件，如下图所示：
图2.1.2.1 ATK-MB026模块驱动代码
2.1.2.1 ATK-MB026模块接口驱动
在图2.1.2.1中，atk_mb026_uart.c和atk_mb026_uart.h是开发板与ATK-MB026模块通
讯而使用的 UART 驱动文件，关于 UART 的驱动介绍，请查看正点原子各个开发板对应的
开发指南中UART对应的章节。
值得一提的是，由于ATK-MB026模块通过UART发送给主控芯片的数据的长度是不固
定的，因此主控芯片就无法直接通过接收到数据的长度来判断ATK-MB026模块传来的一帧
数据是否完成。对于这种通过UART接收不定长数据的情况，我们可以通过STM32的UART
提供的总线空闲中断来判断一帧的传输是否完成，并在中断中做相应的处理。但在本例程中
还考虑到其它不具备总线空闲中断的单片机，因此采用了比较通用的超时分包方法，不依赖
于总线空闲中断，而是采用定时器判断超时。具体的实现过程可以查看ATK-MB026模块的
模块接口驱动代码，这里不做过多的描述。
2.1.2.2 ATK-MB026模块驱动
在图2.1.2.1 中，atk_mb026.c和 atk_mb026.h 是ATK-MB026 模块的驱动文件，包含了
ATK-MB026 模块初始化、硬件复位、发送 AT 指令的相关 API 函数和部分 AT 指令的封装
函数。函数比较多，下面仅介绍几个重要的API函数。
1. 函数atk_mb026_init()
该函数用于初始化ATK-MB026模块，具体的代码，如下所示：
/**
使用说明 www.alientek.com
2

ATK-MB026 模块使用说明
WIFI & BLE模块
* @brief ATK_MB026初始化
* @param baudrate: ATK_MB026 UART通讯波特率
* @retval ATK_MB026_EOK : ATK_MB026初始化成功，函数执行成功
* ATK_MB026_ERROR : ATK_MB026初始化失败，函数执行失败
*/
uint8_t atk_mb026_init(uint32_t baudrate)
{
atk_mb026_hw_init(); /* ATK_MB026硬件初始化 */
atk_mb026_hw_reset(); /* ATK_MB026硬件复位 */
atk_mb026_uart_init(baudrate); /* ATK_MB026 UART初始化 */
if (atk_mb026_at_test() != ATK_MB026_EOK) /* ATK_MB026 AT指令测试 */
{
return ATK_MB026_ERROR;
}
return ATK_MB026_EOK;
}
从上面的代码中可以看出，函数 atk_mb026_init()会对 ATK-MB026 模块进行硬件复位
（拉低ATK-MB026模块的RST引脚，随后拉高），然后初始化主控芯片与ATK-MB026模
块的 UART，最后进行 AT 指令测试，若 AT 指令测试成功，则说明 ATK-MB026 模块及其
通讯接口初始化成功，反之，则初始化失败。
2. 函数atk_mb026_at_test()
该函数用于对 ATK-MB026 模块进行 AT 指令测试，可以由此判断主控与 ATK-MB026
模块的通讯是否无误，具体的代码，如下所示：
/**
* @brief ATK_MB026 AT指令测试
* @param 无
* @retval ATK_MB026_EOK : AT指令测试成功
* ATK_MB026_ERROR: AT指令测试失败
*/
uint8_t atk_mb026_at_test(void)
{
uint8_t ret;
uint8_t i;
for (i=0; i<10; i++)
{
ret = atk_mb026_send_at_cmd("AT", "OK", 500);
if (ret == ATK_MB026_EOK)
{
return ATK_MB026_EOK;
}
}
return ATK_MB026_ERROR;
使用说明 www.alientek.com
3

|     |     |     |     | ATK-MB026 | 模块使用说明 |     |
| --- | --- | --- | --- | --------- | ------ | --- |

WIFI & BLE模块
}
| 从上面的代码中可以看出，该函数会通过 |                                                 |     | UART | 向 ATK-MB026 | 模块发送“AT”字符 |     |
| ------------------ | ----------------------------------------------- | --- | ---- | ----------- | ---------- | --- |
| 串（函数               | atk_mb026_send_at_cmd()会根据通讯规则在字符串末尾添加换行符，通讯规则见 |     |      |             |            |     |
《ATK-MB026 WIFI & BLE模块用户手册》），并在一段时间内等待ATK-MB026模块的“OK”
响应，如果收到ATK-MB026模块的“OK”响应，说明主控芯片与ATK-MB026模块的UART
通讯正常，AT指令测试成功，反之，则说明AT指令测试失败，主控芯片不能与ATK-MB026
模块进行正常的通讯。
3. 函数atk_mb026_send_at_cmd()
该函数主要实现主控芯片与ATK-MB026模块的AT指令传输，本驱动代码中的大部分
驱动函数都是基于该函数实现的，但由于ATK-MB026的AT指令众多，在驱动代码中无法
一一实验，因此在使用ATK-MB026模块的时候，可以根据《ATK-MB026 WIFI & BLE模块
| 用户手册》中列出的 |     | AT 指令，并参考驱动文件中的驱动函数 |         |         |         | ，对函数      |
| --------- | --- | ------------------- | ------- | ------- | ------- | --------- |
|           |     | 进 行 简               | 单 的 封 装 | ， 即 可 实 | 现 相 应 的 | 功 能 。 函 数 |
atk_mb026_send_at_cmd()
atk_mb026_send_at_cmd()的具体代码，如下所示：
/**
|  * @brief   | ATK-MB026发送AT指令   |             |           |     |     |     |
| ----------- | ----------------- | ----------- | --------- | --- | --- | --- |
|  * @param   | cmd               | : 待发送的AT指令  |           |     |     |     |
|  *          | ack               | : 等待的响应     |           |     |     |     |
|  *          | timeout : 等待超时时间  |             |           |     |     |     |
|  * @retval  | ATK_MB026_EOK     |             | : 函数执行成功  |     |     |     |
ATK_MB026_ETIMEOUT : 等待期望应答超时，函数执行失败
|  *      |     |     |     |     |     |     |
| ------- | --- | --- | --- | --- | --- | --- |
 */
uint8_t atk_mb026_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;

    atk_mb026_uart_rx_restart();
    atk_mb026_uart_printf("%s\r\n", cmd);

    if ((ack == NULL) || (timeout == 0))
    {
|        return ATK_MB026_EOK;  |     |     |     |     |     |     |
| ----------------------------- | --- | --- | --- | --- | --- | --- |
    }
    else
    {
|        while (timeout > 0)  |                                                |                        |     |     |     |     |
| --------------------------- | ---------------------------------------------- | ---------------------- | --- | --- | --- | --- |
|        {                    |                                                |                        |     |     |     |     |
|                             | ret = atk_mb026_uart_rx_get_frame();           |                        |     |     |     |     |
|                             | if (ret != NULL)                               |                        |     |     |     |     |
|                             | {                                              |                        |     |     |     |     |
|                             |   if (strstr((const char *)ret, ack) != NULL)  |                        |     |     |     |     |
|                             |   {                                            |                        |     |     |     |     |
|                             |                                                | return ATK_MB026_EOK;  |     |     |     |     |
|                             |   }                                            |                        |     |     |     |     |
使用说明                                                                    www.alientek.com

4

ATK-MB026 模块使用说明
WIFI & BLE模块
else
{
atk_mb026_uart_rx_restart();
}
}
timeout--;
delay_ms(1);
}
return ATK_MB026_ETIMEOUT;
}
}
从上面的代码中可以看出，函数atk_mb026_send_at_cmd()函数会将待发送的AT指令加
上换行符后通过UART发送至ATK-MB026模块，随后等待ATK-MB026模块的响应，并判
断响应中是否包含期望等待的响应，如果有，则说明本次AT指令传输成功。
2.1.2.3 实验测试代码
实验的测试代码为文件demo.c，在工程目录下的User子目录中。测试代码的入口函数
为demo_run()，具体的代码，如下所示：
/**
* @brief 例程演示入口函数
* @param 无
* @retval 无
*/
void demo_run(void)
{
uint8_t ret;
char ip_buf[16];
uint8_t key;
uint8_t is_unvarnished = 0;
/* 初始化ATK-MB026 */
ret = atk_mb026_init(115200);
if (ret != 0)
{
printf("ATK-MB026 init failed!\r\n");
while (1)
{
LED0_TOGGLE();
delay_ms(200);
}
}
printf("Joining to AP...\r\n");
ret = atk_mb026_restore(); /* 恢复出厂设置 */
delay_ms(1000);
ret += atk_mb026_at_test(); /* AT测试 */
使用说明 www.alientek.com
5

ATK-MB026 模块使用说明
WIFI & BLE模块
ret += atk_mb026_set_mode(1); /* Station模式 */
ret += atk_mb026_sw_reset(); /* 软件复位 */
delay_ms(500);
ret += atk_mb026_ate_config(0); /* 关闭回显功能 */
ret += atk_mb026_join_ap(DEMO_WIFI_SSID, DEMO_WIFI_PWD);/* 连接WIFI */
ret += atk_mb026_get_ip(ip_buf); /* 获取IP地址 */
if (ret != 0)
{
printf("Error to join ap!\r\n");
while (1)
{
LED0_TOGGLE();
delay_ms(200);
}
}
demo_show_ip(ip_buf);
/* 连接TCP服务器 */
ret = atk_mb026_connect_tcp_server(DEMO_TCP_SERVER_IP,
DEMO_TCP_SERVER_PORT);
if (ret != 0)
{
printf("Error to connect tcp server!\r\n");
while (1)
{
LED0_TOGGLE();
delay_ms(200);
}
}
/* 重新开始接收新的一帧数据 */
atk_mb026_uart_rx_restart();
while (1)
{
key = key_scan(0);
switch (key)
{
case KEY0_PRES:
{
/* 功能测试 */
demo_key0_fun(is_unvarnished);
break;
}
使用说明 www.alientek.com
6

ATK-MB026 模块使用说明
WIFI & BLE模块
case WKUP_PRES:
{
/* 透传模式切换 */
demo_keywkup_fun(&is_unvarnished);
break;
}
default:
{
break;
}
}
/* 发送透传接收自TCP Server的数据到串口调试助手 */
demo_upload_data(is_unvarnished);
delay_ms(10);
}
}
从上面的代码中可以看出，整个测试代码的逻辑还是比较简单的。但要注意的是，函数
demo_run()首先会配置 ATK-MB026 模块连接 WIFI和 TCP 服务器，其中 WIFI 的名称和密
码、TCP服务器的地址和端口均在demo.c文件中通过宏的方式定义，具体的代码，如下所
示：
#define DEMO_WIFI_SSID "ALIENTEK-YF"
#define DEMO_WIFI_PWD "15902020353"
#define DEMO_TCP_SERVER_IP "192.168.2.33"
#define DEMO_TCP_SERVER_PORT "8080"
在完成本实验的时候，需要根据具体的情况对这四个宏定义进行配置，才能顺利地完成
本实验。
2.1.3 实验现象
将ATK-MB026模块按照第一节“硬件连接”中介绍的连接方式与开发板连接，并将实
验代码编译烧录至开发板中，如果此时开发板连接 OLED，那么 OLED 显示的内容，如下
图所示：
图2.1.3.1 OLED显示内容一
同时，通过串口调试助手输出实验信息，如下图所示：
使用说明 www.alientek.com
7

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.1.3.2 串口调试助手显示内容一
接下来，程序会初始化ATK-MB026模块并自动配置连接WIFI和TCP服务器，因此在
此之前，需要先打开网络调试助手，设置好TCP服务器IP和款口号，并开启TCP服务器连
接，否则 ATK-MB026 模块将无法成功连接 TCP 服务器，网络调试助手的设置界面，如下
图所示：
图2.1.3.3 网络调试助手设置
如果ATK-MB026模块成功连接上WIFI和TCP服务器，便会在OLED和串口调试助手
上显示ATK-MB026的IP地址，方便网络调试助手确认TCP客户端的IP地址，OLED和串
口调试助手显示的IP地址，如下图所示：
图2.1.3.4 OLED显示内容二
使用说明 www.alientek.com
8

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.1.3.5 串口调试助手显示内容二
当ATK-MB026成功连接WIFI和TCP服务器后，就能够通过开发板上的按键来进行本
实验的操作了。
在默认没有进入透传的模式下，按下按键 0，会对 ATK-MB026 进行 AT 指令测试，测
试的结果会通过串口调试助手输出，如下图所示：
图2.1.3.6 串口调试助手显示内容三
如果AT指令测试成功，那么说明开发板与ATK-MB026模块的通讯正常，那么接下来
可以按下按键WKUP，配置ATK-MB026进入透传模式，在透传模式下，开发板上主控芯片
通过UART 发送给 ATK-MB026 模块的数据，会原封不动地通过网络发送给 TCP 服务器，
同样的，TCP服务器通过网络发送给ATK-MB026模块的数据，也会原封不动地通过UART
发送给开发板上的主控芯片。
接下来按下按键0，发送数据给ATK-MB026模块，此时，便可以在网络调试助手上看
到，ATK-MB026模块发送过来的消息，如下图所示：
使用说明 www.alientek.com
9

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.1.3.7 网络调试助手显示内容
这时通过网络助手发送消息给ATK-MB026模块，那么ATK-MB026模块就会将接收到
的数据通过 UART 发送给开发板上的主控芯片，为了观察实验现象，本实验将接收到的信
息打印在串口调试助手上，如下图所示：
图2.1.3.8 串口调试助手显示内容四
2.2 ATK-MB026 模块原子云连接实验
2.2.1 功能说明
在本实验中，开发板主控芯片通过串口与ATK-MB026模块进行通讯，并在上电后自动
根据配置信息，配置ATK-MB026模块连接WIFI，成功连接WIFI后，将在串口调试助手和
OLED上显示ATK-MB026模块的IP地址，随后便可通过按键对ATK-MB026模块进行AT
指令测试和连接原子云服务器（原子云服务器的连接方式，请见《ATK-MB026 WIFI & BLE
模块用户手册》，在本实验中不再进行过多的描述），AT 指令测试的测试结果将显示在串口
调试助手上，当模块成功连接原子云后，可通过按键发送数据至原子云服务器，同时也可接
收来自原子云服务器的数据，并实时显示在串口调试助手上。
2.2.2 源码解读
2.2.2.1 ATK-MB026模块接口驱动
本实验中，ATK-MB026 模块接口的驱动代码与 2.1 小节中“ATK-MB026 模块 TCP 透
使用说明 www.alientek.com
10

ATK-MB026 模块使用说明
WIFI & BLE模块
传实验”中的接口驱动代码一致，请见第2.1.2.1小节“ATK-MB026模块接口驱动”。
2.2.2.2 ATK-MB026模块驱动
本实验中，ATK-MB026 模块的驱动代码与 2.1 小节中“ATK-MB026 模块 TCP 透传实
验”中的驱动代码一致，请见第2.1.2.2小节“ATK-MB026模块驱动”。
2.2.2.3 实验测试代码
实验的测试代码为文件demo.c，在工程目录下的User子目录中。测试代码的入口函数
为demo_run()，具体的代码，如下所示：
/**
* @brief 例程演示入口函数
* @param 无
* @retval 无
*/
void demo_run(void)
{
uint8_t ret;
char ip_buf[16];
uint8_t key;
uint8_t is_atkcld = 0;
/* 初始化ATK-MB026 */
ret = atk_mb026_init(115200);
if (ret != 0)
{
printf("ATK-MB026 init failed!\r\n");
while (1)
{
LED0_TOGGLE();
delay_ms(200);
}
}
printf("Joining to AP...\r\n");
ret = atk_mb026_restore(); /* 恢复出厂设置 */
delay_ms(1000);
ret += atk_mb026_at_test(); /* AT测试 */
ret += atk_mb026_set_mode(1); /* Station模式 */
ret += atk_mb026_sw_reset(); /* 软件复位 */
delay_ms(500);
ret += atk_mb026_ate_config(0); /* 关闭回显功能 */
ret += atk_mb026_join_ap(DEMO_WIFI_SSID, DEMO_WIFI_PWD); /* 连接WIFI */
ret += atk_mb026_get_ip(ip_buf); /* 获取IP地址 */
if (ret != 0)
{
使用说明 www.alientek.com
11

ATK-MB026 模块使用说明
WIFI & BLE模块
printf("Error to join ap!\r\n");
while (1)
{
LED0_TOGGLE();
delay_ms(200);
}
}
demo_show_ip(ip_buf);
/* 重新开始接收新的一帧数据 */
atk_mb026_uart_rx_restart();
while (1)
{
key = key_scan(0);
switch (key)
{
case KEY0_PRES:
{
/* 功能测试 */
demo_key0_fun(is_atkcld);
break;
}
case WKUP_PRES:
{
/* 透传模式切换 */
demo_keywkup_fun(&is_atkcld);
break;
}
default:
{
break;
}
}
/* 发送透传接收自TCP Server的数据到串口调试助手 */
demo_upload_data(is_atkcld);
delay_ms(10);
}
}
从上面的代码中可以看出，整个测试代码的逻辑还是比较简单的。但要主要的是，函数
demo_run()首先会配置ATK-MB026模块连接WIFI和原子云服务器，其中WIFI的名称和密
码、原子云服务器设备的ID和密码均在demo.c文件中通过宏的方式定义，具体的代码，如
下所示：
#define DEMO_WIFI_SSID "ALIENTEK-YF"
使用说明 www.alientek.com
12

ATK-MB026 模块使用说明
WIFI & BLE模块
#define DEMO_WIFI_PWD "15902020353"
#define DEMO_ATKCLD_DEV_ID "86112558784372656615"
#define DEMO_ATKCLD_DEV_PWD "12345678"
在完成本实验的时候，需要根据具体的情况对这四个宏定义进行配置，才能顺利地完成
本实验。
值得一提的是，该例程也能适配新版的原子云，只需要修改上述宏定义中的设备ID和
设备密码，即“DEMO_ATKCLD_DEV_ID”以及“DEMO_ATKCLD_DEV_PWD”，这两部
分的内容在新版原子云的设备列表中。具体的配置方法请参考《ATK-MB026 WIFI & BLE
模块用户手册》。
2.2.3 实验现象
将ATK-MB026模块按照第一节“硬件连接”中介绍的连接方式与开发板连接，并将实
验代码编译烧录至开发板中，如果此时开发板连接 OLED，那么 OLED 显示的内容，如下
图所示：
图2.2.3.1 OLED显示内容一
同时，通过串口调试助手输出实验信息，如下图所示：
图2.2.3.2 串口调试助手显示内容一
接下来，程序会初始化 ATK-MB026 模块并自动配置连接 WIFI，如果 ATK-MB026 模
块成功连接上WIFI，便会在OLED和串口调试助手上显示ATK-MB026的IP地址，OLED
和串口调试助手显示的IP地址，如下图所示：
使用说明 www.alientek.com
13

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.2.3.3 OLED显示内容二
图2.2.3.4 串口调试助手显示内容二
当ATK-MB026成功连接WIFI后，就能通过开发板上的按键来进行本实验的操作了。
在默认没有连接原子云的模式下，按下按键 0，会对 ATK-MB026 进行 AT 指令测试，
测试的结果会通过串口调试助手输出，如下图所示：
图2.2.3.5 串口调试助手显示内容三
使用说明 www.alientek.com
14

ATK-MB026 模块使用说明
WIFI & BLE模块
如果AT指令测试成功，那么说明开发板与ATK-MB026模块的通讯正常，那么接下来
可以按下按键WKUP，配置ATK-MB026连接原子云，因为要连接原子云服务器，因此在此
之前，需要在原子云上创建好设备，具体的创建过程，请见《ATK-MB026模块使用说明》，
否则ATK-MB026模块将无法成功连接原子云服务器，成功连接原子云服务器后，就能够在
原子云的网页中开到设备的状态为“已连接”，如下图所示：
图2.2.3.6 原子云网页设备状态
接下来按下按键0，发送数据给ATK-MB026模块，此时，便可以在原子云网页中的“消
息收发”界面中查看到ATK-MB026模块发送过来的消息，如下图所示：
图2.2.3.7 原子云网页设备“消息收发”界面
这时通过原子云网页设备的“消息收发”界面发送消息给 ATK-MB026 模块，那么
ATK-MB026模块就会将接收到的数据通过UART发送给开发板上的主控芯片，为了观察实
验现象，本实验将接收到的信息打印在串口调试助手上，如下图所示：
使用说明 www.alientek.com
15

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.2.3.8 串口调试助手显示内容四
新版原子云的实验步骤与上述内容基本一致，笔者在此不再赘述。具体的配置方法请参
考《ATK-MB026 WIFI & BLE模块用户手册》。
2.3 ATK-MB026 模块 Bluetooth LE 透传实验
2.3.1 功能说明
在本实验中，开发板主控芯片通过串口与ATK-MB026模块进行通讯，并在上电后自动
根据配置信息，配置 ATK-MB026 模块（作为服务端）连接蓝牙主设备（作为客户端），成
功连接主设备后，将在串口调试助手和OLED上显示ATK-MB026模块的蓝牙地址，随后便
可通过按键对ATK-MB026模块进行AT指令测试和连接主设备（主设备的连接方式，请见
《ATK-MB026 WIFI & BLE模块用户手册》，在本实验中不再进行过多的描述），AT指令测
试的测试结果将显示在串口调试助手上，当模块成功连接主设备后，可通过按键发送数据到
主设备上，主设备也同样可以发送数据到模块上，并实时显示在串口调试助手上。
2.3.2 源码解读
2.3.2.1 ATK-MB026模块接口驱动
本实验中，ATK-MB026 模块接口的驱动代码与 2.1 小节中“ATK-MB026 模块 TCP 透
传实验”中的接口驱动代码一致，请见第2.1.2.1小节“ATK-MB026模块接口驱动”。
2.3.2.2 ATK-MB026模块驱动
本实验中，ATK-MB026 模块的驱动代码与 2.1 小节中“ATK-MB026 模块 TCP 透传实
验”中的驱动代码一致，请见第2.1.2.2小节“ATK-MB026模块驱动”。
2.3.2.3 实验测试代码
实验的测试代码为文件demo.c，在工程目录下的User子目录中。测试代码的入口函数
为demo_run()，具体的代码，如下所示：
/**
* @brief 例程演示入口函数
* @param 无
使用说明 www.alientek.com
16

ATK-MB026 模块使用说明
WIFI & BLE模块
* @retval 无
*/
void demo_run(void)
{
uint8_t ret;
char ble_buf[30];
uint8_t key;
uint8_t *recv_dat;
uint8_t is_unvarnished = 0;
/* 初始化ATK-MB026 */
ret = atk_mb026_init(115200);
if (ret != 0)
{
printf("ATK-MB026 init failed!\r\n");
while (1)
{
LED0_TOGGLE();
delay_ms(200);
}
}
printf("Joining to BLE...\r\n");
ret = atk_mb026_restore(); /* 恢复出厂设置 */
delay_ms(1000); /* 添加延时，等待响应 */
ret += atk_mb026_at_test(); /* AT测试 */
atk_mb026_ble_init(3); /* ATK_MB026 Bluetooth LE初始化 */
ret += atk_mb026_ble_gatts(); /* GATTS创建服务 */
ret += atk_mb026_ble_gattssrvstart(); /* GATTS开启全部服务 */
/* 设置广播设备名称 */
ret += atk_mb026_set_advdataex(DEMO_BLE_NAME,
DEMO_BLE_UUID,
DEMO_BLE_DATA, DEMO_BLE_POWER);
ret += atk_mb026_ate_config(0); /* 关闭回显功能 */
ret += atk_mb026_get_addr(ble_buf); /* 获取BLE地址 */
ret += atk_mb026_advstart(); /* 开启设备广播 */
/* 设置Bluetooth LE SPP参数 */
ret += atk_mb026_set_sppcfg(1,1,7,1,5,1);
if (ret != 0)
{
printf("ATK-MB026 config failed!\r\n");
while (1)
{
使用说明 www.alientek.com
17

ATK-MB026 模块使用说明
WIFI & BLE模块
LED0_TOGGLE();
delay_ms(200);
}
}
demo_show_ip(ble_buf);
/* 重新开始接收新的一帧数据 */
atk_mb026_uart_rx_restart();
while (1)
{
key = key_scan(0);
switch (key)
{
case KEY0_PRES:
{
/* 功能测试 */
demo_key0_fun(is_unvarnished);
break;
}
case WKUP_PRES:
{
/* BLE透传模式切换 */
demo_keywkup_fun(&is_unvarnished);
break;
}
default:
{
break;
}
}
recv_dat = atk_mb026_uart_rx_get_frame();
if (recv_dat != NULL)
{
printf("%s", recv_dat);
atk_mb026_uart_rx_restart();
}
delay_ms(10);
}
}
从上面的代码中可以看出，整个测试代码的逻辑还是比较简单的。但要主要的是，函数
使用说明 www.alientek.com
18

ATK-MB026 模块使用说明
WIFI & BLE模块
demo_run()首先会配置ATK-MB026模块，让模块处于广播状态，方便主设备进行搜索，其
中蓝牙设备名称、设备的服务特征 UUID 等参数均在 demo.c文件中通过宏的方式定义，具
体的代码，如下所示：
#define DEMO_BLE_NAME "ATK-MB026" /* 蓝牙名称 */
#define DEMO_BLE_UUID "A002" /* 服务特征UUID */
#define DEMO_BLE_DATA "0102030405" /* 制造商数据 */
#define DEMO_BLE_POWER 1 /* 包含TX功率 */
在完成本实验的时候，需要根据具体的情况对这四个宏定义进行配置，才能顺利地完成
本实验。具体的配置方法请参考《ATK-MB026 WIFI & BLE模块用户手册》。
2.3.3 实验现象
将ATK-MB026模块按照第一节“硬件连接”中介绍的连接方式与开发板连接，并将实
验代码编译烧录至开发板中，如果此时开发板连接 OLED，那么 OLED 显示的内容，如下
图所示：
图2.3.3.1 OLED显示内容一
同时，通过串口调试助手输出实验信息，如下图所示：
图2.3.3.2 串口调试助手显示内容一
接下来，程序会初始化 ATK-MB026 模块并自动配置连接 WIFI，如果 ATK-MB026 模
块配置成功，便会在OLED和串口调试助手上显示ATK-MB026的蓝牙地址，OLED和串口
调试助手显示的蓝牙地址，如下图所示：
使用说明 www.alientek.com
19

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.3.3.3 OLED显示内容二
图2.3.3.4 串口调试助手显示内容二
当ATK-MB026配置完，设备便处于广播状态，此时可以通过主设备进行搜索模块，从
而实现模块（服务端）与主设备（客户端）之间的连接，最终通过开发板上的按键来进行本
实验的操作，以下是两个设备连接成功的实验现象，模块（服务端）通过串口助手打印出主
设备（客户端）的蓝牙地址等信息，如下所示：
图2.3.3.5 串口调试助手显示内容三
在默认没有连接主设备的模式下，按下按键 0，会对 ATK-MB026 进行 AT 指令测试，
测试的结果会通过串口调试助手输出，如下图所示：
使用说明 www.alientek.com
20

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.3.3.6 串口调试助手显示内容四
如果AT指令测试成功，那么说明开发板与ATK-MB026模块的通讯正常，那么接下来
只要连接上可以按下按键WKUP，进入透传模式，因为需要在两个模块之间建立透传通信，
因此在此之前，也需要对主设备进行相应的配置，具体的创建过程，请见《ATK-MB026 WIFI
& BLE模块用户手册》，否则ATK-MB026模块将无法成功与主设备之间建立透传，成功连
接主设备后，就能够在两个模块之间互发数据了，如下图所示：
图2.3.3.7 主设备与模块进入透传模式成功
接下来按下按键0，发送数据给ATK-MB026模块，此时，便可以在连接主设备的串口
助手中查看到ATK-MB026模块发送过来的消息，如下图所示：
图2.3.3.8 串口调试助手显示内容五
这时通过该串口助手发送消息给ATK-MB026模块，那么ATK-MB026模块就会将接收
到的数据通过 UART 发送给开发板上的主控芯片，为了观察实验现象，本实验将接收到的
信息打印在串口调试助手上，如下图所示：
使用说明 www.alientek.com
21

ATK-MB026 模块使用说明
WIFI & BLE模块
图2.3.3.9 串口调试助手显示内容六
使用说明 www.alientek.com
22

ATK-MB026 模块使用说明
WIFI & BLE模块
3，其他
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
使用说明 www.alientek.com
23