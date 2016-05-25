#include "network.h"
#include "receiver.h"

int subStringMatchSelfMac (char *strSearch, char *strString) {
   int nIndexOfSearch,nIndexOfString,nLengthOfString;
   nLengthOfString = (int)strlen (strString);
   for (nIndexOfString=0; nIndexOfString < nLengthOfString;nIndexOfString++) {
      for (nIndexOfSearch=0; nIndexOfSearch < MAC_ALEN_CHAR; nIndexOfSearch++,nIndexOfString++) {
         if (strSearch[nIndexOfSearch] != strString[nIndexOfString])
            break;
      }
      if (nIndexOfSearch == MAC_ALEN_CHAR) {
         return 0;
      }
      nIndexOfString += (MAC_ALEN_CHAR - nIndexOfSearch); 
   }
   return -1;
}
