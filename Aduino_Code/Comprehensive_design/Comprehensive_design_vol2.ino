//본 코딩은 아두이노 나노 33 BLE 의 내장된 가속도 센서 LSM9DS1을 활용한 코딩입니다. 
//아두이노 나노 33 BLE 사용을 위해 보드매니저에서 Arduino Mbed OS Nano Board 설치
//온도센서 관련 라이브러리에서 Adafruit MLX90614 Library 설치
//가속도 센서 관련 라이브러리에서 Arduino_LSM9DS1 설치
//산소포화도 센서 관련 라이브러리에서 SparkFun MAX3010x Pulse and Sensor Library 설치

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Arduino_LSM9DS1.h>
#include "MAX30105.h"
#include "heartRate.h"

long t = 1;
long t1 = 0;
float ax, ay, az; // 가속도 상수 값 설정
float gx, gy, gz; // 자이로 상수 값 설정
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;

MAX30105 particleSensor; // MAX30105.h 에서 particleSensor 함수 불러오기
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 온도센서 라이브러리 생성
 
void setup() {
  Serial.begin(115200); // 통신속도 설정
  Wire.begin(); // wire 함수
  
  if (!IMU.begin() && !particleSensor.begin(Wire, I2C_SPEED_FAST)){ 
    // 가속도 센서와 심박센서가 인식되지 않을 경우 출력됨
    Serial.println("센서가 감지되지 않습니다");
    while (1);
  }
  else{
  particleSensor.setup(); // 심박센서 기본 설정으로 센서 구성
  particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻임
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
  mlx.begin(); // 온도센서 시작
  }
}


void loop() {
// 값을 계산함
  unsigned long t = millis();

  float Rtemp = mlx.readObjectTempC() - 10; //온도 상수 설정
  
  IMU.readAcceleration(ax, ay, az); // 가속도 센서 설정
  IMU.readGyroscope(gx, gy, gz); // 자이로 센서 설정
  
  long irValue = particleSensor.getIR(); // 심박센서 값 설정
  if (checkForBeat(irValue) == true){
    long delta = t - lastBeat;
    lastBeat = t;
    beatsPerMinute = 60 /(delta/1000.0);
    if(beatsPerMinute < 255 && beatsPerMinute > 20){
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      }
  }

// 이 아래부터 계산된 값을 출력합니다.

  if (t - t1 >= 100 && irValue > 50000 && IMU.accelerationAvailable()){ // 보통 사람피부에 접촉할 경우 7~10만 사이의 값이 출력됨
    t1 = t; // t - t1 = 0 으로 초기화
    
    Serial.print("[체온] ") ; Serial.print(Rtemp); Serial.println("*C"); // 체온 출력

    Serial.print("[가속도]"); // 가속도 값 출력
    Serial.print(" [X] ");
    Serial.print(ax);
    Serial.print("m/s^2 [Y] ");
    Serial.print(ay);
    Serial.print("m/s^2 [Z] ");
    Serial.print(az);
    Serial.println("m/s^2");

    Serial.print("[자이로]"); // 자이로 값 출력
    Serial.print(" [X] ");
    Serial.print(gx);
    Serial.print("dps [Y] ");
    Serial.print(gy);
    Serial.print("dps [Z] ");
    Serial.print(gz);
    Serial.println("dps");
    
    Serial.print("[BPM] "); Serial.println(beatsPerMinute); // BPM 값 출력
    }
  else if (t - t1 >= 100 && irValue <= 50000 && IMU.accelerationAvailable()){ 
    t1 = t;
    Serial.println("신체가 감지되지 않습니다.");
    }
  }
