#include "network.h"
#include "sender.h"

int sendBroadcastPacket (unsigned int *nSequenceNumber,char **argv) {
  int nNoOfSendsBytes,nSocket_fd_Broadcast;
  unsigned int nSequenceNumberTemp;
  char *strBufferBroadcast;
  char strSourceMac[MAC_ALEN_CHAR],strBufferFile[PACKET_LENGTH];
  struct sockaddr_ll sockaddr_ll_Broadcast;
  strcpy(strSourceMac,SELF_MAC_ID);
  nSocket_fd_Broadcast = socket (AF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
  if (nSocket_fd_Broadcast == -1) {
    fprintf (stderr,"%d %s\n",errno,strerror(errno));
    return -1;
  }
  createSockStructure (&sockaddr_ll_Broadcast,nSocket_fd_Broadcast,strBufferFile);
  createFrameBuffer (&strBufferBroadcast,strBufferFile,strSourceMac,(unsigned int)*nSequenceNumber);
  nNoOfSendsBytes = sendto (nSocket_fd_Broadcast, strBufferBroadcast,( size_t)PACKET_LENGTH, 0, (struct sockaddr*)&sockaddr_ll_Broadcast, (socklen_t)sizeof(sockaddr_ll_Broadcast));
  if (nNoOfSendsBytes == -1 ) {
    fprintf (stderr,"%d %s\n",errno,strerror(errno));
    return -1;
  }
  fprintf(stdout,"B Seq No:%d\n",*nSequenceNumber);
  free(strBufferBroadcast);
  close(nSocket_fd_Broadcast);
  nSequenceNumberTemp=(*nSequenceNumber)+1;
  takeActionDependOnFile(&nSequenceNumberTemp,argv);
  *nSequenceNumber=nSequenceNumberTemp;
  return 0;
}
