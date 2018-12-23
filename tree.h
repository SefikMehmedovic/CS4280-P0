//tree.h

#ifndef TREE_H
#define TREE_H

//global node_t root
extern node_t *root;

//build tree 
void buildTree(FILE *tempFile);

void search(node_t *searchNode);
char *concat(const char *s1, const char *s2);

//traversals
void preorder(node_t *root, char *outputBase);
void inorder(node_t *root, char *outputBase);
void postorder(node_t *root, char *outputBase);

//printing traversals
void printInorder(node_t *n, FILE *outputFile);
void printPreorder(node_t *n, FILE *outputFile);
void printPostorder(node_t *n, FILE *outputFile);

#endif