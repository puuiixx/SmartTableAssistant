#include <Servo.h>
#include <EEPROM.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
char receivedData[32] = "";
int  boto1state, boto2state, xAxis, yAxis, recordState, playState, resetState, tornarState;

int servoPin = 9;
int servoPin2 = 10;
int servoPin3 = 3;
int servoPin4 = 4;

int addr;

int val1;
int val2;
int val3;
int val4;

int direccio;
int accio;
int res;

Servo myServo;
Servo myServo2;
Servo myServo3;
Servo myServo4;


void setup() {

  Serial.begin(9600);

  myServo.attach(servoPin);
  myServo2.attach(servoPin2);
  myServo3.attach(servoPin3);
  myServo4.attach(servoPin4);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop()
{

  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    boto1state = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    boto2state = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    xAxis = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    yAxis = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    recordState = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    playState = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    resetState = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    tornarState = atoi(&receivedData[0]);
    delay(1);
  }


  if (resetState == 1023)
  {
    Serial.println("Borrando EEPROM, espere...");
    for (addr = 0; addr <= 512; addr++) {
      EEPROM.write(addr, 255);
    }
    addr = 0;

    Serial.println("EEPROM borrada");
  }

  if (recordState == 1023)
  {
    delay(270);
    grabaServos(servoPin, servoPin2, servoPin3, servoPin4, recordState);


  }

  else {

  }

  if (playState == 1023)
  {
    delay(270);
    ejecutaServos(servoPin, servoPin2, servoPin3, servoPin4, playState);

  }

  else {

    switch (accio) {
      case 'M':
        girarA(servoPin, servoPin2, servoPin3, servoPin4);
        delay(1);
        break;

      case 'N':
        girarB(servoPin, servoPin2, servoPin3, servoPin4);
        delay(1);
        break;
    }

    if (yAxis > 550) {
      if (xAxis > 550) {
        endavantdreta(servoPin, servoPin2, servoPin3, servoPin4);
        delay(1);


      }
      else {
        if (xAxis < 470) {
          endavantesquerra(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);


        }
        else {
          endavant(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);

        }
      }

    }
    else {
      if (yAxis < 470) {
        if (xAxis > 550) {
          enreredreta(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);

        }
        else {
          if (xAxis < 470) {
            enrereesquerra(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);



          }
          else {
            enrere(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);

          }
        }
      }

      else {
        if (xAxis > 550) {
          dreta(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);

        }
        else {
          if (xAxis < 470) {
            esquerra(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);
          }
          else {
            quieto(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);

          }
        }
      }
    }
  }

  if (tornarState == 1023)
  {

    delay(270);
    tornarMateix(servoPin, servoPin2, servoPin3, servoPin4, tornarState);

  }

  else {

    switch (accio) {
      case 'M':
        girarA(servoPin, servoPin2, servoPin3, servoPin4);
        delay(1);
        break;

      case 'N':
        girarB(servoPin, servoPin2, servoPin3, servoPin4);
        delay(1);
        break;
    }

    if (yAxis > 550) {
      if (xAxis > 550) {
        endavantdreta(servoPin, servoPin2, servoPin3, servoPin4);
        delay(1);


      }
      else {
        if (xAxis < 470) {
          endavantesquerra(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);


        }
        else {
          endavant(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);

        }
      }

    }
    else {
      if (yAxis < 470) {
        if (xAxis > 550) {
          enreredreta(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);

        }
        else {
          if (xAxis < 470) {
            enrereesquerra(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);



          }
          else {
            enrere(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);

          }
        }
      }

      else {
        if (xAxis > 550) {
          dreta(servoPin, servoPin2, servoPin3, servoPin4);
          delay(1);

        }
        else {
          if (xAxis < 470) {
            esquerra(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);
          }
          else {
            quieto(servoPin, servoPin2, servoPin3, servoPin4);
            delay(1);

          }
        }
      }
    }
  }
}



