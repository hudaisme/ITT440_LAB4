#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

//Chat between Client and Server is performed by this function
void func(int sockfd)
{
	char buff[100];
	int h;

	//infinite loop for chat
	for(;;)
	{
		bzero(buff,100);

		//read the messtruct sockaddrge from Client and copy it in buffer
		read(sockfd, buff, sizeof(buff));
		//print buffer which contains the CLIENT CONTENT
		printf("Client:%sYou :", buff);
		bzero(buff,100);
		h = 0;

		//copy Server messtruct sockaddrge in the buffer
		while((buff[h++] = getchar()!='\n'));

		// send that buffer to client
		write(sockfd, buff, sizeof(buff));

		//if the message includes word EXIT, the server will exit and the conversation will stop
		if(strncmp("exit", buff, 4) == 0)
		{
			printf("\nEXIT SERVER...\n");
			printf("---HELLO & WELCOME TO CHAT ROOM---\n\n");
			break;
		}
	}
}

//Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	//Creating & verify socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Creation of Socket is FAILED!!\n");
		exit(0);
	}
	else
	{
		printf("Socket created SUCCESSFULLY!!\n");
	}
	bzero(&servaddr,sizeof(servaddr));

	//Prepare the sockaddr_in structure
	servaddr.sin_family =AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8888);

	//Binding a newly formed SOCKET to a SPECIFIED IP, and CHECKING
	if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))!=0)
	{
		printf("SOCKET FAILED TO BIN!!\n");
		exit(0);
	}
	else
	{
		printf("SOCKET SUCESSFULLY BINDED");
	}

	//Listen
	if((listen(sockfd, 5))!=0)
	{
		printf("FAILED to LISTEN!!\n");
		exit(0);
	}
	else
	{
		printf("\nSERVER is WAITING for YOU\n");
	}
	len = sizeof(cli);

	//Accept data packet from CLIENT & verification
	connfd = accept(sockfd,(struct sockaddr*)&cli, &len);
	if(connfd < 0)
	{
		printf("ACCEPTANCCED BY THE SERVER FAILED!!\n");
		exit(0);
	}
	else
	{
		printf("A CLIENT was APPROVED by the SERVER. To START a conversation, SEND a response message!!\n");
		printf("\nType [EXIT} to close the server and chat.\n\n----DA TEA SPILLERS CHAT----\n");
	}

	//Function for chatting between CLIENT & SERVER
	func(connfd);

	//Closing socket
	close(sockfd);
}
