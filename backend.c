#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "a1_lib.h"
#include "message.h"
#define BUFSIZE  3072
//
int addInts(int a, int b) {
    return a + b;
}

int multiplyInts(int a, int b) {
    return a * b;
}

float divideFloats(float a, float b) {
    return a / b;
}

unsigned int sleepServer(int x) {
    return sleep(x);
}

uint64_t factorial(int x) {
    uint64_t result = 1;
    while (x > 0) {
        result *= x;
        x -= 1;
    }
    return result;
}

char* process_request(struct message *msg, char *response) {
    if(strcmp(msg ->command, "add")==0) {
        int sum = addInts(msg->arg1, msg->arg2);
        sprintf(response, "%d", sum);
    } else if (strcmp(msg ->command, "multiply")== 0 ) {
        int product = multiplyInts(msg->arg1, msg->arg2);
        sprintf(response, "%d", product);
    } else if ( strcmp(msg->command, "divide") == 0 ) {
        float numerator = (float)msg->arg1;
        float denominator = (float)msg->arg2;
        if (denominator == 0) {
            strcpy(response, "Cannot divide by 0\n");
        } else {
            sprintf(response, "%f", divideFloats(numerator, denominator));
        }
    } else if ( strcmp(msg->command, "sleep") == 0 ) {
        int time = msg->arg1;
        unsigned int slept = sleepServer(time);
        if (slept != 0) {
            fprintf(stderr, "Sleep command failed\n");
        }
        sprintf(response, "sleep %d", time);
    } else if ( strcmp(msg->command, "factorial") == 0 ) {
        sprintf(response, "%lu", factorial(msg->arg1));
    } else {
        sprintf(response, "Invalid command! %s", msg -> command);
    }

    return response;
}



int main(void) {
  int sockfd, clientfd;
  char msg[BUFSIZE];
  char response[BUFSIZE];
  const char *greeting = "hello, world\n";
  int running = 1;
  if (create_server("0.0.0.0", 10000, &sockfd) < 0) {
    fprintf(stderr, "oh no\n");
    return -1;
  }

  if (accept_connection(sockfd, &clientfd) < 0) {
    fprintf(stderr, "oh no\n");
    return -1;
  }

  while (strcmp(msg, "shutdown\n")) {
    memset(msg, 0, sizeof(msg));
    ssize_t byte_count = recv_message(clientfd, msg, BUFSIZE);

    if (byte_count <= 0) {
      break;
    }
    printf("%s\n", msg);
    struct message *parsed_msg = (struct message *) msg;
    printf("%s - %d - %d\n", parsed_msg->command, parsed_msg->arg1, parsed_msg->arg2);
//    process_request(parsed_msg, response);
//    puts(m->command);
    process_request(parsed_msg, response);
    send_message(clientfd, response, sizeof(response));
  }

  return 0;
}





