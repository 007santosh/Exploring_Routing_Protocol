#include "network.h"
#include "receiver.h"

int decidePathQuality (char *strMacInfo, char *strSearchString, char **strDestination,Quality qualityOfMacs[MAX_HOST]) {
  int nMaxReceiveAckCount=0,nDestinationIndex=0,nIndexOfMacInfoTemp=0,nLengthMacInfo,nIndexOfTempMac,nIndexOfPossiblePaths=0,nMinLengthInPaths=0,nCounterMinPaths=0,i=0,nArrayIndexesOfMinPathsInPossiblePaths[MAX_HOST];
  char strTempMac[PACKET_LENGTH],*strDestinationTemp,**strPossiblePaths;

  if((strPossiblePaths=(char **)malloc(sizeof(char *)*MAX_HOST))==NULL){ 
    fprintf(stdout,"Memory Allocation Error\n"); return -1;}
  for(i=0;i<MAX_HOST;i++) {
    if((strPossiblePaths[i]=(char *)malloc(sizeof(char)*PACKET_LENGTH))==NULL){ 
      fprintf(stdout,"Memory Allocation Error\n"); return -1;}
  }
  nLengthMacInfo = (int)strlen (strMacInfo);
  if (nLengthMacInfo>(MAC_ALEN_CHAR+4)) {
    while (nIndexOfMacInfoTemp < nLengthMacInfo) {/* for no. of entries in MacInfo */
      nIndexOfTempMac = 0;
      while (strMacInfo [nIndexOfMacInfoTemp] != '#') /* retrive 1 entry from MacInfo */
        strTempMac[nIndexOfTempMac++] = strMacInfo[nIndexOfMacInfoTemp++];
      nIndexOfMacInfoTemp++;
      strTempMac[nIndexOfTempMac] = '\0';
      if (subStringMatch (strSearchString,strTempMac,&strDestinationTemp) == 0)  {
        strcpy(strPossiblePaths[nIndexOfPossiblePaths++],strTempMac);
      }
    }

    /*do searching for best path */
    nMinLengthInPaths=(int)strlen(strPossiblePaths[0]);
    for(i=1;i<nIndexOfPossiblePaths;i++) {
      if((int)strlen(strPossiblePaths[i])<nMinLengthInPaths) {
        nMinLengthInPaths=(int)strlen(strPossiblePaths[i]);
      }
    }
    for(i=0;i<nIndexOfPossiblePaths;i++) {
      if(nMinLengthInPaths==(int)strlen(strPossiblePaths[i])) {
        nArrayIndexesOfMinPathsInPossiblePaths[nCounterMinPaths++]=i;
      }
    }
    if((strDestinationTemp=(char *)malloc(sizeof(char)*(MAC_ALEN_CHAR+1)))==NULL) {
      fprintf(stdout,"Memory Allocation Error\n"); return -1;}

    for(i=0;i<nCounterMinPaths;i++) {
      strncpy(strTempMac,strPossiblePaths[nArrayIndexesOfMinPathsInPossiblePaths[i]]+(MAC_ALEN_CHAR+1),MAC_ALEN_CHAR);
      strTempMac[MAC_ALEN_CHAR]='\0';
      if(qualityOfMacs[getIndexOfMac(strTempMac)].nReceiveAckCount>nMaxReceiveAckCount) {
        nMaxReceiveAckCount=qualityOfMacs[getIndexOfMac(strTempMac)].nReceiveAckCount;
        nDestinationIndex=i;
      }  
    }
    if(nCounterMinPaths==0) {
      for(i=0;i<MAX_HOST;i++)
        free(strPossiblePaths[i]);
      free(strPossiblePaths);
      return -1;
    }

    strncpy(strDestinationTemp,strPossiblePaths[nArrayIndexesOfMinPathsInPossiblePaths[nDestinationIndex]]+(MAC_ALEN_CHAR+1),MAC_ALEN_CHAR);
    strDestinationTemp[MAC_ALEN_CHAR]='\0';
    for(i=0;i<MAX_HOST;i++)
      free(strPossiblePaths[i]);
    free(strPossiblePaths);
    *strDestination=strDestinationTemp;
    return 0;
  }
  return -1;
}
