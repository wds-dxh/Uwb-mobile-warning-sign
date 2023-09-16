/**********************************************************
*** WIFI控制类
*** 编写作者：wds
**********************************************************/

#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#define LED_BUILTIN 2     //测试是否连接成功的指示灯

#include "Car_control.h"
#include "WiFi_control.h"
#include "Arduino.h"
#include "Blinker.h"
// #include "Blinker/BlinkerDebug.h"

char auth[] = "3f19661dfb92";
char ssid[] = "asus";
char pswd[] = "00000000";

Car_control car_control;        // 小车控制类对象



int counter = 0;        

// 新建组件对象
BlinkerButton Button1("btn-forward");  //前进组件绑定（按键）

BlinkerButton Button2("btn-backward"); //后退组件绑定（按键）

BlinkerButton Button3("btn-stop");  //停止组件绑定（按键）

BlinkerButton Button4("btn-toright"); //右平移组件绑定（按键）
BlinkerButton Button5("btn-toleft");  //左平移组件绑定（按键）

BlinkerNumber Number1("num-abc");   // 还未用到


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
    car_control.Car_forward(5,10);digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}





// 按下按键2即会执行该函数  后退
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_back(5,10);digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

// 按下按键3即会执行该函数  停止
void button3_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_stop();digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}


//按下按键4即会执行该函数  右平移
void button4_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_right_translation(5,10);digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}

//按下按键5即会执行该函数  左平移
void button5_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    car_control.Car_left_translation(5,10);digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   //测试是否连接成功的指示灯
}




/**
  * @brief    WiFi控制类初始化(链接blinker)
  * @param    None
  * @retval   None
  */
void WIFI_control :: WiFi_control_init(){
    
    // 初始化有LED的IO  用于测试是否连接成功
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);


    car_control.Car_control_init();  // 初始化小车
    

    Serial.begin(115200);  //初始化串口0，用于和电脑通信,打印调试信息

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
}

void WIFI_control :: WiFi_control_run(){
    Blinker.run();
}

