#include "opcodes.h"

#define SPEAKER_PIN 10
#define MAX_MELODY_LENGTH 100

int melody_size;
char notes[MAX_MELODY_LENGTH];
char note_length[MAX_MELODY_LENGTH];
bool melody_playing=false;
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
melody_size = 4;
notes[0]=1;
notes[1]=3;
notes[2]=2;
notes[3]=5;
note_length[0] = 30;
note_length[1] = 20;
note_length[2] = 40;
note_length[3] = 15;
melody_playing = true;
}

void loop() {
  if(Serial.available()){
    switch(Serial.read()){
    case OP_LOAD_MUSIC:
     while(!Serial.available());
       melody_size = Serial.read();
       while(Serial.available() < melody_size * 2);
       for(int i = 0; i < melody_size; i++){
        notes[i] = Serial.read();
        note_length[i] = Serial.read();
       }
   break;
    }
   case OP_PLAY_MUSIC:
       melody_playing = true;
   break;
   case OP_STOP_MUSIC:
       melody_playing = false;
   break;
  }
  if(melody_playing)
    play_note();
}
