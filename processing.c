# include "network.h"
# include "processing.h"

int main(int argc,char **argv) {
  int nTokenCount,i=0,nSequenceNumber;
  char strBuffer[PACKET_LENGTH],**strToken;
  if(argc<2){
    fprintf(stderr,"Warning : Please give senquence number\n");
    return -1;
  }
  nSequenceNumber=atoi(argv[1]);
  while(1) {
    fgets(strBuffer,PACKET_LENGTH,stdin);
    tokenise(strBuffer,&strToken,&nTokenCount);
    memset(&strBuffer,0,PACKET_LENGTH);
    takeActionDependOnLine(strToken,nTokenCount,&nSequenceNumber);
    for(i=0;i<MAX_TOKEN_COUNT;i++)
      free(strToken[i]);
    free(strToken);
    fflush(stdin);
  }
  return 0;
}
