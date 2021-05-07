#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

/* Function for Chat */
void func(int sockfd)
{
	char buff[100];
	int h;
	for(;;)
	{
		bzero(buff,sizeof(buff));
		printf("\nYOU :");
		h = 0;
		while((buff[h++] = getchar())!= '\n');
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("SERVER:%s ",buff);
		bzero(buff,100);

		if((strncmp(buff,"exit", 4)) == 0)
		{
			printf("\nClient is Leaving...\n");
			printf("---HELLO & WELCOME TO THE CHAT ROOM---\n\n");
			break;
		}
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in server, client;

	//Creating & Verify Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Creation of the Socket FAILED!!\n");
		exit(0);
	}
	else
	{
		printf("Creation of the Socket SUCCESS!!\n");
	}
	bzero(&server, sizeof(server));

	//Assign IP, PORT
	printf("PLEASE ENTER THE IP ADDRESS OF THE SERVER>> ");
	char ipserv[30];
	scanf("%s", ipserv);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ipserv);
	server.sin_port = htons(8888);

	//Connecting the CLIENT SOCKET to SERVER SOCKET
	if(connect(sockfd,(struct sockaddr*)&server, sizeof(server)) !=0)
	{
		printf("The server's connection is LOST!!\n");
		exit(0);
	}
	else
	{
		printf("The server is CONNECTED!! WAITING for respon...\n Press [CTRL + C] to QUIT anytime\n\n -----DA TEA SPILLER CHAT----\n");
	}

	//function for chat
	func(sockfd);

	//close the socket
	close(sockfd);
}
