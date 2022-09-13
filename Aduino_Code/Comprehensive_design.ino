//온도센서 관련 라이브러리에서 Adafruit MLX90614 Library 설치
//가속도 센서 관련 라이브러리에서 L3G 설치
//산소포화도 센서 관련 라이브러리에서 SparkFun MAX3010x Pulse and Sensor Library 설치

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <L3G.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

long A = 0;
long t = 1;
long t1 = 0;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 온도센서 라이브러리 생성
L3G gyro; // 가속도센서 관련 명령어?
 
void setup() {
  Serial.begin(115200); // 통신속도 설정
  Wire.begin(); // wire 함수
  
  if (!gyro.init()) // 센서가 인식되지 않을 경우 출력됨
  {
    Serial.println("센서가 감지되지 않습니다");
    while (1);
  }
  else{
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) // 센서 연결 인식 안될 시 출력
  {
    Serial.println("심박센서가 감지되지 않습니다");
    while (1);
  }
  gyro.enableDefault(); // 인식될경우 자이로센서 시작
  particleSensor.setup(); // 기본 설정으로 센서 구성
  particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻임
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
  mlx.begin(); // 온도센서 시작
  }
}
void loop() {
  t = millis();
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true){
    long delta = t - lastBeat;
    lastBeat = t;
    beatsPerMinute = 60 /(delta/1000.0);
    if(beatsPerMinute < 255 && beatsPerMinute > 20){
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      }
  }
  
 if(irValue < 50000){ // IR 적외선 값이 50000 이하면은 사람 피부가 가까이 있지 않다고 판단한다.
    if(t - t1 >= 1000){ // 1초 간격으로 출력
      t1 = t; // t - t1 = 0 으로 초기화
      Serial.println("신체가 감지되지 않습니다.");
    }
    }
    else{
  if (t - t1 >= 1000){ // 1초 간격으로 온도 출력
    t1 = t; // t - t1 = 0 으로 초기화
   
    float Rtemp = mlx.readObjectTempC() - 10; // 가정용 체온계 보다 대략 10도 높게 나와서 값을 10 정도 깎음
    Serial.print("[체온] ") ; Serial.print(Rtemp); Serial.println("*C"); // [온도] xx.xx*C 로 출력함 
    
    gyro.read(); // 가속도 값 읽고 출력함
    
    Serial.print("[가속도]");
    Serial.print(" [X] ");
    Serial.print((int)gyro.g.x);
    Serial.print(" [Y] ");
    Serial.print((int)gyro.g.y);
    Serial.print(" [Z] ");
    Serial.println((int)gyro.g.z);

    Serial.print("[BPM] "); Serial.println(beatsPerMinute); // BPM 값 출력
  }
  }
  }
