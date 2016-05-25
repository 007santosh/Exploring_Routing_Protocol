#include "network.h"
int subStringMatch (char *strSearch, char *strString, char **strDestination) {
  int nIndexOfSearch,nIndexOfString,nLengthOfString;
  char *strDestinationTemp;
  if ((strDestinationTemp = (char *)malloc(sizeof(char)*(MAC_ALEN_CHAR+4))) == NULL) {
    fprintf (stderr,"%s\n",strerror(errno));
    return -1;
  }
  nLengthOfString = (int)strlen (strString);
  for (nIndexOfString=0; nIndexOfString < nLengthOfString;nIndexOfString++) {
    for (nIndexOfSearch=0; nIndexOfSearch < MAC_ALEN_CHAR; nIndexOfSearch++,nIndexOfString++) {
      if (strSearch[nIndexOfSearch] != strString[nIndexOfString])
        break;
    }
    if (nIndexOfSearch == MAC_ALEN_CHAR) {
      for (nIndexOfString=MAC_ALEN_CHAR+1,nIndexOfSearch=0; nIndexOfString < (2*MAC_ALEN_CHAR+1); nIndexOfString++,nIndexOfSearch++) 
        strDestinationTemp[nIndexOfSearch]=strString[nIndexOfString];
      strDestinationTemp[nIndexOfSearch]='\0';
      *strDestination = strDestinationTemp;
      return 0;
    }
    nIndexOfString += (MAC_ALEN_CHAR - nIndexOfSearch); 
  }
  return -1;
}
