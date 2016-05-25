#include "network.h"
int deleteOneLine(char *strPath) {
  char *strBuffer;
  strBuffer=(char *)malloc(sizeof(char)*PACKET_LENGTH);
  if(strBuffer==NULL){
    fprintf(stderr,"Error: Memory Allocation Failed\n");
    return -1;
  }
  strcpy(strBuffer,"sed -e '1d' < ");
  strcpy(strBuffer+(int)strlen(strBuffer),strPath);
  strcpy(strBuffer+(int)strlen(strBuffer)," > a.txt; ");
  strcpy(strBuffer+(int)strlen(strBuffer)," unlink ");
  strcpy(strBuffer+(int)strlen(strBuffer),strPath);
  strcpy(strBuffer+(int)strlen(strBuffer)," ;mv a.txt ");
  strcpy(strBuffer+(int)strlen(strBuffer),strPath);
  system(strBuffer);
  free(strBuffer);
  return 0;
}
