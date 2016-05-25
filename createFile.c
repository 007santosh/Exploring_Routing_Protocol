# include "network.h"

FILE* createFile(char *strPath) {
   FILE *fpWriteFile;
   if( access (strPath,F_OK) == 0) {
      while(1) {
         fpWriteFile = fopen (strPath,"a");
         if(fpWriteFile != NULL) 
            break;
      }
   }
   else {
      while(1) {
         fpWriteFile = fopen (strPath,"w+");
         if(fpWriteFile != NULL) 
            break;
      }
   }
   return fpWriteFile;
}
