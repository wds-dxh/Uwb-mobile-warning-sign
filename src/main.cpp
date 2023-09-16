/**********************************************************
*** uwb移动警示牌
*** 编写作者：wds
**********************************************************/


#include <Arduino.h>
#include "WiFi_control.h" //wifi控制小车运行
#include "Voice_prompt.h"  //语音提示模块
#include "Mpu6050.h"  //陀螺仪模块  
#include "Rain_sensor.h" //雨滴检测模块

WIFI_control wifi_control;


void setup() {
   
    wifi_control.WiFi_control_init();  // 初始化WIFI
}

void loop() {
   
    wifi_control.WiFi_control_run();     // wifi控制小车运行
    

}