#ifndef __SYS_H
#define __SYS_H	

#include "stm32f10x.h"//固件包头文件
#include "bsp_config.h"
#include "./delay/delay.h"//内核SysTick														    

#include "stdio.h"      
#include "stdarg.h"//keil提供编译器
#include "string.h"

#include "math.h"

#include "main.h"
#include "./menu/menu.h"		//OLED显示
#include "./time/time2.h"		// 定时器驱动
#include "./my_usart/my_usart2.h"//usart2驱动
#include "./flash/BridgeFlash.h"//Flash驱动

#include "./key/key.h"			//KEY驱动
#include "./led/led.h"			//LED驱动
#include "./oled/bsp_oled_iic.h"//oled驱动
#include "./oled/oledFont.h"	//字体库
#include "./beep/bsp_beep.h"	//beep驱动
#include "./relay/relay.h"		//RELAY驱动
#include "./adc/adc.h"			//adc驱动
#include "./illumination/illumination.h"//光照算法
#include "./dht11/DHT11.h"		//DHT11驱动
#include "./mqttwifi/esp8266_drv.h"//esp8266驱动
#include "./mqttwifi/mqtt_drv.h"//mqtt驱动



/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i)   {p->ODR ^=i;} 	 //输出反转状态

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
 
//IO口操作,只对单一的IO口!

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

//传感器数据结构体
typedef struct
{
	uint8_t TempVal;//温度
    float SoilVal;//土壤湿度
	uint16_t LightVal;//光照强度
}SENSOR;

//阈值数据结构体
typedef struct
{
	uint8_t TempThreshold;//温度阈值
    uint8_t SoilThreshold;//土壤湿度阈值
	uint16_t LightThreshold;//光照阈值
}THRESHOLD;

//系统标志位结构体
typedef struct
{
	uint8_t mqttflag;//MQTT消息发布标志
    uint8_t Switch1;//继电器-风扇标志位
	uint8_t Switch2;//继电器-水泵标志位
	uint8_t Switch3;//灯光标志位
	uint8_t Switch4;//报警标志位
}SYSTEM;


extern THRESHOLD Threshold;//定义阈值结构体
extern SENSOR SensorData;//定义传感器结构体
extern SYSTEM System;//定义系统标志位结构体

void NVIC_Config(void);

#endif
