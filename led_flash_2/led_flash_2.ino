int led = 2;
void setup() {
 pinMode (OUTPUT,led); // put your setup code here, to run once:

}

void loop() {
for (int x=0; x<4; x++){
 flash ();
}
 delay (1500);
 for (int x=0; x<3; x++){
 flash ();
 }
 delay (1500);
 for (int x=0; x<2; x++){
  flash();
 }// put your main code here, to run repeatedly:
 delay (1500);
 for (int x=0; x<1; x++){
  flash();
 }
 delay (1500);
 
}
void flash () {
  digitalWrite (led,HIGH);
  delay (200);
  digitalWrite (led,LOW);
  delay(200);
}
