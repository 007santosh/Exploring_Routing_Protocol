# include "network.h"

int main (int argc,char *argv[]) {
  unsigned int nMacTime [MAX_HOST];
  int nSocket_fd_DeleteMac,nSequenceNumber = 1000,i;
  int nIndexOfDecreaseTime = 0,nIndexOfstrMacTime = 0,nSizeOfMacTime = 0,nIndexOfCheckMac = 0;
  char strMacTime [MAX_HOST][PACKET_LENGTH], strBuffer[16],strBufferDeleteMac [PACKET_LENGTH] ,*strSequenceChar;
  FILE * fp_Time_Info;
  struct sockaddr_ll sockaddr_ll_DeleteMac;
  struct timeval pTime;
  struct stat pStat; 
  if(argc < 3){
    fprintf(stderr,"Warning: Please give input filename and time for keep alive\n");
    return -1;
  }
  strBuffer[0]=SEND_SELF_PACKET;
  strBuffer[1]='\0';

  strSequenceChar = (char *) malloc (sizeof (char) * ETH_ALEN);
  if (strSequenceChar == NULL) {
    fprintf (stderr,"Memory Allocation Failed\n");
    return -1;
  }

  nSocket_fd_DeleteMac = socket (AF_PACKET,SOCK_DGRAM,htons (ETH_P_ALL));
  if (nSocket_fd_DeleteMac == -1) {
    fprintf (stderr,"%d %s\n",errno,strerror(errno));
    return -1;
  }
  createSockStructure(&sockaddr_ll_DeleteMac,nSocket_fd_DeleteMac,strBuffer);
  while (1) {
TIME :
    stat (argv[1],&pStat);
    sleep(1);
    if (((fp_Time_Info = fopen (argv[1],"r")) != NULL) && (pStat.st_size>0)) {
      rewind(fp_Time_Info);
      fgets (strBuffer,16,fp_Time_Info);
      fclose (fp_Time_Info);
      strBuffer[MAC_ALEN_CHAR]='\0';
      fp_Time_Info=fopen (argv[1],"w");
      deleteOneLine(argv[1]);
      fclose(fp_Time_Info);
      for(nIndexOfCheckMac = 0; nIndexOfCheckMac < nSizeOfMacTime; nIndexOfCheckMac++) {
        if (strcmp (strBuffer,strMacTime [nIndexOfCheckMac]) == 0) {
          gettimeofday(&pTime,NULL);
          nMacTime[nIndexOfCheckMac]=(unsigned int)pTime.tv_sec;
          nMacTime[nIndexOfCheckMac]+=(atoi(argv[2])+10);
          goto DONT_WRITE_MAC;
        }
      }
      strcpy (strMacTime [nIndexOfstrMacTime],strBuffer);
      gettimeofday(&pTime,NULL);
      nMacTime[nIndexOfstrMacTime]=(unsigned int)pTime.tv_sec;
      nMacTime[nIndexOfstrMacTime]+=(atoi(argv[2])+10);
      nIndexOfstrMacTime++;
      nSizeOfMacTime++; 
    }
DONT_WRITE_MAC :
    gettimeofday(&pTime,NULL);   
    for (nIndexOfDecreaseTime  = 0; nIndexOfDecreaseTime  < nSizeOfMacTime; nIndexOfDecreaseTime ++) {
      if( (nMacTime [nIndexOfDecreaseTime] <=pTime.tv_sec) && (nMacTime[nIndexOfDecreaseTime]!=0)) { 
        strBufferDeleteMac [0] = DELETE_MAC ;
        integerToCharacter (nSequenceNumber,&strSequenceChar);
        strBufferDeleteMac [1] = strSequenceChar[0];
        strBufferDeleteMac [2] = strSequenceChar[1];
        strBufferDeleteMac [3] = strSequenceChar[2];
        strBufferDeleteMac [4] = strSequenceChar[3];
        strcpy (strBufferDeleteMac + PACK_HEADER_LEN,strMacTime[nIndexOfDecreaseTime]);
        for(i=PACK_HEADER_LEN;i< (MAC_ALEN_CHAR+PACK_HEADER_LEN);i++)     
          fprintf(stdout,"%c",strBufferDeleteMac[i]);
        fprintf(stdout,"\n");
        if ((sendto (nSocket_fd_DeleteMac, strBufferDeleteMac,(size_t) PACKET_LENGTH,0, (struct sockaddr *) &sockaddr_ll_DeleteMac, (socklen_t) sizeof (sockaddr_ll_DeleteMac))) == -1) {
          fprintf (stderr,"%d %s\n",errno,strerror (errno));
          return -1;
        }
        nSequenceNumber++;
        nMacTime[nIndexOfDecreaseTime]=0;
      }
    }
    goto TIME;
  }
  return 0;
}
