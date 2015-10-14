//server udp

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv)
{
   int sockfd,n, portno;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[1000];

   if (argc < 2) portno = 32000;
   else portno = atoi(argv[1]);


   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(portno);
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   for (;;)
   {
      len = sizeof(cliaddr);
      n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
      mesg[n] = 0;
      int x = atoi(mesg);
      int sum = 0;
      int flag = 0;
      if (x==0) {
      	char mesg[] = "Sorry, cannot compute!";

      	//sprintf(mesg, "%d", sum);
      	n = strlen(mesg);
      	sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr, sizeof(cliaddr));
      	return 0;
      }
      while (x > 9) {
      	sum += x % 10; x = x / 10;
      }
      sum += x % 10;
      if (sum < 10) flag = 1;
      sprintf(mesg, "%d", sum);
      n = strlen(mesg);
      sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
      if (flag == 1) return 0;
   }
}