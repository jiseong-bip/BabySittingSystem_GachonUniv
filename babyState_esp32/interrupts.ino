void IRAM_ATTR onTimer(){
  secService();
}

void interrupt_init(){
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void secService(){
  flagOneSec = true;
  if (!--hourTimer){
      hourTimer = 3600;
      flagOneHour = true;
  }
  if (!--tenSecTimer){
      tenSecTimer = 10;
      flagTenSec = true;
  }
  if (!--minTimer){
      minTimer = 60;
      flagOneMin = true;
  }
}

