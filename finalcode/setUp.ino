class MyCallbacks: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0){
      memset(bleInput, 0, sizeof bleInput);
      for (int i = 0; i < value.length()+1; i++){
        if((value[i] != '\r')&&(value[i]!='\n')) bleInput[i] = value[i];
      }
      readCmd = true;
    }
  }
};

void setup(){
    Serial.begin(115200);
    particleSensor.begin();
    particleSensor.setup(); // 심박센서 기본 설정으로 센서 구성
    //particleSensor.setPulseAmplitudeRed(0x0A); // 빨간색 LED가 켜져있을 경우 센서가 작동한다는 뜻입니다.
    //particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
    gyro.init();
    gyro.enableDefault(); // 자이로센서 시작
    mlx.begin();
    interrupt_init();
    EEPROM.begin(EEPROM_SIZE);
    initEEPROM();
    getMyEEProm();
    EEPROM.commit();
    BLEDevice::init("ESP32-BLE-01");
    BLEServer *pServer = BLEDevice::createServer();
  
    BLEService *pService = pServer->createService(SERVICE_UUID);
  
    pTxCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_BROADCAST |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                        
    //pTxCharacteristic->addDescriptor(new BLE2902());
  
    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID_RX,
                                           BLECharacteristic::PROPERTY_READ |
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
  
    pRxCharacteristic->setCallbacks(new MyCallbacks());
    pService->start();
  
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
  
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network:
      status = WiFi.begin(ssid, pass);
      // wait 10 seconds for connection:
      delay(10000);
    }
    configTime(3600 * timeZone, 3600 * summerTime, ntpServer); //init and get the time
    Serial.println("WiFi Connected - Setup Done..");
    //insertDB();
}

boolean initEEPROM(){
    if (!(EEPROM.read(EEPROM_INIT_FLAG) == 0x77 && EEPROM.read(EEPROM_INIT_FLAG+1) == 0x33)){
        Serial.println (F("Erasing EEPROM----- "));
        for (int i = 0; i < EEPROM_SIZE; i++){
            EEPROM.write(i, 0);
        }
        EEPROM.write(EEPROM_INIT_FLAG, 0x77);
        EEPROM.write(EEPROM_INIT_FLAG+1, 0x33);
    }//if
    
    if (!(EEPROM.read(EEPROM_INIT_FLAG+2) == 0xAA && EEPROM.read(EEPROM_INIT_FLAG+3) == 0x55)){
        initEEPROMData();
        EEPROM.write(EEPROM_INIT_FLAG+2,0xAA);
        EEPROM.write(EEPROM_INIT_FLAG+3,0x55);
    }// if
    
    #define UPDATE_FLAG 0x55
    if (EEPROM.read(EEPROM_CUSTOM_FLAG) != UPDATE_FLAG){         
          EEPROM.write(EEPROM_CUSTOM_FLAG,UPDATE_FLAG);
    }// if
}// initEEPROM

void initEEPROMData(){
     int ADD_TEST = TEST_BASE;
     writeEEPROM(ADD_TEST, testNum);
}

void getMyEEProm(){
     int ADD_TEST = TEST_BASE;
     readEEPROM(ADD_TEST, testNum);
}
