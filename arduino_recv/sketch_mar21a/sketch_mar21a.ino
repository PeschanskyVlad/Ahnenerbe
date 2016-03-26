int IN3 = 5; // Input3 подключен к выводу 5 
int IN4 = 4;
int ENB = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode (ENB, OUTPUT); 
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
   digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite(ENB,50);
}

void loop() {
  if(Serial.available()){
    int incoming = Serial.read();
    incoming-='1';
    incoming = (incoming * 255)/10;
    Serial.println(incoming % 255, DEC);
    analogWrite(ENB, incoming % 255);
    delay(300);
  }
}
