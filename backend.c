#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a1_lib.h"
#include "message.h"
#include "linked_list.h"

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

char *process_request(struct message *msg, char *response) {
    if (strcmp(msg->command, "add") == 0) {
        int sum = addInts(msg->arg1, msg->arg2);
        sprintf(response, "%d", sum);
    } else if (strcmp(msg->command, "multiply") == 0) {
        int product = multiplyInts(msg->arg1, msg->arg2);
        sprintf(response, "%d", product);
    } else if (strcmp(msg->command, "divide") == 0) {
        float numerator = (float) msg->arg1;
        float denominator = (float) msg->arg2;
        if (denominator == 0) {
            strcpy(response, "Cannot divide by 0\n");
        } else {
            sprintf(response, "%f", divideFloats(numerator, denominator));
        }
    } else if (strcmp(msg->command, "sleep") == 0) {
        int time = msg->arg1;
        unsigned int slept = sleepServer(time);
        if (slept != 0) {
            fprintf(stderr, "Sleep command failed\n");
        }
        sprintf(response, "sleep %d", time);
    } else if (strcmp(msg->command, "factorial") == 0) {
        sprintf(response, "%lu", factorial(msg->arg1));
    } else {
        sprintf(response, "Invalid command! %s", msg->command);
    }

    return response;
}


int main(void) {
    node_t pid = {0, NULL};
    node_t rval = {0, NULL};
    int sockfd, clientfd;
    char msg[BUFSIZE];
    char response[BUFSIZE];
    if (create_server("127.0.0.1", 4444, &sockfd) < 0) {
        fprintf(stderr, "oh no\n");
        return -1;
    }
    while (1) {
        if (accept_connection(sockfd, &clientfd) < 0) {
            fprintf(stderr, "oh no\n");
            return -1;
        } else {
            printf("accepted connection from client %d\n", clientfd);
        }
//      for (int i = 0; i < 10; i++) {
//          waitpid(pids[i], &rvals[i], 1);
//          printf("Testing %d: %d\n", i, WEXITSTATUS(rvals[i]));
//          if (WEXITSTATUS(rvals[i]) == 3) {
//              printf("Shutdown signal received.\n");
//              exit(0);
//          }
//      }

        node_t *curr1 = &pid;
        node_t *curr2 = &rval;
        int shutdownSig = 0;
        sleep(2);
        while (curr2 != NULL && curr2->next != NULL) {
            puts("waiting for child");
            sleep(2);
            waitpid((curr1->val), &(curr2->val), 1);
            sleep(2);
            if (WEXITSTATUS(curr2->next->val) == 3) {
                curr2->next = curr2->next->next;
                curr1->next = curr1->next->next;
                shutdownSig = 1;
            } else {
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }
        if(shutdownSig == 1) {
            printf("shutdown signal received");
            exit(0);
        }
        pid_t pid1 = fork();
        add_node(&pid, pid1); // return 0 if in the child process, >0 if it's the parent process, parent will go on to else
        add_node(&rval, 0);

        if (pid1 == 0) { // in the child process
//          close(sockfd);

            while (1) {
                memset(msg, 0, sizeof(msg));
                ssize_t byte_count = recv_message(clientfd, msg, BUFSIZE);

                if (byte_count <= 0) {
                    exit(1);
                }
                struct message *parsed_msg = (struct message *) msg;
                printf("Command: %s", parsed_msg->command);
                if (strcmp(parsed_msg->command, "shutdown\n") != 0) {
                    printf("it's not shutdown, moving on... \n");
                    process_request(parsed_msg, response);
                    send_message(clientfd, response, sizeof(response));
                } else {
                    printf("it is a shutdown!!!");
                    sprintf(response, "shutting down...");
                    send_message(clientfd, response, sizeof(response));
                    puts("child exited");
//                  shutdownsignal = 1;
                    return 3;
                }
            }
        } else {
            node_t * t_pid = tail(&pid);
            node_t * t_rval = tail(&rval);
            waitpid((t_pid->val), &(t_rval->val), 1);
            puts("waiting for child, sleep 2");
            sleep(2);
        }
    }
}





