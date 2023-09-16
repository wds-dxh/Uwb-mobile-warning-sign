#ifndef __WIFI_CONTROL_H__
#define __WIFI_CONTROL_H__


#include <Arduino.h>   // Arduino核心库
#include <Car_control.h>         // 小车控制类

#include <WiFi_control.h>        // WiFi控制类




class WIFI_control{
public:
    void WiFi_control_init();    //链接
    void WiFi_control_run();     //运行

};




#endif