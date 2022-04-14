char inputChar = "";         // a String to hold incoming data
bool stringComplete = false;
int buzzer = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(OUTPUT,buzzer);

}

void loop() {
  // put your main code here, to run repeatedly:

  while(Serial.available()>0){
    inputChar= Serial.read(); 
    if (inputChar=='F'){
      Serial.println(inputChar);
    }
    else if (inputChar=='B'){
      Serial.println(inputChar);
    } 
  }

}
