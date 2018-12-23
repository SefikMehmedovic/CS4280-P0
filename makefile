# makefile for P0
#
all: *.c
	gcc -g -Wall -o P0 *.c

clean:
	$(RM) P0 *preorder *.inorder *.postorder
