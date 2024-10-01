/**
 * @file WiFi控制类
 * @author wds
 * @date 2023/9/16
 * @email wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
*/
extern float ypr[3];
extern int run_count; //运行到距离uwb固定位置

// #define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_WITHOUT_SSL

#define LED_BUILTIN 2     //测试是否连接成功的指示灯

#include "Car_control.h"
#include "WiFi_control.h"
#include "Arduino.h"
#include "Blinker.h"
#include "Color_light_control.h"
// #include "Blinker/BlinkerDebug.h"
#include "Rain_sensor.h"


extern  Color_light_control color_light_control; //声明在其他文件中定义的 color_light_control 对象，避免重复定义
extern motor motor1;
int count_go;
extern uint8_t led_quantity;
extern uint8_t car_go_wifi;

extern uint8_t weather; //天气  0默认不播报语音提示

char auth[] = "3f19661dfb92";
// char ssid[] = "asus";
// char pswd[] = "00000000";


 char ssid[] = "wds";
 char pswd[] = "wdsshy0320";



Car_control car_control;        // 小车控制类对象
uint16_t SPEED = 50;             // 速度
uint16_t ACC = 999;               // 加速度
char mark_led = 'A';           // 标记灯光是否闪烁
int32_t luminance =255;             // 灯光亮度
int counter = 0;
extern int count; 
char mark_rain  = 'A';      
extern Rain_sensor rain_sensor; //声明在其他文件中定义的 rain_sensor 对象，避免重复定义
extern char mark_voice;

// 新建组件对象
BlinkerNumber Number1("num-uwb");   // uwb距离
BlinkerNumber Number2("num-angle");   //陀螺仪角度





BlinkerButton Button1("btn-forward");  //前进组件绑定（按键）

BlinkerButton Button2("btn-backward"); //后退组件绑定（按键）

BlinkerButton Button3("btn-stop");  //停止组件绑定（按键）

BlinkerButton Button4("btn-toright"); //右平移组件绑定（按键）
BlinkerButton Button5("btn-toleft");  //左平移组件绑定（按键）

BlinkerButton Button6("btn-speedup"); //速度+组件绑定（按键）
BlinkerButton Button7("btn-speeddown"); //速度-组件绑定（按键）



BlinkerButton Button8("btn-left"); //左转组件绑定（按键）
BlinkerButton Button9("btn-right"); //右转组件绑定（按键）


BlinkerButton Button10("btn-red"); //红灯组件绑定（按键）
BlinkerButton Button11("btn-green"); //绿灯组件绑定（按键）
BlinkerButton Button12("btn-blue"); //彩灯

BlinkerButton Button13("btn-yushui"); //雨水检测组件绑定（按键）

BlinkerButton Button14("btn-run");   //停止运动到固定距离
BlinkerButton Button15("btn-star");   //开始运动到固定距离

BlinkerButton Button16("btn-rain"); 
BlinkerButton Button17("btn-accident"); 
BlinkerButton Button18("btn-guoge"); 




BlinkerSlider Slider1("luminance"); //滑动条组件绑定（滑动条）

// BlinkerSlider Slider2("angle"); //滑动条组件绑定（滑动条）






// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}



// 按下按键1即会执行该函数  前进
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_forward(SPEED,ACC);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯

//       uint8_t cmd[16] = {0};

//   // 装载命令
//   cmd[0] =  0;                       // 地址
//   cmd[1] =  0xF6;                       // 功能码
//   cmd[2] =  0;                        // 方向
//   cmd[3] =  0;        // 速度(RPM)高8位字节
//   cmd[4] =  0;        // 速度(RPM)低8位字节
//   cmd[5] =  0;                        // 加速度，注意：0是直接启动
//   cmd[6] =  0;                        // 多机同步运动标志
//   cmd[7] =  0x6B;                       // 校验字节
  
//   // 发送命令
//   Serial.write(cmd, 8);
}





// 按下按键2即会执行该函数  后退
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_back(SPEED,ACC);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

// 按下按键3即会执行该函数  停止
void button3_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_stop();
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
    uint16_t SPEED = 10; 
    color_light_control.colr_light_all_off(led_quantity);
    mark_led = 'A';  //停止灯光
    mark_voice = 'B' ;
}


//按下按键4即会执行该函数  右平移
void button4_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_right_translation(SPEED,ACC);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键5即会执行该函数  左平移
void button5_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_left_translation(SPEED,ACC);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键6即会执行该函数  速度+
void button6_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    SPEED += 10;
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键7即会执行该函数  速度-
void button7_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    SPEED -= 10;
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键八，左转
void button8_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_left_rotation(SPEED,ACC);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键九，右转
void button9_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_right_rotation(SPEED,ACC);
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键十，红灯闪烁
void button10_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    // color_light_control.color_flash(10,'R');  //闪烁红灯
    mark_led = 'R';
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键十一，绿灯闪烁
void button11_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    // color_light_control.color_flash(10,'G');  //闪烁绿灯
    mark_led = 'G';
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键十二，彩灯灯闪烁
void button12_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    // color_light_control.color_flash(10,'B');  //闪烁彩灯
    // color_light_control.color_riot_of_colours(10);  //七彩灯
    mark_led = 'B';
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键十三，天气控制灯光
void button13_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    mark_rain = 'A';
    // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键十四，小车停止行驶到固定距离
