/**
 * @file 全向轮控制类
 * @author wds
 * @date 2023/9/14
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
*/

#include "Car_control.h"
#include "motor.h"
#include "Arduino.h"



motor motor1;


/**
  * @brief    小车控制初始化(初始化串口2)
  * @param    无
  * @retval   无
  */

void Car_control :: Car_control_init(){

  // // 初始化串口
  // Serial2.begin(115200);

  // 等待串口初始化完成
  // while (!Serial2) {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }

  // 上电延时2秒等待Emm_V5.0闭环初始化完毕
  delay(2000);

}


/**
  * @brief    小车前进
  * @param    vel ：速度       ，范围0 - 5000RPM
  * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
  * @retval   条件不满足返回 地址 FF E2 6B，错误命令返回 地址 00 EE 6B
  */
void Car_control :: Car_forward(uint16_t vel, uint8_t acc){

    motor1.Emm_V5_Vel_Control(1, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(2, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(3, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(4, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Synchronous_motion(0);delay(DELAY_TIME);

}

/**
  * @brief    小车后退
  * @param    vel ：速度       ，范围0 - 5000RPM
  * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
  * @retval   条件不满足返回 地址 FF E2 6B，错误命令返回 地址 00 EE 6B
  */
void Car_control :: Car_back(uint16_t vel, uint8_t acc){

    motor1.Emm_V5_Vel_Control(1, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(2, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(3, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(4, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Synchronous_motion(0);delay(DELAY_TIME);

}


/**
  * @brief    向右平移
  * @param    vel ：速度       ，范围0 - 5000RPM
  * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
  * @retval   条件不满足返回 地址 FF E2 6B，错误命令返回 地址 00 EE 6B
  */
void Car_control :: Car_right_translation(uint16_t vel, uint8_t acc){

    motor1.Emm_V5_Vel_Control(1, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(2, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(3, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(4, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Synchronous_motion(0);delay(DELAY_TIME);

}


/**
  * @brief    向左平移
  * @param    vel ：速度       ，范围0 - 5000RPM
  * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
  * @retval   条件不满足返回 地址 FF E2 6B，错误命令返回 地址 00 EE 6B
  */
void Car_control :: Car_left_translation(uint16_t vel, uint8_t acc){

    motor1.Emm_V5_Vel_Control(1, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(2, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(3, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(4, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Synchronous_motion(0);delay(DELAY_TIME);

}


/**
 * @brief    向右旋转
 * @param    vel ：速度       ，范围0 - 5000RPM
 * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
 * @retval   条件不满足返回 地址 FF E2 6B，错误命令返回 地址 00 EE 6B
 */
void    Car_control :: Car_right_rotation(uint16_t vel, uint8_t acc){

    motor1.Emm_V5_Vel_Control(1, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(2, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(3, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(4, 0, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Synchronous_motion(0);delay(DELAY_TIME);

}


/**
 * @brief    向左旋转
 * @param    vel ：速度       ，范围0 - 5000RPM
 * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
 * @retval   条件不满足返回 地址 FF E2 6B，错误命令返回 地址 00 EE 6B
 */
void    Car_control :: Car_left_rotation(uint16_t vel, uint8_t acc){

    motor1.Emm_V5_Vel_Control(1, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(2, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(3, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Vel_Control(4, 1, vel, acc, true);delay(DELAY_TIME);
    motor1.Emm_V5_Synchronous_motion(0);delay(DELAY_TIME);
}


/**
 * @brief    停止
 * @param    无
 * @retval   无
 */

void    Car_control :: Car_stop(){


    motor1.Emm_V5_Stop_Now(0, false);delay(DELAY_TIME);

}







