/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*For Single Bit*/
#define PUTBIT(basis, pos, val)         ((val)? SETBIT(basis,pos) : CLRBIT(basis, pos))
#define SETBIT(basis, pos)              (basis | (1U << pos))
#define CLRBIT(basis, pos)              (basis & ~(U << pos))
#define TOGGLEBIT(basis, pos)           (basis ^ (1U << pos))
#define CHECKBIT(basis, pos)            (basis & (1U << pos))

/*For multiple continuous bits */
#define PUTBITS(basis, start,end, val)  ((val) ? SETBITS(basis, start, end) : CLRBITS(basis, start,end))
#define SETBITS(basis, start, end)      (basis | ((CREATEMASK(start,end) << start)))       
#define CLRBITS(basis, start, end)      (basis & ~((CREATEMASK(start,end) << start)))       
#define TOGGLEBITS(basis , start, end)  (basis ^ ((CREATEMASK(start,end) << start)))       
#define CREATEMASK(start, end) 			((1U << (end-start+1U)) -1U)

/*Bit swapping operations */
#define SWAP32(val)  (((val) >> 16U) | ((val) & 0xFFFFU) << 16U)
#define SWAP16(val)  (((val) >> 8U)  | ((val) & 0xFF) << 8U)
#define SWAP8(val)   (((val & 0x0FU) << 4U)  | ((val) & 0xF0U) >> 4U)
#define SWAPBYTES32  (((val & 0xFFU) << 24U) | ((val & 0xFF00) << 8U) | ((val & 0xFF0000) >> 8U) | ((val & 0xFF000000) >>24U))

/*swap 2 numbers */
#define SWAP(x, y) (x ^= y ^= x ^= y)

int main()
{
   volatile unsigned int x  = 0x45E;
  x = SETBITS(x, 0,5);
  printf("x:%x\n", x);
  x = CLRBITS(x, 0,5);
  printf("x:%x\n", x);
  x = TOGGLEBITS(x, 0,5);
  printf("x:%x\n", x);
   x = TOGGLEBITS(x, 0,5);
  printf("x:%x\n", x);
  x = PUTBITS(x, 0,7,0);
   printf("x:%x\n", x);
   x = PUTBITS(x, 0,7,1);
   printf("x:%x\n", x);
   
}
/*print the value in binary format */
void print_binary(unsigned int x)
{
  while(x)
  {
      (x & 1)? printf("1") : printf("0");
      x>>=1;
  }
}