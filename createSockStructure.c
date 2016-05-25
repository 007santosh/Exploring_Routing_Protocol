# include "network.h"

int createSockStructure (struct sockaddr_ll * sockaddr_ll_structure,int nSocket_fd,char strBuffer[PACKET_LENGTH]) {
   int j,nIndexBuffer;
   struct sockaddr_ll sockaddr_ll_temp;
   struct ifreq ifreq1;

   sockaddr_ll_temp.sll_family = AF_PACKET;
   sockaddr_ll_temp.sll_protocol= htons(ETH_P_ALL);
   memset (&ifreq1, 0, sizeof(struct ifreq));
   strncpy (ifreq1.ifr_name, INTERFACE_NAME, IFNAMSIZ-1);
   if (ioctl (nSocket_fd, SIOCGIFINDEX, &ifreq1) < 0) {
      fprintf (stderr,"%d %s\n",errno,strerror(errno));
      return 0;
   }
   sockaddr_ll_temp.sll_ifindex = ifreq1.ifr_ifindex;
   /* ARPHRD_ETHER  = 1 for hatype*/
   sockaddr_ll_temp.sll_hatype = 1;
   sockaddr_ll_temp.sll_halen=ETH_ALEN;

   switch (strBuffer[0]) {
      case PING:
      case ACK_PING:
      case ACK_BROADCAST :
         sockaddr_ll_temp.sll_pkttype = PACKET_OTHERHOST;

         /* PUT MAC ADDRESS OF DEST MACHINE */
         for (j = 0, nIndexBuffer = PACK_HEADER_LEN;nIndexBuffer < (MAC_ALEN_CHAR+PACK_HEADER_LEN);nIndexBuffer=nIndexBuffer+2, j++)
            sockaddr_ll_temp.sll_addr[j] = convert2CharToHex(strBuffer [nIndexBuffer], strBuffer [nIndexBuffer+1]);

         /* PADDING FOR 8 BYTE ADDRESS CONVERSION FOR MAC ADDRESS */
         sockaddr_ll_temp.sll_addr[6]=0x00;
         sockaddr_ll_temp.sll_addr[7]=0x00;

         break;

      case SEND_SELF_PACKET:
         sockaddr_ll_temp.sll_pkttype = PACKET_OTHERHOST;
         if (ioctl (nSocket_fd, SIOCGIFHWADDR, &ifreq1) < 0) {
            fprintf (stderr,"%d %s\n",errno,strerror(errno));
            return 0;
         }

         /* PUT MAC ADDRESS OF DEST MACHINE */
         sockaddr_ll_temp.sll_addr[0]=ifreq1.ifr_hwaddr.sa_data[0];
         sockaddr_ll_temp.sll_addr[1]=ifreq1.ifr_hwaddr.sa_data[1];
         sockaddr_ll_temp.sll_addr[2]=ifreq1.ifr_hwaddr.sa_data[2];
         sockaddr_ll_temp.sll_addr[3]=ifreq1.ifr_hwaddr.sa_data[3];
         sockaddr_ll_temp.sll_addr[4]=ifreq1.ifr_hwaddr.sa_data[4];
         sockaddr_ll_temp.sll_addr[5]=ifreq1.ifr_hwaddr.sa_data[5];
         /* PADDING FOR 8 BYTE ADDRESS CONVERSION FOR MAC ADDRESS */
         sockaddr_ll_temp.sll_addr[6]=0x00;
         sockaddr_ll_temp.sll_addr[7]=0x00;


         break;
      default :
         sockaddr_ll_temp.sll_pkttype = PACKET_BROADCAST;

         /* PUT MAC ADDRESS OF DEST MACHINE */
         sockaddr_ll_temp.sll_addr[0]=0xFF;
         sockaddr_ll_temp.sll_addr[1]=0xFF;
         sockaddr_ll_temp.sll_addr[2]=0xFF;
         sockaddr_ll_temp.sll_addr[3]=0xFF;
         sockaddr_ll_temp.sll_addr[4]=0xFF;
         sockaddr_ll_temp.sll_addr[5]=0xFF;
         /* PADDING FOR 8 BYTE ADDRESS CONVERSION FOR MAC ADDRESS */
         sockaddr_ll_temp.sll_addr[6]=0x00;
         sockaddr_ll_temp.sll_addr[7]=0x00;
         break;
   }
   *sockaddr_ll_structure = sockaddr_ll_temp;
   return 0;
}
