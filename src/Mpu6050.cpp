/**
 * @file 陀螺仪模块类
 * @author wds
 * @date 2023/9/14
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
*/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>  //包含数学函数,进行陀螺仪数据处理

#include "Mpu6050.h"  //包含头文件

Adafruit_MPU6050 mpu;



/**
 * @brief   陀螺仪初始化
 * @param   none
 * @retval  none
 * 
*/
void Mpu6050::mpu6050_init() {
    
    // Wire.begin();  //初始化I2C    

  //初始化陀螺仪
  if (!mpu.begin()) {   //初始化陀螺仪
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G); //设置加速度范围
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);  //设置陀螺仪范围
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);  //设置陀螺仪带宽
  // Serial.println("");
  delay(100);
}




/**
 * @brief   陀螺仪获取数据并打印
 * @param   none
 * @retval  none
 * 
*/
void Mpu6050::mpu6050_get_test() {

  //获取陀螺仪数据
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


    //打印数据
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");


  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");

  delay(10);
}



/**
  * @brief    根据传感器的加速度数据计算与自然坐标轴（X、Y、Z）的角度
  * @param    dir : 读取角度的方向
  * @retval   none
  */

short Mpu6050 ::mpu6050_gain_angle(uint8_t dir){

  //获取陀螺仪数据
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float x = a.acceleration.x; //获取X轴加速度
    float y = a.acceleration.y; //获取Y轴加速度
    float z = a.acceleration.z; //获取Z轴加速度


    float temp1;
    float res=0;
    switch(dir)
    {
                case 0://与自然Z轴的角度
                        temp1=sqrt((x*x+y*y))/z;
                        res=atan(temp1);
                        break;
                case 1://与自然X轴的角度
                        temp1=x/sqrt((y*y+z*z));
                        res=atan(temp1);
                        break;
                case 2://与自然Y轴的角度
                        temp1=y/sqrt((x*x+z*z));
                        res=atan(temp1);
                        break;
    }
    return res*1800/3.14;//把弧度转换成角度

}
