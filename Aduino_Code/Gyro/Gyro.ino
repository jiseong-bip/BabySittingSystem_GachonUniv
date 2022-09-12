#include <Wire.h>
#include <L3G.h>

long A = 0;
long t = 1;
long t1 = 0;

L3G gyro; // 가속도센서 관련 명령어?

void setup() {
  Serial.begin(9600); //통신속도 설정
  Wire.begin(); // wire 함수

  if (!gyro.init()) // 자이로센서가 인식되지 않을 경우 출력됨
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  else
  gyro.enableDefault(); // 인식될경우 자이로센서 시작
}

void loop() {
  t = millis();
  long delta = t - A;
  A = t;
  if (t - t1 >= 1000){ // 1초 간격으로 가속도 값 출력
    t1 = t; // t - t1 = 0 으로 초기화
    gyro.read();
    Serial.print("[가속도]");
    Serial.print(" [X] ");
    Serial.print((int)gyro.g.x);
    Serial.print(" [Y] ");
    Serial.print((int)gyro.g.y);
    Serial.print(" [Z] ");
    Serial.println((int)gyro.g.z);
    }
}
