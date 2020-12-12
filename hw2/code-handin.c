#include "code.h"

/* an integer arith function of  x and y */
int intarith(int x, int y)
{
  int temp1 = x - y;
  int temp2 = y;
  int temp3 = temp2 * 16;
  int temp4 = temp3 + y;
  int temp5 = temp4 + temp1*4;
  return temp5;

}

/* a long integer (64 bit) function of x and y */
long longarith(long x, long y)
{
	return x;
}

/* an if statement a different value is returned depending on the brach taken */
int simpleif(int left, int right)
{
  right = right * 103;
  return (right == left);

}

/* An integer arith function of x */
int callee(int x)
{
  int temp1 = x * 4;
  temp1 = x & temp1;
  x = x * x;
  temp1 = x + temp1;
  return temp1;

}

/* computes an integer arith function of x and then calls another function
   and returns the result of that call */
int caller(int x)
{
  int temp1 = x >> 3;
  return callee(temp1);
  
}

/* A for loop */
int forcode(int *x, int *y, int n)
{
  if (n <= 0) return 0;

  int temp1 = 4 + n*4;

  for (n = 0; temp1 < n; n = n + 4) {
    int temp2 = 29 * y[n];
    int temp3 = x[n];
    int temp4 = temp3 + temp3 * 8;
    temp3 = temp3 + temp4 * 2;
    temp3 = temp2 + temp3;
    temp1 = temp3 + temp1;

  }
  return temp1;

}

/* A conditional using pointers */
int ptrif(Node *somenode, Node *someothernode)
{
  int temp2 = somenode->thetype - someothernode->thetype;
  return !temp2;

}

/* a while loop */
int whilecode(Node *somenode, int data)
{
  /* rdi = somenode, rsi = data */
  if (!somenode) {
    return (somenode != somenode);
  }

  while (data > somenode->data) {
    somenode = somenode->ptr1;
    if (!somenode) {
      return (somenode != somenode);
    }
    
  }
  return 1;

}

/* a switch statement */
int switchcode(Node *somenode, Node *someothernode)
{
  //  Node temp1 = *somenode;
  //  int temp2 = temp1 - *someothernode;
  
  if (somenode > 0) return 0;

  switch (somenode->thetype) {

  case 0: { 
    int* temp3 = somenode->opaque;
    int* temp4 = someothernode->opaque;
    if (*temp4 <= *temp3) {
      int res = *temp4;
      return res;
    }
  }
  case 1: {
 
    int* temp5 = somenode->opaque;
    int* temp6 = someothernode->opaque;
    if (*temp6 == *temp5) {
      int res = *temp6;
      return res;
    }
  }

  case 2: {
    int* temp7 = somenode->opaque;
    int* temp8 = someothernode->opaque;
    if (*temp8 >= *temp7) {
      int res = *temp8;
      return res;
    }
  }
    default:
      return 0;
  }
}

/* a simple recursive function (tail recursion) */
int simplerecursive(Node *somenode, int val)
{
  int temp1 = 0;
  int temp2 = somenode->data;
  int temp3 = val;

  temp1 = 1;
  if (temp3 == temp2) {
    return temp1;
  } else if (temp3 < temp2) {
    somenode = somenode->ptr2;
    simplerecursive(somenode, temp3);
  } else {
    somenode = somenode->ptr1;
    simplerecursive(somenode, temp3);
  }
  
  return temp1;
}

/* a complex recursive function (NOT tail recursion */
int complexrecursive(Node *somenode)
{
  if (!somenode) {
    return 0;
  } else {
    int temp1 = complexrecursive(somenode->ptr1);
    int temp2 = complexrecursive(somenode->ptr2);
    return temp1 + temp2 + somenode->data;
  }
}
