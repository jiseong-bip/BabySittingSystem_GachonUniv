void gyroState(){
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

void getTemperature(){ 
  Rtemp = mlx.readObjectTempC() * 36 / 46;
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
}

void GyroPrint(){ //자이로 값 시리얼 모니터로 나타내기
  gyroState();
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
  getTemperature();
  Serial.print("[체온] ") ; Serial.print(Rtemp); Serial.println("*C"); // 체온 출력
  }

void BPMPrint(){ //심박수 값 시리얼 모니터로 나타내기
  BPM();
  if (irValue > 50000){ // 보통 사람피부에 접촉할 경우 적외선 값이 7~10만 사이의 값이 출력됨
  Serial.print("[AvgBPM] "); Serial.println(beatAvg);
  }
  else{  // 적외선 값이 5만 이하일 경우 신체와 접촉해 있지 않다고 판단
  Serial.println("No detecting body");
  }
}

void inputData(){
  if (conn.connect(server_addr1, 5900, user, password)){
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    sprintf(query, INSERT_DATA, "09/27 19:00", "jiseong", temperature, beatAvg, "false");
    cur_mem->execute(query);
    delete cur_mem;
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}
