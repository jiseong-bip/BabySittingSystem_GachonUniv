//온도센서 MLX90614 관련 라이브러리에서 Adafruit MLX90614 Library 설치
//자이로 센서 L3G4200D 관련 라이브러리에서 L3G 설치
//산소포화도 센서 MAX30102 관련 라이브러리에서 SparkFun MAX3010x Pulse and Sensor Library 설치
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <WiFi.h>
#include <Wire.h>
#include <time.h> 
#include <EEPROM.h>
#include "esp.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Adafruit_MLX90614.h> //0x5A
#include <L3G.h>
#include <MAX30105.h> //0x57
#include <heartRate.h>

BLECharacteristic * pTxCharacteristic;
IPAddress MySQL_Server(221,142,47,16);
WiFiClient client;
MySQL_Connection conn(&client);
MAX30105 particleSensor; // MAX30105.h 에서 particleSensor 함수 불러오기
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 온도센서 라이브러리 생성
L3G gyro; // L3G.h 에서 gyro 함수 불러오기

void loop(){
  readGyro();
  if(flagOneSec){
    flagOneSec = false;
    readSensors();
    printDataRaw();
    setState(); 
    //printBLE("hi\n");
  }
  if(flagThreeSec){
    flagThreeSec = false;
    insertDB(currTime);
  }
  if(flagOneMin){
    flagOneMin = false;
  }   
  if(flagOneHour){
    flagOneHour = false;
  }
  menuService();
}
