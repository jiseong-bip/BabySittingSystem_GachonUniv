
void setup() {
  Serial.begin(115200); // 통신속도 설정
  Wire.begin(); // wire 함수
  startTimer40ms();

  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr1, 3306, user, password)) {
    delay(1000);
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Save
    sprintf(query, INSERT_DATA, "09/27 19:00", "jiseong", 36, 85, "false");
    // Execute the query
    cur_mem->execute(query);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    Serial.println("Data recorded.");
  }
  else
    Serial.println("Connection failed.");
  conn.close();

  if (!gyro.init() || !particleSensor.begin(Wire, I2C_SPEED_FAST)){ 
    // 자이로 혹은 심박센서가 인식되지 않을 경우 출력됩니다.
    Serial.println("No detecting gyro or bpm sensor");
  }
  else{
  gyro.enableDefault(); // 자이로센서 시작
  particleSensor.setup(); // 심박센서 기본 설정으로 센서 구성
  particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻입니다.
  particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
  mlx.begin(); // 온도센서 시작
  }
  Serial.println("Setup Done..");
}

void startTimer40ms() {
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  //OCR1A = 31;    // 4ms for SDMS-30 main board with 2561 
  OCR1A = 310;    // 40ms for SDMS-30 main board with 2561 
  //OCR1A = 155;    // 20ms for SDMS-30 main board with 2561 
  //OCR1A = 7812;    // 1000ms for SDMS-30 main board with 2561 

  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);

  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);

  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
}  