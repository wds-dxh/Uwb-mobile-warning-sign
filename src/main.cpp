/**
 * @file ws2812b控制程序
 * @author wds
 * @date 2023/9/14
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
 */

//串口0驱动步进电机 ---打印blnker的调试信息 ----freeRTOS等系统级的调试信息
//串口2读取uwb的距离
//注意灯光和测试的引脚都是GPIO2

#include <Arduino.h>
#include "WiFi_control.h" //wifi控制小车运行
#include "Voice_prompt.h"  //语音提示模块
#include"Mpu6050_eleccat.h"
#include "Rain_sensor.h" //雨滴检测模块
#include "Color_light_control.h" //灯光控制模块
#include "Uwb_get_distance.h" //uwb测距模块
#include"Adafruit_NeoPixel.h"


#include <soc/soc.h> 
#include <soc/rtc_cntl_reg.h>  //关闭低电压检测,避免无限重启

#define PID_P 1 //比例系数

#define USE_MULTCORE  1 //使用多核心
#define USW_MULTTHREAD 0 //使用多线程
#define car_go true //小车运行的距离



WIFI_control wifi_control;
Voice_prompt voice_prompt;
Rain_sensor rain_sensor;
Color_light_control color_light_control;
Uwb_get_distance uwb_get_distance;
Mpu6050_eleccat mpu6050;
extern Car_control car_control;       // 声明在其他文件中定义的 car_control 对象，避免重复定义
extern int count_go;
extern float ypr[3];
extern Adafruit_NeoPixel strip;
extern uint8_t luminance;
int count = 0;

int acc_main = 10;  //加速度
int acc_main_1 = 10;//加速度

// int acc_main = 10;  //加速度
// int acc_main_1 = 10;//加速度


extern char mark_led;
extern char mark_rain;
uint8_t led_quantity = 30;
// extern BlinkerNumber Number1;   // 还未用到

extern int range[4];


void Xcontrol_wifi(void *parameter) ;
void Xothers(void *parameter) ;

int run_count = 0; //运行次数

#define SPEED 50 //速度


void setup() {

    rain_sensor.Rain_sensor_init(); //初始化雨滴检测模块

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);//关闭低电压检测,避免无限重启
    
    wifi_control.WiFi_control_init();  // 初始化WIFI

    mpu6050.Mpu6050_eleccat_init(); //初始化陀螺仪

    HardwareSerial& Serial_WIFI = Serial2; //声明一个串口对象   可以不声明，直接用Serial2
    
    uwb_get_distance.Uwb_get_distance_init(Serial_WIFI,115200); //初始化uwb测距模块

  //  HardwareSerial& Serial_WIFI = Serial; //声明一个串口对象
  //   wifi_control.WiFi_control_init(Serial_WIFI);  // 初始化WIFI
    
    delay(1000);



#if !USE_MULTCORE //

  xTaskCreate(
    Xcontrol_wifi,   /* Task function. */
    "TaskOne", /* String with name of task. */
    10000,     /* Stack size in bytes. */
    NULL,      /* Parameter passed as input of the task */
    1,         /* Priority of the task. */
    NULL);     /* Task handle. */
 
  xTaskCreate(
    Xothers,   /* Task function. */
    "TaskTwo", /* String with name of task. */
    10000,     /* Stack size in bytes. */
    NULL,      /* Parameter passed as input of the task */
    1,         /* Priority of the task. */
    NULL);     /* Task handle. */
#else


    xTaskCreatePinnedToCore(Xcontrol_wifi, "TaskOne", 15000, NULL, 2, NULL, 0);  //Xcontrol_wifi在 0核心
    xTaskCreatePinnedToCore(Xothers, "TaskTwo", 4096, NULL, 1, NULL, 1);  //Xothers在 1核心
#endif

}


void Xcontrol_wifi(void *pvParameters)//执行初始的运行到固定距离的任务
 
