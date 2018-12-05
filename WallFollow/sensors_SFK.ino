#define DISTSENSOR 0
#define REFLSENSOR 4
#define PHOTOTRANSISTOR 5

float a = 0.000000002;
float b = -0.000004;
float c = 0.0024;
float d = -0.7002;
float e = 91.825;


void initSensors(){
  pinMode(DISTSENSOR, INPUT);
  pinMode(REFLSENSOR, INPUT);
  pinMode(PHOTOTRANSISTOR, INPUT);
}
bool onRed(){
  return (analogRead(REFLSENSOR) > 760 && analogRead(REFLSENSOR) < 775 );
}

void testSensors(){ 
  Serial.print("dist: ");
  Serial.println(analogRead(DISTSENSOR));

  Serial.print("Relfectance : ");
  Serial.println(analogRead(REFLSENSOR));
  
  Serial.print("Phototransistor: ");
  Serial.println(analogRead(PHOTOTRANSISTOR));
  
}
float distanceI(){//only correct if > 5 inches
  float x = analogRead(DISTSENSOR);
  float inches = (x*x*x*x*a)+(x*x*x*b)+(x*x*c)+(x*d)+e;
  return inches;
}
