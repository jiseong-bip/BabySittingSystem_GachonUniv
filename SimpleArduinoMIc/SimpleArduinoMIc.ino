//code for mic
//by using MAX9814
//
const int input = 0;
int MicVolume = 0; 

void setup()
{
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  MicVolume = (analogRead(input));
  Serial.println(MicVolume);
  delay(5);
}
