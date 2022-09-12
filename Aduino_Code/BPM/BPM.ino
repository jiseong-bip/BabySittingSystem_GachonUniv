#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
long t = 1;
long t1 = 0;
float beatsPerMinute;

void setup()
{
  Serial.begin(9600); // 통신속도 설정
  
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) // 센서 연결 인식 안될 시 출력
  {
    Serial.println("심박센서가 감지되지 않습니다");
    while (1);
  }
  Serial.println("측정 중");

  particleSensor.setup(); // 기본 설정으로 센서 구성
  particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻임
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
}

void loop(){
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
  //
  if(irValue < 50000){ // IR 적외선 값이 50000 이하면은 사람 피부가 가까이 있지 않다고 판단한다.
    if(t - t1 >= 1000){ // 1초 간격으로 출력
      t1 = t; // t - t1 = 0 으로 초기화
      Serial.println("신체가 감지되지 않습니다.");
    }
    }
  else{
    if(t - t1 >= 1000){
        t1 = t;
        Serial.print("[BPM] "); Serial.println(beatsPerMinute); // BPM 값 출력
      }
    }
  }
