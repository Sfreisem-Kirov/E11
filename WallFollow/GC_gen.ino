/** 
 * @file GC_gen.pde 
 * @brief source file for generating GC
 * @author Yizhe Chang(yichang@g.hmc.edu) 
 * @version 0.1 
 * @date complete: 10- 05 -2018 
 * @time used: 1 hr 0 min
 */

//you can choose not having this header file at all
#include"GC_gen.h"

void GC_gen(bool s1[], bool s2[], bool t1[], bool t2[], bool GC[]){
  bool MLSRS1[numGCBits], MLSRS2[numGCBits];
  _LFSR(s1, t1, MLSRS1);//generate MLSRS 1
  _LFSR(s2, t2, MLSRS2);//generate MLSRS 2

  for(int i = 0; i < numGCBits; i++){//do bit-wise XOR for GC
    GC[i] = MLSRS1 [i] != MLSRS2[i];
  }
}

void printResult(){
  for(int i = 0; i < numGCs; i++){
    Serial.print("GC");
    Serial.print(i+1);
    Serial.print(":");

    for(int j = 0; j < numGCBits; j++){
      Serial.print(GCs[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

bool _feedbackXOR(bool shifted_s[], bool t[]){
  //in this function we used the nXOR property:
  //if the input of nXOR has odd number of 1s (e.g. 0 XOR 1 XOR 0), nXOR result: 1
  //if the input of nXOR has even number of 1s (e.g. 0 XOR 1 XOR 1), nXOR result: 0 
  int sum = 0;
  for (int i = 0; i < numRegs; i++){
    // we only care bits where tap == 1;
    // therefore, we only count the bit when both shifted_s[i] && tap[i] are 1 
    if(shifted_s[i] && t[i]){
      sum++;
    }
  }
  if (sum % 2 == 0){//even number of 1s
    return false; 
  }
  else{//odd number of 1s
    return true;
  }
}

void _LFSR(bool s[], bool t[], bool M[]){
  bool firstBit;
  for(int i = 0; i < numGCBits; i++){
    M[i] = s[numRegs - 1]; //our MLSRS is the last bit of shifted seed sequence  
    firstBit = _feedbackXOR(s, t); //compute the first bit
    for(int j = numRegs - 1; j > 0; j--){
      s[j] = s[j-1];
    }
    s[0] = firstBit;
  }
}
