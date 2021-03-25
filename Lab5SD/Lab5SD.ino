// Noel Prado
//19025
//Laboratorio 5


#include <SPI.h>
#include <SD.h>
File root;
File myFile;
int inByte = 0;
int control = 0;
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  SPI.setModule(0);

  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  //root = SD.open("/");
  printDirectory();
    Serial.println();
    printDirectory();
    
  Serial.println();

}

void loop()
{
  if (control == 0) {
    Serial.println();
    Serial.println("**************************************");
    Serial.println("Seleccione que dibujo desea visualziar");
    Serial.println("**************************************");
    Serial.println();
    Serial.println();
    printDirectory();
    Serial.println();
    Serial.println("**************************************");
    control = 1;

  }
  //se revisa que selecciona el usuario
  if (Serial.available()) {
    inByte = Serial.read();
  
  }
 if (inByte == '1') {
      control = 0;
      
      myFile = SD.open("/mew.txt");
      if (myFile) {
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println();
      inByte = 0;
    }

    if (inByte == '2') {
      control = 0;

      myFile = SD.open("/icon.txt");
      if (myFile) {
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println();
      inByte = 0;
    }

    if (inByte == '3') {
      control = 0;

      myFile = SD.open("/pikachu.txt");
      if (myFile) {
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println();
      inByte = 0;
    }


}

void printDirectory() {
  delay(250);
  myFile = SD.open("/");
  myFile.rewindDirectory(); 
    
  while (true) {

    File entry =  myFile.openNextFile();
    if (! entry) {
      // no more files
      return;//break;
    }
    /*for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }*/
    Serial.println(entry.name());
    /*if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\n");
    }*/
    entry.close();
  }
}
