#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define PORT "5575" // the port users will be connecting to 
#define BACKLOG 5   // how many pending connections queue will hold
#define haiku "An old silent pond\nA frog jumps into the pond—\nSplash! Silence again.\n" 

int main(void) {
  /*
  servinfo(res)   - pointer to a linked-list of results
  hints           - points to a struct addrinfo with relevant info
  */
  int sockfd, new_fd; // listen on sockfd, new connections on new_fd
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr; // connector's address info
  socklen_t sin_size;
  struct sigaction sa;
  int yes = 1;
  char s[INET6_ADDRSTRLEN];
  int rv;


  memset(&hints, 0, sizeof hints); // clear memory
  hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE; // means use my IP

  if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) { // get info about machine
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  } 

  if ((sockfd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol)) == -1) {
    perror("server: socket");
    return 1;
  }

  return 0;
}

