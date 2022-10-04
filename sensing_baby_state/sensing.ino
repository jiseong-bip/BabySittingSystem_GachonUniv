//아두이노 나노 33 IOT 사용을 위해 보드매니저에서 Arduino SAMD Boards 설치
//온도센서 MLX90614 관련 라이브러리에서 Adafruit MLX90614 Library 설치
//자이로 센서 L3G4200D 관련 라이브러리에서 L3G 설치
//산소포화도 센서 MAX30102 관련 라이브러리에서 SparkFun MAX3010x Pulse and Sensor Library 설치
#include "test.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <L3G.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFi.h>


const char* ssid = "GC_free_WiFi";        // WiFi의 SSID(수정필요)
const char* pass = "";     // WiFi의 비밀번호(수정필요)
int status = WL_IDLE_STATUS;

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr1(221,142,47,16);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "1q2w3e4r!";        // MySQL user login password

// Sample query
char INSERT_DATA[] = "INSERT INTO status.tbl_status VALUES('%s','%s', %0.1lf, %d, '%s')";
char query[128];
char temperature[10];

EthernetClient client;
MySQL_Connection conn((Client *)&client);

MAX30105 particleSensor; // MAX30105.h 에서 particleSensor 함수 불러오기
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 온도센서 라이브러리 생성
L3G gyro; // L3G.h 에서 gyro 함수 불러오기

// boolean sendData = false;
// boolean gyroFlag = false;
// boolean tempFlag = false;
// boolean bpmFlag = false;


void loop() {
  /*GYRO();
  Temperature();
  BPM();*/ // 시리얼 모니터가 필요 없어졌을 때 아래의 함수를 지우고 다음 함수를 푼다.
  GyroPrint();
  TemperaturePrint();
  BPMPrint();
  if(gyroFlag){
    gyroFlag = false;
    gyroState();
    if(fallbaby)
      state = "Fall";
    else 
      state = "Not fall";
  }
  if(tempFlag){
    tempFlag = false;
    getTemperature();
  }
  if(bpmFlag){
    bpmFlag = false;
    BPM();
  }
  if(sendData){
    sendData = false;
    inputData();
  }    
}
