//
// Created by vincenthuang on 9/29/20.
//

#ifndef REMOTE_PROCEDURE_CALL_SERVICE_MESSAGE_H
#define REMOTE_PROCEDURE_CALL_SERVICE_MESSAGE_H
#define BUFSIZE   1024

struct message {
    char command[BUFSIZE];
    int arg1;
    int arg2;
};
#endif //REMOTE_PROCEDURE_CALL_SERVICE_MESSAGE_H
