#ifndef _code
#define _code

int intarith(int x, int y);

long longarith(long x, long y);

int simpleif(int left, int right);

int callee(int x);

int caller(int x);

int forcode(int *x, int *y, int n);

double doublearith(double *x, int n);

typedef enum {CHAR,SHORT,INT} Type;

typedef struct node {
  Type   thetype;
  long    data;
  void   *opaque;
  struct node *ptr1, *ptr2;
} Node;


int ptrif(Node *left, Node *right);

int whilecode(Node *somenode, int data);

int switchcode(Node *somenode, Node *someothernode);

int simplerecursive(Node *somenode, int val);

int complexrecursive(Node *somenode);

#endif