void ejecutaServos (int servoPin, int servoPin2, int servoPin3, int servoPin4, int playState) {
  addr = 0;

  Serial.println("Activando Servos");
  myServo.attach(servoPin);
  myServo2.attach(servoPin2);
  myServo3.attach(servoPin3);
  myServo4.attach(servoPin4);
  while (playState == 1023)
  {

    int direccio = EEPROM.read(addr);
    Serial.print("Lee EE: "); Serial.print(direccio);
    if (direccio == 255) break;

    /* if (sadad) {}*/

    switch (EEPROM.read(addr)) {
      case 'a':
        val1 = 0;
        val2 = 180;
        val3 = 0;
        val4 = 180;
        Serial.println("Endavant");
        break;

      case 'b':
        val1 = 180;
        val2 = 0;
        val3 = 180;
        val4 = 0;
        Serial.println("enrere");
        break;

      case 'c':
        val1 = 0;
        val2 = 90;
        val3 = 90;
        val4 = 180;
        Serial.println("endavantdreta");
        break;

      case 'd':

        val1 = 90;
        val2 = 180;
        val3 = 0;
        val4 = 90;
        Serial.println("endavantesquerra");
        break;

      case 'e':

        val1 = 90;
        val2 = 0;
        val3 = 180;
        val4 = 90;
        Serial.println("enreredreta");
        break;

      case 'f':
        val1 = 180;
        val2 = 90;
        val3 = 90;
        val4 = 0;
        Serial.println("enrereesquerra");
        break;

      case 'g':
        val1 = 0;
        val2 = 0;
        val3 = 180;
        val4 = 180;
        Serial.println("dreta");
        break;

      case 'h':
        val1 = 180;
        val2 = 180;
        val3 = 0;
        val4 = 0;
        Serial.println("esquerra");
        break;

      case 'i':
        val1 = 90;
        val2 = 90;
        val3 = 90;
        val4 = 90;
        Serial.println("quieto");
        break;

      case 'z':
        val1 = 180;
        val2 = 180;
        val3 = 180;
        val4 = 180;
        Serial.println("girarA");
        break;

      case 'q':
        val1 = 0;
        val2 = 0;
        val3 = 0;
        val4 = 0;
        Serial.println("girarB");
        break;

    }


    myServo.write(val1);
    myServo2.write(val2);
    myServo3.write(val3);
    myServo4.write(val4);

    delay(540);
    addr++;
    if (addr == 512) break;

  }

  Serial.println(" y acaba");
  delay(300);
}


void grabaServos(int servoPin, int servoPin2, int servoPin3, int servoPin4, int recordState) {

  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    xAxis = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    yAxis = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    recordState = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    playState = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    resetState = atoi(&receivedData[0]);
    delay(1);
    radio.read(&receivedData, sizeof(receivedData));
    tornarState = atoi(&receivedData[0]);
    delay(1);
  }

  Serial.println("Grabando posiciones");

  switch(accio){
    case 'M':
    EEPROM.write(addr, 'z');
    break;

    case 'N':
    EEPROM.write(addr, 'q');
    break;
      }

  if (yAxis > 550) {
    if (xAxis > 550) {
      EEPROM.write(addr, 'c');

    }
    else {
      if (xAxis < 470) {
        EEPROM.write(addr, 'd');


      }
      else {
        EEPROM.write(addr, 'a');

      }
    }

  }
  else {
    if (yAxis < 470) {
      if (xAxis > 550) {
        EEPROM.write(addr, 'e');

      }
      else {
        if (xAxis < 470) {
          EEPROM.write(addr, 'f');



        }
        else {
          EEPROM.write(addr, 'b');

        }
      }
    }

    else {
      if (xAxis > 550) {
        EEPROM.write(addr, 'g');

      }
      else {
        if (xAxis < 470) {
          EEPROM.write(addr, 'h');
        }
        else {
          EEPROM.write(addr, 'i');

        }
      }
    }
  }



  addr++;
  Serial.println(addr);
  Serial.println("Posiciones grabadas");
  delay(300);


}


