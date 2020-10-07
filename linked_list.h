typedef struct node {
    int val;
    struct node *next;
} node_t;

void add_node (node_t *node, int val);

int find_and_remove(node_t *pid, node_t *rval, int val);

node_t* tail(node_t *node);