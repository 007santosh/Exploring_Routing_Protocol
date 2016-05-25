# include "network.h"

int characterToInteger (char *strBufferReceive, unsigned int *nSequenceNumber,void ***strFreeMem) {
   unsigned int nSequenceTemp=0;
   int nIndexOfBufferReceive, nIndexOfBinary8Bit,nIndexOfFreeMemoryPointers=0,i=0;
   char *strBinary8Bit;
   void **strFreeMemoryPointers;
   strFreeMemoryPointers = (void **) malloc(sizeof(void *)*5);
   strFreeMemoryPointers[nIndexOfFreeMemoryPointers]=strFreeMemoryPointers;
   for (nIndexOfBufferReceive = 4,i = 0,nIndexOfFreeMemoryPointers=1; nIndexOfBufferReceive > 0 ; nIndexOfBufferReceive--,nIndexOfFreeMemoryPointers++) {
      characterToBinary8Bit (strBufferReceive [nIndexOfBufferReceive], &strBinary8Bit);
      for (nIndexOfBinary8Bit = 0; nIndexOfBinary8Bit < 8; nIndexOfBinary8Bit++, i++) {
         if (strBinary8Bit[nIndexOfBinary8Bit]=='1')
            nSequenceTemp=nSequenceTemp+powerOf2(i);
      }
      strFreeMemoryPointers[nIndexOfFreeMemoryPointers]=strBinary8Bit;
   }
   *strFreeMem=strFreeMemoryPointers;
   *nSequenceNumber=nSequenceTemp;
   return 0;
}
