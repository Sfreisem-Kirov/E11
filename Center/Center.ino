//time to complete:started 6:07pm 10/29

#include <Servo.h>
#define SERVOPIN 10
#define DISTSENSOR 0

#include"GC_gen.h" 
#include"GC_cor.h"

#define numGCs 4
#define numRegs 5
#define numGCBits 31
#define RED 2
#define COLORSWITCH 3
#define PHOT 5
#define BUZZ 4

#define REFL 4
#define REFR 3

bool seed1[numRegs] = {0,0,0,0,1};
bool seed2[numGCs][numRegs] = {//{0,0,0,0,1},//1
                               //{0,0,0,1,0}, //2
                               //{0,0,0,1,1},//3
                               //{0,0,1,0,0},//4
                               {0,0,1,0,1},//5
                               {0,0,1,1,0},//6
                               {0,0,1,1,1},//7
                               {0,1,0,0,0},//8
                               //{0,1,0,0,1},//9
                               //{0,1,0,1,0}, //10
                               //{0,1,0,1,1},//11
                               //{0,1,1,0,0},//12
                               //{0,1,1,0,1},//13
                               //{0,1,1,1,0},//14
                               //{0,1,1,1,1},//15
                               //{1,0,0,0,0},//16
                               //{1,0,0,0,1},//17
                               //{1,0,0,1,0},//18
                               //{1,0,0,1,1}//19
                               };

bool tap1[numRegs] = {0, 1, 1, 1, 1}; //You can also initialize it by tap1[] = {0,1,1,1,1};
bool tap2[numRegs] = {0, 0, 1, 0, 1};
bool GCs[numGCs][numGCBits]; //GC result stored here
bool flipGCs[numGCs][numGCBits]; //GC result stored here

unsigned long currentTime(0);

int sensorRead[numGCBits];

bool team; // green=0, white=1 Green is inverted

int avg;
bool possibleGC[numGCBits];
int maxCorr;


int newMax =0;
int gi = 0;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(COLORSWITCH, INPUT);
  pinMode(PHOT, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(DISTSENSOR, INPUT);
  pinMode(BUZZ, OUTPUT);
  
  pinMode(REFL, INPUT);
  pinMode(REFR, INPUT);
  
  initServo();
  servo.write(105);

  setTeam();
  gen();
  flipBits();
  //getWhichGC();
  //for(int i = 0; i < numGCBits; i++){
 //   Serial.print(GCs[0][i]);
  //}
  
  //Serial.println();

  start();
}
void loop() {
  bCastAll();
}


void start(){
  delay(2000);
  forward();
  delay(800);
  halt();
}

void circle(){
  if(analogRead(REFL) < 850){
    curveS();
  }else if(analogRead(REFR) > 925){
    curveK();
  }else
  curveL();
}






bool goodDistance(){
  bool toClose = false;
  if(analogRead(DISTSENSOR)> 450){
    toClose=true;
  }
  return toClose;  
}



void goAround(){

  tone(BUZZ, 294);
  turnL();
  delay(200);
  
  
  
  noTone(BUZZ);
  goish();
  delay(800);
}
void hit(){
  goish();
  delay(2500);

  
  backward();
  delay(500);
  
  //goHalf();
  //delay(600);
  
  turnL();
  delay(200);
  
  goish();
  delay(600);
  
  hugR();
}
void wallFollow(){
  choose();
  hugR();
}
void choose(){
  getWhichGC();
  if(goodDistance()){
    if(!sameteam()){
      Serial.println("HIT!");
      hit();
    }else{
      
      Serial.println("TURN!");
      goAround();
    }
  }else{
    return false;
  }
}
bool sameteam(){
  bool t=team;
  if(newMax > 0){
    return t;
  }else{
    return !t;
  }
}
void getWhichGC(){
  currentTime=readPhoto(currentTime);


  //Serial.println();
  avg = getAvg();
  setBits();
  newMax =0;
  gi = 0;
  for(int i = 0; i < numGCs; i++){
    //for(int j = 0; j < numGCBits;j++){
      //shiftBits();
      maxCorr=GC_cor(GCs[i],possibleGC,false);//set true if we want to print
      //Serial.print("max :");
      //Serial.println(maxCorr);
      if(abs(maxCorr) >= abs(newMax)){
        newMax=maxCorr;
        gi = i;
        
      }
    //}
  }
  
}

unsigned long readPhoto(unsigned long oldGoalTime){
  unsigned long goalTime = micros()+250;
  for(int i = 0; i < 31; i++){
    sensorRead[i] = analogRead(PHOT);
    while(micros() < goalTime);
    goalTime = goalTime + 250;
  }
  return goalTime;
}

void shiftBits(){
  bool temp = possibleGC[0];
  for(int i = 0; i < numGCBits - 1; i++){
    possibleGC[i]=possibleGC[i+1];
  }
  possibleGC[numGCBits - 1] = temp;
}

int readReflSensor(){
  return analogRead(A4);
}

void setBits(){
  for(int i = 0; i < numGCBits; i++){
    if(sensorRead[i] < avg){
      possibleGC[i]=1;
    }else{
      possibleGC[i]=0;
    }
  }
}

void bCastAll(){
  if(team){
    for(int i = 0; i < numGCs; i++){
      broadcastGC(GCs[i]);    
    }
  }else{
    for(int i = 0; i < numGCs; i++){
      broadcastGC(flipGCs[i]);    
    }
  }
}

void setTeam(){
  team=digitalRead(COLORSWITCH);
}

void flipBits(){
  for(int i = 0; i < numGCs; i++){
    for(int j = 0; j < numGCBits; j++){
     flipGCs[i][j] = !GCs[i][j];
    }
  }
}
unsigned long broadcastGC(bool GC[]){
  unsigned long goalTime = micros() + 250;
  //for(int j = 0; j < 1;j++){
    
  
    for(int i = 0; i < 31; i++){
      if(GC[i]){
      //Serial.println("yes");
        digitalWrite(RED, HIGH);
      }
      else{
      //Serial.println("no");
        digitalWrite(RED, LOW);
      }
      while(micros() < goalTime){
        circle();
      }
      goalTime = goalTime + 250;
    }
  //}
  return goalTime;
}

int getAvg(){
  int sum=0;
  for(int i = 0; i < numGCBits; i++){
    sum+=sensorRead[i];
  }
  //Serial.println(sum/numGCBits);
  return sum/numGCBits;
}
void gen(){
  for(int i = 0; i < numGCs; i++){
    GC_gen(seed1, seed2[i], tap1, tap2, GCs[i]);
  }
}
