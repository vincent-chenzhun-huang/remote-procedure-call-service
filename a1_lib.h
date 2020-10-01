/**
 *  @author: Trung Vuong Thien
 *  @email: trung.vuongthien@mail.mcgill.ca
 *  @description: Header file for socket wrapper functions
 */

#ifndef A1_LIB_
#define A1_LIB_

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BACKLOG_SIZE    10

/**
 *  Set up a server socket.
 *
 *  @params:
 *    host:     A string representing the host address of the server.
 *    port:     An integer in the range [0, 65536) representing the port.
 *    sockfd:   The file descriptor associated with the server socket.
 *  @return:    On success, the file descriptor associated with the newly
 *              created socket is assigned to sockfd, and 0 is returned.
 *              If the function fails to set up the socket, -1 is returned.
 */
int create_server(const char *host, uint16_t port, int *sockfd);

/**
 *  Accept a client connection on a server socket.
 *
 *  @params:
 *    sockfd:   The file descriptor of the server socket.
 *    clientfd: The file descriptor of the client connection.
 *  @return:    On success, a connection is set up between the server and
 *              client processes. The function assigns the file descriptor
 *              value to clientfd, and returns 0. If an error occurs, the
 *              function will return -1.
 */
int accept_connection(int sockfd, int *clientfd);

/**
 *  Connect to a server.
 *
 *  @params:
 *    host:     A string representing the host address of the server.
 *    port:     An integer in the range [0, 65536) representing the port.
 *    sockfd:   The file descriptor associated with the socket
 *  @return:    On success, the fiel descriptor associated with the newly
 *              created socket is assigned to sockfd, and 0 is returned.
 *              If the function fails to set up the socket, -1 is returned.
 */
int connect_to_server(const char *host, uint16_t port, int *sockfd);

/**
 *  Send a frontend on a socket.
 *
 *  @params:
 *    sockfd:   The file descriptor of the socket.
 *    buf:      The frontend to send.
 *    len:      Number of bytes to send.
 *  @return:    On success, the functions returns the number of bytes send.
 *              On error, -1 is returned.
 */
ssize_t send_message(int sockfd, const char *buf, size_t len);

/**
 *  Receive a frontend from a socket.
 *
 *  @params:
 *    sockfd:   The file descriptor of the socket.
 *    buf:      A buffer to store the received frontend.
 *    len:      The size of the buffer.
 *  @return:    On success, the function returns he number of bytes received.
 *              A value of 0 means the connection on this socket has been
 *              closed. On error, -1 is returned.
 */
ssize_t recv_message(int sockfd, char *buf, size_t len);

#endif  // A1_LIB_

