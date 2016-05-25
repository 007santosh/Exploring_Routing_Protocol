#ifndef __NETWORK_H_
#define __NETWORK_H_

#include <stdio.h>             /* fprintf (),fgets(),fputc (),fputs (),fopen (),fclose () */
#include <string.h>            /* strcpy (),memset (),strcmp (),strlen (),strerror (),strncpy () */
#include <stdlib.h>            /* malloc (), free() */   
#include <unistd.h>            /* unlink (),close (),access (),sync ()*/
#include <errno.h>             /* errno */
#include <sys/socket.h>        /* socket (),sendto (),recvfrom() */
#include <sys/stat.h>          /* stat() */
#include <sys/types.h>         /* socket () */
#include <sys/ioctl.h>         /* ioctl () */
#include <net/if.h>            /* struct ifreq */
#include <net/ethernet.h>      /* AF_PACKET for socket() */  
#include <linux/if_packet.h>   /* ---||--- */
#include <linux/if_ether.h>    /* list of allowed protocol */ 
#include <arpa/inet.h>         /* htons() */
#include <netinet/in.h>        /* Some system use this instead of <arpa/inet.h> for htons() */
#include <sys/time.h>          /* gettimeofday() */
#include <fcntl.h>             /* open() */

/* No for Types of Packet */
#define BROADCAST 1
#define ACK_BROADCAST 2
#define DELETE_MAC 3
#define ACK_DATA 4
#define NACK_DATA 5
#define DATA_PACKET 6
#define NOT_DEAD 7
#define PROCESS_PING 21
#define PING 22
#define ACK_PING 23
#define SEND_SELF_PACKET 15


/* CONSTANT VALUES */
/*# define SELF_MAC_ID "ACD1B8EB095D"*/
/*# define SELF_MAC_ID "645A048A13B0"*/
/*# define SELF_MAC_ID "A4DB30CA36E7"*/
/*# define SELF_MAC_ID "78E400AED159"*/
/*# define SELF_MAC_ID "B010411BE545"*/
/*# define SELF_MAC_ID "F82AA8D4A7E9"*/
#define SELF_MAC_ID "4CBB5830067B"
#define UNIQUE "UNIQUE"
#define INTERFACE_NAME "wlan0"
#define TIME_TEN_SEC 21000000
#define TIME_ONE_MIN 84000000
#define PACKET_LENGTH 1024
#define MAC_ALEN_CHAR 12
#define PACK_HEADER_LEN 5
#define MAX_TOKEN_COUNT 10
#define ONEMB 1048576
#define MAX_HOST 31
#define DELETE_ONE_LINE(strPath) "sed -e '1d' < "strPath" > a.txt; unlink "strPath"; mv a.txt "strPath";"
#define DELETE_ONE(strPath) "vi -c ':1d' -c ':wq' "strPath";"


typedef struct quality{
   char strMacName[MAC_ALEN_CHAR];
   int nReceiveAckCount;
}Quality;


/* Function Prototyping */
unsigned int powerOf2 (unsigned int nNumber);
unsigned int convert2CharToHex (char cFirst,char cSencod);
unsigned int binaryToInteger (char *strBuffer,int nPowerOf2StartFrom);
int binaryBitsConversion (int nNumber,char **strResult,int nIndexOfResult);
int integerToCharacter (unsigned int nSequenceNumber,char **strSequenceChar);
int characterToBinary8Bit (unsigned int nNumber,char **strBinary8Bit);
int characterToInteger (char *strBufferReceive,unsigned int *nSequenceNumber,void ***strFreeMem);
int createSockStructure (struct sockaddr_ll * sockaddr_ll_structure,int nSocket_fd,char strBuffer[PACKET_LENGTH]);
int createFrameBuffer (char **strReturnBuffer,char strBuffer[PACKET_LENGTH],char strSourceMac[MAC_ALEN_CHAR],unsigned int nSequenceNumber);
int stringMatch (char *strFirstString,char *strSecondString,int nIndexOfBuffer);
int subStringMatch (char *strSearch, char *strString, char **strDestination); 
int decidePath (char *strMacInfo, char *strSearchString, char **strDestination);
int decidePathQuality (char *strMacInfo, char *strSearchString, char **strDestination,Quality qualityOfMacs[MAX_HOST]); 
int fileInfo (char *strPath);
FILE* createFile (char *strPath); 
int deleteOneLine(char *strPath);

# endif
