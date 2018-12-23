//node.h

#ifndef NODE_H
#define NODE_H

// node struct
typedef struct node{
  struct node *left;
  struct node *right;
  char id[2];
  char string[255];
  int level;
} node_t;

#endif 
