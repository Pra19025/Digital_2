//PARA DEBOUNCE 1
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
const int buttonPin = PUSH2;     // the number of the pushbutton pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

//PARA DEBOUNCE 2
int ledState2 = HIGH;         // the current state of the output pin
int buttonState2;             // the current reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin
const int buttonPin2 = PA_2;     // the number of the pushbutton pin
long lastDebounceTime2 = 0;  // the last time the output pin was toggled
long debounceDelay2 = 50;    // the debounce time; increase if the output flickers

//PARA DEBOUNCE 3
int ledState3 = HIGH;         // the current state of the output pin
int buttonState3;             // the current reading from the input pin
int lastButtonState3 = LOW;   // the previous reading from the input pin
const int buttonPin3 = PA_3;     // the number of the pushbutton pin
long lastDebounceTime3 = 0;  // the last time the output pin was toggled
long debounceDelay3 = 50;    // the debounce time; increase if the output flickers


//variables
int contador1 = 0;
int contador2 = 0;




//prototipos de funciones
void semaforo(void);
void boton1(void);


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(PA_2, INPUT_PULLUP);
  pinMode(PA_3, INPUT_PULLUP);
  pinMode(PA_7, OUTPUT);
  pinMode(PA_6, OUTPUT);
  pinMode(PA_5, OUTPUT);
  pinMode(PB_4, OUTPUT);
  pinMode(PE_5, OUTPUT);
  pinMode(PE_4, OUTPUT);
  pinMode(PB_1, OUTPUT);
  pinMode(PB_0, OUTPUT);
}

void loop() {
  //BOTON 1
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;
    if (buttonState == 0) {
      semaforo();
    }

  }

  //BOTON 2
  int reading2 = digitalRead(buttonPin2);
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay2) {
    buttonState2 = reading2;
    if (buttonState2 == 0) {
     delay(100);
      boton1();
      
      contador1++;
    }

  }




  lastButtonState = reading;




}


void semaforo(void) {


  digitalWrite(RED_LED, 1);
  delay(1000);
  digitalWrite(RED_LED, 1);
  digitalWrite(GREEN_LED, 1);
  delay(1000);
  digitalWrite(GREEN_LED, 1);
  digitalWrite(RED_LED, 0);
  delay(1000);

  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BLUE_LED, 0);

}

void boton1(void) {

  if (contador1 == 0) {
    digitalWrite(PA_7, 1);
    return;
  }


  if (contador1 == 1) {
    digitalWrite(PA_7, 0);
    digitalWrite(PA_6, 1);
    return;
  }


  if (contador1 == 2) {
    digitalWrite(PA_5, 1);
    digitalWrite(PA_6, 0);
    return;
  }

}
