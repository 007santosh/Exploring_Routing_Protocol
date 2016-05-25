# include "network.h"

unsigned int binaryToInteger (char *strBuffer,int nPowerOf2StartFrom) {
   unsigned int nNumber = 0,i;

   for (i=0;i<(unsigned int)strlen (strBuffer);i++,nPowerOf2StartFrom++) {
      if(strBuffer[i]=='1')
         nNumber = nNumber + (unsigned int)powerOf2(nPowerOf2StartFrom);
   }
   return nNumber;
}

unsigned int powerOf2 (unsigned int nNumber) {
   if (nNumber == 0)
      return 1;
   else if (nNumber == 1)
      return 2;
   else
      return 2*powerOf2 (nNumber-1);
}
