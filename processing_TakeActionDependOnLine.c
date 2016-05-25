# include "network.h"
#include "processing.h"

int takeActionDependOnLine(char **strToken,int nTokenCount,int *nSequenceNumber) {
  int nSocket_fd_Processing,nSequenceNumberTemp,i=0;
  int nPingCount=1;
  char strBuffer[ETH_ALEN],strBufferProcessing[PACKET_LENGTH],*strSequenceChar;
  struct sockaddr_ll sockaddr_ll_Processing;
  nSequenceNumberTemp=*nSequenceNumber;

  strBuffer[0]=SEND_SELF_PACKET;
  strBuffer[1]='\0';

  strSequenceChar = (char *) malloc (sizeof (char) * ETH_ALEN);
  if (strSequenceChar == NULL) {
    fprintf (stderr,"Memory Allocation Failed\n");
    return -1;
  }

  nSocket_fd_Processing = socket (AF_PACKET,SOCK_DGRAM,htons (ETH_P_ALL));
  if (nSocket_fd_Processing == -1)  {
    fprintf (stderr,"%d %s\n",errno,strerror(errno));
    return -1;
  }
  createSockStructure(&sockaddr_ll_Processing,nSocket_fd_Processing,strBuffer);

  switch(nTokenCount) {
    case 2:
    case 3:if( (strcmp(strToken[0],"p")==0) || (strcmp(strToken[0],"P")==0) ) {
             if(nTokenCount==3) {
               nPingCount=atoi(strToken[2]);
             }
             strBufferProcessing[0]=PROCESS_PING;
             integerToCharacter (nSequenceNumberTemp,&strSequenceChar);
             strBufferProcessing [1] = strSequenceChar[0];
             strBufferProcessing [2] = strSequenceChar[1];
             strBufferProcessing [3] = strSequenceChar[2];
             strBufferProcessing [4] = strSequenceChar[3];
             strcpy (strBufferProcessing + PACK_HEADER_LEN,strToken[1]);
             fprintf(stdout,"PING TO: %s\n",strToken[1]);
             for(i=0;i<nPingCount;i++) {
               if ((sendto (nSocket_fd_Processing, strBufferProcessing,(size_t) PACKET_LENGTH,0, (struct sockaddr *) &sockaddr_ll_Processing, (socklen_t) sizeof (sockaddr_ll_Processing))) == -1) {
                 fprintf (stderr,"%d %s\n",errno,strerror (errno));
                 return -1;
               }
               usleep(SLEEP_TIME);
             }
             nSequenceNumberTemp++;
           }
           break;

    case 4:
           break;

    default:
           break;
  }
  *nSequenceNumber=nSequenceNumberTemp;
  return 0;
}
