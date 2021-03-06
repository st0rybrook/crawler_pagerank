/*****
** network.c
** - implements the methods declared in network.h
** - ¶ÔÍøÂçsocketµÄÊÕ·¢œøÐÐ·â×°
*/

#include "network.h"

int open_tcp(char *hostname, int port)
{
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;
	struct timeval tv = {TIMEOUT, 0};

	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error!\n");
		return -1; 	
	}
	
	if ((hp = gethostbyname(hostname)) == NULL)
	{
		printf("host_name error!\n");
		return -2;
	}

	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
	serveraddr.sin_port = htons(port);

	/* Establish a connection with the server */
	if (connect(clientfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
	{
		printf("failed to connect to the server!\n");
		return -1;
	}
	setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	return clientfd;
}
/*
nsend();//发送字节到网络
nrecv();//从网络接收字节
recv_line();//从socket接收一行，以换行结束
close();//socket中已经有这个函数了，没有必要再写一个
*/
