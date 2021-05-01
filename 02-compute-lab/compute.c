/*------------------------------------------------------------------------------
 * 4190.308 Computer Architecture                                    Spring 2020
 *
 * Compute Lab
 *
 * Handout:    April  8, 2020
 * Due:        April 20, 2020 11:00
 *
 * compute.c - implement the functions in this file. Push to your CSAP GitLab
 *             account when done. You can push as many times as you want, the
 *             last submission will be graded.
 *             The date/time of the last submission counts as the submission
 *             date.
 *
 * WARNING:    You should use only 32-bit interger operations inside the
 *             Uadd64(), Usub64(), Umul64(), and Udiv64() functions.
 */

#include <stdio.h>
#include "compute.h"


/* Uadd64() implements the addition of two 64-bit unsigned integers.
 * Assume that A and B are the 64-bit unsigned integer represented by
 * a and b, respectively. Uadd64() should return x, where x.hi and x.lo
 * contain the upper and lower 32 bits of (A + B), respectively.
 */
HL64 Uadd64 (HL64 a, HL64 b)
{
  HL64 r = {0, 0};
  r.lo=a.lo+b.lo;
  r.hi=a.hi+b.hi;
  if(r.lo<a.lo) r.hi+=1;

//just add each 32-upper, lower bit and add carry if there was an overflow in lower 32- bits


  return r;
}

/* Usub64() implements the subtraction between two 64-bit unsigned integers.
 * Assume that A and B are the 64-bit unsigned integer represented by
 * a and b, respectively. Usub64() should return x, where x.hi and x.lo
 * contain the upper and lower 32 bits of (A - B), respectively.
 */
HL64 Usub64 (HL64 a, HL64 b)
{
  HL64 r = {0, 0};
  r.hi=a.hi-b.hi;
  r.lo=a.lo-b.lo;
  if(a.lo<b.lo) r.hi-=1;

//just subtract each 32-upper, lower bit and subtract carry if there was an overflow in lower 32-bits


  return r;
}


/* Umul64() implements the multiplication of two 64-bit unsigned integers.
 * Assume that A and B are the 64-bit unsigned integer represented by
 * a and b, respectively.  Umul64() should return x, where x.hi and x.lo
 * contain the upper and lower 32 bits of (A * B), respectively.
 */
HL64 Umul64 (HL64 a, HL64 b)
{
  //upper 32-bits of Umul64 includes a.hi*b.lo and a.lo*b.hi. So first saved it in temp
  HL64 r = {0, 0};
  u32 temp = a.hi*b.lo+a.lo*b.hi;
  //now we just add a.lo*b.lo in 64-bits
  for(int i=0;i<32;i++){

    if(r.lo>=2147483648) r.hi=2*r.hi+1;
    else r.hi=2*r.hi;
    r.lo=2*r.lo;// these three lines means r=r*2

    if(b.lo>=2147483648){//if b.lo.msb = 1
     r.lo+=a.lo;
     if(r.lo<a.lo) r.hi+=1;//r=r+a.lo
    }
    b.lo=b.lo*2;
  }
  
  r.hi+=temp;//now add temp in 32-upper bits
  



  return r;
}


/* Udiv64() implements the division of two 64-bit unsigned integers.
 * Assume that A and B are the 64-bit unsigned integer represented by
 * a and b, respectively.  Udiv64() should return x, where x.hi and x.lo
 * contain the upper and lower 32 bits of the quotient of (A / B),
 * respectively.
 */
HL64 Udiv64 (HL64 a, HL64 b)
{
  HL64 r = {0, 0};
  int i=0;
  if(b.hi==0 && b.lo==0) return r;//return 0 if b=0
  while(b.hi<2147483648){//shift left b until b.msb=1 (make b largest from in 64 bit)
    b.hi=b.hi*2;
    if(b.lo>=2147483648) b.hi++;
    b.lo=b.lo*2;
    i++;//save the number of shifting b
  }
  while(i>=0){
    if(a.hi<b.hi || (a.hi==b.hi && a.lo<b.lo)){//if a<b

      b.lo=b.lo/2;
      if(b.hi%2) b.lo+=2147483648;
      b.hi=b.hi/2;//shift right b

      if(i>0){
       r.hi=r.hi*2;
       if(r.lo>=2147483648) r.hi++;
       r.lo=r.lo*2;//shift left r if not the end of the loop
      }
      i--;

    }
    else {//can subtract b from a
      r.lo+=1;
      if(a.lo<b.lo) a.hi--;
      a.lo=a.lo-b.lo;
      a.hi=a.hi-b.hi;
    }
  }//just like hand-writing method



  return r;
}
