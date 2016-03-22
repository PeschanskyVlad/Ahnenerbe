#define R_DC_PA 3
#define R_DC_P1 4
#define R_DC_P2 5

#define L_DC_PA 9
#define L_DC_P1 7
#define L_DC_P2 8

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
  L_DC_stop();
  R_DC_stop();
}

void setup(){
  setup_DC();
  R_DC_setSpeed(180);
  L_DC_setSpeed(180);
}

void LR(){
  L_DC_rotateForward();
  R_DC_rotateBackward();
  delay(350);
  L_DC_rotateBackward();
  R_DC_rotateForward();
  delay(350);
}

void FB(){
  L_DC_rotateForward();
  R_DC_rotateForward();
  delay(550);
  L_DC_rotateBackward();
  R_DC_rotateBackward();
  delay(550);
}

void loop() {
 //FB();  
// LR();
}

