/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

int test_tmin(void) {
  return 0x80000000;
}
int test_isTmax(int x) {
    return x == 0x7FFFFFFF;
}
int test_negate(int x) {
  return -x;
}
int test_isLessOrEqual(int x, int y)
{
  return x <= y;
}
int test_bitAnd(int x, int y)
{
  return x&y;
}
int test_oddBits(void) {
  int result = 0;
  int i;
  for (i = 1; i < 32; i+=2)
    result |= 1<<i;
  return result;
}







int test_allOddBits(int x) {
  int i;
  for (i = 1; i < 32; i+=2)
      if ((x & (1<<i)) == 0)
   return 0;
  return 1;
}

int test_byteSwap(int x, int n, int m)
{
    /* little endiamachine */
    /* least significant byte stored first */

    unsigned int nmask, mmask;

    switch(n) {
    case 0:
      nmask = x & 0xFF;
      x &= 0xFFFFFF00;
      break;
    case 1:
      nmask = (x & 0xFF00) >> 8;
      x &= 0xFFFF00FF;
      break;
    case 2:
      nmask = (x & 0xFF0000) >> 16;
      x &= 0xFF00FFFF;
      break;
    default:
      nmask = ((unsigned int)(x & 0xFF000000)) >> 24;
      x &= 0x00FFFFFF;
      break;
    }

    switch(m) {
    case 0:
      mmask = x & 0xFF;
      x &= 0xFFFFFF00;
      break;
    case 1:
      mmask = (x & 0xFF00) >> 8;
      x &= 0xFFFF00FF;
      break;
    case 2:
      mmask = (x & 0xFF0000) >> 16;
      x &= 0xFF00FFFF;
      break;
    default:
      mmask = ((unsigned int)(x & 0xFF000000)) >> 24;
      x &= 0x00FFFFFF;
      break;
    }

    nmask <<= 8*m;
    mmask <<= 8*n;

    return x | nmask | mmask;
}
int test_rotateRight(int x, int n) {
  unsigned u = (unsigned) x;
  int i;
  for (i = 0; i < n; i++) {
      unsigned lsb = (u & 1) << 31;
      unsigned rest = u >> 1;
      u = lsb | rest;
  }
  return (int) u;
}
int test_bitReverse(int x) {
    int result = 0;
    int i;
    for (i = 0; i < 32; i++) {
 int bit = (x >> i) & 0x1;
 int pos = 31-i;
 result |= bit << pos;
    }
    return result;
}
unsigned test_floatAbsVal(unsigned uf) {
  float f = u2f(uf);
  unsigned unf = f2u(-f);
  if (isnan(f))
    return uf;
  /* An unfortunate hack to get around a limitation of the BDD Checker */
  if ((int) uf < 0)
      return unf;
  else
      return uf;
}
unsigned test_floatInt2Float(int x) {
  float f = (float) x;
  return f2u(f);
}
unsigned test_floatScale2(unsigned uf) {
  float f = u2f(uf);
  float tf = 2*f;
  if (isnan(f))
    return uf;
  else
    return f2u(tf);
}
