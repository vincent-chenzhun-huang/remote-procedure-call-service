#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "a1_lib.h"
#include "message.h"
#define BUFSIZE   3072

int main(void) {
  int sockfd;
  char user_input[BUFSIZE] = { 0 };
  char server_msg[BUFSIZE] = { 0 };

  if (connect_to_server("0.0.0.0", 10000, &sockfd) < 0) {
    fprintf(stderr, "oh no\n");
    return -1;
  }
  while (strcmp(user_input, "shutdown\n")) {
    memset(user_input, 0, sizeof(user_input));
    memset(server_msg, 0, sizeof(server_msg));
    struct message parsed_msg = { 0 };

    printf("Enter commands: ");
    // read user input from command line
    fgets(user_input, BUFSIZE, stdin);
//    sscanf(user_input, "%s %d %d", parsed_msg->command, &(parsed_msg->arg1), &(parsed_msg->arg2));
    char * token = strtok(user_input, " ");
    int count = 0;
    while ( token != NULL ) {
        if (count == 0) {
            strcpy(parsed_msg.command, token);
        } else if (count == 1) {
            parsed_msg.arg1 = atoi(token);
        } else if (count == 2) {
            parsed_msg.arg2 = atoi(token);
        }
        count += 1;
        token = strtok(NULL, " ");
    }
    // send the input to server
    send_message(sockfd, (char *) &parsed_msg, sizeof(parsed_msg));
    // receive a msg from the server
    ssize_t byte_count = recv_message(sockfd, server_msg, sizeof(server_msg));
    if (byte_count <= 0) {
      break;
    }
    printf("Server: %s\n", server_msg);
  }

  return 0;
}

