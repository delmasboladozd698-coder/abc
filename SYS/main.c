#include "sys.h"

SENSOR SensorData;//传感器结构体定义
THRESHOLD Threshold;//阈值结构体定义
SYSTEM System;//系统标志位结构体定义

int main(void)
{
    delay_init();		//延时函数初始化
    NVIC_Config();		//中断优先级配置
    BdgFlashInit();		//flash初始化包含阈值参数初始化
    My_USART2();		//初始化串口2，用于esp8266通信
    WIFI_RESET_init();	//ESP8266复位引脚初始化
    Ali_MsessageInit();	//服务器连接相关的变量初始化
    KEY_Init();			//按键初始化
    LED_GPIO_Config();	//LED初始化
    oled_Init();		//oled初始化
	  RELAY_GPIO_Config();
    TIM2_Init(499, 7199); //定时器2初始化 定时扫描按键
    Adc_Init();			//ADC初始化
    DHT11_Init();		//DHT11初始化
    oled_Clear();		//清屏

    /*******************************************/
    while (1) {
        ESP8266_run_handle();//连接MQTT服务器并与之通信
        DHT11_Read_TempAndHumidity(&dht11Data); //获取温湿度;

        if (dht11Data.isvalid) {
            SensorData.TempVal = dht11Data.temp_int;
        }

        SensorData.LightVal = (int)R_to_Lux(Get_Adc_Average(0, 10)); //获取光照强度;
        float adc_val = (float)Get_Adc_Average(5, 10);
        float soil_hum = 159.222f - 0.09042f * adc_val;
        if(soil_hum > 100.0f) soil_hum = 100.0f;
        if(soil_hum < 0.0f) soil_hum = 0.0f;
        SensorData.SoilVal = soil_hum;//获取土壤湿度;
        Mode_selection();//模式选择（按键1选择模式）
        save_Threshold();//当阈值数据有改变是存入flash函数
    }
}


