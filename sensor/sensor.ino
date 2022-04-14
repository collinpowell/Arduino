
int sensor = 3;
int state;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(INPUT,sensor);

}

void loop() {
  // put your main code here, to run repeatedly:

  state = digitalRead(sensor);
  Serial.println(state);
  
   

}
