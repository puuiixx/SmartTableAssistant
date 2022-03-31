
  //          PROGRAMA S.T.A STEPPER MOTORS - BLYNK          //

// definim per poder utilizar l'aplicació blynk

#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial1 

#include <BlynkSimpleSerialBLE.h> // llibreria per el bluetooth

char auth[] = "0OC9g-iVlVC3WVey-SJ581kVdCvOfD7y"; // és la clau per conectar-se del bluetooth a l'aplicació del smartphone

// definim constants de les direccions i els stepper motors

const int stepX = 2;
const int dirX  = 5;

const int stepY = 3;
const int dirY  = 6;

const int stepZ = 4;
const int dirZ  = 7;

const int enPin = 8;

int leds = A7; // introduim el pin A7 per les LEDS

void setup()
{
  Serial1.begin(9600); // fem servir serial1 que és una alternativa al serial predeterminat però aquest permet conectar sense problema el bluetooth siguent extern al serial inicial
  Blynk.begin(Serial1, auth);

  pinMode(stepX, OUTPUT); // definim pin de sortida stepX
  pinMode(dirX, OUTPUT); // definim pin de sortida dirX

  pinMode(stepY, OUTPUT); // definim pin de sortida stepY
  pinMode(dirY, OUTPUT); // definim pin de sortida dirX

  pinMode(stepZ, OUTPUT); // definim pin de sortida stepZ
  pinMode(dirZ, OUTPUT); // definim pin de sortida dirZ

  pinMode(enPin, OUTPUT); // definim pin de sortida enPin

  pinMode(leds, OUTPUT); // definim pin de sortida leds

  digitalWrite(enPin, LOW);

}

void loop() {

  if (Serial1.available()) {
    Blynk.run();
  }
}

// si la conexió amb Blynk està estable fes el següent

BLYNK_WRITE(V1) // si premem el botó virtual (del mòvil) 1 fes...
{ 
  int i = param.asInt();
  if (i == 1) { // si està encés
    for (int x = 0; x < 3000; x++) {  // 3000 és la distància que ha de recòrrer
      digitalWrite(dirX, HIGH);

      digitalWrite(stepX, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepX, LOW);

      delayMicroseconds(1000);

    }
  }
  else if (i == 0) { // si està apagat

    for (int x = 0; x < 3000; x++) { // torna a fer 3000 de recorregut però al revès 

      digitalWrite(dirX, LOW);

      digitalWrite(stepX, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepX, LOW);

      delayMicroseconds(1000);

    }
  }
}

BLYNK_WRITE(V2) // si premem el botó virtual (del mòvil) 2 fes...
{
  int i = param.asInt();
  if (i == 1) { // si està encés
    for (int x = 0; x < 5880; x++) { // 5880 és la distància que ha de recòrrer
      digitalWrite(dirY, LOW);

      digitalWrite(stepY, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepY, LOW);

      delayMicroseconds(1000);

    }
  }
  else if (i == 0) { // si està apagat
    for (int x = 0; x < 5880; x++) { // torna a fer 5880 de recorregut però al revès
      digitalWrite(dirY, HIGH);

      digitalWrite(stepY, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepY, LOW);

      delayMicroseconds(1000);

    }
  }
}

BLYNK_WRITE(V3) // si premem el botó virtual (del mòvil) 3 fes...
{
  int i = param.asInt();
  if (i == 1) { // si està encés
    for (int x = 0; x < 6880; x++) { // 6880 és la distància que ha de recòrrer
      digitalWrite(dirZ, LOW);

      digitalWrite(stepZ, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepZ, LOW);

      delayMicroseconds(1000);

    }

  }

  else if (i == 0) { // si està apagat
    for (int x = 0; x < 6880; x++) { // torna a fer 6880 de recorregut però al revès
      digitalWrite(dirZ, HIGH);
      digitalWrite(stepZ, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepZ, LOW);

      delayMicroseconds(1000);

    }
  }
}

BLYNK_WRITE(V4) // si premem el botó virtual (del mòvil) 4 fes...
{
  int i = param.asInt();
  if (i == 1) { // si està encés

    digitalWrite(leds, HIGH); // encèn les LEDS

    delay(500);


  }

  else if (i == 0) { // si està apagat

    digitalWrite(leds, LOW); // apaga les LEDS

    delay(500);

  }
}
