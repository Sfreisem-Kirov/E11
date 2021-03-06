#define LPLUS 9
#define LMINUS 8
#define RPLUS 7
#define RMINUS 12
#define LEN 6
#define REN 11

void initMotors(){
  pinMode(LPLUS, OUTPUT);
  pinMode(LMINUS, OUTPUT);
  pinMode(RPLUS, OUTPUT);
  pinMode(RMINUS, OUTPUT);
  pinMode(LEN,OUTPUT);
  pinMode(REN,OUTPUT);
}
void halt(){
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LMINUS, LOW);
  digitalWrite(RMINUS, LOW);
}
void forward(){
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}
void backward(){
  
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, HIGH);
  digitalWrite(LPLUS, HIGH);
  digitalWrite(RMINUS, LOW);
  digitalWrite(LMINUS, LOW);
}

void turnL(){
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, HIGH);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, LOW);
  digitalWrite(LMINUS, HIGH);
}
void turnR(){
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, HIGH);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, LOW);
}
void hugR(){
  analogWrite(LEN, 191);
  analogWrite(REN, 181);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}
void goish(){
  analogWrite(LEN, 255);
  analogWrite(REN, 255);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}
void goHalf(){
  analogWrite(LEN, 128);
  analogWrite(REN, 128);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}
void curveL(){
   analogWrite(LEN, 110);
  analogWrite(REN, 147);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}

void curveS(){
   analogWrite(LEN, 50);
  analogWrite(REN, 130);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}
void curveK(){
   analogWrite(LEN, 100);
  analogWrite(REN, 50);
  digitalWrite(RPLUS, LOW);
  digitalWrite(LPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
  digitalWrite(LMINUS, HIGH);
}
