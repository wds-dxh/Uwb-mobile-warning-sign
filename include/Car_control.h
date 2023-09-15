#ifndef _CAR_CONTROL_H_
#define _CAR_CONTROL_H_



#include <Arduino.h>
#include <motor.h>


 
#define DELAY_TIME 10  //电机控制延时时间


//小车控制类
class Car_control
{
public:

    void Car_control_init();                                //小车控制初始化
    void Car_forward(uint16_t vel, uint8_t acc);   //前进
    void Car_back(uint16_t vel, uint8_t acc);      //后退
    void Car_right_translation(uint16_t vel, uint8_t acc);  //向右平移
    void Car_left_translation(uint16_t vel, uint8_t acc);   //向左平移
    void Car_right_rotation(uint16_t vel, uint8_t acc);     //向右旋转
    void Car_left_rotation(uint16_t vel, uint8_t acc);      //向左旋转
    void Car_stop();                                        //停止

    


};


#endif