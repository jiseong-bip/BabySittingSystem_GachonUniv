#include <Wire.h>
#include <Adafruit_MLX90614.h>

long A = 0;
long t = 1;
long t1 = 0;

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // 라이브러리 생성
 
void setup() {
  Serial.begin(9600); // 통신속도 설정
  mlx.begin(); // 온도센서 시작
}
void loop() {
  t = millis();
  long delta = t - A;
  A = t;
  if (t - t1 >= 1000){ // 1초 간격으로 온도 출력
    t1 = t; // t - t1 = 0 으로 초기화
    float Rtemp = mlx.readObjectTempC() - 10; // 가정용 체온계 보다 대략 10도 높게 나와서 값을 10 정도 깎음
    Serial.print("[체온] ") ; Serial.println(Rtemp); Serial.println("*C"); // [온도] xx.xx*C 로 출력함 
  }
}
