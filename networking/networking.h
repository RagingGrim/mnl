#ifndef NETWORKING_H
#define NETWORKING_H
//DEFINES
#define SOCKET_MAGIC_NUMBER 1

// FUNCTIONS
#ifdef __linux__
short getAddrP(const char *Hostname,char *strIP,const int AI_FAM);
#endif

ssize_t recvAllFixed(int Socket , char *Buffer , size_t Size ; int Flags);
ssize_t sendAllFixed(int Socket , char *Buffer , size_t Size ; int Flags);
#endif
