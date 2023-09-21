#ifndef __UWB_GET_DISTANCE_H__
#define __UWB_GET_DISTANCE_H__
#include<Arduino.h> 

/**
 * @brief  uwb测距模块控制类
 * @param  None
 * 
*/
class Uwb_get_distance{

private:
    HardwareSerial& serial; //串口对象
    int distance[4]; //存放测距结果的数组


public:
    void Uwb_get_distance_init(HardwareSerial& serial,unsigned long baud);//初始化uwb测距模块
    int Uwb_get_distance_run(int anchor);    //获得uwb测距模块的距离，返回数组，分别为到0123号锚点的距离

};




#endif