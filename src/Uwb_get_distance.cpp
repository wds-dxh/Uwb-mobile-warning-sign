/**
 * @file uwb测距模块控制类
 * @author wds
 * @date 2023/9/21
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
 */

#include<Arduino.h>
#include "Uwb_get_distance.h"
char type;
int mask, range_return[4],lnum, seq, tid, aid;
int range[4] = {0};
int rangetime;

/**
 * @brief 初始化uwb测距模块
 * @param serial 串口对象
 * @return None
*/
void Uwb_get_distance::Uwb_get_distance_init(HardwareSerial& Serial_WIFI,unsigned long baud){

        Serial_WIFI.begin(baud);

}

/**
 * @brief 获得uwb测距模块的距离，返回数组，分别为到0123号锚点的距离
 * @param anchor 锚点号0-3
 * @return int* 返回数组，分别为到0123号锚点的距离
*/
void Uwb_get_distance::Uwb_get_distance_run(){


    if (Serial2.available()) 
  {

    String data = Serial2.readStringUntil('\n');  // 从串口读取一行数据，直到遇到换行符

    if (data.startsWith("m")) {
    
      sscanf(data.c_str(), "m%c %x %x %x %x %x %x %x %x %*c%d:%d", &type, &mask, 
      &range[0], &range[1], &range[2], &range[3], &lnum, &seq, &rangetime, &tid, &aid);

    //   for (int i = 0; i < 4; i++)  //将测距结果存放到数组中，返回
    //   {
    //     range[i]=range[i];
    //   }
    //     return range_return;
        // return range[anchor];


    }
  }

}

