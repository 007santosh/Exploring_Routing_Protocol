#ifndef __PROCESSING_H_
#define __PROCESSING_H_
#define SLEEP_TIME 50000
int tokenise (char *strBuffer,char ***strToken,int *nTokenCount);
int takeActionDependOnLine(char **strToken,int nTokenCount,int *nSequenceNumber);

#endif
