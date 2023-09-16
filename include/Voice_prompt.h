/**********************************************************
*** 语音提示模块
*** 编写作者：wds
***邮箱：wdsnpshy@163.com
**********************************************************/

#ifndef VOICE_PROMPT_H
#define VOICE_PROMPT_H
#include <Arduino.h>


//语音提示类
class Voice_prompt
{

public:
    void Voice_prompt_init();  //初始化语音提示模块
    void Vioce_prompt_run(uint8_t weather);   //语音提示模块运行

   
};





#endif