# include "network.h"
#include "processing.h"

int tokenise (char *strBuffer,char ***strToken,int *nTokenCount) {
  int nTokenCountTemp=0,nLengthOfBuffer=0,nIndexOfBuffer=0,i=0;
  char **strTokenTemp;
  strTokenTemp =(char **)malloc(sizeof(char *)*MAX_TOKEN_COUNT);
  for(i=0;i<MAX_TOKEN_COUNT;i++)
    strTokenTemp[i]=(char *)malloc(sizeof(char)*PACKET_LENGTH);
  nLengthOfBuffer=(int)strlen(strBuffer);
  while(nLengthOfBuffer>nIndexOfBuffer) {
    i=0;
    while(strBuffer[nIndexOfBuffer]==' ') {
      if(strBuffer[nIndexOfBuffer++]!=' ')
        break;
    }
    while(strBuffer[nIndexOfBuffer]!=' ') {
      if(strBuffer[nIndexOfBuffer]=='\n')
        break;
      strTokenTemp[nTokenCountTemp][i]=strBuffer[nIndexOfBuffer];
      i++;nIndexOfBuffer++;
    }
    if(i!=0)
      strTokenTemp[nTokenCountTemp++][i]='\0';
    nIndexOfBuffer++;
  }
  *strToken=strTokenTemp;
  *nTokenCount=nTokenCountTemp;
  return 0;
}
