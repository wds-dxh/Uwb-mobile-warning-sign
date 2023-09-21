/**
 * @file ws2812b控制程序
 * @author wds
 * @date 2023/9/14
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
 */

//注意灯光和测试的引脚都是GPIO2

#include <Arduino.h>
#include "WiFi_control.h" //wifi控制小车运行
#include "Voice_prompt.h"  //语音提示模块
#include "Mpu6050.h"  //陀螺仪模块  
#include "Rain_sensor.h" //雨滴检测模块
#include "Color_light_control.h" //灯光控制模块
#include "Uwb_get_distance.h" //uwb测距模块

#include <soc/soc.h> 
#include <soc/rtc_cntl_reg.h>  //关闭低电压检测,避免无限重启



#define USE_MULTCORE  1 //使用多核心

WIFI_control wifi_control;
Color_light_control color_light_control;




void Xcontrol_wifi(void *parameter) ;
void Xothers(void *parameter) ;


void setup() {

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);//关闭低电压检测,避免无限重启

  //  HardwareSerial& Serial_WIFI = Serial; //声明一个串口对象
  //   wifi_control.WiFi_control_init(Serial_WIFI);  // 初始化WIFI
    wifi_control.WiFi_control_init();  // 初始化WIFI 
    delay(1000);



#if !USE_MULTCORE //

  xTaskCreate(
    Xcontrol_wifi,   /* Task function. */
    "TaskOne", /* String with name of task. */
    10000,     /* Stack size in bytes. */
    NULL,      /* Parameter passed as input of the task */
    1,         /* Priority of the task. */
    NULL);     /* Task handle. */
 
  xTaskCreate(
    Xothers,   /* Task function. */
    "TaskTwo", /* String with name of task. */
    10000,     /* Stack size in bytes. */
    NULL,      /* Parameter passed as input of the task */
    1,         /* Priority of the task. */
    NULL);     /* Task handle. */

#else
     
    xTaskCreatePinnedToCore(Xcontrol_wifi, "TaskOne", 15000, NULL, 2, NULL, 0);  //Xcontrol_wifi在 0核心
    xTaskCreatePinnedToCore(Xothers, "TaskTwo", 4096, NULL, 1, NULL, 1);  //Xothers在 1核心

#endif
}


void Xcontrol_wifi(void *pvParameters)//执行初始的运行到固定距离的任务
 
{

  
    while (1)
    {
      wifi_control.WiFi_control_run();     // wifi控制小车运行
   
    }
   vTaskDelete(NULL);  

}
 
void Xothers(void *pvParameters) 
{
  for (int i = 0; i < 3; i++)
  {
 
    Serial.println("Hello from task 2");
 
    delay(1000);
  }
 
  Serial.println("Ending task 2");


  vTaskDelete(NULL);


}

void loop() {
//测试用
   
}