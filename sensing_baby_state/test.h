#define _01_SECOND  100/40
#define _1_SECOND  1000/40                       // Constant for timer setting in times of 40ms 
#define _2_SECOND 2000/40
#define _3_SECOND 3000/40
#define _5_SECOND 5000/40
#define _10_SECOND 10000/40
#define _2_MIN 120000/40
#define _1_HOUR 3600000/40

float GX; float GY; float GZ; // 자이로 센서 관련 상수
float Rtemp; // 온도센서 관련상수
// 심박수 센서 관련 상수
long t = 1;
long irValue;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg; // float에서 int로 수정
boolean fallbaby = false; // 아기가 떨어지면 1로 변함
String state = "";


/*
  Timer
*/
unsigned int gyroTimer = _1_SECOND;
unsigned int tempTimer = _1_SECOND;
unsigned int bpmTimer = _1_SECOND;
unsigned int sendTimer = _1_SECOND;


boolean sendData = false;
boolean gyroFlag = false;
boolean tempFlag = false;
boolean bpmFlag = false;

