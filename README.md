# Uwb-mobile-warning-sign

#### 介绍
{**以下是 Gitee 平台说明，您可以替换此简介**
Gitee 是 OSCHINA 推出的基于 Git 的代码托管平台（同时支持 SVN）。专为开发者提供稳定、高效、安全的云端软件开发协作平台
无论是个人、团队、或是企业，都能够用 Gitee 实现代码托管、项目管理、协作开发。企业项目请看 [https://gitee.com/enterprises](https://gitee.com/enterprises)}

#### 软件架构
软件架构说明

![哈哈哈](readme/系统架构.png)

![系统架构](readme/电机驱动.png)

#### 安装教程

xxxxxx

#### 使用说明

1.  本项目基于esp32开发，通过uwb实现警示牌精确定位。
2.  未经本人允许，禁止用于商业用途！

#### 参与贡献

1.  xxxxxx

#### 演示视频
[观看视频](https://www.bilibili.com/video/BV1vC4y1d7iW/?share_source=copy_webvd_source=59d27872ea6a7ea7390ac0fae3dc29bd)


#### 备注
const char* Adafruit_MQTT::connectErrorString(int8_t code) {
   switch (code) {
      case 1: return reinterpret_cast<const char*>(F("The Server does not support the level of the MQTT protocol requested"));
      case 2: return reinterpret_cast<const char*>(F("The Client identifier is correct UTF-8 but not allowed by the Server"));
      case 3: return reinterpret_cast<const char*>(F("The MQTT service is unavailable"));
      case 4: return reinterpret_cast<const char*>(F("The data in the user name or password is malformed"));
      case 5: return reinterpret_cast<const char*>(F("Not authorized to connect"));
      case 6: return reinterpret_cast<const char*>(F("Exceeded reconnect rate limit. Please try again later."));
      case 7: return reinterpret_cast<const char*>(F("You have been banned from connecting. Please contact the MQTT server administrator for more details."));
      case -1: return reinterpret_cast<const char*>(F("Connection failed"));
      case -2: return reinterpret_cast<const char*>(F("Failed to subscribe"));
      default: return reinterpret_cast<const char*>(F("Unknown error"));
   }
}