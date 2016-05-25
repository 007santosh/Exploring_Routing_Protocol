# include "network.h"
# include "receiver.h"

int stringMatch(char *strFirstString,char *strSecondString,int nIndexOfBuffer) {
	int nAllAsciiFirst=0,nAllAsciiSecond=0,nIndexOfString,nLengthFirstString,nLengthSecondString;
   nLengthFirstString=(int)strlen(strFirstString);
   nLengthSecondString=(int)strlen(strSecondString);
   if ((subStringMatchSelfMac(SELF_MAC_ID,strFirstString)==0) && (nIndexOfBuffer!=(MAC_ALEN_CHAR+PACK_HEADER_LEN)))
      return 0;
   if(nLengthFirstString==nLengthSecondString) {
	for(nIndexOfString=0;nIndexOfString<nLengthFirstString;nIndexOfString++)
		nAllAsciiFirst=nAllAsciiFirst+strFirstString[nIndexOfString];
	for(nIndexOfString=0;nIndexOfString<nLengthFirstString;nIndexOfString++)
		nAllAsciiSecond=nAllAsciiSecond+strSecondString[nIndexOfString];
	if(nAllAsciiFirst==nAllAsciiSecond)
		return 0;
   }
	return -1;
}
