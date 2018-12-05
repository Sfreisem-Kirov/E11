/** 
 * @file GC_gen.h 
 * @brief header file for generate GC
 * @author Yizhe Chang(yichang@g.hmc.edu) 
 * @version 0.1 
 * @date complete: 10- 05 -2018 
 * @time used:  hr  min
 */
 
//header file, strict for C/C++ multi-file system, you may choose not having it for Arduino
#ifndef _GC_GEN_H_ //ensure this header file will only be included once (if multiple file need this header)
#define _GC_GEN_H_

//giving seed1, seed2, tap1, tap2, store generated GC in GC[]
void GC_gen(bool s1[], bool s2[], bool t1[], bool t2[], bool GC[]);
//print GC_result according to hw requirement
void printResult();

//input seed: s[](5 bit), tap: t[](5 bit), do linear feedback shifting and store resulting MLSRS in M[] array
//It is a good habit to name a function "_myfunction" for internal functions (i.e. functions are not called inside setup() or loop())
void _LFSR(bool s[], bool t[], bool M[]);
//input shifted seed sequence shifted_s[](5 bit), tap: t[](5 bit), do nXOR on bits where tap t[i] = 1;
bool _feedbackXOR(bool shifted_s[], bool t[]);

#endif
