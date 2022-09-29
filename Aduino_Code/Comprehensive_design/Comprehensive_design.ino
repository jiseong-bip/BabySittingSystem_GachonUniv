//아두이노 나노 33 IOT 사용을 위해 보드매니저에서 Arduino SAMD Boards 설치
//온도센서 MLX90614 관련 라이브러리에서 Adafruit MLX90614 Library 설치
//자이로 센서 L3G4200D 관련 라이브러리에서 L3G 설치
//산소포화도 센서 MAX30102 관련 라이브러리에서 SparkFun MAX3010x Pulse and Sensor Library 설치

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <L3G.h>
#include "MAX30105.h"
#include "heartRate.h"

float GX; float GY; float GZ; // 자이로 센서 관련 상수
float Rtemp; // 온도센서 관련상수
// 심박수 센서 관련 상수
long t = 1;
long irValue;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg; // float에서 int로 수정
boolean fallbaby = false; // 아기가 떨어지면 1로 변함
boolean hightemp = false; // 아기 체온이 높으면 1로 변함
boolean warningBPM = false; // 아기 심박수가 낮으면 1로 변함

MAX30105 particleSensor; // MAX30105.h 에서 particleSensor 함수 불러오기
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 온도센서 라이브러리 생성
L3G gyro; // L3G.h 에서 gyro 함수 불러오기

/////////////////////////////////////////////////아래 함수는 가속도, 온도, 심박수에 관한 함수입니다.

void GYRO(){
  gyro.read();
  // 각가속도의 절댓값
  GX = abs((int)gyro.g.x); 
  GY = abs((int)gyro.g.y);
  GZ = abs((int)gyro.g.z);
  if (GX >= 2000 || GY >= 2000 || GZ >= 2000){ //dps가 어느 방향이든 2000이 넘으면 fallbaby값이 true가 됨
    fallbaby = true;
    }
  else {
    fallbaby = false;
    }
}

void Temperature(){ 
  Rtemp = mlx.readObjectTempC() * 36 / 46;
  if (Rtemp > 40){ // 체온이 40도를 초과 하면 hightemp값이 true가 됨
    hightemp = true;
    }
  else{
    hightemp = false;
    }
}

void BPM(){
  irValue = particleSensor.getIR(); // 심박센서 값 설정
  if (checkForBeat(irValue) == true){
    long delta = t - lastBeat;
    lastBeat = t;
    beatsPerMinute = 60 /(delta/1000.0);
    if(beatsPerMinute < 255 && beatsPerMinute > 20){
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
      }
  }
  else if (beatAvg <= 20 && millis() >= 60){ // bpm이 20 이하이고 60초가 지났을 경우 warningBPM 값이 true가 됨
    warningBPM = true;
    }
  else{
    warningBPM = false;
    }
}

/////////////////////////////////////////// 여기서부터는 위의 함수들을 시리얼 모니터로 출력하기 위한 함수입니다. 시리얼 모니터가 필요 없어졌을 때 삭제해도 무방합니다.

void GyroPrint(){ //자이로 값 시리얼 모니터로 나타내기
  GYRO();
  Serial.print("[자이로]"); // 자이로 값 출력
  Serial.print(" [X] ");
  Serial.print(GZ);
  Serial.print("dps [Y] ");
  Serial.print(GY);
  Serial.print("dps [Z] ");
  Serial.print(GZ);
  Serial.println("dps");
  Serial.println(fallbaby);
}

void TemperaturePrint(){ //온도 값 시리얼 모니터로 나타내기
  Temperature();
  Serial.print("[체온] ") ; Serial.print(Rtemp); Serial.println("*C"); Serial.println(hightemp); // 체온 출력
  }

void BPMPrint(){ //심박수 값 시리얼 모니터로 나타내기
  BPM();
  if (irValue > 50000){ // 보통 사람피부에 접촉할 경우 적외선 값이 7~10만 사이의 값이 출력됨
  Serial.print("[AvgBPM] "); Serial.println(beatAvg);Serial.println(warningBPM);
  }
  else{  // 적외선 값이 5만 이하일 경우 신체와 접촉해 있지 않다고 판단
  Serial.println("No detecting body");
  }
}

/////////////////////////////////////////// 여기서 부터 setup, loop 함수

void setup() {
  Serial.begin(115200); // 통신속도 설정
  Wire.begin(); // wire 함수
  
  if (!gyro.init() || !particleSensor.begin(Wire, I2C_SPEED_FAST)){ 
    // 자이로 혹은 심박센서가 인식되지 않을 경우 출력됩니다.
    Serial.println("No detecting gyro or bpm sensor");
    while (1);
  }
  else{
  
  gyro.enableDefault(); // 자이로센서 시작
  particleSensor.setup(); // 심박센서 기본 설정으로 센서 구성
  particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻입니다.
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
  mlx.begin(); // 온도센서 시작
  }
 }

void loop() {
  /*GYRO();
  Temperature();
  BPM();*/ // 시리얼 모니터가 필요 없어졌을 때 아래의 함수를 지우고 다음 함수를 푼다.
  GyroPrint();
  TemperaturePrint();
  BPMPrint();
  delay(100);// 보기에 편하라고 넣어뒀지만 빼도 무방합니다.
  }
