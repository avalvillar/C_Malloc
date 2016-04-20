/*
Author: Antonio V. Alvillar
Version: 03/December/2015

This file will do multiple calls to all the functions listed in the 
mallok.c file - in doing so, will be testing the functionality of the 
program and does not produce any errors using the test indicated below. 
*/

/* Inlude the header file for mallok (which inludes the mallok.c) */
#include "mallok.h"

/* Main function just calls all the test functions. */
int main(void) {
  test1();
  test2();
  test2();
  test3();
  test4();
  return 0;
}

/*
Per the assignment instructions - "create a pool of 1000 bytes. Count how 
times you can successfully request a block of size 10."
*/
void test1() {
  int count = 0;
  create_pool(1000);
  while (my_malloc(10) != NULL) {
    count++;
  }
  printf("\nTest 1\n");
  printf("Calls my_malloc(10): %d times when Heap is 1000 bytes\n", count);
  free_pool();
}

/*
Per the assignment instructions - "create a pool of 1000 bytes. Make 5 
requests for blocks of 200 bytes. Free all 5 blocks. Repeat this 
request/free pattern several times to make sure you can reuse blocks after
they are returned."

This function is called twice to check for errors. 
*/
void test2() {
  printf("\nTest 2\n");
  create_pool(1000);
  void *one = my_malloc(200);
  void *two = my_malloc(200);
  void *three = my_malloc(200);
  void *four = my_malloc(200);
  void *five = my_malloc(200);
  printf("Here are 5 allocations of 200:\n");
  print_list(list);
  my_free(one);
  my_free(two);
  my_free(three);
  my_free(four);
  my_free(five);
  printf("Here is the list after they are freed:\n");
  print_list(list);
  free_pool(); 
}

/*
Per the assignment instructions - "create a pool of 1000 bytes. Make 5 
requests for blocks of 200 bytes. Free the middle block. Request a block of
210 bytes (it should fail) Request a block of 150 bytes (it should succeed) 
Request a block of 60 bytes (it should fail) Request a block of 50 bytes 
(it should succeed) etc."
*/
void test3() {
  create_pool(1000);
  void *one = my_malloc(200);
  void *two = my_malloc(200);
  void *three = my_malloc(200);
  void *four = my_malloc(200);
  void *five = my_malloc(200);
  my_free(three);
  void *failOne = my_malloc(210);
  void *successOne = my_malloc(150);
  void *failTwo = my_malloc(60);
  void *successTwo = my_malloc(50);
  printf("\nTest 3\n");
  printf("210 bytes should be NULL (0): %x\n", failOne);
  printf("150 bytes should not be NULL: %x\n", successOne);
  printf("60 bytes should be NULL (0): %x\n", failTwo);
  printf("50 bytes should not be NULL: %x\n", successTwo);
  free_pool();
}

/*
Per the assignment instructions - "create a pool of 1000 bytes. Request and 
return a block of 1000 bytes Request and return four blocks of 250 bytes 
Request and return ten blocks of 100 bytes"
*/
void test4() {
  printf("\nTest 4\n");
  create_pool(1000);
  void *thousand = my_malloc(1000);
  printf("List after allocating 1000:\n");
  print_list(list);
  my_free(thousand);
  printf("List after freeing 1000:\n");
  print_list(list);
  void *one = my_malloc(250);
  void *two = my_malloc(250);
  void *three = my_malloc(250);
  void *four = my_malloc(250);
  printf("List after allocating 4 blocks of 250:\n");
  print_list(list);
  my_free(one);
  my_free(two);
  my_free(three);
  my_free(four);
  printf("List after freeing 4 blocks of 250:\n");
  print_list(list);
  free_pool();
  /*Call a helper function for the "request and return 10 blocks of 100."*/
  test4b();
}

/*
This is a helper function to complete test 4 as it was quite lengthy and 
the needed testing is "request and return 10 blocks of 100.". 
*/
void test4b() {
  create_pool(1000);
  void *one = my_malloc(100);
  void *two = my_malloc(100);
  void *three = my_malloc(100);
  void *four = my_malloc(100);
  void *five = my_malloc(100);
  void *six = my_malloc(100);
  void *seven = my_malloc(100);
  void *eight = my_malloc(100);
  void *nine = my_malloc(100);
  void *ten = my_malloc(100);
  printf("List after allocating 10 blocks of 100:\n");
  print_list(list);
  my_free(one);
  my_free(two);
  my_free(three);
  my_free(four);
  my_free(five);
  my_free(six);
  my_free(seven);
  my_free(eight);
  my_free(nine);
  my_free(ten);
  printf("List after freeing 10 blocks of 100:\n");
  print_list(list);
  free_pool();
}

/*
Below is code used as testing during the creation of the program. 
*/
/*
  printf("\n");
  create_pool(1000);
  int *test = my_malloc(sizeof(int));
  *test = 10;
  int *test3 = my_malloc(125);
  *test3 = 124;
  int *test4 = my_malloc(10);
  *test4 = 124;
  print_list(list);
  my_free(test3);
  printf("\n");
  print_list(list);
  test3 = my_malloc(25);
  printf("\n");
  print_list(list);
  my_free(test3);
  printf("\n");
  print_list(list);
  my_free(test);
  printf("\n");
  print_list(list);
  my_free(test4);
  printf("\n");
  print_list(list);
  free_pool();
  test3 = my_malloc(25);
  printf("\n");
  print_list(list);
  free_pool();
  return 0;
  */