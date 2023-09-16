/**********************************************************
*** 雨滴检测驱动
*** 编写作者：wds
*** 邮箱：wdsnpshy@163.com
*** CSDN博客：https://blog.csdn.net/weixin_63211230
*** qq:3412363587
**********************************************************/

#include "Rain_sensor.h"
#include "Arduino.h"

#define Serial_debugging_Rain true    

#define RAIN_ADC 26                     //模拟输入信号
#define RAIND_igital_quantity     27  //开关信号
 
// 初始化电位计输入信号
int adc_value;
bool Rain_sensor_is_rain_flag = false;


/**
 * @brief   雨滴检测模块初始化
 * @param   none
 * @retval  none
*/
void Rain_sensor::Rain_sensor_init() {

   
    #if defined(Serial_debugging_Rain)  
       Serial.begin(115200); // 设置串口通信波特率 9600
    #endif

    pinMode(RAIN_ADC, INPUT);
    pinMode(RAIND_igital_quantity, INPUT);

}


/**
 * @brief   获取雨滴检测模块的值
 * @param   none
 * @retval  none
*/ 
int Rain_sensor::Rain_sensor_get() {
    // 读取电位计模拟输入值
    adc_value = analogRead(RAIN_ADC);
   
    #if defined(Serial_debugging_Rain)  
        // 打印模拟值在串口屏上
        Serial.println(adc_value);
        delay(50);
    #endif
    return adc_value;

    
}

/**
 * @brief   获取雨滴检测模块的值(开关量)
 * @param   none
 * @retval  none
*/ 
bool Rain_sensor::Rain_sensor_is_rain() {
    // 读取电位计模拟输入值
    Rain_sensor_is_rain_flag = digitalRead(RAIND_igital_quantity);
   
    #if defined(Serial_debugging_Rain)  
        // 打印模拟值在串口屏上
        Serial.println(Rain_sensor_is_rain_flag);
        delay(50);
    #endif
    return Rain_sensor_is_rain_flag;

    
}


/**
 * @brief  显示雨滴检测模块的值,开关于模拟量同时显示
 * @param   none
 * @retval  none
*/

void Rain_sensor::show_rain_sensor() {
    // 读取电位计模拟输入值
    adc_value = analogRead(RAIN_ADC);
    Rain_sensor_is_rain_flag = digitalRead(RAIND_igital_quantity);
   
    #if defined(Serial_debugging_Rain)  
        // 打印模拟值在串口屏上
        Serial.print("模拟量：");
        Serial.println(adc_value);
        Serial.print("开关量：");
        Serial.println(Rain_sensor_is_rain_flag);
        delay(50);
    #endif

} 






