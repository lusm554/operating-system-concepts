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

void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);

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


  for (p = servinfo; p != NULL; p = p->ai_next) {
    if (p->ai_family == AF_INET) // IPv4
      break;
  }

  if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
    perror("server: socket");
    return 1;
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
    close(sockfd);
    perror("server: bind");
    exit(1);
  }

  freeaddrinfo(servinfo);

  if (p == NULL) {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
  }

  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  sa.sa_handler = sigchld_handler; // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
 	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	} 

  printf("server: waiting for connections...\n");

  while (1) { // main accept() loop
    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == - 1) {
      perror("accept");
      continue;
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
    printf("server: got connection from %s\n", s);

    if (!fork()) { // this is the child process
      close(sockfd); // child doesn't need the listener
      if (send(new_fd, haiku, sizeof haiku, 0) == -1)
        perror("send");
      close(new_fd);
      exit(0);
    }
    close(new_fd); // parent doesn't need this
  }

  return 0;
}

void sigchld_handler(int s) {
  // waitpid() might overwrite errno, so we save and restore it:
  int saved_errno = errno;

  while(waitpid(-1, NULL, WNOHANG) > 0);

  errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