void button14_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    run_count = 1;
}


//按下按键十五，小车开始行驶到固定距离
void button15_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_go_wifi = true;
}

//按下按键十六，雨雪天气
void button16_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    // voice_prompt.Vioce_prompt_run(2); //语音提示雨雪天气
    weather = 2;   //雨雪天气
    mark_led = 'R';
    mark_voice = 'A';   
}


//按下按键十七，交通事故
void button17_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    // voice_prompt.Vioce_prompt_run(3); //语音提示交通事故
    weather = 3;   //交通事故
    mark_led = 'R';
    mark_voice = 'A';
}

//按下按键十八，国歌
void button18_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    weather = 4;   //国歌

    mark_led = 'B';
    mark_voice = 'A';
}




//滑动滑动条，调节灯光亮度
void slider1_callback(int32_t value)
{
    BLINKER_LOG("get slider value: ", value);
    luminance = value;
    Serial.println(luminance);
}


// //滑动滑动条，调节小车角度
// void slider2_callback(int32_t value)
// {
//     BLINKER_LOG("get slider value: ", value);


//     if (value>0)
//     {car_control.Car_control_rotate(abs(54*value),50, 1);}
    
//     if(value<0)
//     {car_control.Car_control_rotate(-abs(54*value),50, 0);}
    

//     if(value==0)
//     motor1.Emm_V5_Reset_CurPos_To_Zero(0);
    
    
// }






/**
  * @brief    WiFi控制类初始化(链接blinker)
  * @param    None
  * @retval   None
  */
void WIFI_control :: WiFi_control_init(){
    
    // 初始化有LED的IO  用于测试是否连接成功
    // pinMode(LED_BUILTIN, OUTPUT);
    // digitalWrite(LED_BUILTIN, HIGH);


    car_control.Car_control_init();  // 初始化小车
    

    Serial.begin(115200);  //初始化串口0，用于和电脑通信,打印调试信息
    
//     while (!Serial) {
//     delay(10); // will pause Zero, Leonardo, etc until serial console opens
//   }

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);

    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Button4.attach(button4_callback);
    Button5.attach(button5_callback);
    Button6.attach(button6_callback);
    Button7.attach(button7_callback);
    Button8.attach(button8_callback);
    Button9.attach(button9_callback);


    Button10.attach(button10_callback);//红灯闪烁
    Button11.attach(button11_callback);//绿灯闪烁
    Button12.attach(button12_callback);//彩灯闪烁
    Button13.attach(button13_callback);//雨水控制
    Button14.attach(button14_callback);//停止运动到uwb固定距离
    Button15.attach(button15_callback);

    Button16.attach(button16_callback);//雨雪天气
    Button17.attach(button17_callback);//交通事故
    Button18.attach(button18_callback);//国歌

    Slider1.attach(slider1_callback);//滑动条，调节灯光亮度
    // Slider2.attach(slider2_callback);//滑动条，调节小车角度
}



// /**
//   * @brief    WiFi控制类初始化(链接blinker)
//   * @param    Serial_WIFI  串口对象
//   * @retval   None
//   */
// void WIFI_control :: WiFi_control_init(HardwareSerial& Serial_WIFI){
    
//     // 初始化有LED的IO  用于测试是否连接成功
//     pinMode(LED_BUILTIN, OUTPUT);
//     digitalWrite(LED_BUILTIN, HIGH);


//     car_control.Car_control_init();  // 初始化小车
    

//     Serial_WIFI.begin(115200);  //初始化串口0，用于和电脑通信,打印调试信息

//     #if defined(BLINKER_PRINT)
//         BLINKER_DEBUG.stream(BLINKER_PRINT);
//     #endif

//     // 初始化blinker
//     Blinker.begin(auth, ssid, pswd);

//     Blinker.attachData(dataRead);

//     Button1.attach(button1_callback);
//     Button2.attach(button2_callback);
//     Button3.attach(button3_callback);
//     Button4.attach(button4_callback);
//     Button5.attach(button5_callback);
// }



/**
  * @brief    WiFi控制小车运行
  * @param    None
  * @retval   None
  */
void WIFI_control :: WiFi_control_run(){
    Blinker.run();
    
}






/**
 * @brief   雨滴检测,正常控制灯光
 * @param   None
 * @retval  None
*/
void WIFI_control :: Rain_control(){
    if (rain_sensor.Rain_sensor_is_rain() == false){
      

      mark_led = 'R';
      }
else{
    

      mark_led = 'B';  //七彩灯
    }
}


void WIFI_control :: Wifi_data_transmission(int range){
    Number1.print(range);
    Number2.print(ypr[0] * 180/M_PI);
}