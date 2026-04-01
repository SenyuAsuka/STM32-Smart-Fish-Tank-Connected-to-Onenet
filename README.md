# STM32-Smart-Fish-Tank-Connected-to-Onenet
Smart Fish Tank Based on STM32

基于STM32F103C8T6的智能鱼缸

修改esp8266.c下的wifi账号及密码

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"12345678\",\"12345678\"\r\n"

默认WIFI账户是12346578 密码也是12345678

修改onenet.c下的PROID、ACCESS_KEY_key和DEVICE_NAME

连接OneNet参考视频https://www.bilibili.com/video/BV1jS421A7Bk/?spm_id_from=333.337.search-card.all.click&vd_source=63d0cb9e8c7ff2b9228c56010532a7fc

<img width="1340" height="768" alt="image" src="https://github.com/user-attachments/assets/f81d8291-249f-4ca2-a7e1-9547eb922b6f" />

<img width="1324" height="740" alt="image" src="https://github.com/user-attachments/assets/0d532fda-85fe-4603-9879-8560385c5783" />
