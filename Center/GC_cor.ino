/** 
 * @file GC_cor.pde
 * @brief source file for correlating GC
 * @author Yizhe Chang(yichang@g.hmc.edu) 
 * @version 0.1 
 * @date complete: 10- 05 -2018 
 * @time used:  hr  min
 */
#include"GC_cor.h"

int _dotProduct(bool GC_known[], bool GC_received[]){
  int sum = 0;
  for(int i = 0; i < numGCBits; i++){
    if(GC_known[i] == GC_received[i]){
      sum++;
    }
    else{
      sum--;
    }
  }
  return sum;
}

void _offsetUnknown(bool GC_received[],bool GC_off[],int offset){
  for(int i = 0; i < numGCBits - offset; i++){
    GC_off[i + offset] = GC_received[i];
  }
  for(int i = 0; i < offset; i++){
    GC_off[i] = GC_received[numGCBits - offset + i];
  }
}

int _getAbsMax(int scoreArray[]){
  int max_score = scoreArray[0];//In Arduino, 'max' is defined by the system,
  for(int i = 0; i < numGCBits - 1; i++){
    if(abs(max_score) < abs(scoreArray[i])){
      max_score = scoreArray[i];
    }
  }
  return max_score;
}

int GC_cor(bool GC_known[], bool GC_received[], bool printOutput){
  bool GC_offset[numGCBits]; //array to store received GC
  int max_score; //max correlation after offset
  int corrScore[numGCBits];
  //at max we can offset (right shift) 30 bits, but start from shifting 0 bit, we should shift 31 times
  for(int i = 0; i < numGCBits; i++){
    _offsetUnknown(GC_received, GC_offset, i);
    corrScore[i] = _dotProduct(GC_known,GC_offset);
  }
  max_score = _getAbsMax(corrScore);

  if(printOutput){ //output correlation result if printOutput == true (default false)
    for(int i = 0; i < numGCBits; i++){
      Serial.print(corrScore[i]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println("MAX: " + String(max_score));
  }
  return max_score;
}
