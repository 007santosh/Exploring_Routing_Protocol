# include "network.h"
# include "sender.h"

int main(int argc,char **argv) {
  unsigned int nSequenceNumber;
  if(argc<5)  {
    fprintf(stderr,"Warning: Please give all arguments\n");
    return 0;
  }
  nSequenceNumber=(unsigned int)atoi(argv[4]);
  for(;;)
    sendNotDeadPacket(&nSequenceNumber,argv);
  return 0;
}
