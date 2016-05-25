#include "network.h"

int getIndexOfMac(char *strBuffer) {
   int nAsciiAdd=0,i,nLength;
   nLength=(int)strlen(strBuffer);
   for(i=0;i<nLength;i++)
      nAsciiAdd+=strBuffer[i];
   nAsciiAdd*=41;
   return nAsciiAdd%31;
}

int main(int argc,char **argv)
{
  char strMacName[10][15]={
"ACD1B8EB095D",
"645A048A13B0",
"A4DB30CA36E7",
"78E400AED159",
"B010411BE545",
"4CBB5830067B",
"F82AA8D4A7E9"};
  int i=0,j=0,nAsciiAdd=0;
  for(i=0;i<7;i++)
  {
    nAsciiAdd=0;
    for(j=0;j<MAC_ALEN_CHAR;j++)
      nAsciiAdd+=strMacName[i][j];
    fprintf(stdout,"MacName:%s HashIndex:%d nAsciiAdd:%d\n",strMacName[i],getIndexOfMac(strMacName[i]),nAsciiAdd);
  }
 // deleteOneLine(argv[1]);
  return 0;
}
