#include "receiver.h"
#include "network.h"
int getIndexOfMac(char *strBuffer){
   int nAsciiAdd=0,i,nLength;
   nLength=(int)strlen(strBuffer);
   for(i=0;i<nLength;i++)
      nAsciiAdd+=strBuffer[i];
   nAsciiAdd*=41;
   return nAsciiAdd%MAX_HOST;
}
