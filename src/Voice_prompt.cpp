/**
 * @file 语音提示模块类
 * @author wds
 * @date 2023/9/16
 * 邮箱：wdsnpshy@163.com
 * 博客：https://blog.csdn.net/weixin_63211230
 * qq:3412363587
*/
#include "Voice_prompt.h"
#include "Arduino.h"

#define VOICE_PROMPT_PIN_normal  5  //语音提示模块引脚--正常天气
#define VOICE_PROMPT_PIN_rain  18  //语音提示模块引脚--雨雪天气
#define VOICE_PROMPT_PIN_reserve1  19  //语音提示模块引脚--预留提示     //事故天气
#define VOICE_PROMPT_PIN_reserve2  23  //语音提示模块引脚--预留提示    //国歌



//初始化语音提示模块--初始化引脚
void Voice_prompt::Voice_prompt_init()
{
        //默认高电平
        pinMode(VOICE_PROMPT_PIN_normal, OUTPUT);
        digitalWrite(VOICE_PROMPT_PIN_normal, HIGH);

        pinMode(VOICE_PROMPT_PIN_rain, OUTPUT);
        digitalWrite(VOICE_PROMPT_PIN_rain, HIGH);

        pinMode(VOICE_PROMPT_PIN_reserve1, OUTPUT);
        digitalWrite(VOICE_PROMPT_PIN_reserve1, HIGH);

        pinMode(VOICE_PROMPT_PIN_reserve2, OUTPUT);
        digitalWrite(VOICE_PROMPT_PIN_reserve2, HIGH);



}

//语音提示模块运行
void Voice_prompt::Vioce_prompt_run(uint8_t weather){

  switch (weather)
    {
    case 1:   //雨雪天气正常天气
        digitalWrite(VOICE_PROMPT_PIN_normal, LOW);
        digitalWrite(VOICE_PROMPT_PIN_rain, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_reserve1, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_reserve2, HIGH);

        delay(100);
        digitalWrite(VOICE_PROMPT_PIN_normal, HIGH);  //复位引脚保证能重复触发单个语音提示

        break;


    case 2:  //雨雪天气
        digitalWrite(VOICE_PROMPT_PIN_normal, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_rain, LOW);
        digitalWrite(VOICE_PROMPT_PIN_reserve1, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_reserve2, HIGH);

        delay(100);
        digitalWrite(VOICE_PROMPT_PIN_rain, HIGH);  //复位引脚保证能重复触发单个语音提示

        break;


    case 3:  //预留提示
        digitalWrite(VOICE_PROMPT_PIN_normal, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_rain, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_reserve1, LOW);
        digitalWrite(VOICE_PROMPT_PIN_reserve2, HIGH);

        delay(100);
        digitalWrite(VOICE_PROMPT_PIN_reserve1, HIGH);  //复位引脚保证能重复触发单个语音提示

        break;


    case 4://预留提示
        digitalWrite(VOICE_PROMPT_PIN_normal, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_rain, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_reserve1, HIGH);
        digitalWrite(VOICE_PROMPT_PIN_reserve2, LOW);

        delay(100);  
        digitalWrite(VOICE_PROMPT_PIN_reserve2, HIGH);  //复位引脚保证能重复触发单个语音提示

        break;


    default:
        break;
    }
    
    //避免误触发
    delay(10);

}