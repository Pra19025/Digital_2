



void setup() {
  // put your setup code here, to run once:
pinMode(RED_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT);
pinMode(BLUE_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   
  semaforo();
  
}


void semaforo(void){
  digitalWrite(RED_LED,0);
  digitalWrite(GREEN_LED,0);
  digitalWrite(BLUE_LED, 0);
  
  digitalWrite(RED_LED,1);
  delay(1000);
  digitalWrite(RED_LED,1);
  digitalWrite(GREEN_LED,1);
  delay(1000);
  digitalWrite(GREEN_LED,1);
  digitalWrite(RED_LED,0);
  delay(1000);
  
}
