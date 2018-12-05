/** 
 * @file GC_cor.h 
 * @brief header file for correlate GC
 * @author Yizhe Chang(yichang@g.hmc.edu) 
 * @version 0.1 
 * @date complete: 10- 05 -2018 
 * @time used:  hr  min
 */

//header file, strict for C/C++ multi-file system, you may choose not having it for Arduino
#ifndef _GC_COR_H_ //ensure this header file will only be included once (if multiple file need this header)
#define _GC_COR_H_

//perform dot product of two GC, if two bits are same, score + 1, else score - 1
int _dotProduct(bool GC_known[], bool GC_received[]);

//offset the received GC by offset bits
void _offsetUnknown(bool GC_received[],bool GC_off[],int offset);

//get the max of absolute value of the input array
int _getAbsMax(int scoreArray[]);

//correlate Gold Code, return max correlation score
//we set printOutput = false by default
int GC_cor(bool GC_known[], bool GC_received[], bool printOutput = false);

#endif