{
  #if  (car_go)
    
    while (range[0]<10000&&run_count ==0)//运行到固定距离count<100
    {  
     /*
      mpu6050.Mpu6050_run(); //运行陀螺仪
      uwb_get_distance.Uwb_get_distance_run(); //运行uwb测距模块
      wifi_control.Wifi_data_transmission(range[0]); //wifi数据传输
      Serial.println(range[0]);
     
      // Number1.print(range[0]); //显示距离
      
      if(ypr[0] * 180/M_PI>-1 && ypr[0] * 180/M_PI<1){
      car_control.Car_forward(50, acc_main_1); //前进
      }

      if(ypr[0] * 180/M_PI>1){  
     
       car_control.Car_left_rotation(abs(PID_P*(ypr[0] * 180/M_PI)), acc_main); //左转
      }

      if(ypr[0] * 180/M_PI<1){
      car_control.Car_right_rotation(abs(PID_P*(ypr[0] * 180/M_PI)), acc_main); //右转
      }  

      Serial.print("distance:");
      Serial.println(ypr[0] * 180/M_PI);

      if(range[0]==2000){
       car_control.Car_stop(); //停止
        run_count++;
       }

      //  delay(100);
      //   count++;
      */

      // uwb_get_distance.Uwb_get_distance_run(); //运行uwb测距模块
      // wifi_control.Wifi_data_transmission(range[0]); //wifi数据传输
      // car_control.Car_forward(50, acc_main_1); //前进




      mpu6050.Mpu6050_run(); //运行陀螺仪
      uwb_get_distance.Uwb_get_distance_run(); //运行uwb测距模块
      wifi_control.Wifi_data_transmission(range[0]); //wifi数据传输
      Serial.println(range[0]);
     
      // Number1.print(range[0]); //显示距离
      
     

      if(ypr[0] * 180/M_PI>1){  
     
       car_control.Car_left_rotation(SPEED, acc_main); //左转
      }

      if(ypr[0] * 180/M_PI<1){
      car_control.Car_right_rotation(SPEED, acc_main); //右转
      }  

       if(range[0]==10000){
       car_control.Car_stop(); //停止
        // run_count++;
       }

      else//(ypr[0] * 180/M_PI>-1 && ypr[0] * 180/M_PI<1)
      {
        car_control.Car_forward(SPEED, acc_main_1); //前进
      }



      Serial.print("distance:");
      Serial.println(ypr[0] * 180/M_PI);

    

      //  delay(100);
      //   count++;
   

    }
    car_control.Car_stop(); //停止
    delay(100);  //延时1s
    car_control.Car_stop(); //停止
    #endif
   
    while (1)
    {
      uwb_get_distance.Uwb_get_distance_run(); //运行uwb测距模块
      wifi_control.Wifi_data_transmission(range[0]); //wifi数据传输

      wifi_control.WiFi_control_run();     // wifi控制小车运行
      Serial.println(range[0]);
    }
   vTaskDelete(NULL);  

}
 
void Xothers(void *pvParameters) 
{

while (1){

if(mark_rain=='A'){

if (rain_sensor.Rain_sensor_is_rain() == false){
      voice_prompt.Vioce_prompt_run(1); //语音提示雨雪天气
      // color_light_control.color_flash(10,'B');  //闪烁红灯

      mark_led = 'R';
      }
else{
    voice_prompt.Vioce_prompt_run(2); //语音提示正常天气
    //  color_light_control.color_flash(10,'R');  //闪烁红灯

      mark_led = 'B';  //七彩灯
    }

}

  if(mark_led=='R'||mark_led=='G'||mark_led=='B'){
        mark_rain = 'B';
        if (mark_led=='R')
        {
        color_light_control.color_flash(led_quantity,'R');  //闪烁红灯
        }
        else if (mark_led=='G')
        {
        color_light_control.color_flash(led_quantity,'G');  //闪烁绿灯
        }
        else if (mark_led=='B')
        {
        color_light_control.color_riot_of_colours(led_quantity);  //七彩灯
        // color_light_control.color_flash(led_quantity,'B');  //闪烁蓝灯
        }
        color_light_control.colr_light_all_off(led_quantity);

        delay(10);
        
  }



}  

  vTaskDelete(NULL);

}

void loop() {
//测试用
//  mpu6050.Mpu6050_run(); //运行陀螺仪
 
}