/*
Author: Antonio V. Alvillar
Version: 03/December/2015

This file will create a private heap of allocated memory that can be 
used by the client (mallok_text.c) to allocate memory from this private 
heap. This simulates what the C library does with malloc and free but in 
this instance the file is using my_malloc and my_free. A linked list will 
be used to create and keep track of block of memory as they are freed 
and allocated. 
*/

/*
Creates the private heap of allocated memory depending on the size passed 
in as a parameter. This heap will then be used for other client calls for 
memory allocation. This will also set the address the first block points to
then sets the size contained in the structure to the size passed into the 
function, then set the free int to show this block is available while its 
next field points to null. 
*/
void create_pool(int size) {
  heap = malloc(size);
  list = malloc(sizeof(Block));
  list->address = heap;
  list->free = 1;
  list->size = size;
  list->next = NULL;
}

/*
This function will scan through the list until an available block is found
that also has enough space free to allocate to a pointer then return the
address to the client. Effectively creating a new block for the client that
is not free but then seperating an identifying the next available block. If 
no block is available for the size needed, the NULL is returned.  
*/
void *my_malloc(int size) {
  int sizeAvail = 0;
  Block *scan = list;
  void *returnAddress = NULL;
  while (scan && (!scan->free || scan->size < size)) {
      scan = scan->next;
  }
  if (scan) { 
    scan->free = 0;
    if (scan->size >= size) {	
      sizeAvail = scan->size;		
      scan->size = size; 
      if (sizeAvail - size > 0) { 
        Block *newBlock = malloc(sizeof(Block));
        newBlock->free = 1;  
        newBlock->size = sizeAvail - size;
        newBlock->address = scan->address + size;
        newBlock->next = scan->next; 
        scan->next = newBlock;
      }
    }
    returnAddress = scan->address; 
  }
  return returnAddress;  
}

/*
This function will free the block passed that was previouslly allocated
but will also check for the block next to it and in front of it to see
if either is free as well so that they can be combined into a larger
sized block for future use. 
*/
void my_free(void *block) {
  Block *scan = list;
  Block *back = NULL;
  Block *temp = NULL;
  while (scan && scan->address != block) {
    back = scan;
    scan = scan->next;
  }
  if (scan) {
    scan->free = 1;
    if (scan->next && scan->next->free) {
      temp = scan->next;
      scan->size += temp->size;
      scan->next = temp->next;
      free(temp);
      temp = NULL;
    }
    if (back && back->free) {
      back->size += scan->size;
      back->next = scan->next;
      free(scan);
    }
  }
}

/*
Fucntion to first call a helper function (free_list) in order to free
all the blocks, then will free the private heap. 
*/
void free_pool() {
  free_list(list);
  free(heap);
}

/*
Recursive function to free each block in the linked list. Will stop
calling when list == null.
*/
void free_list(Block *list) {
  if (list) {
    free_list(list->next);
    free(list);
  }
}

/*
Function to print all the blocks (the list). The details printed 
are the address in hex of each block, the size and if free or not. 
Each block is on a seperate line. 
*/
void print_list(Block *list) {
  if (list) {
    printf("Address:%7X, Size:%5d, Free:%3d\n", 
           list->address, list->size, list->free);
    print_list(list->next);
  }
}
