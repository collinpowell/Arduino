int led =9;
int button = 7;
int buttonState;
void setup() {
 pinMode(led,OUTPUT);
 pinMode(button,INPUT);
 // put your setup code here, to run once:

}

void loop() {
  buttonState=digitalRead(button);
  if (buttonState==HIGH){
    for(int x=0; x<3;x++){
      flash();
    }
  }else {
    digitalWrite(led,LOW);
  }
}

 void flash(){
  digitalWrite(led,HIGH);
  delay(200);
  digitalWrite(led,LOW);
  delay(200);
 }
