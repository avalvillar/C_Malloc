/*
Author: Antonio V. Alvillar
Version: 03/December/2015

This is the header file that works in conjunction with the mallok.c and the 
driver mallok_test.c; Contained will be the static variables needed as well 
as the prototypes for functions that will be used during the program.
*/

/* Needed includes. */
#include <stdio.h>
#include <stdlib.h>

/* 
The structure for the linked list implementation - in this case they are 
called block as in "block of memory" and the two names Block and List. 
Fields are: 
	void * - to an address of allocated memory.
	int - to store the size of the block this structure is pointed to. 
	int free - indicates if the block is free (0 unavailable, 1 avaiable).
	block * - to the next block in the list.
*/
typedef struct block {
  void *address;
  int size;
  int free;
  struct block *next;
} Block, List;

/* Static variables for the private Heap and List which is a structure. */
static void *heap;
static List *list;

/* Prototypes for the functions. */
void create_pool(int); /* create the private heap of allocated memory. */
void free_pool(); /* Free the private heap of allocated memory. */
void free_list(Block *); /* Free all blocks of used memory. */
void *my_malloc(int); /* Allocate memory from the private heap. */
void my_free(void *); /* Free a specific block of used memory. */
void print_list(Block *); /* Print all the blocks of memory. */

/* Prototypes for the test functions in the driver program. */
void test1();
void test2();
void test3();
void test4();
void test4b();

#include "mallok.c"
