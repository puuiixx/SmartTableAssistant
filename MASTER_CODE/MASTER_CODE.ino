#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
char xyData[32] = "";
String xAxis, yAxis, recordState, playState, resetState, tornarState;

int record = A2;
int play = A8;
int reset = A9;
int tornar = A10;

void setup() {

  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(record, INPUT);
  pinMode(play, INPUT);
  pinMode(reset, INPUT);
  pinMode(tornar, INPUT);

}
void loop() {

  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis
  recordState = analogRead(record);
  playState = analogRead(play);
  resetState = analogRead(reset);
  tornarState = analogRead(tornar);
  // X value
  xAxis.toCharArray(xyData, 5); // Put the String (X Value) into a character array
  radio.write(&xyData, sizeof(xyData)); // Send the array data (X value) to the other NRF24L01 modile
  // Y value
  yAxis.toCharArray(xyData, 5);
  radio.write(&xyData, sizeof(xyData));

    recordState.toCharArray(xyData, 5);
    radio.write(&xyData, sizeof(xyData));

    playState.toCharArray(xyData, 5);
    radio.write(&xyData, sizeof(xyData));

    resetState.toCharArray(xyData, 5);
    radio.write(&xyData, sizeof(xyData));

    tornarState.toCharArray(xyData, 5);
    radio.write(&xyData, sizeof(xyData));

  delay(20);
  Serial.print("recordState="); Serial.print(recordState); Serial.print(" playState=");
  Serial.print(playState); Serial.print(" resetState="); Serial.print(resetState);
  Serial.print(" tornarState="); Serial.println(tornarState);

}
