ISR(TIMER1_COMPA_vect){ 
    interrupts();
    if(!--sendTimer){
       sendData = true;
       sendTimer = _1_SECOND;
    }
    if(!--gyroTimer){
       gyroFlag = true;
       gyroTimer = _1_SECOND;
    }
    if(!--gyroTimer){
       tempFlag = true;
       tempTimer = _1_SECOND;
    }
    if(!--bpmTimer){
       bpmFlag = true;
       bpmTimer = _1_SECOND;
    }
}


// boolean sendData = false;
// boolean gyroFlag = false;
// boolean tempFlag = false;
// boolean bpmFlag = false;
