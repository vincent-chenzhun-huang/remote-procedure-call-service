/**
 *  @author: Trung Vuong Thien
 *  @email: trung.vuongthien@mail.mcgill.ca
 *  @description: Implementation of the functions declared in a1_lib.h
 */

#include "a1_lib.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int create_server(const char *host, uint16_t port, int *sockfd) {
  struct sockaddr_in server_address = { 0 };

  // create TCP socket
  *sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (*sockfd < 0) {
    perror("Failed to create a new socket\n");
    return -1;
  }

  // set options
  int opt = 1;
  if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("Failed to set options for socket\n");
    return -1;
  }

  // bind to an address
  server_address.sin_family = AF_INET;
  inet_pton(AF_INET, host, &(server_address.sin_addr.s_addr));
  server_address.sin_port = htons(port);
  if (bind(*sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("Failed to bind to an address\n");
    return -1;
  }

  // start listening
  if (listen(*sockfd, BACKLOG_SIZE) < 0) {
    perror("Failed to listen to socket\n");
    return -1;
  }

  return 0;
}

int accept_connection(int sockfd, int *clientfd) {
  struct sockaddr_in connection_address = { 0 };
  socklen_t addrlen = sizeof(connection_address);

  // wait for a new connection on the server socket and accept it
  *clientfd = accept(sockfd, (struct sockaddr *)&connection_address, &addrlen);
  if (*clientfd < 0) {
    perror("Failed to accept client connection\n");
    return -1;
  }
  return 0;
}

int connect_to_server(const char *host, uint16_t port, int *sockfd) {
  struct sockaddr_in server_address = { 0 };

  // create a new socket
  *sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (*sockfd < 0) {
    perror("Failed to create a new socket\n");
    return -1;
  }

  // connect to server
  server_address.sin_family = AF_INET;
  inet_pton(AF_INET, host, &(server_address.sin_addr.s_addr));
  server_address.sin_port = htons(port);
  if (connect(*sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("Failed to connect to server\n");
    return -1;
  }
  return 0;
}

ssize_t send_message(int sockfd, const char *buf, size_t len) {
  return send(sockfd, buf, len, 0);
}

ssize_t recv_message(int sockfd, char *buf, size_t len) {
  return recv(sockfd, buf, len, 0);
}

