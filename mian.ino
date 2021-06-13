#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
int smoke_sense = 250;
void send_sms(String msg)
{
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"08051230116\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(msg); //text content
  updateSerial();
  mySerial.write(26);
  updateSerial();
  }
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  pinMode(A3, INPUT);
pinMode(13, OUTPUT);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
}

void loop()
{
  Serial.println(analogRead(A3));
  if(analogRead(A3) > smoke_sense)
  {
  send_sms("Alert! Alert!, Smoke Detected at your Apartment. Do something about it now!");
  while (analogRead(A3) > smoke_sense)
  {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  }
  }

 
}





void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
