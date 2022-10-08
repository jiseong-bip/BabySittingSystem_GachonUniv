//아두이노 나노 33 IOT 사용을 위해 보드매니저에서 Arduino SAMD Boards 설치
//온도센서 MLX90614 관련 라이브러리에서 Adafruit MLX90614 Library 설치
//자이로 센서 L3G4200D 관련 라이브러리에서 L3G 설치
//산소포화도 센서 MAX30102 관련 라이브러리에서 SparkFun MAX3010x Pulse and Sensor Library 설치
#include "test.h"
#include "TcTimer5.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <L3G.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFi.h>


EthernetClient client;
IPAddress server_addr1(221,142,47,16);  // IP of the MySQL *server* here
MySQL_Connection conn((Client *)&client);

MAX30105 particleSensor; // MAX30105.h 에서 particleSensor 함수 불러오기
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 온도센서 라이브러리 생성
L3G gyro; // L3G.h 에서 gyro 함수 불러오기

void loop() {
  if(TcTimer5::get(0) >= 1000) TcTimer5::reset(0);

  readGyro();
  readBPM();
  readTemp();
  
  intervalServices();
}

void intervalServices(){   
    if(flagOneSec){
        flagOneSec = false;
        printGyro();
        if(fallbaby){
          state = "Fall";
        }else {
          state = "Not fall";
        }
        printTemperature();
        printBPM();
        
    }
    if(flagTenSec){
        flagTenSec = false;
    }
    if(flagOneMin){
        flagOneMin = false; 
        //inputData(CurrentTime, SelectedUser);
    }
}
