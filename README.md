# STM32-Smart-Fish-Tank-Connected-to-Onenet
Smart Fish Tank Based on STM32
修改esp8266.c下的wifi账号及密码
#define ESP8266_WIFI_INFO		"AT+CWJAP=\"12345678\",\"12345678\"\r\n"
默认WIFI账户是12346578 密码也是12345678
修改onenet.c下的PROID、ACCESS_KEY_key和DEVICE_NAME
