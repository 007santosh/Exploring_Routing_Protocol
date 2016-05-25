# include "network.h"

int createFrameBuffer (char **strReturnBuffer,char strBuffer[PACKET_LENGTH],char strSourceMac[MAC_ALEN_CHAR],unsigned int nSequenceNumber) {
  int i,j;
  char *strBufferTemp,*strSequenceChar;

  strBufferTemp = (char *) malloc( sizeof (char) * PACKET_LENGTH);
  if((strBufferTemp == NULL) && (strSequenceChar == NULL)) {
    fprintf(stdout,"Memory Allocation Failed\n");
    return 0;
  }
  switch (strBuffer[0]) {
    case ACK_BROADCAST :
    case PING:
    case ACK_PING:
      strBufferTemp [0] = strBuffer[0]; 
      for(i = 1; i < PACK_HEADER_LEN; i++)
        strBufferTemp[i]=strBuffer[i];
      for(j = PACK_HEADER_LEN,i = (MAC_ALEN_CHAR+PACK_HEADER_LEN);(strBuffer[i] != '\n'); i++, j++) {
        if (i == 1000)  break;
        strBufferTemp [j] = strBuffer [i];
      }
      strBufferTemp [j] = '\0';		
      break;

    default :
      strBufferTemp[0] = BROADCAST;
      integerToCharacter (nSequenceNumber, &strSequenceChar);
      for(i = 1; i < PACK_HEADER_LEN; i++)
        strBufferTemp [i] = strSequenceChar [i-1];
      strcpy (strBufferTemp + PACK_HEADER_LEN, UNIQUE);
      for (j = 0,i = 11; j < MAC_ALEN_CHAR; j++,i++)
        strBufferTemp[i] = strSourceMac[j];
      strBufferTemp[i]='\0';
      free(strSequenceChar);
      break;
  }
  *strReturnBuffer = strBufferTemp;
  return 0;
}
