#ifndef NETWORKING_H
#define NETWORKING_H
#include <sys/socket.h>
//DEFINES
#define SOCKET_MAGIC_NUMBER 1


// FUNCTIONS
#ifdef __linux__
/**
 * Returns the first ipv4/ipv6 address associated with a hostname.
 * @param  Hostname The hostname to resolve.
 * @param  strIP    The buffer to write the ip to.
 * @param  AI_FAM   AF_INET / AF_INET6
 * @return          Returns 1 on success.
 */
short getAddrP(const char *Hostname,char *strIP,const int AI_FAM);
#endif

/**
 * Receives all incoming data on a BLOCKING socket.
 * @param  Socket Socket to receive on.
 * @param  Buffer Buffer to receive to (preallocated).
 * @param  Size   The amount of bytes to receive
 * @param  Flags  Socket Flags
 * @return        The amount of bytes returned / or -1 for an error
 */
ssize_t recvAllFixed(int Socket , char *Buffer , const size_t Size , const int Flags);

/**
 * Sends all incoming data on a BLOCKING socket ( This function may be redundant).
 * @param  Socket Socket to send to.
 * @param  Buffer Buffer to send to (preallocated).
 * @param  Size   The amount of bytes to receive
 * @param  Flags  Socket Flags
 * @return        The amount of bytes returned / or -1 for an error
 */
ssize_t sendAllFixed(int Socket , char *Buffer , const size_t Size , int Flags);

// TODO: Check why inside a thread this function isn't setting the ip.
char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen);
char *getPeerAddr(const struct sockaddr *sa, socklen_t maxlen);
#endif
