em/* 
 * CS:APP Data Lab 
 * 
 * NAMES: RORY NGUYEN, MELIA TOMLINSON
 * NETID: dtn7756, mlt1693
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
       int tmin = 1 << 31;
       return tmin;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* if x = Tmax, then x+1 = 0 due to overflow */
  int min = ~ (x + (!(x+1)));
  return !(min ^ (x+1)); 

}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int negate = ~x + 1;
  return negate; 
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* determines whether x is less than y based on the same or different signs */
    int ysig = (y >> 31) & 1;
    int xsig = (x >> 31) & 1;
    int diff = (!(ysig ^ xsig)) & (((x + (~y)) >> 31) & 1);
    return diff | ((!ysig) & xsig);
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* uses DeMorgan's law */
    int x1 = ~x;
    int y1 = ~y;
    return ~(x1 | y1);

}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int oddBits(void) {
  /* creates a mask of 0xAAAAAAAA by the first half then the second half */
  int m = (0xAA << 8) + 0xAA;
  m = (m << 16) + m;
  return m;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* creates a mask of oddbits and uses xor to see x and mask are equal */
  int result;
  int mask = (0xAA << 8) + 0xAA;
  mask = (mask << 16) + mask;
  result = !((x & mask) ^ mask);
  return result;

}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  /* create masks for n, m, and the bytes to keep in their original places, then or them together */
  int bitm;
  int bitn;
  int mask;
  int setn = x;
  int setm = x;
  
  int maskF = (0xFF << 8) + 0xFF;
  maskF = (maskF <<16) + maskF;

  setn = x >> (n << 3);
  setm = x >> (m << 3);
  setn = setn & 0xFF;
  setm = setm & 0xFF;

  bitm = (0xFF << (m<<3));
  bitn = (0xFF << (n<<3));
  mask = (bitm | bitn) ^ maskF;
  return (x & mask) | (setm << (n << 3)) | (setn << (m << 3));
}

/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x187654321
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  /* mask a front portion to be shifted and a back portion to be moved to the front if needed */
  int front = x >> n;
  int back;
  int mask = ~(1 << 31);
  mask = mask >> (n + (~1 + 1));

  front = front & mask;
  back = x << (32 + (~n + 1));
  return front | back;

}
/*
 * bitReverse - Reverse bits in a 32-bit word
 *   Examples: bitReverse(0x80000002) = 0x40000001
 *             bitReverse(0x89ABCDEF) = 0xF7D3D591
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int bitReverse(int x) {
  /* swap the odd and even bits, the consecutive bits, the nibbles, the bytes, and then 2 bytes */
  int oddEven = (0x55 << 8) + 0x55;
  int consec = (0x33 << 8) + 0x33;
  int nibble = (0x0F << 8) + 0x0F;
  int bytes = (0xFF << 16) + 0xFF;
  int bytes2 = (0xFF << 8) + 0xFF;

  oddEven = (oddEven << 16) + oddEven;
  consec = (consec << 16) + consec;
  nibble = (nibble << 16) + nibble;
  
  x = (( x >> 1) & oddEven) | ((x & oddEven) << 1);
  x = (( x >> 2) & consec) | ((x & consec) << 2);
  x = (( x >> 4) & nibble) | ((x & nibble) << 4);
  x = (( x >> 8) & bytes) | ((x & bytes) << 8);
  x = (( x >> 16) & bytes2) | (x << 16);
  return x;

}
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  /* first determine whether uf is NaN using a mask, if not, then return uf with a mask over exponent*/
  unsigned expMask = 0x75800000;
  unsigned frMask = 0x007FFFFF;
  if ((uf & expMask) == expMask && (uf & frMask)) {
    return uf;
  } else {
    return uf & ~(1 << 31);
  }
}
/* 
 * floatInt2Float - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatInt2Float(int x) {
  unsigned sign, unx, E, M, round, exp, f;
  unsigned leaf, half;
  int bits;

  if (x == 0) {
    return 0;
  }
  
  if (x < 0) {
    sign = 1;
    unx = -x;
  } else {
    sign = 0;
    unx = x;
  }

  E = 0; 
  M = unx;
  round = 0;

  while (unx > 1) {
    unx = unx >> 1;
    E = E + 1;
  }

  exp = E + 127;
  f = M & (( 1 << E) - 1);
  bits = E - 23;
  /* rounding if leaf greater than half, etc */
  if (bits > 0) {
    leaf = f & (( 1 << bits) - 1);
    half = 1 << (bits - 1);
    f = f >> bits;
    
    if (leaf > half || (leaf == half && f & 0x1)) {
      round = 1;
    }
  } else {
      f = f << (-bits);
  }

    return ((sign << 31) | (exp << 23) | f) + round;
  
}
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  /* same as above, but shift the exponent to the left by 1 place and account for rounding and overflow*/
  unsigned signMask = 0x80000000;
  unsigned expMask = 0x7F800000;
  unsigned fMask = 0x007FFFFF;
  unsigned posInf = 0x7F800000;
  unsigned negInf = 0XFF800000;
  unsigned sign, exp, f;
  int E;

  if ( (uf & expMask) == expMask && (uf & fMask)) {
    return uf;
  }
  if ((uf & ~(1 << 31)) == 0) {
    return uf;
  }

  sign = uf & signMask;
  exp = (uf & expMask) >> 23;
  f = uf & fMask;
  

  if (exp == 0) {
    E = -125;
    while ( (f & 0x800000) == 0 && E > -126) {
      f = f << 1;
      E = E - 1;
    }

    if (f & 0x800000) {
      f = f & 0x7FFFFF;
      exp = E + 127;
    } else {
      exp = 0;
    }
  } else {
    E = exp - 126;
    if (E >= 128) {
      if (sign) {
	return negInf;
      } else {
	return posInf;
      }
    }
      exp = E + 127;
  }  
    return sign | (exp << 23) | f;
  
}
