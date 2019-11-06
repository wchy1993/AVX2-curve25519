#include "ge.h"
#include "out.h"
#include <stdio.h>

/*
r = p + q
*/


void pt()
{
	printf("print ");
}


void fe_dump(fe a)
{
	int i;

	printf("(");
	printf("(%d * 2^%d)", a[0], 0);
	printf("+ (%d * 2^%d)", a[1], 26);

	for (i = 2; i < 10; i += 2)
	{
		printf("+ (%u * 2^%d)", a[i+0], (i/2)*51);
		printf("+ (%u * 2^%d)", a[i+1], (i/2)*51 + 26);
	}

	printf(")");
}
void nl()
{
	printf("\n");
}


void ge_add(ge_p1p1 *r, const ge_p3 *p, const ge_cached *q) {
    fe t0;
    fe_add(r->X, p->Y, p->X);
    fe_sub(r->Y, p->Y, p->X);
    fe_mul(r->Z, r->X, q->YplusX);
    fe_mul(r->Y, r->Y, q->YminusX);
    fe_mul(r->T, q->T2d, p->T);
    fe_mul(r->X, p->Z, q->Z);
    fe_add(t0, r->X, r->X);
    fe_sub(r->X, r->Z, r->Y);
    fe_add(r->Y, r->Z, r->Y);
    fe_add(r->Z, t0, r->T);
    fe_sub(r->T, t0, r->T);
}