void tornarMateix (int servoPin, int servoPin2, int servoPin3, int servoPin4, int tornarState) {


  Serial.println("Activando retorno");
  myServo.attach(servoPin);
  myServo2.attach(servoPin2);
  myServo3.attach(servoPin3);
  myServo4.attach(servoPin4);
  while (tornarState == 1023)
  {

    int direccio = EEPROM.read(addr);
    Serial.print("Lee EE: "); Serial.print(direccio);


    switch (EEPROM.read(addr)) {
      case 'a':
        val1 = 180;
        val2 = 0;
        val3 = 180;
        val4 = 0;
        Serial.println("Endavant");
        break;

      case 'b':
        val1 = 0;
        val2 = 180;
        val3 = 0;
        val4 = 180;
        Serial.println("enrere");
        break;

      case 'c':
        val1 = 180;
        val2 = 90;
        val3 = 90;
        val4 = 0;
        Serial.println("endavantdreta");
        break;

      case 'd':

        val1 = 90;
        val2 = 0;
        val3 = 180;
        val4 = 90;
        Serial.println("endavantesquerra");
        break;

      case 'e':

        val1 = 90;
        val2 = 180;
        val3 = 0;
        val4 = 90;
        Serial.println("enreredreta");
        break;

      case 'f':
        val1 = 0;
        val2 = 90;
        val3 = 90;
        val4 = 180;
        Serial.println("enrereesquerra");
        break;

      case 'g':
        val1 = 180;
        val2 = 180;
        val3 = 0;
        val4 = 0;
        Serial.println("dreta");
        break;

      case 'h':
        val1 = 0;
        val2 = 0;
        val3 = 180;
        val4 = 180;
        Serial.println("esquerra");
        break;

      case 'i':
        val1 = 90;
        val2 = 90;
        val3 = 90;
        val4 = 90;
        Serial.println("quieto");
        break;

      case 'z':
        val1 = 0;
        val2 = 0;
        val3 = 0;
        val4 = 0;
        Serial.println("girarA");
        break;

      case 'q':
        val1 = 180;
        val2 = 180;
        val3 = 180;
        val4 = 180;
        Serial.println("girarB");
        break;

    }


    myServo.write(val1);
    myServo2.write(val2);
    myServo3.write(val3);
    myServo4.write(val4);

    delay(540);
    addr--;
    Serial.println(addr);
    if (addr == 0) break;

  }

  Serial.println(" y acaba");
  delay(300);
}

void endavant(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("Endavant");
  myServo.write(0);
  myServo2.write(180);
  myServo3.write(0);
  myServo4.write(180);

  val1 = 0;
  val2 = 180;
  val3 = 0;
  val4 = 180;

  int direccio = 'a';

}

void enrere(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("Enrere");
  myServo.write(180);
  myServo2.write(0);
  myServo3.write(180);
  myServo4.write(0);

  val1 = 180;
  val2 = 0;
  val3 = 180;
  val4 = 0;

  int direccio = 'b';
}

void endavantdreta(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("EndavantDreta");
  myServo.write(0);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(180);

  val1 = 0;
  val2 = 90;
  val3 = 90;
  val4 = 180;

  int direccio = 'c';
}

void endavantesquerra(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("EndavantEsquerra");
  myServo.write(90);
  myServo2.write(180);
  myServo3.write(0);
  myServo4.write(90);

  val1 = 90;
  val2 = 180;
  val3 = 0;
  val4 = 90;

  int direccio = 'd';
}

void enreredreta(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("EnrereDreta");
  myServo.write(90);
  myServo2.write(0);
  myServo3.write(180);
  myServo4.write(90);

  val1 = 90;
  val2 = 0;
  val3 = 180;
  val4 = 90;

  int direccio = 'e';

}

void enrereesquerra(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("EnrereEsquerra");
  myServo.write(180);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(0);

  val1 = 180;
  val2 = 90;
  val3 = 90;
  val4 = 0;

  int direccio = 'f';
}

void dreta(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("Dreta");
  myServo.write(0);
  myServo2.write(0);
  myServo3.write(180);
  myServo4.write(180);

  val1 = 0;
  val2 = 0;
  val3 = 180;
  val4 = 180;

  int direccio = 'g';
}

void esquerra(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("Esquerra");
  myServo.write(180);
  myServo2.write(180);
  myServo3.write(0);
  myServo4.write(0);

  val1 = 180;
  val2 = 180;
  val3 = 0;
  val4 = 0;

  int direccio = 'h';

}

void quieto(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("quieto");
  myServo.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);

  val1 = 90;
  val2 = 90;
  val3 = 90;
  val4 = 90;

  int direccio = 'i';
}

void girarA(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("girarA");
  myServo.write(180);
  myServo2.write(180);
  myServo3.write(180);
  myServo4.write(180);

  val1 = 180;
  val2 = 180;
  val3 = 180;
  val4 = 180;

  int direccio = 'z';
}

void girarB(int servoPin, int servoPin2, int servoPin3, int servoPin4) {

  Serial.println("girarB");
  myServo.write(0);
  myServo2.write(0);
  myServo3.write(0);
  myServo4.write(0);

  val1 = 0;
  val2 = 0;
  val3 = 0;
  val4 = 0;

  int direccio = 'q';
}

void botoaccio() {

  if (boto1state == 1023) {
    int accio = 'M';
  }

  else {

  }

  if (boto2state == 1023) {
    int accio = 'N';
  }
  else {

  }
}
