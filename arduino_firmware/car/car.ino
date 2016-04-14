#include "opcodes.h"

#define SPEAKER_PIN 10
#define MAX_MELODY_LENGTH 100

int melody_size;
char notes[MAX_MELODY_LENGTH];
char note_length[MAX_MELODY_LENGTH];
bool melody_playing;
char current_note;

int note_to_freq(char note){
  return 50+note * 78;
}

void play_note(){
  tone(SPEAKER_PIN,
       note_to_freq(notes[current_note]));
  int delay_val = (int)(note_length[current_note]) * 6;
  Serial.println(delay_val,DEC);
  delay(delay_val);
  current_note++;
  //current_note %= melody_size;
  if(current_note>=melody_size)
    current_note = 0;
}

void setup() {
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
    play_note();
}
