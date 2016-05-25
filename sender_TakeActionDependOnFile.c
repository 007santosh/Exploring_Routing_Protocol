# include "network.h"
#include "sender.h"

int takeActionDependOnFile(unsigned int *nSequenceNumber,char **argv) {
  int nSocket_fd_Ack,nNoOfSendsBytes;
  unsigned long int nTimeLoop1;
  unsigned int nSequenceNumberTemp;
  char *strBufferAck;
  char strSourceMac [MAC_ALEN_CHAR] = SELF_MAC_ID, strBufferFile[PACKET_LENGTH];
  FILE *fpReadFile;
  struct sockaddr_ll sockaddr_ll_Ack;
  struct stat pStat;
  struct timeval pTime;

  memset (&strBufferFile , 0, (sizeof(char)*PACKET_LENGTH));
  nSequenceNumberTemp=(unsigned int)*nSequenceNumber;
  gettimeofday(&pTime,NULL);
  nTimeLoop1=(unsigned long int)pTime.tv_sec;
  nTimeLoop1+=(unsigned int)atoi(argv[3]);
  do {
    fpReadFile = fopen (argv[1],"r");
    if (fpReadFile != NULL) {
      rewind(fpReadFile);
      fgets (strBufferFile, PACKET_LENGTH, fpReadFile);
      if (strBufferFile [0] == ACK_BROADCAST || strBufferFile[0]==PING || strBufferFile[0]==ACK_PING) {    
        nSocket_fd_Ack = socket (AF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
        if (nSocket_fd_Ack == -1) {
          fprintf (stderr,"%d %s\n",errno,strerror(errno));
          return 0;
        }
        createSockStructure (&sockaddr_ll_Ack,nSocket_fd_Ack,strBufferFile);
        createFrameBuffer (&strBufferAck,strBufferFile,strSourceMac,nSequenceNumberTemp);
        nNoOfSendsBytes = sendto (nSocket_fd_Ack, strBufferAck, (size_t)PACKET_LENGTH, 0, (struct sockaddr*)&sockaddr_ll_Ack, (socklen_t)sizeof(sockaddr_ll_Ack));
        if (nNoOfSendsBytes == -1) {
          fprintf(stderr,"%s %d\n",strerror(errno),errno);
          return 0;
        }
        fprintf(stdout,"Packet Type %d seq no:%d\n",(int)strBufferAck[0],nSequenceNumberTemp);
        free(strBufferAck);
        nSequenceNumberTemp++;
      }
      fclose (fpReadFile);
      fpReadFile = fopen (argv[1],"w");
      deleteOneLine(argv[1]);
      stat (argv[1],&pStat);
      if (pStat.st_size == 0) {
        unlink (argv[1]);
      }
    }
    memset(&pTime,0,sizeof(pTime));
    gettimeofday(&pTime,NULL);
    if( access (argv[1],F_OK) != 0 ) 
      usleep(5000);
  }while(nTimeLoop1>(unsigned long int)pTime.tv_sec);
  *nSequenceNumber=nSequenceNumberTemp;
  return 0;
}
