# include "network.h"

int characterToBinary8Bit (unsigned int nNumber,char **strBinary8Bit) {
   unsigned int nTemp;
   int nIndexOfTemp=0;
   char *strTemp;
   strTemp = (char *) malloc (sizeof(char)*40);
   if (strTemp == NULL) {
      fprintf(stderr,"Memory Allocation Error\n");
      return -1;
   }
   nTemp = nNumber;
   while (nTemp > 1) {
      if (nTemp%2==0)
         strTemp[nIndexOfTemp] = '0';
      else   
         strTemp[nIndexOfTemp] = '1';
      nTemp=nTemp/2;
      nIndexOfTemp ++;
   }

   if (nTemp == 1)
      strTemp [nIndexOfTemp] = '1';
   else 
      strTemp [nIndexOfTemp] = '0';
   nIndexOfTemp++;
   for (; nIndexOfTemp < 8; nIndexOfTemp++)
      strTemp [nIndexOfTemp] = '0';
   strTemp [nIndexOfTemp ] = '\0';
   *strBinary8Bit = strTemp;
   return 0;
}
