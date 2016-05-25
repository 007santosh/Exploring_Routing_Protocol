# ifndef __SENDER_H_
# define __SENDER_H_

/* Function Prototyping */
int sendNotDeadPacket (unsigned int *nSequenceNumber,char **argv);
int sendBroadcastPacket (unsigned int *nSequenceNumber,char **argv);
int createNotDeadFrame (char **strBufferNotDead, unsigned int nSequenceNumber);
int takeActionDependOnFile(unsigned int *nSequenceNumber,char **argv);

# endif
