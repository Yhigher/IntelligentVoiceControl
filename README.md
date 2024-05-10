# IntelligentVoiceControl
一个通过百度API进行语音识别，连接Linux服务器控制NXP开发板的智能项目
## 修改QT中Speed.h文件百度API相关信息
const QString BaiduSpeechUrl = "url的地址?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString BaiduSpeechClientID = "ClientID";
const QString BaiduSpeechClientSecret = "ClientSecret";
