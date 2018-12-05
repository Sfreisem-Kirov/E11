#define DISTSENSOR 0
#define REFL 4
#define REFR 3
#define PHOTOTRANSISTOR 5

float a = 0.000000002;
float b = -0.000004;
float c = 0.0024;
float d = -0.7002;
float e = 91.825;


void initSensors(){
  pinMode(REFL, INPUT);
  pinMode(REFR, INPUT);
}

void testSensors(){ 

  Serial.print("RefR : ");
  Serial.println(analogRead(REFR));
  
  Serial.print("RefL ");
  Serial.println(analogRead(REFL));
  
}
float distanceI(){//only correct if > 5 inches
  float x = analogRead(DISTSENSOR);
  float inches = (x*x*x*x*a)+(x*x*x*b)+(x*x*c)+(x*d)+e;
  return inches;
}
