
#include "config.h"

String variable = "";
float ax, ay, az;

#define IO_LOOP_DELAY 6000
unsigned long lastUpdate = 0;

AdafruitIO_Feed *Ax = io.feed("Ax");

AdafruitIO_Feed *Ay = io.feed("Ay");

AdafruitIO_Feed *Az = io.feed("Az");



void setup() {

  Serial.begin(9600);

  while (! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();

  Serial.println("1");

  while (Serial.available()) {

    char entrante = Serial2.read();
    if ( entrante != '\n') variable.concat(entrante);
    else {
      Serial.println(variable);
      ax = (variable.substring(0, 7)).toFloat();
      ay = (variable.substring(7, 14)).toFloat();
      Serial.println(variable.substring(14, 21));
      az = (variable.substring(14, 21)).toFloat();
      variable = "";

      if (millis() > (lastUpdate + IO_LOOP_DELAY)) {

        Serial.print("sending -> ");
        Serial.println(ax);
        Ax->save(ax);
        Serial.print("sending -> ");
        Serial.println(ay);
        Ay->save(ay);
        Serial.print("sending -> ");
        Serial.println(az);
        Az->save(az);


        // after publishing, store the current time
        lastUpdate = millis();
      }

    }
  }
}
