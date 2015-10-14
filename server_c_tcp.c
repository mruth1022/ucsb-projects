//server tcp

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char**argv)
{
   int listenfd,connfd,n,portno;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   pid_t     childpid;
   char mesg[1000];

   if (argc < 2) portno = 32000;
   else portno = atoi(argv[1]);

   listenfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(portno);
   bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   listen(listenfd,1024);

   for(;;)
   {
      clilen=sizeof(cliaddr);
      connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

      //if ((childpid = fork()) == 0)
      //{
         close (listenfd);

         for(;;)
         {
            n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
            //printf("receiving\n");
            mesg[n] = 0;
      		int x = atoi(mesg);
      		int sum = 0;
	      	int flag = 0;
	      	if (x==0) {
	      		char mesg[] = "Sorry, cannot compute!";

		      	//sprintf(mesg, "%d", sum);
		      	n = strlen(mesg);
		      	sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr, sizeof(cliaddr));
		      	//printf("sent");
		      	close(connfd);
		      	exit(0);
	      	}
	      	//printf("past cannot compute\n");
		    while (x > 9) {
		      sum += x % 10; x = x / 10;
	      	}
	      	sum += x % 10;
	      	if (sum < 10) flag = 1;
	      	sprintf(mesg, "%d", sum);
	      	n = strlen(mesg);
            sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   			//printf("check flag\n");
            if (flag == 1) {
            	//printf("broke\n");
            	close(connfd);
            	exit(0);
            }
         }
         
      //}
      //close(connfd);
      //int status;
      //wait(&status);
      //return 0;
   }
}