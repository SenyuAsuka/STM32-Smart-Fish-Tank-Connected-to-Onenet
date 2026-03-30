# STM32-Smart-Fish-Tank-Connected-to-Onenet
Smart Fish Tank Based on STM32

基于STM32F103C8T6的智能鱼缸

修改esp8266.c下的wifi账号及密码

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"12345678\",\"12345678\"\r\n"

默认WIFI账户是12346578 密码也是12345678

修改onenet.c下的PROID、ACCESS_KEY_key和DEVICE_NAME

参考视频https://www.bilibili.com/video/BV1jS421A7Bk/?spm_id_from=333.337.search-card.all.click&vd_source=63d0cb9e8c7ff2b9228c56010532a7fc

DHT11接的PB11 DS18B20接PB1 TDS接PA0 SG90接PB0 DH接PA1
<img width="1375" height="788" alt="image" src="https://github.com/user-attachments/assets/d6d60765-7f5e-4e11-98db-22686c7e8365" />
<img width="2014" height="1190" alt="image" src="https://github.com/user-attachments/assets/b7f2140d-f37d-4519-9499-bbfb1daa78fa" />
