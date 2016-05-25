#include "network.h"
#include "sender.h"

int createNotDeadFrame (char **strBufferNotDead,unsigned int nSequenceNumber) {
   char *strBufferNotDeadTemp,*strSequenceChar;
   if ((strBufferNotDeadTemp = (char *)malloc(sizeof(char)*PACKET_LENGTH)) == NULL) {
      fprintf (stdout,"%d %s\n",errno,strerror(errno));
      return -1;
   }
   strBufferNotDeadTemp [0] = NOT_DEAD;
   integerToCharacter (nSequenceNumber, &strSequenceChar);
   strBufferNotDeadTemp[1]=strSequenceChar[0];
   strBufferNotDeadTemp[2]=strSequenceChar[1];
   strBufferNotDeadTemp[3]=strSequenceChar[2];
   strBufferNotDeadTemp[4]=strSequenceChar[3];
   free(strSequenceChar);
   strcpy (strBufferNotDeadTemp + PACK_HEADER_LEN,SELF_MAC_ID); 
   *strBufferNotDead=strBufferNotDeadTemp;
   return 0;
}
