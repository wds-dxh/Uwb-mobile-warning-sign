#ifndef __WIFI_CONTROL_H__
#define __WIFI_CONTROL_H__


#include <Arduino.h>   // Arduino核心库
#include <Car_control.h>         // 小车控制类

#include <WiFi_control.h>        // WiFi控制类




class WIFI_control{
public:
    // void WiFi_control_init(HardwareSerial& Serial_WIFI);    //链接
    void WiFi_control_init();
    void WiFi_control_run();     //运行
    void Rain_control();         //雨滴检测

    void Wifi_data_transmission(int range);//wifi数据传输

};




#endif