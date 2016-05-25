# include "network.h"

int binaryBitsConversion (int nNumber,char **strResult,int nIndexOfResult) {
   char *strTemp,*strStoreAns;
   int nTemp,nIndexOfTemp = 0 ,i = 0; 
   strStoreAns=(char *)malloc(sizeof(char));
   strTemp = (char *)malloc(sizeof(char));
   if (strTemp==NULL && strStoreAns==NULL)
      return -1;

   nTemp = nNumber;
   while (nTemp > 1) {
      if(nTemp%2==0)
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
   strTemp [nIndexOfTemp + 1] = '\0';
   for (i = 0;i < 4 - (int)strlen (strTemp);i++)
      strStoreAns [i] = '0';

   for (nIndexOfTemp=0 ;i < 4;i++,nIndexOfTemp++)
      strStoreAns [i] = strTemp [(int)strlen(strTemp)-nIndexOfTemp-1];
   strStoreAns [i] = '\0';
   if(nIndexOfResult==3) {
      strcpy(strTemp,strStoreAns);
      strcpy(strStoreAns,*strResult);
      for(i=4;i<8;i++)
         strStoreAns[i]=strTemp[i-4];
      strStoreAns [i] = '\0';
   }

   *strResult=strStoreAns;
   return 0;
}
