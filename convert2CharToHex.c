# include "network.h"
unsigned int convert2CharToHex (char cFirst,char cSecond) {
  int nIndexOfTemp=0;
  char *strBinaryStore,*strTemp;
  if( ((strBinaryStore = (char *)malloc(sizeof(char)))==NULL) && ((strTemp = (char *)malloc(sizeof(char)))==NULL) )
    return 0;

  if ((cFirst < 71 && cFirst >64) && (cSecond < 71 && cSecond > 64))      /* Both are Characters */     
  {
    binaryBitsConversion (cFirst-55,&strBinaryStore,0);
    binaryBitsConversion (cSecond-55,&strBinaryStore,3);
    for(nIndexOfTemp=0;nIndexOfTemp<(int)strlen(strBinaryStore);nIndexOfTemp++)
      strTemp[nIndexOfTemp]=strBinaryStore[((int)strlen(strBinaryStore)-1)-nIndexOfTemp];
    strTemp[nIndexOfTemp]='\0';
    strcpy(strBinaryStore,strTemp);	
    return binaryToInteger (strBinaryStore,0);
  }
  else if ((cFirst < 58 && cFirst > 47) && (cSecond < 58 && cSecond > 47)) /* Both are Integer */
  {
    binaryBitsConversion (cFirst-48,&strBinaryStore,0);
    binaryBitsConversion (cSecond-48,&strBinaryStore,3);
    for(nIndexOfTemp=0;nIndexOfTemp<(int)strlen(strBinaryStore);nIndexOfTemp++)
      strTemp[nIndexOfTemp]=strBinaryStore[((int)strlen(strBinaryStore)-1)-nIndexOfTemp];
    strTemp[nIndexOfTemp]='\0';
    strcpy(strBinaryStore,strTemp);	
    return binaryToInteger (strBinaryStore,0);
  }
  else if ((cFirst < 71 && cFirst >64) && (cSecond < 58 && cSecond > 47))  /*Character and Integer */
  {
    binaryBitsConversion (cFirst-55,&strBinaryStore,0);
    binaryBitsConversion (cSecond-48,&strBinaryStore,3);
    for(nIndexOfTemp=0;nIndexOfTemp<(int)strlen(strBinaryStore);nIndexOfTemp++)
      strTemp[nIndexOfTemp]=strBinaryStore[((int)strlen(strBinaryStore)-1)-nIndexOfTemp];
    strTemp[nIndexOfTemp]='\0';
    strcpy(strBinaryStore,strTemp);	
    return binaryToInteger (strBinaryStore,0);
  }
  else if ((cFirst < 58 && cFirst > 47) && (cSecond < 71 && cSecond > 64))  /* Integer and Character */
  {
    binaryBitsConversion (cFirst-48,&strBinaryStore,0);
    binaryBitsConversion (cSecond-55,&strBinaryStore,3);
    for(nIndexOfTemp=0;nIndexOfTemp<(int)strlen(strBinaryStore);nIndexOfTemp++)
      strTemp[nIndexOfTemp]=strBinaryStore[((int)strlen(strBinaryStore)-1)-nIndexOfTemp];
    strTemp[nIndexOfTemp]='\0';
    strcpy(strBinaryStore,strTemp);	
    return binaryToInteger (strBinaryStore,0);
  }
  return 0;
}
