#include "network.h"
#include "receiver.h"

int subStringMatch1 (char *strSearch, char *strString) {
  int nIndexOfSearch,nIndexOfString,nLengthOfString,nLengthOfSearch;
  nLengthOfString = (int)strlen (strString);
  nLengthOfSearch = (int)strlen (strSearch);
  for (nIndexOfString=0; nIndexOfString < nLengthOfString;nIndexOfString++) {
    for (nIndexOfSearch=0;nIndexOfSearch<nLengthOfSearch; nIndexOfSearch++,nIndexOfString++) {
      if(strSearch[nIndexOfSearch] != strString[nIndexOfString])
        break;
    }
    if (nIndexOfSearch == nLengthOfSearch) {
      if(nLengthOfString==(MAC_ALEN_CHAR+1) && nLengthOfSearch!=((2*MAC_ALEN_CHAR)+2) )
        return -1;
      return 0;
    }
    nIndexOfString += (MAC_ALEN_CHAR - nIndexOfSearch); 
  }
  return -1;
}
