#ifndef __RECEIVER_H_
#define __RECEIVER_H_
#include "network.h"

/* Function Prototyping */
int checkMacIsPresent(char *strBuffer,char **strMacInfo,int *nIndexOfMacInfo);
int subStringMatchSelfMac (char *strSearch, char *strString);
int packetIdentification (char strBufferReceive [PACKET_LENGTH],char ** strMacInfo, int * nIndexOfMacInfo,char **strFileNames,Quality qualityOfMacs[MAX_HOST]);
int subStringMatch1 (char *strSearch, char *strString); 
int getIndexOfMac(char *strBuffer);
# endif
