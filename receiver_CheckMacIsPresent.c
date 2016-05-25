#include "network.h"
#include "receiver.h"

int checkMacIsPresent(char *strBuffer,char **strMacInfo,int *nIndexOfMacInfo) {
  int nLengthBuffer,nLengthMacInfo=0,nIndexOfReceiverMac=0,nIndexOfBuffer=PACK_HEADER_LEN,nIndexOfMacInfoTemp=0,nIndexOfBufferMac=0,nIndexOfReceiverMacTemp=0;
  char *strReceiverMac,*strReceiverMacTemp,*strSelfMac,*strMacInfoTemp,*strBufferMac;

  for(nLengthBuffer=PACK_HEADER_LEN;strBuffer[nLengthBuffer]!='\0';nLengthBuffer++);

  strMacInfoTemp = (char *) malloc(sizeof(char)*ONEMB);
  memset(strMacInfoTemp,0,ONEMB);
  strcpy(strMacInfoTemp,*strMacInfo);
  free(*strMacInfo);	
  strReceiverMac=(char *)malloc(sizeof(char)*PACKET_LENGTH);
  strReceiverMacTemp=(char *)malloc(sizeof(char)*PACKET_LENGTH);
  strSelfMac=(char *)malloc(sizeof(char)*PACKET_LENGTH);
  strBufferMac=(char *)malloc(sizeof(char)*PACKET_LENGTH);

  if(((strReceiverMac==NULL) && (strReceiverMacTemp) && (strSelfMac==NULL) && (strMacInfoTemp==NULL) && (strBufferMac==NULL))) {
    fprintf(stderr,"Memory Allocation Error\n");
    return -1;
  }
  while(nLengthBuffer!=nIndexOfBuffer) { /* no. of entry in Receiver Buffer that check and update strMacInfo */
    nIndexOfReceiverMac=0;
    while(strBuffer[nIndexOfBuffer]!='#')	{ /* retrive one entry from Receiver Buffer */
      strReceiverMac[nIndexOfReceiverMac]=strBuffer[nIndexOfBuffer];
      nIndexOfBuffer++;
      nIndexOfReceiverMac++;	
    }
    strReceiverMac[nIndexOfReceiverMac]='#';
    strReceiverMac[++nIndexOfReceiverMac]='\0';
    if(nIndexOfBuffer==(MAC_ALEN_CHAR+PACK_HEADER_LEN)) { /* if retrive entry is Just One Mac (like A) it make (Like SELF_MAC_ID-A) */
      strcpy(strReceiverMacTemp,SELF_MAC_ID);
      strReceiverMacTemp[MAC_ALEN_CHAR]='-';
      nIndexOfReceiverMacTemp=MAC_ALEN_CHAR+1;
      strcpy(strReceiverMacTemp+nIndexOfReceiverMacTemp,strReceiverMac);
    }

    nIndexOfMacInfoTemp=0;nLengthMacInfo=(int)strlen(strMacInfoTemp);
    while( nIndexOfMacInfoTemp!=nLengthMacInfo) { /* check in already strMacInfo of no. of entry */
      nIndexOfBufferMac=0;
      while(strMacInfoTemp[nIndexOfMacInfoTemp]!='#') {	
        strBufferMac[nIndexOfBufferMac]=strMacInfoTemp[nIndexOfMacInfoTemp];
        nIndexOfMacInfoTemp++;
        nIndexOfBufferMac++;	
      }
      nIndexOfMacInfoTemp = 	nIndexOfMacInfoTemp + 1;
      strBufferMac[nIndexOfBufferMac]='#';
      strBufferMac[++nIndexOfBufferMac]='\0';
      if( (nIndexOfBuffer==(MAC_ALEN_CHAR+PACK_HEADER_LEN)) && (stringMatch(strReceiverMacTemp,strBufferMac,nIndexOfBuffer)==0))
        goto DoNotWriteOnMacInfo;
      else {
        if (nIndexOfBuffer!=(MAC_ALEN_CHAR+PACK_HEADER_LEN)){
          if((stringMatch(strReceiverMac,strBufferMac,nIndexOfBuffer)==0) || (subStringMatch1(strReceiverMac,strBufferMac)==0) )
            goto DoNotWriteOnMacInfo;
        }
      }
    }
    strcpy(strMacInfoTemp+nLengthMacInfo,SELF_MAC_ID);
    strMacInfoTemp[((nLengthMacInfo+MAC_ALEN_CHAR))]='-';
    strcpy(strMacInfoTemp+nLengthMacInfo+MAC_ALEN_CHAR+1,strReceiverMac);
    nIndexOfMacInfoTemp=nLengthMacInfo+MAC_ALEN_CHAR+1+(int)strlen(strReceiverMac);
    *nIndexOfMacInfo=nIndexOfMacInfoTemp;

DoNotWriteOnMacInfo:
    nIndexOfBuffer++;
  }
  *strMacInfo=strMacInfoTemp;
  free(strReceiverMac);
  free(strReceiverMacTemp);
  free(strSelfMac);
  free(strBufferMac);
  return 0;
}
