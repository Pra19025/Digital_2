//Noel Prado  19025
//Laboratorio 4

//variables

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

int ledState4 = HIGH;         // the current state of the output pin
int buttonState4;             // the current reading from the input pin
int lastButtonState4 = LOW;   // the previous reading from the input pin
const int buttonPin4 = PUSH1;     // the number of the pushbutton pin
long lastDebounceTime4 = 0;  // the last time the output pin was toggled
long debounceDelay4 = 50;    // the debounce time; increase if the output flickers


int contador1 = 0;
int contador2 = 0;
char control = 0;

int port1[] = {PB_5, PB_0, PB_1, PE_4, PE_5, PB_4, PA_5, PA_6, PA_7};
int port2[] = {PB_2, PE_3, PB_7, PB_6, PA_4, PE_1, PD_7, PD_6, PE_2};



//prototipos de funciones
void semaforo(void);
void boton1(void);
void boton2 (void);


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
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
  pinMode(PB_5, OUTPUT);

  pinMode(PB_2, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PB_7, OUTPUT);
  pinMode(PB_6, OUTPUT);
  pinMode(PA_4, OUTPUT);
  pinMode(PE_1, OUTPUT);
  pinMode(PD_7, OUTPUT);
  pinMode(PD_6, OUTPUT);
  pinMode(PE_2, OUTPUT);


}

void loop() {

  //botones y sus antirebotes
  //---------------------------------------------------------------------------------
  //BOTON 1
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;
    if (buttonState == 0) {
      semaforo();
      control = 1;
      contador1 = 0;
      contador2 = 0;
      for (int i = 0; i < 9; i++) {
        digitalWrite(port1[i], 0);
      }
      for (int i = 0; i < 9; i++) {
        digitalWrite(port2[i], 0);
      }
    }

  }

  //BOTON 2 de la tiva
  int reading4 = digitalRead(buttonPin4);
  if (reading4 != lastButtonState4) {
    lastDebounceTime4 = millis();
  }

  if ((millis() - lastDebounceTime4) > debounceDelay4) {
    buttonState4 = reading4;
    if (buttonState4 == 0) {
      semaforo();
      control = 1;
      contador1 = 0;
      contador2 = 0;
      for (int i = 0; i < 9; i++) {
        digitalWrite(port1[i], 0);
      }
      for (int i = 0; i < 9; i++) {
        digitalWrite(port2[i], 0);
      }
    }

  }

  

  if (control == 1) {

    //BOTON 2
    int reading2 = digitalRead(buttonPin2);
    if (reading2 != lastButtonState2) {
      lastDebounceTime2 = millis();
    }

    if ((millis() - lastDebounceTime2) > debounceDelay2) {
      buttonState2 = reading2;

      if (reading2 == 0) {
        delay(10);
        //se agrego esto para que no se cuenten los avances si no se suelta el boton
        reading2 = digitalRead(buttonPin2);
        if (reading2 == 1) {
          boton1();
          buttonState2 = 1;
          contador1++;

          if (contador1 == 9) {
            control = 0;
            contador1 = 0;
            contador2 = 0;
          }

        }
      }
    }

    //BOTON 3
    int reading3 = digitalRead(buttonPin3);
    if (reading3 != lastButtonState3) {
      lastDebounceTime3 = millis();
    }

    if ((millis() - lastDebounceTime3) > debounceDelay3) {
      buttonState3 = reading3;

      if (reading3 == 0) {
        delay(10);
        //se agrego esto para que no se cuenten los avances si no se suelta el boton
        reading3 = digitalRead(buttonPin3);
        if (reading3 == 1) {
          boton2();
          buttonState3 = 1;
          contador2++;

          if (contador2 == 9) {
            control = 0;
            contador1 = 0;
            contador2 = 0;
          }
        }
      }
    }


    //---------------------------------------------------------------------------------
    //lastButtonState = reading;
    lastButtonState2 = reading2;
    lastButtonState3 = reading3;



  }
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

  for (int i = 0; i < 9; i++) {
    digitalWrite(port1[i], i == contador1);
  }

}

void boton2(void) {

  for (int i = 0; i < 9; i++) {
    digitalWrite(port2[i], i == contador2);
  }

}
