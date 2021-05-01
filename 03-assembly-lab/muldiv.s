/*------------------------------------------------------------------------------
 * 4190.308 Computer Architecture                                    Spring 2020
 *
 * Assembly Lab
 *
 * Handout:    April 22, 2020
 * Due:        May    4, 2020 11:00
 *
 * multdiv.s - implement the functions in this file. Push to your CSAP GitLab
 *             account when done. You can push as many times as you want, the
 *             last submission will be graded.
 *             The date/time of the last submission counts as the submission
 *             date.
 */

    .text
    .align  2

#----------------------------------------------------------------
#   int mul(int a, int b)
#----------------------------------------------------------------
    .globl  mul
mul:
    addi  a2, zero, 0   # a2 : result of multiplication lower 32 bits (don't care carry)
    addi  a3, zero, 0
    addi  a4, zero, 32
mulLoop:
    beq   a3, a4, mulExit   # 32 loop -> out
    slli  a2, a2, 1
    bge   a1, zero, mulSkipAdd
    add   a2, a2, a0    # add a0 if a1's msb is 1(like hand-writing method)
mulSkipAdd:
    slli  a1, a1, 1
    addi  a3, a3, 1
    beq   zero, zero, mulLoop
mulExit:
    addi  a0, a2, 0   #return a2
    ret

#----------------------------------------------------------------
#   int mulh(int a, int b)
#----------------------------------------------------------------
    .globl  mulh
mulh:
    addi  a5, a1, 0     # store b
    addi  a2, zero, 0   # upper 32bit of multiplication
    addi  a3, zero, 0   # lower 32bit of multiplication
    addi  a4, zero, 32   # how many times looped
mulhLoop:
    beq   a4, zero, mulhExit  # 32 loops -> out
    slli  a2, a2, 1   # shift left a2 and a3(like one 64 bits)
    bge   a3, zero, mulhSkipCarry
    addi  a2, a2, 1
mulhSkipCarry:
    slli  a3, a3, 1
    bge   a1, zero, mulhSkipAdd   # like mul, if a1's msb is 1, add a0 t0 a3 and check overflow to a2
    addi  a6, a3, 0
    add   a3, a3, a0
    bgeu   a3, a6, mulhSkipAddCarry
    addi  a2, a2, 1
mulhSkipAddCarry:

mulhSkipAdd:
    slli  a1, a1, 1
    addi  a4, a4, -1
    beq   zero, zero, mulhLoop

mulhExit:
    bge   a0, zero, skipExtension1    # a's signExtensioned hi 32 bit * b's lo 32 bit
    sub   a2, a2, a5
skipExtension1:
    bge   a5, zero, skipExtension2    # b's signExtensioned hi 32 bit * a's lo 32 bit, these two contributes to mulh
    sub   a2, a2, a0
skipExtension2:
    
    addi  a0, a2, 0
    ret

#----------------------------------------------------------------
#   int div(int a, int b)
#----------------------------------------------------------------
    .globl  div
div:
    beq   a1, zero, zeroReturnDiv   # zero divisor exception
    addi  a2, a0, 0
    addi  a3, a1, 0
    bge   a2, zero, posDividend1
    sub   a2, zero, a2    # a2=|a|
posDividend1:
    bge   a3, zero, posDivisor1
    sub   a3, zero, a3    # a3=|b|
posDivisor1:
    addi  a4, zero, 0   # a4 : remainder bits
    addi  a5, zero, 32
divLoop:
    bltu  a4, a3, skipMinusQuotient
    sub   a4, a4, a3
    addi  a2, a2, 1   # if remainder > divisor -> we can divide once (like hand-writing method)
skipMinusQuotient:
    beq   a5, zero, divOut    # 32 loops -> out
    slli  a4, a4, 1
    bge   a2, zero, divSkipCarry
    addi  a4, a4, 1
divSkipCarry:
    slli  a2, a2, 1
    addi  a5, a5, -1
    beq   zero, zero, divLoop
divOut:
    bge   a0, zero, posDividend2
    sub   a2, zero, a2
posDividend2:
    bge   a1, zero, posDivisor2   # sign of quotient depends on sign of a*b
    sub   a2, zero, a2
posDivisor2:
    addi  a0, a2, 0
    ret
zeroReturnDiv:
    addi  a0, zero, -1
    ret

#----------------------------------------------------------------
#   int rem(int a, int b)
#----------------------------------------------------------------
    .globl  rem
rem:
    beq   a1, zero, zeroReturnRem
    addi  a2, a0, 0
    addi  a3, a1, 0
    bge   a2, zero, posRDividend1
    sub   a2, zero, a2    # a2=|a|
posRDividend1:
    bge   a3, zero, posRDivisor1
    sub   a3, zero, a3    # a3=|b|
posRDivisor1:
    addi  a4, zero, 0
    addi  a5, zero, 32
remLoop:
    bltu  a4, a3, skipMinusQuotientR
    sub   a4, a4, a3
    addi  a2, a2, 1
skipMinusQuotientR:
    beq   a5, zero, remOut
    slli  a4, a4, 1
    bge   a2, zero, remSkipCarry
    addi  a4, a4, 1
remSkipCarry:
    slli  a2, a2, 1
    addi  a5, a5, -1
    beq   zero, zero, remLoop
remOut:
    bge   a0, zero, posRDividend2   #same as function div, but we should return remainder
    sub   a4, zero, a4
posRDividend2:    # remainder's sign depends on dividend's sign
    addi  a0, a4, 0
    ret
zeroReturnRem:
    ret


