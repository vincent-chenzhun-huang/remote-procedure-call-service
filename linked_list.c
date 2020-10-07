#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include "linked_list.h"

void add_node (node_t *node, int val) {
    node_t *current = node;
    while(current->next != NULL) {
        current = current->next;
    }
    current ->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;

}

int find_and_remove(node_t *pid, node_t *rval, int val) {
    /*
     * We know that pids are unique, we only remove the corresponding values of pid according to rval
     */
    int found = 0;
    node_t *curr1 = pid;
    node_t *curr2 = rval;

    while (curr2 != NULL && curr2->next != NULL) {
        if (curr2->next->val == val) {
            curr2->next = curr2->next->next;
            curr1->next = curr1->next->next;
            found = 1;
        } else {
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    }
    return found;
}

node_t* tail(node_t *node) {
    node_t * curr = node;
    while(curr->next !=NULL) {
        curr = curr -> next;
    }
    return curr;
}

