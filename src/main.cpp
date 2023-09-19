/**
 * @file ws2812b控制程序
 * @author wds
 * @date 2023/9/14
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
 */
*/


#include <Arduino.h>
#include "WiFi_control.h" //wifi控制小车运行
#include "Voice_prompt.h"  //语音提示模块
#include "Mpu6050.h"  //陀螺仪模块  
#include "Rain_sensor.h" //雨滴检测模块
#include "Color_light_control.h" //灯光控制模块

WIFI_control wifi_control;


void setup() {
   
    wifi_control.WiFi_control_init();  // 初始化WIFI
}

void loop() {
   
    wifi_control.WiFi_control_run();     // wifi控制小车运行
    delay(500);

}

