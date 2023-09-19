#ifndef __MPU6050_H__
#define __MPU6050_H__


class Mpu6050
{
public:
    void mpu6050_init();  //初始化陀螺仪
    void mpu6050_get_test();   //获取陀螺仪数据
    short mpu6050_gain_angle(uint8_t dir);  //获取角度

};




#endif // __MPU6050_H__