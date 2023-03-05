void readSensors(){
    readTemp();
    readBPM();
}

void insertDB(char* _time){
  if (conn.connect(MySQL_Server, 5900, user, password)) {
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    //dtostrf(50.125, 1, 1, temperature);
    sprintf(query, INSERT_DATA, _time,"s0000", Rtemp, bpm_val, babyState);
    cur_mem->execute(query);
    delete cur_mem;
    Serial.println("Data recorded.");
    tempState = false;
  }else{
    Serial.println("Connection failed.");
  }
  conn.close();
}

void printBLE(String _str){
  _str.toCharArray(BLEstr,_str.length()+1);
  pTxCharacteristic->setValue(BLEstr);
  pTxCharacteristic->notify();
}

void printDataRaw() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }
  //Serial.println(&timeinfo, "%Y-%02m-%02d %H:%M:%S");
  sprintf(currTime, "%04d-%02d-%02d %02d:%02d:%02d", timeinfo.tm_year+1900, timeinfo.tm_mon, 
          timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  Serial.printf("[TIME] %s [TEMP] %.1f ", currTime, Rtemp);
  Serial.printf("[BPM] %d\n", bpm_val);
}


/* EEPROM FUNCTION */

template <class T> int writeEEPROM(int ee, const T& value){
  const byte* p = (const byte*)(const void*)&value;
  byte i;
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
    EEPROM.commit();
  //return i;
}

template <class T> int readEEPROM(int ee, T& value){
  byte* p = (byte*)(void*)&value;
  byte i;
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  //return i;
}
