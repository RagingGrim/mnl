#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include "../lib/networking.h"

#ifdef __linux__
	short getAddrP(const char *Hostname,char *strIP,const int AI_FAM){
		  char temp[30] = {0};
		  struct addrinfo *res;   //contrary to what I thought , getaddrinfo returns a malloc addrinfo structure.
		  struct addrinfo hints;

		  memset(&hints,0,sizeof(struct addrinfo));//zero out hints


		  //set hints
		  hints.ai_socktype = SOCK_DGRAM;
		  hints.ai_family = AI_FAM;
		  hints.ai_flags = AI_PASSIVE;

		  if( getaddrinfo(Hostname,NULL,&hints,&res) != 0)
		      return 0;
		  void *addr = NULL;

		  struct sockaddr_in *ipv4;
		  struct sockaddr_in6 *ipv6;

		  if (AI_FAM == AF_INET){
		        //ipv4
		        ipv4 = (struct sockaddr_in *)res->ai_addr;
		        addr = &(ipv4->sin_addr);
		        }
		  else if (AI_FAM == AF_INET6){
		        //ipv6
		        ipv6 = (struct sockaddr_in6 *)res->ai_addr; //typecast the addr into a sockaddr_in6 structure
		        addr = &(ipv6->sin6_addr); //Save the void pointer to use as a one liner lately.
		        }

		  inet_ntop(AI_FAM,addr ,temp, 30);
		  strcpy(strIP,(char *)(&temp));
		  freeaddrinfo(res);
		  return 1;
	}
#endif

ssize_t recvAllFixed(int Socket , char *Buffer , const size_t Size , const int Flags){
	size_t bytesLeft = Size;
	char *buffptr = Buffer;
	while(bytesLeft > 0){
		ssize_t recvRet = recv(Socket, buffptr, bytesLeft, Flags);
		if( recvRet <= 0)
			return recvRet;
		buffptr += recvRet;
		bytesLeft -= recvRet;
	}
	return Size;
}

ssize_t sendAllFixed(int Socket , char *Buffer , const size_t Size , int Flags){
	size_t bytesLeft = Size;
	char *buffptr = Buffer;
	while(bytesLeft > 0){
		ssize_t sndRet = send(Socket, buffptr, bytesLeft, Flags);
		if( sndRet <= 0)
			return sndRet;
		buffptr += sndRet;
		bytesLeft -= sndRet;
	}
	return Size;
}
//TODO: Define sendAllFixed/recvAllFixed.
