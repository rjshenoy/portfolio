/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  
         
    // opposite of & is |, opposite of ~x is x
    return ~(~x & ~y);
    /*
        
        example
        
        6 in binary = 0110
        5 in binary = 0101
        answer-       0111 = 7
    
    */
}
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
    
    int word = 0x55; // 01010101, an even-numbered bits number
    word = word | (word << 8);
    
    /*
    
        example
                        
                        0000000001010101
                      |
        01010101 << 8 = 0101010100000000 
                        0101010101010101 16-bits even number
                           
    */
    
    word = word | (word << 16);
    
    /*
    
        example
                                00000000000000000101010101010101
                                
                              |
        101010101010101 << 16 = 01010101010101010000000000000000
        
                                01010101010101010101010101010101 32 bits 
        
    
    
    */
    
    
    
    // word is now 1010101010101010000000000000000
    
    return word;
    
}
/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {

    // reverses all 0s to all 1s, signed left most bit = 1, equals -1
    return ~0;
}
/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  
    int totalBits;
    int oddBits = 0xAA | (0xAA << 8); // we use 0xAA because it is has odd-numbered bits, shift of 8 to get 16 bit odd-numbered
    
    /*
    
        example
        
                    0000000010101010
                   |
        0xAA << 8 = 1010101000000000 
                    1010101010101010
        
        
    
    
    
    */
    
    oddBits = oddBits | oddBits << 16;
    
    /*
    
        
        00000000000000001010101010101010
       |
        10101010101010100000000000000000
        
        10101010101010101010101010101010
    
    */
    
    
    totalBits = oddBits | x;
    
    /*
    
        10101010101010101010101010101010
       |
        01010101010101010101010101010101 // in case of even bit-number
        
        11111111111111111111111111111111
        
        10101010101010101010101010101010
       |
        10101010101010101010101010101010
        
        10101010101010101010101010101010 // in case of odd bit-number
        
    
    
    
    */
    
    
    
    totalBits = ~totalBits; 
    
    /*
    
    11111111111111111111111111111111 becomes all 0s when even bits is "true"
    10101010101010101010101010101010 becomes 0101... when even bits is "false"
    
    
    
    */
    
    
    return !(totalBits); // !0 = 1, else 0
    
    
    
    
    
}
/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) { // GO OVER
    
    
    int totalBits;
    
    int oddBits = 0xAA | (0xAA << 8); // same thing as above, now a 16 odd-bit number
    oddBits = oddBits | (oddBits << 16); // same thing as above, now a 32 odd-bit number
    
    totalBits = x & oddBits; 
    
    /*
    
    ex 1
    
    10101010101010101010101010101010
  & 00000000000000000000000000000101
    00000000000000000000000000000000 // false
    
    10101010101010101010101010101010
  & 00000000000000000000000000000111
    00000000000000000000000000000010 // true


    */

    totalBits = !(!totalBits);
    
    /*
    
    
    !(!totalBits) makes any non-0 value to true, otherwise false
    
    */
    
    
    return totalBits;
    
    
    
    
    
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
int byteSwap(int x, int n, int m) { // come back to **
    
    
    int switch1, byte1, byte2;
    n = n << 3; // shift to get entire byte
    m  = m << 3;
    
    switch1 = ((0xFF << n) | (0xFF << m)); 
    switch1 = ~switch1;
    
    /*
    
        example
        
        0xFF << 3 = 00000011111111000
        0xFF << 9 = 11111111000000000
                    ~11111111111111000
                     00000000000000111
                    
        
    
    
    */
    
    
    
    byte1 = 0xFF & (x >> n); // store byte(s) to be swapped
    byte2 = 0xFF & (x >> m);
    
    return (x & switch1) | ((byte1 << m) | (byte2 << n)); 
    
    /*
        x & switch1 keeps the bits that match with both bytes
        the 1st | statement keeps bits from the & statement
        the 2nd | statement decides whether to swap with byte1 or byte2
        
        
    
    
    */
       
    
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) { 
  
    int sum = x + y;
    
    
    // using XOR to determine whether either x or the sum has an overflow, value will be 0 if overflow occurs
    int checkX = x ^ sum;
    int checkY = y ^ sum;
    
    
    // negative number in leftmost bit, shift 31 to show it
    return !((checkX & checkY) >> 31);
    
    // ! allows for a simple 0/1 answer, and if the & statement returns true, overflow has occured, making the overall function return false 
    
    
    
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    
    
    int condition = (!x + ~0);
    
    /*
    
     (!2) 0 + 1111 = 1111 
    
    */
    
    // if x was 0, giving making conditional 1 (true), return y, else return z
    return ((~condition) & z) | ((condition) & y);
    
    /*
    
        ~condition = 0000
                   & 0101
                     0000
         condition = 1111
                   & 0100
                     0100
                     
                     0000
                   | 0100
                     0100
    
    */
    
}
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) { 
  
    int high = 0x3a + ~x; // 58 because max ASCII number for digits    
    int low = ~0x2f + x; // 48 because min ASCII number for digits
    /*
        
        example
        
        58 - 54 = 4, 0100 
        -48 + 53 = 5, 0101
        
    
    
    */
    
    
    int highLeft = 0x01 & (high >> 31); // shifting, then masking to isolate the LSB
    int lowLeft = 0x01 & (low >> 31);
    
    /*
    
       highLeft = 0
       lowLeft = 0    
    
    */
    
    
    int result = (highLeft | lowLeft); // 0 for either shows it falls within the range 
    
    return !result; // 0 is 1 and 1 is 0, so we use ! to flip it so 1 is 1 and 0 is 0
    
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  
    int z = 0xFF; // z functions as a mask
    n = n << 3; // shifting 1 byte
    z = ~(z << n); // we need all 0s so x stays the same, later when we do the and statement    
    c = c << n; // we shift c the same amount of times as z to "line it up" for the replace
    
    return (x & z) | c;
    // the and statement "zeros" out the part that needs to be replaced  
    // then part gets replaced with the or statement
    
    
}
/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n) { // not finished
  
    int rotater = x << (32 + (~n + 1)); // we need to shift by 32-n to get n bits in the front 
    int tmax = ~(1 << 31); // make T_MAX ourselves
    tmax = tmax >> (n + ((~1) + 1)); // shifting tmax right by n-1 as to not lose bits
    x = x >> n; // shift the number by n to "line it up"
    x = x & tmax; // use and remove arithmetic shift

    /* 
    
    1000 0111 0110 0011 0010 0011 0010 0001 -> 0001 0000 0000 0000 0000 0000 0000 0000
    0111 1111 1111 1111 1111 1111 1111 1111 = T_MAX -> 0000 1111 1111 1111 1111 1111 1111 1111
    1111 1000 0111 0110 0011 0010 0011 0010
  & 0000 1111 1111 1111 1111 1111 1111 1111
    0000 1000 0111 0110 0011 0010 0011 0010
  | 0001 0000 0000 0000 0000 0000 0000 0000
    0001 1000 0111 0110 0011 0010 0011 0010
    
    
    
    */
    
        
    return x | rotater; // use or to merge the bit with the remaining number

    
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value (Tmax), and when negative overflow occurs,
 *          it returns minimum negative value (Tmin)
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) { // GO OVER
  
    int sum = x+y;
    
    int ovfl = (x ^ sum) & (y ^ sum); // checks for overflow, if ovfl = 1, there is are the same sign and an overflow has occured
    ovfl = ovfl >> 31; // we shift right by 31 to prepare the sum to be shifted
    
    return (sum >> ovfl) ^ (ovfl << 31); 
    // shift the sum to the right for negative overflow and ovfl to left for positive ovfl, it is impossible for both to occur
}
/*
 * Extra credit
 */
/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {

    
    return 2;
}
/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  
    return 0;
}
/*
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  return 2;
}
