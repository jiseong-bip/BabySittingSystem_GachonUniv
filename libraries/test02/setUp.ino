void setup(){
  Serial.begin(115200); // 통신속도 설정
  Wire.begin(); // wire 함수
  TcTimer5::begin();
  TcTimer5::start(secService);
  if (!gyro.init() || !particleSensor.begin(Wire, I2C_SPEED_FAST)){ 
    // 자이로 혹은 심박센서가 인식되지 않을 경우 출력됩니다.
    Serial.println("No detecting gyro or bpm sensor");
  }else{
      gyro.enableDefault(); // 자이로센서 시작
      particleSensor.setup(); // 심박센서 기본 설정으로 센서 구성
      particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻입니다.
      particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
      mlx.begin(); // 온도센서 시작
  }
  Serial.println("Setup Done..");
}

void secService(){
    flagOneSec = true;
    if (!--tenSecTimer){
        tenSecTimer = 10;
        flagTenSec = true;
    }
    if (!--minTimer){
        minTimer = 60;
        flagOneMin = true;
    }
    /*if(inputTimer){ // for menuservice timer
        inputTimer--;
    }*/ 
}
