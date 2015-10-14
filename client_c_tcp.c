//client tcp

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char**argv)
{
   int sockfd,n,portno;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000];
   char recvline[1000];

   if (argc < 3) portno = 32000;
   else portno = atoi(argv[2]);

   sockfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(portno);

   int status = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
   if (status < 0) {
   	printf("connection failed, connect returned %d\n", status);
   	exit(0);
   }
   printf("Enter string: ");
   while (fgets(sendline, 10000,stdin) != NULL)
   {
      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      recvline[n]=0;
      printf("From server: %s\n", recvline);
      //fputs(recvline,stdout);
      while (atoi(recvline) != 0 && atoi(recvline) >= 10) {
      	strcpy(sendline, recvline);
      	sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      	n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      	recvline[n]=0;
      	printf("From server: %s\n", recvline);
      }
      return 0;
   }
}