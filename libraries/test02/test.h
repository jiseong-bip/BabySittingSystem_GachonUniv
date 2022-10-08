#define _1_SECOND  1000/40                       // Constant for timer setting in times of 40ms 

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
unsigned int inputTimer = 0;
unsigned int secTimer = _1_SECOND; 
unsigned int tenSecTimer = 10; 
unsigned int minTimer = 60; 
boolean flagOneSec = false;
boolean flagTenSec = false;
boolean flagOneMin = false;

/*
   WiFi
*/
const char* ssid = "GC_free_WiFi";        // WiFi의 SSID(수정필요)
const char* pass = "";     // WiFi의 비밀번호(수정필요)

/*
   MySQL
*/
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char user[] = "root";              // MySQL user login username
char password[] = "1q2w3e4r!";        // MySQL user login password
char INSERT_DATA[] = "INSERT INTO status.tbl_status VALUES('%s','%s', %0.1lf, %d, '%s')";
char query[128];
char temperature[10];
