#ifndef MPU6050_ELECCAT_H
#define MPU6050_ELECCAT_H



class Mpu6050_eleccat{

public:
    void Mpu6050_eleccat_init();
    float Mpu6050_eleccat_getYaw(uint8_t angle);  //获取角度
    void Mpu6050_run(); //运行  



};


#endif