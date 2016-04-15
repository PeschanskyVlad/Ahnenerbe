#include "opcodes.h"

/*----+----+----+----PINS---+---+----+*/
#define SPEAKER_PIN 10

#define R_DC_PA 3
#define R_DC_P1 5
#define R_DC_P2 4

#define L_DC_PA 9
#define L_DC_P1 7
#define L_DC_P2 8
/*-----------------PINS END----------*/

#define MAX_MELODY_LENGTH 100

int melody_size;
char notes[MAX_MELODY_LENGTH];
char note_length[MAX_MELODY_LENGTH];
unsigned long note_change_time;
bool melody_playing;
char current_note;

/*********DC CONTROL*******/
void L_DC_stop(){
  digitalWrite(L_DC_P1, LOW);
  digitalWrite(L_DC_P2, LOW);
}
void R_DC_stop(){
  digitalWrite(R_DC_P1, LOW);
  digitalWrite(R_DC_P2, LOW);
}

void L_DC_rotateBackward(){
  digitalWrite(L_DC_P1, LOW);
  digitalWrite(L_DC_P2, HIGH);
}
void R_DC_rotateBackward(){
  digitalWrite(R_DC_P1, LOW);
  digitalWrite(R_DC_P2, HIGH);
}

void L_DC_rotateForward(){
  digitalWrite(L_DC_P1, HIGH);
  digitalWrite(L_DC_P2, LOW);
}
void R_DC_rotateForward(){
  digitalWrite(R_DC_P1, HIGH);
  digitalWrite(R_DC_P2, LOW);
}

void L_DC_setSpeed(int speed){
  analogWrite(L_DC_PA, speed);
}
void R_DC_setSpeed(int speed){
  analogWrite(R_DC_PA, speed);
}

void setup_DC(){
  pinMode(R_DC_PA, OUTPUT);
  pinMode(R_DC_P1, OUTPUT);
  pinMode(R_DC_P2, OUTPUT);
  
  pinMode(L_DC_PA, OUTPUT);
  pinMode(L_DC_P1, OUTPUT);
  pinMode(L_DC_P2, OUTPUT);

  //Stop all DCs
  L_DC_setSpeed(0);
  R_DC_setSpeed(0);
  
  L_DC_rotateForward();
  R_DC_rotateForward();
}
/******DC CONTROL END*****/

int note_to_freq(char note){
  return 50+note * 78;
}

void update_note(){
  unsigned long time_now = millis();
  if(time_now >= note_change_time) {
    tone(SPEAKER_PIN,
    note_to_freq(notes[current_note]));
    note_change_time = time_now + (int)(note_length[current_note]) * 6;
    current_note++;
    current_note%=melody_size;
  }
}

void setup_melody(){
  notes[0] = 0;
  current_note = 0;
  melody_size = 0;
  note_change_time = 0;
}

void setup() {
setup_DC();
Serial.begin(9600);
current_note = 0;
melody_size = 0;
}

void loadMelody(){
  current_note = 0;
  while(!Serial.available());//Wait for melody length
  melody_size = Serial.read();
  while(Serial.available() < melody_size * 2);
  for(int i = 0; i < melody_size; i++){
    notes[i] = Serial.read();
    note_length[i] = Serial.read();
  }
  note_change_time = millis();
}

void loop() {
  if(Serial.available()){
    switch(Serial.read()){
     case OP_LOAD_MUSIC: loadMelody(); break;
     case OP_PLAY_MUSIC: melody_playing = true; noTone(SPEAKER_PIN); break;
     case OP_STOP_MUSIC: melody_playing = false; noTone(SPEAKER_PIN); break;
    }
  }
  if(melody_playing)
    update_note();
}
