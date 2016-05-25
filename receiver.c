#include "network.h"
#include "receiver.h"

int main (int argc,char **argv) {
  unsigned int nTimer=0;
  int socket_fd=0, sock_len=0, nNoReceiveBytes=0, nReceiveCounter=0, nIndexOfMacInfo=0,i;
  char   *strMacInfo,strBufferReceive [PACKET_LENGTH];
  struct sockaddr_ll sockaddr_ll_receiver;
  struct timeval pTimeMac;
  Quality qualityOfMacs[MAX_HOST];

  if(argc<5) {
    fprintf(stderr,"Warning:Please give file names and time\n");
    return 0;
  }
  for(i=0;i<MAX_HOST;i++)
    qualityOfMacs[i].nReceiveAckCount=0;
  strMacInfo = (char *) malloc (sizeof(char)*ONEMB);
  if(strMacInfo ==NULL)	{	
    fprintf(stderr,"Memory Allocation Error\n");	
    return -1; 
  }
  memset(strMacInfo,0,ONEMB);
  strcpy(strMacInfo, SELF_MAC_ID);
  nIndexOfMacInfo = nIndexOfMacInfo + MAC_ALEN_CHAR;
  strMacInfo [nIndexOfMacInfo] = '#';
  strMacInfo [++nIndexOfMacInfo] = '\0';

  fprintf(stdout,"Intial Mac Table:%s\n",strMacInfo);
  socket_fd = socket (AF_PACKET, SOCK_DGRAM, htons (ETH_P_ALL));
  if(socket_fd == -1)	{
    fprintf(stderr, "%d %s\n", errno, strerror (errno));
    return 0; 
  }
  (void) memset(&sockaddr_ll_receiver, 0, sizeof (sockaddr_ll_receiver));
  while(1) {
    nReceiveCounter ++; 
    sock_len = sizeof(sockaddr_ll_receiver);
    nNoReceiveBytes = recvfrom(socket_fd, strBufferReceive, ETH_FRAME_LEN, 0, (struct sockaddr *) &sockaddr_ll_receiver, (socklen_t *) & sock_len); 
    if ((nNoReceiveBytes == PACKET_LENGTH)){
      if(packetIdentification(strBufferReceive, &strMacInfo, &nIndexOfMacInfo,argv,qualityOfMacs)==-1){
        gettimeofday(&pTimeMac,NULL);
        if(nTimer<(unsigned int)pTimeMac.tv_sec){
          nTimer=(unsigned int)pTimeMac.tv_sec;
          nTimer+=(unsigned int)atoi(argv[3]);
          for(i=0;i<MAX_HOST;i++){
            printf("%d ",qualityOfMacs[i].nReceiveAckCount);
            qualityOfMacs[i].nReceiveAckCount=0;
          } 
           printf("\n");
        }
      }
    }
  }
  close(socket_fd);
  return 0;
}