static void slide(signed char *r, const unsigned char *a) {
    int i;
    int b;
    int k;

    for (i = 0; i < 256; ++i) {
        r[i] = 1 & (a[i >> 3] >> (i & 7));
    }

    for (i = 0; i < 256; ++i)
        if (r[i]) {
            for (b = 1; b <= 6 && i + b < 256; ++b) {
                if (r[i + b]) {
                    if (r[i] + (r[i + b] << b) <= 15) {
                        r[i] += r[i + b] << b;
                        r[i + b] = 0;
                    } else if (r[i] - (r[i + b] << b) >= -15) {
                        r[i] -= r[i + b] << b;

                        for (k = i + b; k < 256; ++k) {
                            if (!r[k]) {
                                r[k] = 1;
                                break;
                            }

                            r[k] = 0;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
}

/*
r = a * A + b * B
where a = a[0]+256*a[1]+...+256^31 a[31].
and b = b[0]+256*b[1]+...+256^31 b[31].
B is the Ed25519 base point (x,4/5) with x positive.
*/

void ge_double_scalarmult_vartime(ge_p2 *r, const unsigned char *a, const ge_p3 *A, const unsigned char *b) {
    signed char aslide[256];
    signed char bslide[256];
    ge_cached Ai[8]; /* A,3A,5A,7A,9A,11A,13A,15A */
    ge_p1p1 t;
    ge_p3 u;
    ge_p3 A2;
    int i;
    slide(aslide, a);
    slide(bslide, b);
    ge_p3_to_cached(&Ai[0], A);
    ge_p3_dbl(&t, A);
    ge_p1p1_to_p3(&A2, &t);
    ge_add(&t, &A2, &Ai[0]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[1], &u);
    ge_add(&t, &A2, &Ai[1]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[2], &u);
    ge_add(&t, &A2, &Ai[2]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[3], &u);
    ge_add(&t, &A2, &Ai[3]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[4], &u);
    ge_add(&t, &A2, &Ai[4]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[5], &u);
    ge_add(&t, &A2, &Ai[5]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[6], &u);
    ge_add(&t, &A2, &Ai[6]);
    ge_p1p1_to_p3(&u, &t);
    ge_p3_to_cached(&Ai[7], &u);
    ge_p2_0(r);

    for (i = 255; i >= 0; --i) {
        if (aslide[i] || bslide[i]) {
            break;
        }
    }

    for (; i >= 0; --i) {
        ge_p2_dbl(&t, r);

        if (aslide[i] > 0) {
            ge_p1p1_to_p3(&u, &t);
            ge_add(&t, &u, &Ai[aslide[i] / 2]);
        } else if (aslide[i] < 0) {
            ge_p1p1_to_p3(&u, &t);
            ge_sub(&t, &u, &Ai[(-aslide[i]) / 2]);
        }

        if (bslide[i] > 0) {
            ge_p1p1_to_p3(&u, &t);
            ge_madd(&t, &u, &Bi[bslide[i] / 2]);
        } else if (bslide[i] < 0) {
            ge_p1p1_to_p3(&u, &t);
            ge_msub(&t, &u, &Bi[(-bslide[i]) / 2]);
        }

        ge_p1p1_to_p2(r, &t);
    }
}



static  fe d = {
    56195235, 13857412, 51736253, 6949390, 114729, 24766616, 60832955, 30306712, 48412415, 21499315
};

static  fe sqrtm1 = {
    34513072,25610706,9377949,3500415,12389472,33281959,41962654,31548777,326685,11406482
};


int ge_frombytes_negate_vartime(ge_p3 *h, const unsigned char *s) {
    fe u;
    fe v;
    fe v3;
    fe vxx;
    fe check;
    fe_frombytes(h->Y, s);
    fe_1(h->Z);
    fe_sq(u, h->Y);
    fe_mul(v, u, d);
    fe_sub(u, u, h->Z);     /* u = y^2-1 */
    fe_add(v, v, h->Z);     /* v = dy^2+1 */
    fe_sq(v3, v);
    fe_mul(v3, v3, v);      /* v3 = v^3 */
    fe_sq(h->X, v3);
    fe_mul(h->X, h->X, v);
    fe_mul(h->X, h->X, u);  /* x = uv^7 */
    fe_pow22523(h->X, h->X); /* x = (uv^7)^((q-5)/8) */
    fe_mul(h->X, h->X, v3);
    fe_mul(h->X, h->X, u);  /* x = uv^3(uv^7)^((q-5)/8) */
    fe_sq(vxx, h->X);
    fe_mul(vxx, vxx, v);
    fe_sub(check, vxx, u);  /* vx^2-u */

    if (fe_isnonzero(check)) {
        fe_add(check, vxx, u); /* vx^2+u */

        if (fe_isnonzero(check)) {
            return -1;
        }

        fe_mul(h->X, h->X, sqrtm1);
    }

    if (fe_isnegative(h->X) == (s[31] >> 7)) {
        fe_neg(h->X, h->X);
    }

    fe_mul(h->T, h->X, h->Y);
    return 0;
}



/*
r = p + q
*/

void ge_madd(ge_p1p1 *r, const ge_p3 *p, const ge_precomp *q) {
    fe t0;
    fe_add(r->X, p->Y, p->X);	
    fe_sub(r->Y, p->Y, p->X);
    fe_mul(r->Z, r->X, q->yplusx);
    fe_mul(r->Y, r->Y, q->yminusx);
    fe_mul(r->T, q->xy2d, p->T);
    fe_add(t0, p->Z, p->Z);
    fe_sub(r->X, r->Z, r->Y);
    fe_add(r->Y, r->Z, r->Y);
    fe_add(r->Z, t0, r->T);
    fe_sub(r->T, t0, r->T);
}
void ge_madd4x(ge_p1p14x *r , const ge_p34x *p ,const  ge_precomp4x *q)
{  
     fe4x t0;
     fe4x tmp;
     fe4x_add(r->X4x, p->Y4x, p->X4x);

     fe4x_sub(r->Y4x, p->Y4x, p->X4x);

     fe4x_mul(r->Z4x, r->X4x, q->yplusx4x);

     fe4x_mul(tmp, r->Y4x, q->yminusx4x);

     fe4x_mul(r->T4x, q->xy2d4x, p->T4x);

     fe4x_add(t0, p->Z4x, p->Z4x);
     fe4x_sub(r->X4x, r->Z4x, tmp);
     fe4x_add(r->Y4x, r->Z4x, tmp);
     fe4x_add(r->Z4x, t0, r->T4x);
     fe4x_sub(r->T4x, t0, r->T4x);
}
void ge_p1p14x_to_p24x(ge_p24x *r, const  ge_p1p14x *p) 
{
    fe4x_mul(r->X4x, p->X4x, p->T4x);
    fe4x_mul(r->Y4x, p->Y4x, p->Z4x);
    fe4x_mul(r->Z4x, p->Z4x, p->T4x);
}

void ge_p1p14x_to_p34x(ge_p34x *r, const ge_p1p14x *p) 
{
    fe4x_mul(r->X4x, p->X4x, p->T4x);
    fe4x_mul(r->Y4x, p->Y4x, p->Z4x);
    fe4x_mul(r->Z4x, p->Z4x, p->T4x);
    fe4x_mul(r->T4x, p->X4x, p->Y4x);
}


void ge_p2_04x(ge_p24x *h) 
{
      fe a0[4];
      fe a1[4];
 
      
      int i;
      for(i=0;i<4;i++)
{
      fe_1(a1[i]);
      fe_0(a0[i]);
      
}
      for(i=0;i<10;i++)
{
      h->X4x[i]=_mm256_set_epi64x(a0[3][i],a0[2][i],a0[1][i],a0[0][i]);
      h->Y4x[i]=_mm256_set_epi64x(a1[3][i],a1[2][i],a1[1][i],a1[0][i]);
      h->Z4x[i]=_mm256_set_epi64x(a1[3][i],a1[2][i],a1[1][i],a1[0][i]);
      
}
}

void ge_p2_dbl4x(ge_p1p14x *r, const  ge_p24x *p)
{
    fe4x t0;
    fe4x_sq(r->X4x, p->X4x);
    fe4x_sq(r->Z4x, p->Y4x);
    fe4x_sq(r->T4x, p->Z4x);
    fe4x_add(r->T4x,r->T4x,r->T4x);
    fe4x_add(r->Y4x, p->X4x, p->Y4x);
    fe4x_sq(t0, r->Y4x);
    fe4x_add(r->Y4x, r->Z4x, r->X4x);
    fe4x_sub(r->Z4x, r->Z4x, r->X4x); 
    
    fe4x_sub(r->X4x, t0, r->Y4x);
    fe4x_sub(r->T4x, r->T4x, r->Z4x);
}

void ge_p3_04x(ge_p34x *t)
{
      //fe a;
      //fe b;	
      fe a0[4];
      fe a1[4];
 
      
      int i;
for(i=0;i<4;i++)
{
      fe_1(a1[i]);
      fe_0(a0[i]);
      
}
      for(i=0;i<10;i++)
{
      t->X4x[i]=_mm256_set_epi64x(a0[3][i],a0[2][i],a0[1][i],a0[0][i]);
      t->Y4x[i]=_mm256_set_epi64x(a1[3][i],a1[2][i],a1[1][i],a1[0][i]);
      t->Z4x[i]=_mm256_set_epi64x(a1[3][i],a1[2][i],a1[1][i],a1[0][i]);
      t->T4x[i]=_mm256_set_epi64x(a0[3][i],a0[2][i],a0[1][i],a0[0][i]);
}
}

void ge_p34x_to_p24x(ge_p24x *r,  const ge_p34x *p) 
{   
    fe xp[4];
    fe yp[4];
    fe zp[4];
    int i,j;
    	for (i = 0; i < 10; i++)
{
	for (j = 0; j < 4; j++)
{
           xp[j][i] = _mm256_extract_epi64 (p->X4x[i], j);
           yp[j][i] = _mm256_extract_epi64 (p->Y4x[i], j);
           zp[j][i] = _mm256_extract_epi64 (p->Z4x[i], j);
         
}
}          
         
        for (i = 0; i < 10; i++)
	{
		r->X4x[i] = _mm256_set_epi64x(xp[3][i], xp[2][i], xp[1][i], xp[0][i]);
		r->Y4x[i] = _mm256_set_epi64x(yp[3][i], yp[2][i], yp[1][i], yp[0][i]);
                r->Z4x[i] = _mm256_set_epi64x(zp[3][i], zp[2][i], zp[1][i], zp[0][i]);
              
	}   
   
}

void ge_p3_dbl4x(ge_p1p14x *r, const  ge_p34x *p) 
{
    ge_p24x q;
    ge_p34x_to_p24x(&q, p);
    ge_p2_dbl4x(r, &q);
}

/*
r = p - q
*/

void ge_msub(ge_p1p1 *r, const ge_p3 *p, const ge_precomp *q) {
    fe t0;
    fe_add(r->X, p->Y, p->X);
    fe_sub(r->Y, p->Y, p->X);
    fe_mul(r->Z, r->X, q->yminusx);
    fe_mul(r->Y, r->Y, q->yplusx);
    fe_mul(r->T, q->xy2d, p->T);
    fe_add(t0, p->Z, p->Z);
    fe_sub(r->X, r->Z, r->Y);
    fe_add(r->Y, r->Z, r->Y);
    fe_sub(r->Z, t0, r->T);
    fe_add(r->T, t0, r->T);
}


/*
r = p
*/

void ge_p1p1_to_p2(ge_p2 *p, const ge_p1p1 *r) {
    fe_mul(p->X, r->X, r->T);
    fe_mul(p->Y, r->Y, r->Z);
    fe_mul(p->Z, r->Z, r->T);
}



/*
r = p
*/

void ge_p1p1_to_p3(ge_p3 *r, const ge_p1p1 *p) {
    fe_mul(r->X, p->X, p->T);
    fe_mul(r->Y, p->Y, p->Z);
    fe_mul(r->Z, p->Z, p->T);
    fe_mul(r->T, p->X, p->Y);
}


void ge_p2_0(ge_p2 *h) {
    fe_0(h->X);
    fe_1(h->Y);
    fe_1(h->Z);
}



/*
r = 2 * p
*/

void ge_p2_dbl(ge_p1p1 *r, const ge_p2 *p) {
    fe t0;
    fe_sq(r->X, p->X);
    fe_sq(r->Z, p->Y);
    fe_sq(r->T, p->Z);
    fe_add(r->T,r->T,r->T);
    //printf("r->T=");fe_dump(r->T);nl();
    fe_add(r->Y, p->X, p->Y);
    fe_sq(t0, r->Y);
    fe_add(r->Y, r->Z, r->X);
    fe_sub(r->Z, r->Z, r->X);
  
    //printf("r->Z=");fe_dump(r->Z);nl();
    fe_sub(r->X, t0, r->Y);
    fe_sub(r->T, r->T, r->Z);
    //printf("r->T=");fe_dump(r->T);nl();
}


void ge_p3_0(ge_p3 *h) {
    fe_0(h->X);
    fe_1(h->Y);
    fe_1(h->Z);
    fe_0(h->T);
}


/*
r = 2 * p
*/

void ge_p3_dbl(ge_p1p1 *r, const ge_p3 *p) {
    ge_p2 q;
    ge_p3_to_p2(&q, p);
    ge_p2_dbl(r, &q);
}



/*
r = p
*/

static  fe d2 = 
{
   45281625, 27714825, 36363642, 13898781, 229458, 15978800, 54557047, 27058993, 29715967, 9444199
};

void ge_p3_to_cached(ge_cached *r, const ge_p3 *p) {
    fe_add(r->YplusX, p->Y, p->X);
    fe_sub(r->YminusX, p->Y, p->X);
    fe_copy(r->Z, p->Z);
    fe_mul(r->T2d, p->T, d2);
}


/*
r = p
*/

void ge_p3_to_p2(ge_p2 *r, const ge_p3 *p) {
    fe_copy(r->X, p->X);
    fe_copy(r->Y, p->Y);
    fe_copy(r->Z, p->Z);
}


void ge_p3_tobytes(unsigned char *s, const ge_p3 *h) {
    fe recip;
    fe x;
    fe y;
    fe_invert(recip, h->Z);
    fe_mul(x, h->X, recip);
    fe_mul(y, h->Y, recip);
    fe_tobytes(s, y);
    s[31] ^= fe_isnegative(x) << 7;
}


static unsigned char equal(signed char b, signed char c) {
    unsigned char ub = b;
    unsigned char uc = c;
    unsigned char x = ub ^ uc; /* 0: yes; 1..255: no */
    uint64_t y = x; /* 0: yes; 1..255: no */
    y -= 1; /* large: yes; 0..254: no */
    y >>= 63; /* 1: yes; 0: no */
    return (unsigned char) y;
}

static unsigned char negative(signed char b) {
    uint64_t x = b; /* 18446744073709551361..18446744073709551615: yes; 0..255: no */
    x >>= 63; /* 1: yes; 0: no */
    return (unsigned char) x;
}

static void cmov(ge_precomp *t, const ge_precomp *u, unsigned char b) {
    fe_cmov(t->yplusx, u->yplusx, b);
    fe_cmov(t->yminusx, u->yminusx, b);
    fe_cmov(t->xy2d, u->xy2d, b);
}


static void choose(ge_precomp *t, int pos, signed char b) {
    ge_precomp minust;
    //printf("baa=%d",b);
    unsigned char bnegative = negative(b);
    //printf("a=%d",bnegative);
    unsigned char babs = b - (((-bnegative) & b) << 1);
    //printf("b=%d",babs);
    fe_1(t->yplusx);
    fe_1(t->yminusx);
    fe_0(t->xy2d);
    cmov(t, &base[pos][0], equal(babs, 1));
    cmov(t, &base[pos][1], equal(babs, 2));
    cmov(t, &base[pos][2], equal(babs, 3));
    cmov(t, &base[pos][3], equal(babs, 4));
    cmov(t, &base[pos][4], equal(babs, 5));
    cmov(t, &base[pos][5], equal(babs, 6));
    cmov(t, &base[pos][6], equal(babs, 7));
    cmov(t, &base[pos][7], equal(babs, 8));
    fe_copy(minust.yplusx, t->yminusx);
    fe_copy(minust.yminusx, t->yplusx);
    fe_neg(minust.xy2d, t->xy2d);
    cmov(t, &minust, bnegative);
}

/*
h = a * B
where a = a[0]+256*a[1]+...+256^31 a[31]
B is the Ed25519 base point (x,4/5) with x positive.

Preconditions:
  a[31] <= 127

  */
/*


void edwardsASDADA(fe X1 ,fe Y1,fe Z1,fe T1 ,fe X2 ,fe Y2,fe Z2,fe T2)
{
   fe X3;
   fe Y3;
   fe Z3;
   fe T3;
   fe asub1;
   fe asub2;
   fe badd1;
   fe badd2;
   fe A;
   fe B;
   fe C;
   fe C1;
   fe D;
   fe E;
   fe F;
   fe G;
   fe H;
   fe_sub(asub1,Y1,X1);
   fe_sub(asub2,Y1,X1);
   fe_mul(A,asub1,asub1);
   fe_add(badd1,Y1,X1);
   fe_add(badd2,Y1,X1);
   fe_mul(B,badd1,badd2);
   fe_mul(C,T1,d2);
   fe_mul(C1,C,T1);
   fe_mul(D,Z1,Z1);
   fe_add(D,D,D);
   fe_sub(E,B,A);
   fe_sub(F,D,C1);
   fe_add(G,D,C1);
   fe_add(H,B,A);
   fe_mul(X3,E,F);  
   fe_mul(Y3,G,H);
   fe_mul(T3,E,H);
   fe_mul(Z3,F,G);
   fe_copy(X4,X3);
   fe_copy(Y4,Y3);
   fe_copy(Z4,Z3);
   fe_copy(T4,T3);
}

*/

static void choose4x(ge_precomp4x *t4x ,ge_precomp *t,  int pos1,int pos2,int pos3 , int pos4, signed char b1,signed char b2, signed char b3, signed char b4) 
{
    ge_precomp minust;
    fe yplusxto4x[4];
    fe yminuxto4x[4];
    fe xy2dto4x[4];
    unsigned char bnegative1 = negative(b1);
    unsigned char babs1 = b1 - (((-bnegative1) & b1) << 1);
    
    unsigned char bnegative2 = negative(b2);
    unsigned char babs2 = b2 - (((-bnegative2) & b2) << 1);

    unsigned char bnegative3 = negative(b3);
    unsigned char babs3 = b3 - (((-bnegative3) & b3) << 1);

    unsigned char bnegative4 = negative(b4);
    unsigned char babs4 = b4 - (((-bnegative4) & b4) << 1);
    //1
    fe_1(t->yplusx);
    fe_1(t->yminusx);
    fe_0(t->xy2d);
    cmov(t, &base[pos1][0], equal(babs1, 1));
    cmov(t, &base[pos1][1], equal(babs1, 2));
    cmov(t, &base[pos1][2], equal(babs1, 3));
    cmov(t, &base[pos1][3], equal(babs1, 4));
    cmov(t, &base[pos1][4], equal(babs1, 5));
    cmov(t, &base[pos1][5], equal(babs1, 6));
    cmov(t, &base[pos1][6], equal(babs1, 7));
    cmov(t, &base[pos1][7], equal(babs1, 8));
    fe_copy(minust.yplusx, t->yminusx);
    fe_copy(minust.yminusx, t->yplusx);
    fe_neg(minust.xy2d, t->xy2d);
    cmov(t, &minust, bnegative1);
    fe_copy(yplusxto4x[0],t->yplusx);
    fe_copy(yminuxto4x[0],t->yminusx);
    fe_copy(xy2dto4x[0],t->xy2d);
    //2
    fe_1(t->yplusx);
    fe_1(t->yminusx);
    fe_0(t->xy2d);
    cmov(t, &base[pos2][0], equal(babs2, 1));
    cmov(t, &base[pos2][1], equal(babs2, 2));
    cmov(t, &base[pos2][2], equal(babs2, 3));
    cmov(t, &base[pos2][3], equal(babs2, 4));
    cmov(t, &base[pos2][4], equal(babs2, 5));
    cmov(t, &base[pos2][5], equal(babs2, 6));
    cmov(t, &base[pos2][6], equal(babs2, 7));
    cmov(t, &base[pos2][7], equal(babs2, 8));
    fe_copy(minust.yplusx, t->yminusx);
    fe_copy(minust.yminusx, t->yplusx);
    fe_neg(minust.xy2d, t->xy2d);
    cmov(t, &minust, bnegative2);
    fe_copy(yplusxto4x[1],t->yplusx);
    fe_copy(yminuxto4x[1],t->yminusx);
    fe_copy(xy2dto4x[1],t->xy2d);
    //3
    fe_1(t->yplusx);
    fe_1(t->yminusx);
    fe_0(t->xy2d);
    cmov(t, &base[pos3][0], equal(babs3, 1));
    cmov(t, &base[pos3][1], equal(babs3, 2));
    cmov(t, &base[pos3][2], equal(babs3, 3));
    cmov(t, &base[pos3][3], equal(babs3, 4));
    cmov(t, &base[pos3][4], equal(babs3, 5));
    cmov(t, &base[pos3][5], equal(babs3, 6));
    cmov(t, &base[pos3][6], equal(babs3, 7));
    cmov(t, &base[pos3][7], equal(babs3, 8));
    fe_copy(minust.yplusx, t->yminusx);
    fe_copy(minust.yminusx, t->yplusx);
    fe_neg(minust.xy2d, t->xy2d);
    cmov(t, &minust, bnegative3);
    fe_copy(yplusxto4x[2],t->yplusx);
    fe_copy(yminuxto4x[2],t->yminusx);
    fe_copy(xy2dto4x[2],t->xy2d);
    //4
    fe_1(t->yplusx);
    fe_1(t->yminusx);
    fe_0(t->xy2d);
    cmov(t, &base[pos4][0], equal(babs4, 1));
    cmov(t, &base[pos4][1], equal(babs4, 2));
    cmov(t, &base[pos4][2], equal(babs4, 3));
    cmov(t, &base[pos4][3], equal(babs4, 4));
    cmov(t, &base[pos4][4], equal(babs4, 5));
    cmov(t, &base[pos4][5], equal(babs4, 6));
    cmov(t, &base[pos4][6], equal(babs4, 7));
    cmov(t, &base[pos4][7], equal(babs4, 8));
    fe_copy(minust.yplusx, t->yminusx);
    fe_copy(minust.yminusx, t->yplusx);
    fe_neg(minust.xy2d, t->xy2d);
    cmov(t, &minust, bnegative4);
    fe_copy(yplusxto4x[3],t->yplusx);
    fe_copy(yminuxto4x[3],t->yminusx);
    fe_copy(xy2dto4x[3],t->xy2d);
    int i ;
    for(i=0;i<10;i++)
{
     t4x->yplusx4x[i] = _mm256_set_epi64x(yplusxto4x[3][i],yplusxto4x[2][i],yplusxto4x[1][i],yplusxto4x[0][i]);
     t4x->yminusx4x[i]= _mm256_set_epi64x(yminuxto4x[3][i],yminuxto4x[2][i],yminuxto4x[1][i],yminuxto4x[0][i]);
     t4x->xy2d4x[i] =  _mm256_set_epi64x(xy2dto4x[3][i],xy2dto4x[2][i],xy2dto4x[1][i],xy2dto4x[0][i]);

}

}

void ge_add4X_to_add(ge_p3 *m,fe X1,fe Y1, fe Z1, fe T1,fe X2,fe Y2,fe Z2,fe T2)
{  
   fe asub1;
   fe asub2;
   fe badd1;
   fe badd2;
   fe A;
   fe B;
   fe C;
   fe C1;
   fe D;
   fe E;
   fe F;
   fe G;
   fe H;
   fe X3;
   fe Y3;
   fe Z3;
   fe T3;
   //fe_neg(X1);
   //fe_neg(Y2);
   fe_sub(asub1,Y1,X1);
   fe_sub(asub2,Y2,X2);
   fe_mul(A,asub1,asub2);
   fe_add(badd1,Y1,X1);
   fe_add(badd2,Y2,X2);
   fe_mul(B,badd1,badd2);
   fe_mul(C,T1,d2);
   fe_mul(C1,C,T2);
   fe_mul(D,Z1,Z2);
   fe_add(D,D,D);
   fe_sub(E,B,A);
   fe_sub(F,D,C1);
   fe_add(G,D,C1);
   fe_add(H,B,A);
   fe_mul(X3,E,F);  
   fe_mul(Y3,G,H);
   fe_mul(T3,E,H);
   fe_mul(Z3,F,G);
   fe_copy(m->X,X3);
   fe_copy(m->Y,Y3);
   fe_copy(m->Z,Z3);
   fe_copy(m->T,T3);
}
void ge_scalarmult_base(ge_p3 *h, const unsigned char *a) 
{
    signed char e[64];
    signed char carry;
    ge_p1p1 r;
    ge_p2 s;
    ge_precomp t;
    int i;
   
    //for (i=0;i<32;i++)
//{
  //  printf("a[%d]=%d\n",i,a[i]);
//}
   
    for (i = 0; i < 32;++i)
   {    //printf("a[%d]= %d",i,a[i]);
        //nl();
        e[2 * i + 0] = (a[i] >> 0) & 15;
 	
        e[2 * i + 1] = (a[i] >> 4) & 15;
   }

    /* each e[i] is between 0 and 15 */
    /* e[63] is between 0 and 7 */
    carry = 0;

    for (i = 0; i < 63; ++i) {
        e[i] += carry;
        carry = e[i] + 8;
        carry >>= 4;
        e[i] -= carry << 4;
	//printf("e[%d]= %d",i,e[i]);

    }
    //printf("carry = %d ", carry ); 
	//nl();
      //e[15] + = carry; 
  
    e[63] += carry;  
    /* each e[i] is between -8 and 8 */
    ge_p3_0(h);

    for (i = 1; i < 64; i += 2) {
        choose(&t, i / 2, e[i]);
	//printf("XaddY=");	
        //fe_dump(t.yplusx);
	//nl();
	//printf("ysubx=");	
        //fe_dump(t.yminusx);
	//nl();
	//printf("dyx=");
        //fe_dump(t.xy2d);
	//nl();
	//printf("e[%d]= %d",i,e[i]);
	//nl();
        ge_madd(&r, h, &t);
        ge_p1p1_to_p3(h, &r);
    }
    //printf("Xadd = "); fe_dump(h->X); nl();
    //printf("Yadd = "); fe_dump(h->Y); nl();
    //printf("Zadd = "); fe_dump(h->Z); nl();
    //printf("Tadd = "); fe_dump(h->T); nl();
   
    ge_p3_dbl(&r, h);
    //printf("Xdbl = "); fe_dump(r.X); nl();
    //printf("Ydbl = "); fe_dump(r.Y); nl();
    //printf("Zdbl = "); fe_dump(r.Z); nl();
    //printf("Tdbl = "); fe_dump(r.T); nl();
    ge_p1p1_to_p2(&s, &r);
    ge_p2_dbl(&r, &s);
    
    //printf("Xdbl4 = "); fe_dump(r.X); nl();
    //printf("Ydbl4 = "); fe_dump(r.Y); nl();
    //printf("Zdbl4 = "); fe_dump(r.Z); nl();
    //printf("Tdbl4 = "); fe_dump(r.T); nl();
    
    ge_p1p1_to_p2(&s, &r);
    //printf("Xdbl41 = "); fe_dump(s.X); nl();
    //printf("Ydbl41 = "); fe_dump(s.Y); nl();
    //printf("Zdbl41 = "); fe_dump(s.Z); nl();
    //printf("Tdbl41 = "); fe_dump(s.T); nl();
    ge_p2_dbl(&r, &s);
    //printf("Xdbl8 = "); fe_dump(r.X); nl();
    //printf("Ydbl8 = "); fe_dump(r.Y); nl();
    //printf("Zdbl8 = "); fe_dump(r.Z); nl();
    //printf("Tdbl8 = "); fe_dump(r.T); nl();
    ge_p1p1_to_p2(&s, &r);
    ge_p2_dbl(&r, &s);
    
    //printf("Xdbl16 = "); fe_dump(r.X); nl();
    //printf("Ydbl16 = "); fe_dump(r.Y); nl();
    //printf("Zdbl16 = "); fe_dump(r.Z); nl();
    //printf("Tdbl16 = "); fe_dump(r.T); nl();
    
    ge_p1p1_to_p3(h, &r);
   
    //printf("Xdbl161 = "); fe_dump(h->X); nl();
    //printf("Ydbl161 = "); fe_dump(h->Y); nl();
    //printf("Zdbl161 = "); fe_dump(h->Z); nl();
    //printf("Tdbl161 = "); fe_dump(h->T); nl();
   
    for (i = 0; i < 64; i += 2) {
        choose(&t, i / 2, e[i]);
	//fe_dump(t.yplusx);
	//nl();
        //fe_dump(t.yminusx);
	//nl();
        //fe_dump(t.xy2d);
	//nl();
	//printf("e[%d]= %d",i,e[i]);
	//nl();
        ge_madd(&r, h, &t);
        ge_p1p1_to_p3(h, &r);
    }


}

void ge_scalarmult_base4x(ge_p3 *m, ge_p34x *h, const unsigned char *a)
{
     signed char e[64];
     signed char carry;
     ge_p1p14x r;
     ge_p24x s;
     ge_precomp t;
     ge_precomp4x t4x;
     //fe htest[4];
     //fe h[]
     int i,j;
      for (i = 0; i < 32; ++i) 
{
        e[2 * i + 0] = (a[i] >> 0) & 15;
 	//printf("a[%d]=%d",i,a[i]);
	//nl();
        e[2 * i + 1] = (a[i] >> 4) & 15;
    }

    // each e[i] is between 0 and 15
    // e[63] is between 0 and 7 
    carry = 0;

    for (i = 0; i < 63; ++i) {
        e[i] += carry;
	//printf("e[%d]=%d\n",i,e[i]);
        carry = e[i] + 8;
	//printf("carry[%d]=%d\n",i,carry);
        carry >>= 4;
	//printf("carry[%d]=%d\n",i,carry);
        e[i] -= carry << 4;
	//printf("e[%d]=%d",i,e[i]);
    }
    
    e[63] += carry;
    signed char   era1,era2,era3,era4;
    int   ppos1,ppos2,ppos3,ppos4;
    
    ge_p3_04x(h);
   
    for(i=0;i<8;i++)
{
     era1 = e[8*i+1];
     era2 = e[8*i+3];
     era3 = e[8*i+5];
     era4 = e[8*i+7];
     ppos1 = 4*i;
     ppos2 = 4*i+1;
     ppos3 = 4*i+2;
     ppos4 = 4*i+3;
     //printf("%d %d %d %d %d \n ",i,era1,era2,era3,era4);
     choose4x(&t4x,&t,ppos1,ppos2,ppos3,ppos4,era1,era2,era3,era4);
     ge_madd4x(&r,h,&t4x);
//test
     ge_p1p14x_to_p34x(h,&r);

}
     ge_p3_dbl4x(&r, h);
     ge_p1p14x_to_p24x(&s, &r);
     ge_p2_dbl4x(&r, &s);
     ge_p1p14x_to_p24x(&s, &r);
     ge_p2_dbl4x(&r, &s);
     ge_p1p14x_to_p24x(&s, &r);
     ge_p2_dbl4x(&r, &s);
     ge_p1p14x_to_p34x(h, &r);

    for(i=0;i<8;i++)
{
  
    
     era1 = e[8*i];
     era2 = e[8*i+2];
     era3 = e[8*i+4];
     era4 = e[8*i+6];
     ppos1 = 4*i;
     ppos2 = 4*i+1;
     ppos3 = 4*i+2;
     ppos4 = 4*i+3;
     //printf("%d %d %d %d %d \n ",i,era1,era2,era3,era4);
     choose4x(&t4x,&t,ppos1,ppos2,ppos3,ppos4,era1,era2,era3,era4);
     ge_madd4x(&r,h,&t4x);
     ge_p1p14x_to_p34x(h,&r);

}
     fe x1[4];
     fe y1[4];
     fe z1[4];
     fe t1[4];
    for (i = 0; i < 10; i++){
    for (j = 0; j < 4; j++){
	
 	x1[j][i] = _mm256_extract_epi64 (h->X4x[i], j);
        y1[j][i] = _mm256_extract_epi64 (h->Y4x[i], j);
 	z1[j][i] = _mm256_extract_epi64 (h->Z4x[i], j);
        t1[j][i] = _mm256_extract_epi64 (h->T4x[i], j);
}
}   
   
    ge_p3_0(m);
    for(i=0;i<4;i++)
{
        ge_add4X_to_add(m,m->X,m->Y,m->Z,m->T,x1[i],y1[i],z1[i],t1[i]);
}

}

/*
r = p - q
*/

void ge_sub(ge_p1p1 *r, const ge_p3 *p, const ge_cached *q) {
    fe t0;
    
    fe_add(r->X, p->Y, p->X);
    fe_sub(r->Y, p->Y, p->X);
    fe_mul(r->Z, r->X, q->YminusX);
    fe_mul(r->Y, r->Y, q->YplusX);
    fe_mul(r->T, q->T2d, p->T);
    fe_mul(r->X, p->Z, q->Z);
    fe_add(t0, r->X, r->X);
    fe_sub(r->X, r->Z, r->Y);
    fe_add(r->Y, r->Z, r->Y);
    fe_sub(r->Z, t0, r->T);
    fe_add(r->T, t0, r->T);
}


void ge_tobytes(unsigned char *s, const ge_p2 *h) {
    fe recip;
    fe x;
    fe y;
    fe_invert(recip, h->Z);
    fe_mul(x, h->X, recip);
    fe_mul(y, h->Y, recip);
    fe_tobytes(s, y);
    s[31] ^= fe_isnegative(x) << 7;
}
