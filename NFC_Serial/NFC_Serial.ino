#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(3, 2); //A6 Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(115200);

  //Begin serial communication with Arduino and A6
  mySerial.begin(115200);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+SAPBR=1,1\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+HTTPINIT\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+HTTPPARA=\"CID\",1\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+HTTPPARA=\"URL\",\"http://myengineeringstuffs.com/test/t...\"\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+HTTPACTION=0\r\n"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+HTTPREAD=0,29\r\n"); //Check whether it has registered in the network
  updateSerial();

}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
