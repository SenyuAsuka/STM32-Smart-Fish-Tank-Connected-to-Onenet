# STM32-Smart-Fish-Tank-Connected-to-Onenet
Smart Fish Tank Based on STM32

实现的基本功能有PH检测，TDS检测，SG90舵机，DS18B20的温度检测，DHT11的湿度检测。同时上传数据到ONENET平台

修改esp8266.c下的wifi账号及密码

#define ESP8266_WIFI_INFO		"AT+CWJAP=\"12345678\",\"12345678\"\r\n"

默认WIFI账户是12346578 密码也是12345678

修改onenet.c下的PROID、ACCESS_KEY_key和DEVICE_NAME

连接OneNet参考视频https://www.bilibili.com/video/BV1jS421A7Bk/?spm_id_from=333.337.search-card.all.click&vd_source=63d0cb9e8c7ff2b9228c56010532a7fc

<img width="1949" height="1110" alt="image" src="https://github.com/user-attachments/assets/a2415242-373a-49ec-a9f8-13564429adbb" />

<img width="1949" height="1110" alt="image" src="https://github.com/user-attachments/assets/74153f0f-508d-4045-a60e-71535b00f411" />

