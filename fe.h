#ifndef FE_H
#define FE_H
#include "crypto_int64.h"
#include "crypto_int32.h"

#define ALIGN_BYTES 32
#ifdef __INTEL_COMPILER
#define ALIGN __declspec(align(ALIGN_BYTES))
#else
#define ALIGN __attribute__ ((aligned (ALIGN_BYTES)))
#endif

#define SIZE_FP25519 32
#define BASE0_FP25519 26
#define BASE1_FP25519 25
#define NUM_DIGITS_FP25519 10
#define NUM_DIGITS_FP25519_X64 4


typedef uint32_t  fe[10];
#define argElement_1w uint64_t *
typedef ALIGN uint64_t EltFp25519_1w_fullradix[NUM_DIGITS_FP25519_X64];
typedef ALIGN uint64_t EltFp25519_1w_fullradix_buffer[2 * NUM_DIGITS_FP25519_X64];
/*
fe means field element.
Here the field is \Z/(2^255-19).
An element t, entries t[0]...t[9], represents the integer
t[0]+2^26 t[1]+2^51 t[2]+2^77 t[3]+2^102 t[4]+...+2^230 t[9].
Bounds on each t[i] vary depending on context.
*/


extern void fe_frombytes(fe,const unsigned char *);
extern void fe_tobytes(unsigned char *s ,const fe h);
extern void fe_neg(fe h ,const fe f);
extern void fe_copy(fe h ,const fe f);
extern void fe_0(fe h);
extern void fe_1(fe h);
extern void fe_cswap(fe f,fe g ,unsigned int b) ;
extern int  fe_isnonzero(const fe f);
extern int  fe_isnegative(const fe f );
extern void fe_add(fe h ,const fe f,const fe g);
extern void fe_sub(fe h,const fe f , const fe g );
extern void fe_cmov(fe f ,const fe g ,unsigned int);
extern void fe_mul(fe,const fe,const fe);
extern void fe_sq(fe h ,const fe f);
extern void fe_sq2(fe, const fe f );
extern void fe_mul121666(fe h ,fe f );
extern void fe_invert(fe out ,const fe z);
extern void fe_pow22523(fe out ,const fe z );
extern void fe_to64bit(argElement_1w s, const fe h);
extern void fe_64tobytes(unsigned char  *s, argElement_1w a);
extern void reduce(argElement_1w c, argElement_1w a);
extern void mul(argElement_1w c, argElement_1w a, argElement_1w b);
extern void sqr(argElement_1w a);
extern void copy(argElement_1w c, argElement_1w a);
extern void inv(argElement_1w c, argElement_1w a);
//extern void fe4x_invert(fe4x,fe4x);
//extern void fe4x_neg(fe4x,fe4x);
#endif
