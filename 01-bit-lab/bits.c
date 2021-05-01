/*------------------------------------------------------------------------------
 * 4190.308 Computer Architecture                                    Spring 2020
 *
 * Bit Lab
 *
 * Handout: March 30, 2020
 * Due:     April  8, 2020 11:00
 *
 * bits.c - solve the puzzles  by modifying this file.  Push to your CSAP GitLab
 *          account when done.  You can push as many times as you want, the last
 *          submission will be graded.
 *          The date/time of the  last submission counts as the submission date.
 *
 * WARNING: Do not include the  <stdio.h> header;  it confuses the dlc compiler.
 *          You can still use printf for debugging  without including <stdio.h>,
 *          although you might get a compiler warning. In general, it's not good
 *          practice to ignore compiler warnings, but in this case it's OK.
 */

#if 0

/*******************************************************************************
 *                  STEP 1: Read the following instructions carefully.         *
 ******************************************************************************/

CODING RULES:

  Replace the "return" statement in each function with one or more lines of C 
  code that implements the function. Your code must conform to the following 
  style:

  int Funct(arg1, arg2, ...) {
      /*
       * brief description of how your implementation works
       * >>> IMPORTANT: do not leave the description out! <<<
       */

      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;

      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are not allowed to
     use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further. Each
  "Expr" may consist of multiple operators. You are not restricted to one 
  operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int. This implies that you cannot use arrays,
     structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more than the 
     word size.

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

#endif

/*******************************************************************************
 *     STEP 2: Solve the following puzzles according to the coding rules.      *
 ******************************************************************************/

/*
 * isZero - returns 1 if x == 0, 0 otherwise
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  return !x;
}
//
//
/*
 * minusOne - return minus one (-1)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return ~0;
}
//
//
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(8, 5) = 13
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~(~x&~y);
}
//
//
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 3) = 2
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x|~y);
}
//
//
/* 
 * fitsShort - return 1 if x can be represented as a
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33003) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  int y=x>>15;
  int z=y>>1;

  return !(y^z);
}
//
//
/* 
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(4,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int m=n+~0;
  int y=x>>m;
  int z=y>>1;

  return !(y^z);
}
//
//
/*
 * isNegative - return 1 if x < 0, return 0 otherwise
 *   Example: isNegative(-3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return !!(x>>31);
}
//
//
/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(5,4) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x+~y+1);
}
//
//
/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x4) = 0, anyOddBit(0x6) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int y=(170<<24)+(170<<16)+(170<<8)+170;
  int z=x&y;
  return !!z;
}
//
//
/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFB) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int y=(170<<24)+(170<<16)+(170<<8)+170;
  int z=x|y;
  return !(z+1);
}
//
//
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(80) = 0x10
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {

  return x&(~x+1);
}
//
//
/*
 * addOK - Determine if x+y can be computed without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int a=x>>31;
  int b=y>>31;
  int c=(x+y)>>31;

  return !(~(a^b)&(a^c));
}
//
//
/* 
 * subOK - Determine if x-y can be computed without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int a=x>>31;
  int b=y>>31;
  int c=(x+~y+1)>>31;

  return !((a^b)&(a^c));
}
//
//
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,5,4) = 5
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  return ((~(!x)+1)&z)+((~(!!x)+1)&y);
}
//
//
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(1) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int y=~x+1;
  int z=x|y;
  return (z>>31)+1;
//
//
}
