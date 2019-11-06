#ifndef FE4X_H
#define FE4X_H

#include <immintrin.h>

typedef __m256i fe4x[10];
typedef __m256i fe4;

typedef __m256d fe4xd[10];
typedef __m256d fe4d;


extern void fe4x_add(fe4x,const fe4x,const fe4x);
extern void fe4x_sub(fe4x,const fe4x,const fe4x);
extern void fe4x_mul(fe4x,const fe4x,const fe4x);
extern void fe4x_sq(fe4x,const fe4x);
extern void fe4x_cmov(fe4x,const fe4x,fe4 );

extern void fe4x_neg(fe4x,const fe4x);

extern void fe4x_copy(fe4x,const fe4x);
extern void fe4x_1(fe4x);
extern void fe4x_0(fe4x);
#endif

