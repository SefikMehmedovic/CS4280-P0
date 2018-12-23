//Sefik Mehmedovic
// CS4280
// P0
//main.c

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "node.h"
#include "tree.h"


int main(int argc, char* argv[])
{

  //file pointers
  FILE *filePointer, *tempFilePointer;
  
 
  char *outputBase;
  char *ext = ".fs18";

  //char array to store user input
  char line[300];
  
  tempFilePointer = fopen("tempFile", "w");
  
  if (argc == 1)
  {
	//filePointer for keyboard input
    filePointer = stdin;
 
    outputBase = "out";

  //ask user for keyboard input
   if (isatty(0))
  {
      printf("Keyboard input one string at a time:  ");
  }
	//skips whitespaces from reading in
    while (scanf(" %s[^ \t\n]%*c", line) == 1 && argc == 1){
      if (isatty(0)){
	  	if(!islower(line[0]))
		{
			printf("\nInvalid input\n", line);
      		exit(EXIT_FAILURE);
		}
        printf("\nEnter next string or EOF(CTRL+D) to exit: ");
      }
      fprintf(tempFilePointer, "%s\n", line);
    }

    if (feof(filePointer)){
     printf("reading in complete \n");
     fclose(filePointer);
     fclose(tempFilePointer);
    }
  }
  
  else if(argc == 2)
  {
	char *fileName;
	fileName = malloc(sizeof(argv[1]) + sizeof(ext));
    strncat(fileName, argv[1], strlen(argv[1]));
    strncat(fileName, ext, strlen(ext));
    filePointer = fopen(fileName, "r");

	//output format for inputfile
    outputBase = malloc(sizeof(argv[1]));
    outputBase = argv[1];

    // incase filePointer fails
    if (filePointer == NULL){
      printf("Error: unable to open file");
      exit(EXIT_FAILURE);
    }

    while(fscanf(filePointer, " %s[^ \t\n]%*c", line) == 1 && argc > 1){
      fprintf(tempFilePointer, "%s\n", line);
    }

    if (feof(filePointer)){
      printf("\nFile read complete.\n\n");
      fclose(filePointer);
      fclose(tempFilePointer);
    }
  }
  // if argc >2 and incorrect arguments
  else
  {
	printf("\nError: Too many arguments given\n");
  printf("./P0 < filename runs program on file\n");
  printf("./P0 runs program on keyboard input\n");
  printf("keyboard EOF(CTRL+D) to end user input\n");
    exit(EXIT_FAILURE);
  }
  
  tempFilePointer = fopen("tempFile", "r");
  if (tempFilePointer == NULL){
    printf("Unable to open tempFile for reading into tree: \n");
  //  fclose("tempFile");
    exit(EXIT_FAILURE);
  }
  //build tree
  buildTree(tempFilePointer);
	
  //close tempFilePointer
  fclose(tempFilePointer);

  //tree traversals and printing
  preorder(root, outputBase);
  inorder(root, outputBase);
  postorder(root, outputBase);
  
  printf("Output complete.\n");
  return 0;
}
