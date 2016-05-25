# include "network.h"

int integerToCharacter(unsigned int nSequenceNumber,char **strSequenceChar) {
  unsigned int nSequenceNumberTemp,nIndexOfSequenceCharTemp=3,nTemp=0,i=0,j=0;
  char *strSequenceCharTemp;
  strSequenceCharTemp=(char *) malloc(sizeof(char)*ETH_ALEN);
  if(strSequenceCharTemp==NULL) {
    fprintf(stderr,"Memory Allocation Error\n");
    return -1;
  }
  nSequenceNumberTemp =nSequenceNumber;
  for(j=0,i=0;i<32;i++,j++) {
    if((i%8==0) && (i!=0)) {
      strSequenceCharTemp[nIndexOfSequenceCharTemp]=nTemp;
      nIndexOfSequenceCharTemp--;j=0,nTemp=0;
    }
    if(nSequenceNumberTemp==1) {
      nTemp=nTemp+powerOf2(j);
      nSequenceNumberTemp=0;
    }
    if( nSequenceNumberTemp%2!=0 )
      nTemp=nTemp+powerOf2(j);
    nSequenceNumberTemp=nSequenceNumberTemp/2;
  }
  strSequenceCharTemp[nIndexOfSequenceCharTemp]=nTemp;
  *strSequenceChar = strSequenceCharTemp;
  return 0;
}
