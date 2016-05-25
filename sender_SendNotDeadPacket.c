#include "network.h"
#include "sender.h"

int sendNotDeadPacket (unsigned int *nSequenceNumber,char **argv) {
  unsigned int nTimeLoop;
  unsigned int nSequenceNumberTemp;
  int nNoOfSendsBytes,nSocket_fd_NotDead=0;
  char strBufferFile[PACKET_LENGTH], *strBufferNotDead; 
  struct sockaddr_ll sockaddr_ll_Broadcast;
  struct timeval  pTime;
  memset (&strBufferFile , 0, (sizeof(char)*PACKET_LENGTH));
  nSocket_fd_NotDead = socket (AF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
  if (nSocket_fd_NotDead == -1) {
    fprintf (stderr,"%d %s\n",errno,strerror(errno));
    return -1;
  }
  createSockStructure (&sockaddr_ll_Broadcast,nSocket_fd_NotDead,strBufferFile);
  createNotDeadFrame (&strBufferNotDead,(unsigned int)*nSequenceNumber);
  nNoOfSendsBytes = sendto (nSocket_fd_NotDead, strBufferNotDead,( size_t)PACKET_LENGTH, 0, (struct sockaddr*)&sockaddr_ll_Broadcast, (socklen_t)sizeof(sockaddr_ll_Broadcast));
  if (nNoOfSendsBytes == -1 ) {
    fprintf (stderr,"%d %s\n",errno,strerror(errno));
    return -1;
  }
  close(nSocket_fd_NotDead);
  fprintf(stdout,"ND seq no:%d\n",*nSequenceNumber);
  free(strBufferNotDead);
  nSequenceNumberTemp=(*nSequenceNumber)+1;
  gettimeofday(&pTime,NULL);
  nTimeLoop=(unsigned int)pTime.tv_sec;
  nTimeLoop+=(unsigned int)atoi(argv[2]);
  for (  ;nTimeLoop > (unsigned int)pTime.tv_sec; ) {
    sendBroadcastPacket(&nSequenceNumberTemp,argv);
    gettimeofday(&pTime,NULL);
  }
  *nSequenceNumber=nSequenceNumberTemp;
  return 0;
}
