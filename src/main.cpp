/**********************************************************
*** uwb移动警示牌
*** 编写作者：wds
**********************************************************/


#include <Arduino.h>
#include "WiFi_control.h"
#include "Car_control.h"

WIFI_control wifi_control;


void setup() {
   
    wifi_control.WiFi_control_init();  // 初始化WIFI
}

void loop() {
   
    wifi_control.WiFi_control_run();     // wifi控制小车运行
    

}