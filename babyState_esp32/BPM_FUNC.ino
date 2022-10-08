void readBPM(){
  bpm_val = particleSensor.getIR(); // 심박센서 값 설정
  if (checkForBeat(bpm_val) == true){
    long delta = t - lastBeat;
    lastBeat = t;
    beatsPerMinute = 60 /(delta/1000.0);
    //if(beatsPerMinute < 255 & beatsPerMinute > 20){
    //  rates[rateSpot++] = (byte)beatsPerMinute;
    //  rateSpot %= RATE_SIZE;
    //  beatAvg = 0;
    //  for (byte x = 0 ; x < RATE_SIZE ; x++) beatAvg += rates[x];
    //  beatAvg /= RATE_SIZE;
    //}
    rates[rateSpot++] = (byte)beatsPerMinute;
    rateSpot %= RATE_SIZE;
    beatAvg = 0;
    for (byte x = 0 ; x < RATE_SIZE ; x++) {beatAvg += rates[x];}
    //bpm_val /= 1590;
  }
  
  if (bpm_val > 50000){ // 보통 사람피부에 접촉할 경우 적외선 값이 7~10만 사이의 값이 출력됨
    bpm_val /= avr;
    
  }else{  // 적외선 값이 5만 이하일 경우 신체와 접촉해 있지 않다고 판단
    //Serial.println("No detecting body");
    bpm_val = 0;
  }
}
