#include "network.h"
#include "receiver.h"

int packetIdentification (char strBufferReceive [PACKET_LENGTH],char ** strMacInfo, int * nIndexOfMacInfo,char **argv,Quality qualityOfMacs[MAX_HOST]) {	
  unsigned int nSequenceNumber;
  int i=0,j=0,nIndexOfTempMac = 0,  nIndexOfMacInfoTemp = 0, nIndexOfBufferReceive = PACK_HEADER_LEN, nIndexOfMacInfoTemp1 = 0, nIndexOfMacInfoTemp2 = 0, nIndexOfMacInfoPacket = *nIndexOfMacInfo;
  static int nAckPingCount[PACKET_LENGTH];
  char *strNetworkName,*strCheckMac,*strTempMac,*strSenderMac , *strMacInfoTemp,*strDestination;
  void **strFreeMem,**strFreeMemStore;
  FILE *fpWriteFile;
  struct timeval pTime;
  characterToInteger(strBufferReceive,&nSequenceNumber,&strFreeMem);
  fprintf(stdout,"Seq NO:%u\n",nSequenceNumber);

  strFreeMemStore = (void **) malloc(sizeof(void *)*5);
  for(i=0;i<5;i++)
    strFreeMemStore[i]=strFreeMem[i];

  strMacInfoTemp = (char *) malloc (sizeof (char) *ONEMB);
  memset(strMacInfoTemp,0,ONEMB);
  strcpy (strMacInfoTemp, *strMacInfo);

  free(*strMacInfo);
  for(i=0;i<5;i++)
    free(strFreeMemStore[i]);
  free(strFreeMemStore);

  strSenderMac = (char *) malloc (sizeof(char) * (MAC_ALEN_CHAR+1));
  strCheckMac = (char *) malloc (sizeof (char) * PACKET_LENGTH);
  strTempMac = (char *) malloc (sizeof (char) * PACKET_LENGTH);
  strNetworkName = (char *) malloc (sizeof(char) * 8);
  if (((strSenderMac == NULL) && (strCheckMac == NULL) && (strTempMac == NULL) && (strNetworkName == NULL) &&(strMacInfoTemp==NULL))) { 
    fprintf(stdout,"Memory Allocation Error\n"); return -1;}
  switch (strBufferReceive [0]) {
    case BROADCAST :
      for(i = 0; i < ETH_ALEN; i++, nIndexOfBufferReceive++)
        strNetworkName [i] = strBufferReceive[nIndexOfBufferReceive];
      strNetworkName [i] = '\0';

      for (j = 0;j < MAC_ALEN_CHAR; j++, nIndexOfBufferReceive++)
        strSenderMac [j] = strBufferReceive [nIndexOfBufferReceive];
      strSenderMac [j] = '\0';

      if(strcmp(strSenderMac,SELF_MAC_ID)==0){
        free(strSenderMac);
        free(strCheckMac);
        free(strTempMac);
        free(strNetworkName);
        *strMacInfo = strMacInfoTemp;
        *nIndexOfMacInfo = nIndexOfMacInfoPacket;
        return -1;
      }
      if (((strcmp (strNetworkName, UNIQUE) == 0) &&  !(strcmp (strSenderMac, SELF_MAC_ID) == 0))) {
        fpWriteFile=createFile(argv[1]);
        fputc (ACK_BROADCAST, fpWriteFile);
        for (i=1;i<PACK_HEADER_LEN;i++)
          fputc (strBufferReceive[i],fpWriteFile);
        fputs (strSenderMac, fpWriteFile);				 
        fputs (strMacInfoTemp, fpWriteFile);
        fputc('\n',fpWriteFile);
        fflush(fpWriteFile);
      }
      break ;

    case ACK_BROADCAST :
      for (i=PACK_HEADER_LEN,j=0;i<(PACK_HEADER_LEN+MAC_ALEN_CHAR);j++,i++) 
        strSenderMac[j]=strBufferReceive[i];
      strSenderMac[j]='\0';
      if (!strcmp(strSenderMac,SELF_MAC_ID) == 0) {
        qualityOfMacs[getIndexOfMac(strSenderMac)].nReceiveAckCount+=1;
        checkMacIsPresent (strBufferReceive, &strMacInfoTemp, &nIndexOfMacInfoPacket);
        gettimeofday(&pTime,NULL);
        fprintf(stdout,"%s\n",strMacInfoTemp);
      }
      break;

    case NOT_DEAD :
      nIndexOfBufferReceive = PACK_HEADER_LEN;
      for(i = 0; i < MAC_ALEN_CHAR; i++, nIndexOfBufferReceive++)
        strSenderMac [i] = strBufferReceive [nIndexOfBufferReceive];
      strSenderMac [i] = '\0';

      if (!(strcmp(strSenderMac,SELF_MAC_ID) == 0)) {
        fpWriteFile = createFile(argv[2]);
        fputs (strSenderMac,fpWriteFile);
        fputc('\n',fpWriteFile);
        fflush(fpWriteFile);
      }
      break;

    case DELETE_MAC :
      nIndexOfBufferReceive = PACK_HEADER_LEN; 
      nIndexOfMacInfoTemp = 0;
      for(i = 0; i < MAC_ALEN_CHAR; i++, nIndexOfBufferReceive++)
        strSenderMac [i] = strBufferReceive [nIndexOfBufferReceive];
      strSenderMac [i] = '\0';
      strcpy (strCheckMac,SELF_MAC_ID);
      strCheckMac [MAC_ALEN_CHAR] = '-';
      strcpy (strCheckMac + MAC_ALEN_CHAR + 1, strSenderMac);
      while (nIndexOfMacInfoTemp < (int)strlen(strMacInfoTemp)) { /* for no. of entries in MacInfo */
        nIndexOfTempMac = 0;
        while (strMacInfoTemp [nIndexOfMacInfoTemp] != '#') /* retrive 1 entry from MacInfo */
          strTempMac [nIndexOfTempMac++] = strMacInfoTemp [nIndexOfMacInfoTemp++];
        nIndexOfMacInfoTemp++;
        strTempMac [nIndexOfTempMac] = '\0';
        if (subStringMatch1(strCheckMac,strTempMac) == 0 ) {
          nIndexOfMacInfoTemp1 = nIndexOfMacInfoTemp - ((int)strlen(strTempMac) + 1 ); 
          nIndexOfMacInfoTemp2 = nIndexOfMacInfoTemp ;
          nIndexOfMacInfoTemp = nIndexOfMacInfoTemp1;
          strcpy(strMacInfoTemp+nIndexOfMacInfoTemp1,strMacInfoTemp+nIndexOfMacInfoTemp2);
        }
      }
      nIndexOfMacInfoPacket = (int) strlen (strMacInfoTemp);
      fprintf (stdout,"%s",strMacInfoTemp);
      break;

    case PROCESS_PING:
      nIndexOfBufferReceive = PACK_HEADER_LEN;
      for(i = 0; i < MAC_ALEN_CHAR; i++, nIndexOfBufferReceive++)
        strSenderMac [i] = strBufferReceive [nIndexOfBufferReceive];
      strSenderMac [i] = '\0';
      if(decidePathQuality (strMacInfoTemp,strSenderMac,&strDestination,qualityOfMacs)==0) {
        fpWriteFile=createFile(argv[1]);
        fputc(PING,fpWriteFile);
        for (i=1;i<PACK_HEADER_LEN;i++)
          fputc (strBufferReceive[i],fpWriteFile);
        fputs(strDestination,fpWriteFile);
        fputs(SELF_MAC_ID,fpWriteFile);
        fputs(strSenderMac,fpWriteFile);
        fputc('\n',fpWriteFile);
        fflush(fpWriteFile);
      }
      break;

    case PING:
      nIndexOfBufferReceive=PACK_HEADER_LEN+MAC_ALEN_CHAR;
      for(i = 0; i < MAC_ALEN_CHAR; i++, nIndexOfBufferReceive++)
        strSenderMac [i] = strBufferReceive [nIndexOfBufferReceive];
      strSenderMac [i] = '\0';
      if(stringMatch(strSenderMac,SELF_MAC_ID,16)==0) {
        nIndexOfBufferReceive=PACK_HEADER_LEN;
        for(i = 0; i < MAC_ALEN_CHAR; i++, nIndexOfBufferReceive++)
          strSenderMac [i] = strBufferReceive [nIndexOfBufferReceive];
        strSenderMac [i] = '\0';
        if(decidePathQuality (strMacInfoTemp,strSenderMac,&strDestination,qualityOfMacs)==0) {
          fpWriteFile=createFile(argv[1]);
          fputc(ACK_PING,fpWriteFile);
          for (i=1;i<PACK_HEADER_LEN;i++)
            fputc (strBufferReceive[i],fpWriteFile);
          fputs(strDestination,fpWriteFile);
          for(j=PACK_HEADER_LEN,i=0;i<MAC_ALEN_CHAR;i++,j++)
            fputc(strBufferReceive[j],fpWriteFile);
          fputs(strSenderMac,fpWriteFile);
          fputc('\n',fpWriteFile);
          fflush(fpWriteFile);
        }
      }
      else {
        if(decidePathQuality (strMacInfoTemp,strSenderMac,&strDestination,qualityOfMacs)==0) {
          fpWriteFile=createFile(argv[1]);
          fputc(PING,fpWriteFile);
          for (i=1;i<PACK_HEADER_LEN;i++)
            fputc (strBufferReceive[i],fpWriteFile);
          fputs(strDestination,fpWriteFile);
          for(j=PACK_HEADER_LEN,i=0;i<MAC_ALEN_CHAR;i++,j++)
            fputc(strBufferReceive[j],fpWriteFile);
          fputs(strSenderMac,fpWriteFile);
          fputc('\n',fpWriteFile);
          fflush(fpWriteFile);
        }
      }
      break;
    case ACK_PING:
      nIndexOfBufferReceive=PACK_HEADER_LEN+MAC_ALEN_CHAR;
      for(i = 0; i < MAC_ALEN_CHAR; i++, nIndexOfBufferReceive++)
        strSenderMac [i] = strBufferReceive [nIndexOfBufferReceive];
      strSenderMac [i] = '\0';
      if(stringMatch(strSenderMac,SELF_MAC_ID,16)==0) {
        nAckPingCount[nSequenceNumber%(atoi(argv[4]))]++;
        fprintf(stdout,"PING Successful %d\n",nAckPingCount[nSequenceNumber%atoi(argv[4])]);
      }
      else {
        if(decidePathQuality (strMacInfoTemp,strSenderMac,&strDestination,qualityOfMacs)==0) {
          fpWriteFile=createFile(argv[1]);
          fputc (ACK_PING,fpWriteFile);
          for (i=1;i<PACK_HEADER_LEN;i++)
            fputc (strBufferReceive[i],fpWriteFile);
          fputs(strDestination,fpWriteFile);
          for(j=PACK_HEADER_LEN,i=0;i<MAC_ALEN_CHAR;i++,j++)
            fputc(strBufferReceive[j],fpWriteFile);
          fputs(strSenderMac,fpWriteFile);
          fputc('\n',fpWriteFile);
          fflush(fpWriteFile);
        }
      }
      break;

    default : break;	
  }
  free(strSenderMac);
  free(strCheckMac);
  free(strTempMac);
  free(strNetworkName);
  /*free(strDestination);*/
  *strMacInfo = strMacInfoTemp;
  *nIndexOfMacInfo = nIndexOfMacInfoPacket;
  return 0;
}
