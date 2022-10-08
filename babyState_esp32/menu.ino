boolean noArgument; 
boolean numberArgument = false;
boolean numberArgument1 = false;
byte serialChar = '\0';

void menuService(){
        
        if(!readCmd){
          if(!Serial.available()) return;
        }
        char _input[50];
        int t, t1, t2;
        if(readCmd){
          readCmd = false;
          mCommand = strtok (bleInput, " ");
          argument = strtok (NULL, " ");
          /*argument1 = (String) strtok (NULL, " ");
          argument2 = (String) strtok (NULL, " ");
          argument3 = (String) strtok (NULL, " ");*/
       }else{
          if (!readSerialLine(_input, 48, INPUT_TIME, false)){
            return;
          }
          mCommand = strtok (_input, " ");
          argument = strtok (NULL, " ");
          /*argument1 = (String) strtok (NULL, " ");
          argument2 = (String) strtok (NULL, " ");
          argument3 = (String) strtok (NULL, " ");*/
       }
      if (argument == NULL){  
          noArgument = true;
      } else {
          noArgument = false;
          argument.toCharArray(_input, 20);
      }
          
      numberArgument = parseIntInput (argument, &t);
      numberArgument1 = parseIntInput (argument1, &t1);
      if(argument == "0"){
          numberArgument = true;
      }
      if(argument1 == "0"){
          numberArgument1 = true;
      }
      if(!numberArgument){
          t = 0;
      }
      if(!numberArgument1){
          t1 = -999;
      }

      if(mCommand == "-=-="){
          Serial.println("ADMIN MODE..");
          printBLE("ADMIN MODE..\n");
          adminMode = true;
          return;
      }else if(mCommand == "exit"){
          Serial.println("USER MODE..");
          printBLE("USER MODE..\n");
          adminMode = false;
          return;
      }else if(mCommand == "@insertdb"){
          insertDB(currTime);
          return;
      }
      mCommand = "";
      argument = "";
      argument1 = "";
      argument2 = "";
      argument3 = "";
}

boolean readSerialLine(char* _input, int _bufSize, int _timer, boolean _echo){
    char _c = 0;
    inputTimer = _timer;
    byte i = 0;
    _input[0] = 0;
    
    while((_c != '\r')&&(_c!='\n')){
         if(!inputTimer){
             Serial.print ("\r\ntime-out... try again.\r\n");            // Serial.print ("User input time-out");
             _input[0] = '\0'; 
             return false;
         }
         if(Serial.available()){
             if(serialChar){                    // this is to resolve the issue with lines with or without /r/n 
                 _c = serialChar;               // left over character from the previous reading 
                 serialChar = 0;
             } else {
                _c = Serial.read();
             }
             
             if (_echo){
                 Serial.write (_c);
             }
             if((_c != '\r')&&(_c!='\n')){
                 _input[i]= _c;
                 if (i < _bufSize-1){
                    i++;                      // overwrite 
                 }
             }
             
        }// if Serial.available()
    } // while 

    // see if there's any unnecessary \r or \n at once
    delay(10);                                // do not change this unless you're sure
    if(Serial.available()){
        serialChar = Serial.read();
        if(serialChar=='\n' || serialChar=='\r'){
            serialChar = '\0';      // discard. Otherwise, it will be used at the next readline command 
        }
    }
    
    _input[i] = '\0';
    //if (i>0 && _input[0]!= '\r' && _input[0]!= '\n' && _input[0]!= ' '){
    if (i>0){
        return true;
    } else {
        return false;
    }
}
boolean readAnswer(int _time){
    char _buf[25];
    Serial.print (" are you sure? "); 
    inputTimer = _time;
    while(1){
       if(inputTimer == 0){
       return false;
       }
       readSerialLine(_buf, 23, _time, true);
       if (_buf[0] == 'y') {
               Serial.println (" -> confirmed.");
               return true;
        } else {
               Serial.println (" -> cancelled.");
               return false;
        }
    }
}

void warnInvalidInput(){
    Serial.println ("invalid input -> cancelled");
}

void clearSerial(){
    delay(10);  
    while(Serial.available()){
        Serial.read();
        delay(10);  
    }
}

boolean parseIntInput(String s, int* t){
    if(s == "00"){        // toint doesn't work for 00
        t[0] = 0;
        return true;
    }
    t[0] = s.toInt();
    if (t[0] == 0){
        return false;
    } else {
        return true;
    }
}
