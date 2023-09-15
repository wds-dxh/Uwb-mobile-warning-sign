#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <motor.h>
#include <Blinker.h>
#include <Arduino.h>

motor motor1;

char auth[] = "3f19661dfb92";
char ssid[] = "asus";
char pswd[] = "00000000";




// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-abc");


#define LED_BUILTIN 2

int counter = 0;

// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

void setup() {
  
    Serial.begin(115200);  //初始化串口0，用于和电脑通信,打印调试信息

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);


    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
}

void loop() {
    Blinker.run();


}