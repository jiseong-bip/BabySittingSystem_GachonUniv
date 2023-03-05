/* EEPROM Members */
#define EEPROM_SIZE                               1000      
#define START_EEPROM                              50
#define TEST_BASE                                 50
#define EEPROM_CUSTOM_FLAG                        EEPROM_SIZE-15
#define EEPROM_INIT_FLAG                          EEPROM_SIZE-7 
#define INPUT_TIME                                30 
#define SERVICE_UUID                              "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX                    "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX                    "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

/* WiFi Members */
char ssid[] = "GC_free_WiFi";           //  your network SSID (name)
char pass[] = "";      //  your network password
int status = WL_IDLE_STATUS;      //  the Wifi radio's status

/* BLE Members */
boolean readCmd = false;
char bleInput[256];
char BLEstr[100];
volatile bool interruptCounter = false;
hw_timer_t * timer = NULL;

/* MySQL Members */
char user[] = "root";              // MySQL user login username
char password[] = "1q2w3e4r!";     // MySQL user login password
char INSERT_DATA[] = "INSERT INTO status.tbl_status VALUES ('%s', '%s', %.1f, %d, '%s')";
char query[128];
char currTime[64];

/* Timer Interrupt Members */
bool flagOneSec = false;
bool flagTenSec = false;
bool flagOneMin = false;
bool flagOneHour = false;
bool flagThreeSec = false;
bool tempState = false;

unsigned int tenSecTimer = 5;
unsigned int threeSecTimer = 3; 
unsigned int minTimer = 60; 
unsigned int hourTimer = 3600; 
unsigned int inputTimer = 0;

/* Menu Members */
boolean adminMode = false;
String mCommand = "";
String argument = "";
String argument1 = "";
String argument2 = "";
String argument3 = "";
int testNum = 6163;

/* TimeZone Members */
const char* ntpServer = "pool.ntp.org";
uint8_t timeZone = 9;
uint8_t summerTime = 0; // 3600


/* SENSOR Members */
float Rtemp=0; // 온도센서 관련상수
int bpm_val;
float GX; float GY; float GZ; // 자이로 센서 관련 상수
// 심박수 센서 관련 상수
long t = 1;
const int MPU_addr = 0x68;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg; // float에서 int로 수정
String babyState = "";
int avr = 1590;
 
