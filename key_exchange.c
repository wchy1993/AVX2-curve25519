#include "ed25519.h"
#include "fe.h"
#include "ge.h"
#include "fe4x.h"
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <assert.h>

#ifdef __i386
__inline__ uint64_t rdtsc() {
    uint64_t x;
    __asm__ volatile ("rdtsc" : "=A" (x));
    return x;
}
#elif __amd64
__inline__ uint64_t rdtsc() {
    uint64_t a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (d<<32) | a;
}
#endif
void ed25519_key_exchange(unsigned char *shared_secret, const unsigned char *public_key, const unsigned char *private_key) 
{
    unsigned char e[32];
    unsigned int i;
    
    fe x1;
    fe x2;
    fe z2;
    fe x3;
    fe z3;
    fe tmp0;
    fe tmp1;
    fe x0;
    fe z0;
    fe set1;
    int j;
    clock_t start;
    clock_t end;
    int pos;
    unsigned int swap;
    unsigned int b;
    uint64_t t;

    /* copy the private key and make sure it's valid */
    for (i = 0; i < 32; ++i) 
{
        e[i] = private_key[i];
       
    }

    e[0] &= 248;
    e[31] &= 63;
    e[31] |= 64;

    /* unpack the public key and convert edwards to montgomery */
    /* due to CodesInChaos: montgomeryX = (edwardsY + 1)*inverse(1 - edwardsY) mod p */
    fe_frombytes(x1, public_key);
    fe_copy(x3, x1);
    fe4x x2z2x3z3;
    fe4x x3z3x2z2;
    fe4x z2x2z3x3;
    fe4x negz2x2z3x3;
    fe4x mul4xmonmid;
    fe4x mul2sq2;
    fe tmp[4];
    fe tmp3;
    fe4x mul4121666;
    fe4x mul42121666;
    fe4x mula;
    fe4x mulb;

    fe_1(x2);
    fe_0(z2);
    fe_1(z3);
    for(i = 0;i<10;i++)
{
    x2z2x3z3[i] =_mm256_set_epi64x(x2[i],z2[i],x3[i],z3[i]);

}


    static fe f121666={121666,121666,121666,121666,121666,121666,121666,121666,121666,121666};

    swap = 0;
    for (pos = 254; pos >= 0; --pos) {
        b = e[pos / 8] >> (pos & 7);
        b &= 1;
        swap ^= b;
        for(i=0;i<10;i++)
	{
           x3z3x2z2[i] =  _mm256_permute4x64_epi64(x2z2x3z3[i],0x4e);
        }
        fe4x_cswap(x2z2x3z3, x3z3x2z2, swap);
        
        swap = b;
           for(i = 0;i<10;i++)
{        
        z2x2z3x3[i] =_mm256_permute4x64_epi64(x2z2x3z3[i],0xB1);
}
        fe4x_negmon(negz2x2z3x3,z2x2z3x3);
        fe4x_add(x2z2x3z3,x2z2x3z3,negz2x2z3x3);

        //fe_sub(tmp0, x3, z3);
        //fe_sub(tmp1, x2, z2);
        //fe_add(x2, x2, z2);
        //fe_add(z2, x3, z3);
        for(i = 0;i<10;i++)
{        
        mul4xmonmid[i] = _mm256_permute4x64_epi64(x2z2x3z3[i],0xA5);
}
	fe4x_mul(mul2sq2,mul4xmonmid,x2z2x3z3);
        for (i = 0; i < 10; i++)
	for (j = 0; j < 4; j++)
{
		tmp[j][i] = _mm256_extract_epi64 (mul2sq2[i], j);
                z3[i]=tmp[3][i];
                tmp1[i]=tmp[2][i];
                tmp0[i]=tmp[1][i];
                z2[i] = tmp[0][i];
}

        fe_add(x3, z3, z2);
        fe_sub(z2, z3, z2);
        fe_sub(tmp3, tmp1, tmp0);
       for(i=0;i<10;i++)
{
	
       mul4121666[i] = _mm256_set_epi64x(tmp3[i],tmp1[i],z2[i],x3[i]);
       mul42121666[i] = _mm256_set_epi64x(f121666[i],tmp0[i],z2[i],x3[i]);
} 
       fe4x_mul(mula,mul4121666,mul42121666);
       for (i = 0; i < 10; i++)
	for (j = 0; j < 4; j++)

{
              tmp[j][i] = _mm256_extract_epi64 (mula[i], j);
              z3[i] = tmp[3][i];
              x2[i] = tmp[2][i];
              z2[i] = tmp[1][i];
              x3[i] = tmp[0][i];
}
         fe_add(tmp0, tmp0, z3);
           for(i=0;i<10;i++)
{          
            mula[i] = _mm256_set_epi64x(x2[i],tmp3[i],x3[i],x1[i]);
            mulb[i] = _mm256_set_epi64x(set1[i],tmp0[i],set1[i],z2[i]);
}
            fe4x_mul(x2z2x3z3,mula,mulb);
    }

    fe4x_cswap(x2z2x3z3, x3z3x2z2, swap);
    for (i = 0; i < 10; i++)
	for (j = 0; j < 4; j++)

{
           tmp[j][i] = _mm256_extract_epi64 (x2z2x3z3[i], j);
           x2[i] = tmp[3][i];
           z2[i] = tmp[2][i];   
}
    argElement_1w m;
    argElement_1w q;
    argElement_1w n;
    argElement_1w p;
    fe_to64bit(m,z2);
    fe_to64bit(n,x2);
    inv(q, m);
    mul(p, q, n);
    fe_64tobytes(shared_secret, p);
}
