//tree.c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "tree.h"

// temp node_t
node_t *temp;
//global root node_t
node_t *root;

//build tree function
void buildTree(FILE *tempFile){
  root = NULL;
  char line[255];
  while (fscanf(tempFile, " %s[^ \t\n]", line) == 1){
    temp = malloc(sizeof(node_t));
    temp->left = temp->right = NULL;
    sprintf(temp->id, "%.1s",line);
    strcpy(temp->string, line);
    temp->level = 0;

    // place first node as temp
    if(root == NULL){
      root = temp;
    }
    else{
      search(root);
    }
  }
}
//search node function
void search(node_t *searchNode){

  if (strcmp(temp->id, searchNode->id) == 0){
    strcpy(searchNode->string, concat(searchNode->string, temp->string));
  }
  else if ((strcmp(temp->id, searchNode->id) > 0) && (searchNode->right != NULL)){
    temp->level++;
    search(searchNode->right);
  }

  else if ((strcmp(temp->id, searchNode->id) > 0) && (searchNode->right == NULL)){
    temp->level++;
    searchNode->right = temp;
  }
  else if ((strcmp(temp->id, searchNode->id) < 0) && (searchNode->left != NULL)){
    temp->level++;
    search(searchNode->left);
  }
  else if ((strcmp(temp->id, searchNode->id) < 0) && (searchNode->left == NULL)){
    temp->level++;
    searchNode->left = temp;
  }
}

char *concat(const char *s1, const char *s2){
  char *ns = malloc(snprintf(NULL, 0, "%s %s", s2, s1) + 1);
  sprintf(ns, "%s %s", s2, s1);
  return ns;
}


//-------------------------//
//preorder -----
void preorder(node_t *root, char *outputBase){
  FILE *outpt;
  char *outExtension = ".preorder";
  char *outputFileName = malloc(snprintf(NULL, 0, "%s%s", outputBase, outExtension) + 1);
  sprintf(outputFileName, "%s%s", outputBase, outExtension);
  outpt = fopen(outputFileName, "w");
    if(outpt == NULL){
      fprintf(stderr, "Unable to open output file: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  printPreorder(root, outpt);
  fclose(outpt);
}

//inorder ------
void inorder(node_t *root, char *outputBase){
  FILE *outpt;
  char *outExtension = ".inorder";
  char *outputFileName = malloc(snprintf(NULL, 0, "%s%s", outputBase, outExtension) + 1);
  sprintf(outputFileName, "%s%s", outputBase, outExtension);
  outpt = fopen(outputFileName, "w");
    if(outpt == NULL){
      fprintf(stderr, "Unable to open output file: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  printInorder(root, outpt);
  fclose(outpt);
}

//postorder -----

void postorder(node_t *root, char *outputBase){
  FILE *outpt;
  char *outExtension = ".postorder";
  char *outputFileName = malloc(snprintf(NULL, 0, "%s%s", outputBase, outExtension) + 1);
  sprintf(outputFileName, "%s%s", outputBase, outExtension);
  outpt = fopen(outputFileName, "w");
  if(outpt == NULL){
    fprintf(stderr, "Unable to open output file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printPostorder(root, outpt);
  fclose(outpt);
}

// print traversal functions for above

void printPreorder(node_t *n, FILE *outpt){
  if (root == NULL){
    return;
  }
  fprintf(outpt,"%*s%-9s\n", n->level*2,"", concat(n->string, n->id));
  if (n->left != NULL)
    printPreorder(n->left, outpt);
  if (n->right != NULL)
    printPreorder(n->right, outpt);
}

void printInorder(node_t *n, FILE *outpt){
  if (root == NULL){
    return;
  }
  if (n->left != NULL)
    printInorder(n->left, outpt);
    fprintf(outpt,"%*s%-9s\n", n->level*2,"", concat(n->string, n->id));
  if (n->right != NULL)
    printInorder(n->right, outpt);
}

void printPostorder(node_t *n, FILE *outpt){
  if (root == NULL){
    return;
  }
  if (n->left != NULL)
    printPostorder(n->left, outpt);
  if (n->right != NULL)
    printPostorder(n->right, outpt);
    fprintf(outpt,"%*s%-9s\n", n->level*2,"",concat(n->string, n->id));
}
