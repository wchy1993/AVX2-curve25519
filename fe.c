#include "fe.h"
#include "crypto_int64.h"
#include "crypto_int32.h"



/*
    helper functions
*/
static crypto_int64 load_3(const unsigned char *in) {
    crypto_int64 result;

    result = (crypto_int64) in[0];
    result |= ((crypto_int64) in[1]) << 8;
    result |= ((crypto_int64) in[2]) << 16;

    return result;
}

static crypto_int64 load_4(const unsigned char *in) {
    crypto_int64 result;

    result = (crypto_int64) in[0];
    result |= ((crypto_int64) in[1]) << 8;
    result |= ((crypto_int64) in[2]) << 16;
    result |= ((crypto_int64) in[3]) << 24;
    
    return result;
}



/*
    h = 0
*/

void fe_0(fe h) {
    h[0] = 0;
    h[1] = 0;
    h[2] = 0;
    h[3] = 0;
    h[4] = 0;
    h[5] = 0;
    h[6] = 0;
    h[7] = 0;
    h[8] = 0;
    h[9] = 0;
}



/*
    h = 1
*/

void fe_1(fe h) {
    h[0] = 1;
    h[1] = 0;
    h[2] = 0;
    h[3] = 0;
    h[4] = 0;
    h[5] = 0;
    h[6] = 0;
    h[7] = 0;
    h[8] = 0;
    h[9] = 0;
}



/*
    h = f + g
    Can overlap h with f or g.

    Preconditions:
       |f| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
       |g| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.

    Postconditions:
       |h| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

void fe_add(fe h, const fe f, const fe g) {
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int32 g0 = g[0];
    crypto_int32 g1 = g[1];
    crypto_int32 g2 = g[2];
    crypto_int32 g3 = g[3];
    crypto_int32 g4 = g[4];
    crypto_int32 g5 = g[5];
    crypto_int32 g6 = g[6];
    crypto_int32 g7 = g[7];
    crypto_int32 g8 = g[8];
    crypto_int32 g9 = g[9];
    crypto_int32 h0 = f0 + g0;
    crypto_int32 h1 = f1 + g1;
    crypto_int32 h2 = f2 + g2;
    crypto_int32 h3 = f3 + g3;
    crypto_int32 h4 = f4 + g4;
    crypto_int32 h5 = f5 + g5;
    crypto_int32 h6 = f6 + g6;
    crypto_int32 h7 = f7 + g7;
    crypto_int32 h8 = f8 + g8;
    crypto_int32 h9 = f9 + g9;
  crypto_int64 carry0;
  crypto_int64 carry1;
  crypto_int64 carry2;
  crypto_int64 carry3;
  crypto_int64 carry4;
  crypto_int64 carry5;
  crypto_int64 carry6;
  crypto_int64 carry7;
  crypto_int64 carry8;
  crypto_int64 carry9;
carry0=h0>>26;  // h0
  h1=h1+carry0;
  carry0=carry0<<26;
  h0-=carry0;


  carry1=h1>>25;  // h1
  h2=h2+carry1;
  carry1=carry1<<25;
  h1-=carry1;
 
  carry2=h2>>26;  // h2
  h3=h3+carry2;
  carry2=carry2<<26;
  h2-=carry2;


  carry3=h3>>25;  // h3
  h4=h4+carry3;
  carry3=carry3<<25;
  h3-=carry3;

  carry4=h4>>26;  // h4
  h5=h5+carry4;
  carry4=carry4<<26;
  h4-=carry4;

  carry5=h5>>25;  // h5
  h6=h6+carry5;
  carry5=carry5<<25;
  h5-=carry5;

  carry6=h6>>26;  // h6
  h7=h7+carry6;
  carry6=carry6<<26;
  h6-=carry6;

   carry7=h7>>25;  // h7
   h8=h8+carry7;
   carry7=carry7<<25;
   h7-=carry7;

   carry8=h8>>26;  // h8
   h9=h9+carry8;
   carry8=carry8<<26;
   h8-=carry8;

   carry9=h9>>25;  // h9
   h0=h0+19*carry9;
   carry9=carry9<<25;
   h9-=carry9;

   carry0=h0>>26;  //h0
   h1=h1+carry0;
   carry0=carry0<<26;
   h0-=carry0;
   carry1=h1>>25;    //h1
   h2=h2+carry1;
   carry1=carry1<<25;
   h1-=carry1;
  
  
  h[0] = h0;
  h[1] = h1;
  h[2] = h2;
  h[3] = h3;
  h[4] = h4;
  h[5] = h5;
  h[6] = h6;
  h[7] = h7;
  h[8] = h8;
  h[9] = h9;
}





/*
    Replace (f,g) with (g,g) if b == 1;
    replace (f,g) with (f,g) if b == 0.

    Preconditions: b in {0,1}.
*/

void fe_cmov(fe f, const fe g, unsigned int b)
{
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int32 g0 = g[0];
    crypto_int32 g1 = g[1];
    crypto_int32 g2 = g[2];
    crypto_int32 g3 = g[3];
    crypto_int32 g4 = g[4];
    crypto_int32 g5 = g[5];
    crypto_int32 g6 = g[6];
    crypto_int32 g7 = g[7];
    crypto_int32 g8 = g[8];
    crypto_int32 g9 = g[9];
    crypto_int32 x0 = f0 ^ g0;
    crypto_int32 x1 = f1 ^ g1;
    crypto_int32 x2 = f2 ^ g2;
    crypto_int32 x3 = f3 ^ g3;
    crypto_int32 x4 = f4 ^ g4;
    crypto_int32 x5 = f5 ^ g5;
    crypto_int32 x6 = f6 ^ g6;
    crypto_int32 x7 = f7 ^ g7;
    crypto_int32 x8 = f8 ^ g8;
    crypto_int32 x9 = f9 ^ g9;

    b = (unsigned int) (- (int) b); /* silence warning */
    x0 &= b;
    x1 &= b;
    x2 &= b;
    x3 &= b;
    x4 &= b;
    x5 &= b;
    x6 &= b;
    x7 &= b;
    x8 &= b;
    x9 &= b;
    
    f[0] = f0 ^ x0;
    f[1] = f1 ^ x1;
    f[2] = f2 ^ x2;
    f[3] = f3 ^ x3;
    f[4] = f4 ^ x4;
    f[5] = f5 ^ x5;
    f[6] = f6 ^ x6;
    f[7] = f7 ^ x7;
    f[8] = f8 ^ x8;
    f[9] = f9 ^ x9;
}

/*
    Replace (f,g) with (g,f) if b == 1;
    replace (f,g) with (f,g) if b == 0.

    Preconditions: b in {0,1}.
*/

void fe_cswap(fe f,fe g,unsigned int b) {
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int32 g0 = g[0];
    crypto_int32 g1 = g[1];
    crypto_int32 g2 = g[2];
    crypto_int32 g3 = g[3];
    crypto_int32 g4 = g[4];
    crypto_int32 g5 = g[5];
    crypto_int32 g6 = g[6];
    crypto_int32 g7 = g[7];
    crypto_int32 g8 = g[8];
    crypto_int32 g9 = g[9];
    crypto_int32 x0 = f0 ^ g0;
    crypto_int32 x1 = f1 ^ g1;
    crypto_int32 x2 = f2 ^ g2;
    crypto_int32 x3 = f3 ^ g3;
    crypto_int32 x4 = f4 ^ g4;
    crypto_int32 x5 = f5 ^ g5;
    crypto_int32 x6 = f6 ^ g6;
    crypto_int32 x7 = f7 ^ g7;
    crypto_int32 x8 = f8 ^ g8;
    crypto_int32 x9 = f9 ^ g9;
    b = (unsigned int) (- (int) b); /* silence warning */
    x0 &= b;
    x1 &= b;
    x2 &= b;
    x3 &= b;
    x4 &= b;
    x5 &= b;
    x6 &= b;
    x7 &= b;
    x8 &= b;
    x9 &= b;
    f[0] = f0 ^ x0;
    f[1] = f1 ^ x1;
    f[2] = f2 ^ x2;
    f[3] = f3 ^ x3;
    f[4] = f4 ^ x4;
    f[5] = f5 ^ x5;
    f[6] = f6 ^ x6;
    f[7] = f7 ^ x7;
    f[8] = f8 ^ x8;
    f[9] = f9 ^ x9;
    g[0] = g0 ^ x0;
    g[1] = g1 ^ x1;
    g[2] = g2 ^ x2;
    g[3] = g3 ^ x3;
    g[4] = g4 ^ x4;
    g[5] = g5 ^ x5;
    g[6] = g6 ^ x6;
    g[7] = g7 ^ x7;
    g[8] = g8 ^ x8;
    g[9] = g9 ^ x9;
}



/*
    h = f
*/

void fe_copy(fe h, const fe f) {
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    
    h[0] = f0;
    h[1] = f1;
    h[2] = f2;
    h[3] = f3;
    h[4] = f4;
    h[5] = f5;
    h[6] = f6;
    h[7] = f7;
    h[8] = f8;
    h[9] = f9;
}



/*
    Ignores top bit of h.
*/

void fe_frombytes(fe h, const unsigned char *s) 
{   
 
    uint64_t h0 = load_4(s);
    uint64_t h1 = load_3(s + 4) << 6;
    uint64_t h2 = load_3(s + 7) << 5;
    uint64_t h3 = load_3(s + 10) << 3;
    uint64_t h4 = load_3(s + 13) << 2;
    uint64_t h5 = load_4(s + 16);
    uint64_t h6 = load_3(s + 20) << 7;
    uint64_t h7 = load_3(s + 23) << 5;
    uint64_t h8 = load_3(s + 26) << 4;
    uint64_t h9 = (load_3(s + 29) & 8388607) << 2;
    h[0] = (crypto_int64) h0;
    h[1] = (crypto_int64) h1;
    h[2] = (crypto_int64) h2;
    h[3] = (crypto_int64) h3;
    h[4] = (crypto_int64) h4;
    h[5] = (crypto_int64) h5;
    h[6] = (crypto_int64) h6;
    h[7] = (crypto_int64) h7;
    h[8] = (crypto_int64) h8;
    h[9] = (crypto_int64) h9;
}




void fe_invert(fe out, const fe z) {
    fe t0;
    fe t1;
    fe t2;
    fe t3;
    int i;

    fe_sq(t0, z);

    for (i = 1; i < 1; ++i) {
        fe_sq(t0, t0);
    }

    fe_sq(t1, t0);

    for (i = 1; i < 2; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, z, t1);
    fe_mul(t0, t0, t1);
    fe_sq(t2, t0);

    for (i = 1; i < 1; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t1, t2);
    fe_sq(t2, t1);

    for (i = 1; i < 5; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t2, t1);

    for (i = 1; i < 10; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t2, t2, t1);
    fe_sq(t3, t2);

    for (i = 1; i < 20; ++i) {
        fe_sq(t3, t3);
    }

    fe_mul(t2, t3, t2);
    fe_sq(t2, t2);

    for (i = 1; i < 10; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t2, t1);

    for (i = 1; i < 50; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t2, t2, t1);
    fe_sq(t3, t2);

    for (i = 1; i < 100; ++i) {
        fe_sq(t3, t3);
    }

    fe_mul(t2, t3, t2);
    fe_sq(t2, t2);

    for (i = 1; i < 50; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t1, t1);

    for (i = 1; i < 5; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(out, t1, t0);
}



/*
    return 1 if f is in {1,3,5,...,q-2}
    return 0 if f is in {0,2,4,...,q-1}

    Preconditions:
       |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

int fe_isnegative(const fe f) {
    unsigned char s[32];

    fe_tobytes(s, f);
    
    return s[0] & 1;
}



/*
    return 1 if f == 0
    return 0 if f != 0

    Preconditions:
       |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

int fe_isnonzero(const fe f) {
    unsigned char s[32];
    unsigned char r;

    fe_tobytes(s, f);

    r = s[0];
    #define F(i) r |= s[i]
    F(1);
    F(2);
    F(3);
    F(4);
    F(5);
    F(6);
    F(7);
    F(8);
    F(9);
    F(10);
    F(11);
    F(12);
    F(13);
    F(14);
    F(15);
    F(16);
    F(17);
    F(18);
    F(19);
    F(20);
    F(21);
    F(22);
    F(23);
    F(24);
    F(25);
    F(26);
    F(27);
    F(28);
    F(29);
    F(30);
    F(31);
    #undef F

    return r != 0;
}




void fe_mul(fe h, const fe f, const fe g)
{
  crypto_int32 f0 = f[0];
  crypto_int32 f1 = f[1];
  crypto_int32 f2 = f[2];
  crypto_int32 f3 = f[3];
  crypto_int32 f4 = f[4];
  crypto_int32 f5 = f[5];
  crypto_int32 f6 = f[6];
  crypto_int32 f7 = f[7];
  crypto_int32 f8 = f[8];
  crypto_int32 f9 = f[9];
  crypto_int32 g0 = g[0];
  crypto_int32 g1 = g[1];
  crypto_int32 g2 = g[2];
  crypto_int32 g3 = g[3];
  crypto_int32 g4 = g[4];
  crypto_int32 g5 = g[5];
  crypto_int32 g6 = g[6];
  crypto_int32 g7 = g[7];
  crypto_int32 g8 = g[8];
  crypto_int32 g9 = g[9];
  crypto_int32 g1_19 = 19 * g1; /* 1.4*2^29 */
  crypto_int32 g2_19 = 19 * g2; /* 1.4*2^30; still ok */
  crypto_int32 g3_19 = 19 * g3;
  crypto_int32 g4_19 = 19 * g4;
  crypto_int32 g5_19 = 19 * g5;
  crypto_int32 g6_19 = 19 * g6;
  crypto_int32 g7_19 = 19 * g7;
  crypto_int32 g8_19 = 19 * g8;
  crypto_int32 g9_19 = 19 * g9;
  crypto_int32 f1_2 = 2 * f1;
  crypto_int32 f3_2 = 2 * f3;
  crypto_int32 f5_2 = 2 * f5;
  crypto_int32 f7_2 = 2 * f7;
  crypto_int32 f9_2 = 2 * f9;
  crypto_int64 f0g0    = f0   * (crypto_int64) g0;
  crypto_int64 f0g1    = f0   * (crypto_int64) g1;
  crypto_int64 f0g2    = f0   * (crypto_int64) g2;
  crypto_int64 f0g3    = f0   * (crypto_int64) g3;
  crypto_int64 f0g4    = f0   * (crypto_int64) g4;
  crypto_int64 f0g5    = f0   * (crypto_int64) g5;
  crypto_int64 f0g6    = f0   * (crypto_int64) g6;
  crypto_int64 f0g7    = f0   * (crypto_int64) g7;
  crypto_int64 f0g8    = f0   * (crypto_int64) g8;
  crypto_int64 f0g9    = f0   * (crypto_int64) g9;
  crypto_int64 f1g0    = f1   * (crypto_int64) g0;
  crypto_int64 f1g1_2  = f1_2 * (crypto_int64) g1;
  crypto_int64 f1g2    = f1   * (crypto_int64) g2;
  crypto_int64 f1g3_2  = f1_2 * (crypto_int64) g3;
  crypto_int64 f1g4    = f1   * (crypto_int64) g4;
  crypto_int64 f1g5_2  = f1_2 * (crypto_int64) g5;
  crypto_int64 f1g6    = f1   * (crypto_int64) g6;
  crypto_int64 f1g7_2  = f1_2 * (crypto_int64) g7;
  crypto_int64 f1g8    = f1   * (crypto_int64) g8;
  crypto_int64 f1g9_38 = f1_2 * (crypto_int64) g9_19;
  crypto_int64 f2g0    = f2   * (crypto_int64) g0;
  crypto_int64 f2g1    = f2   * (crypto_int64) g1;
  crypto_int64 f2g2    = f2   * (crypto_int64) g2;
  crypto_int64 f2g3    = f2   * (crypto_int64) g3;
  crypto_int64 f2g4    = f2   * (crypto_int64) g4;
  crypto_int64 f2g5    = f2   * (crypto_int64) g5;
  crypto_int64 f2g6    = f2   * (crypto_int64) g6;
  crypto_int64 f2g7    = f2   * (crypto_int64) g7;
  crypto_int64 f2g8_19 = f2   * (crypto_int64) g8_19;
  crypto_int64 f2g9_19 = f2   * (crypto_int64) g9_19;
  crypto_int64 f3g0    = f3   * (crypto_int64) g0;
  crypto_int64 f3g1_2  = f3_2 * (crypto_int64) g1;
  crypto_int64 f3g2    = f3   * (crypto_int64) g2;
  crypto_int64 f3g3_2  = f3_2 * (crypto_int64) g3;
  crypto_int64 f3g4    = f3   * (crypto_int64) g4;
  crypto_int64 f3g5_2  = f3_2 * (crypto_int64) g5;
  crypto_int64 f3g6    = f3   * (crypto_int64) g6;
  crypto_int64 f3g7_38 = f3_2 * (crypto_int64) g7_19;
  crypto_int64 f3g8_19 = f3   * (crypto_int64) g8_19;
  crypto_int64 f3g9_38 = f3_2 * (crypto_int64) g9_19;
  crypto_int64 f4g0    = f4   * (crypto_int64) g0;
  crypto_int64 f4g1    = f4   * (crypto_int64) g1;
  crypto_int64 f4g2    = f4   * (crypto_int64) g2;
  crypto_int64 f4g3    = f4   * (crypto_int64) g3;
  crypto_int64 f4g4    = f4   * (crypto_int64) g4;
  crypto_int64 f4g5    = f4   * (crypto_int64) g5;
  crypto_int64 f4g6_19 = f4   * (crypto_int64) g6_19;
  crypto_int64 f4g7_19 = f4   * (crypto_int64) g7_19;
  crypto_int64 f4g8_19 = f4   * (crypto_int64) g8_19;
  crypto_int64 f4g9_19 = f4   * (crypto_int64) g9_19;
  crypto_int64 f5g0    = f5   * (crypto_int64) g0;
  crypto_int64 f5g1_2  = f5_2 * (crypto_int64) g1;
  crypto_int64 f5g2    = f5   * (crypto_int64) g2;
  crypto_int64 f5g3_2  = f5_2 * (crypto_int64) g3;
  crypto_int64 f5g4    = f5   * (crypto_int64) g4;
  crypto_int64 f5g5_38 = f5_2 * (crypto_int64) g5_19;
  crypto_int64 f5g6_19 = f5   * (crypto_int64) g6_19;
  crypto_int64 f5g7_38 = f5_2 * (crypto_int64) g7_19;
  crypto_int64 f5g8_19 = f5   * (crypto_int64) g8_19;
  crypto_int64 f5g9_38 = f5_2 * (crypto_int64) g9_19;
  crypto_int64 f6g0    = f6   * (crypto_int64) g0;
  crypto_int64 f6g1    = f6   * (crypto_int64) g1;
  crypto_int64 f6g2    = f6   * (crypto_int64) g2;
  crypto_int64 f6g3    = f6   * (crypto_int64) g3;
  crypto_int64 f6g4_19 = f6   * (crypto_int64) g4_19;
  crypto_int64 f6g5_19 = f6   * (crypto_int64) g5_19;
  crypto_int64 f6g6_19 = f6   * (crypto_int64) g6_19;
  crypto_int64 f6g7_19 = f6   * (crypto_int64) g7_19;
  crypto_int64 f6g8_19 = f6   * (crypto_int64) g8_19;
  crypto_int64 f6g9_19 = f6   * (crypto_int64) g9_19;
  crypto_int64 f7g0    = f7   * (crypto_int64) g0;
  crypto_int64 f7g1_2  = f7_2 * (crypto_int64) g1;
  crypto_int64 f7g2    = f7   * (crypto_int64) g2;
  crypto_int64 f7g3_38 = f7_2 * (crypto_int64) g3_19;
  crypto_int64 f7g4_19 = f7   * (crypto_int64) g4_19;
  crypto_int64 f7g5_38 = f7_2 * (crypto_int64) g5_19;
  crypto_int64 f7g6_19 = f7   * (crypto_int64) g6_19;
  crypto_int64 f7g7_38 = f7_2 * (crypto_int64) g7_19;
  crypto_int64 f7g8_19 = f7   * (crypto_int64) g8_19;
  crypto_int64 f7g9_38 = f7_2 * (crypto_int64) g9_19;
  crypto_int64 f8g0    = f8   * (crypto_int64) g0;
  crypto_int64 f8g1    = f8   * (crypto_int64) g1;
  crypto_int64 f8g2_19 = f8   * (crypto_int64) g2_19;
  crypto_int64 f8g3_19 = f8   * (crypto_int64) g3_19;
  crypto_int64 f8g4_19 = f8   * (crypto_int64) g4_19;
  crypto_int64 f8g5_19 = f8   * (crypto_int64) g5_19;
  crypto_int64 f8g6_19 = f8   * (crypto_int64) g6_19;
  crypto_int64 f8g7_19 = f8   * (crypto_int64) g7_19;
  crypto_int64 f8g8_19 = f8   * (crypto_int64) g8_19;
  crypto_int64 f8g9_19 = f8   * (crypto_int64) g9_19;
  crypto_int64 f9g0    = f9   * (crypto_int64) g0;
  crypto_int64 f9g1_38 = f9_2 * (crypto_int64) g1_19;
  crypto_int64 f9g2_19 = f9   * (crypto_int64) g2_19;
  crypto_int64 f9g3_38 = f9_2 * (crypto_int64) g3_19;
  crypto_int64 f9g4_19 = f9   * (crypto_int64) g4_19;
  crypto_int64 f9g5_38 = f9_2 * (crypto_int64) g5_19;
  crypto_int64 f9g6_19 = f9   * (crypto_int64) g6_19;
  crypto_int64 f9g7_38 = f9_2 * (crypto_int64) g7_19;
  crypto_int64 f9g8_19 = f9   * (crypto_int64) g8_19;
  crypto_int64 f9g9_38 = f9_2 * (crypto_int64) g9_19;
  crypto_int64 h0 = f0g0+f1g9_38+f2g8_19+f3g7_38+f4g6_19+f5g5_38+f6g4_19+f7g3_38+f8g2_19+f9g1_38;
  crypto_int64 h1 = f0g1+f1g0   +f2g9_19+f3g8_19+f4g7_19+f5g6_19+f6g5_19+f7g4_19+f8g3_19+f9g2_19;
  crypto_int64 h2 = f0g2+f1g1_2 +f2g0   +f3g9_38+f4g8_19+f5g7_38+f6g6_19+f7g5_38+f8g4_19+f9g3_38;
  crypto_int64 h3 = f0g3+f1g2   +f2g1   +f3g0   +f4g9_19+f5g8_19+f6g7_19+f7g6_19+f8g5_19+f9g4_19;
  crypto_int64 h4 = f0g4+f1g3_2 +f2g2   +f3g1_2 +f4g0   +f5g9_38+f6g8_19+f7g7_38+f8g6_19+f9g5_38;
  crypto_int64 h5 = f0g5+f1g4   +f2g3   +f3g2   +f4g1   +f5g0   +f6g9_19+f7g8_19+f8g7_19+f9g6_19;
  crypto_int64 h6 = f0g6+f1g5_2 +f2g4   +f3g3_2 +f4g2   +f5g1_2 +f6g0   +f7g9_38+f8g8_19+f9g7_38;
  crypto_int64 h7 = f0g7+f1g6   +f2g5   +f3g4   +f4g3   +f5g2   +f6g1   +f7g0   +f8g9_19+f9g8_19;
  crypto_int64 h8 = f0g8+f1g7_2 +f2g6   +f3g5_2 +f4g4   +f5g3_2 +f6g2   +f7g1_2 +f8g0   +f9g9_38;
  crypto_int64 h9 = f0g9+f1g8   +f2g7   +f3g6   +f4g5   +f5g4   +f6g3   +f7g2   +f8g1   +f9g0   ;
  crypto_int64 carry0;
  crypto_int64 carry1;
  crypto_int64 carry2;
  crypto_int64 carry3;
  crypto_int64 carry4;
  crypto_int64 carry5;
  crypto_int64 carry6;
  crypto_int64 carry7;
  crypto_int64 carry8;
  crypto_int64 carry9;

  carry0=h0>>26;  // h0
  h1=h1+carry0;
  carry0=carry0<<26;
  h0-=carry0;


  carry1=h1>>25;  // h1
  h2=h2+carry1;
  carry1=carry1<<25;
  h1-=carry1;
 
  carry2=h2>>26;  // h2
  h3=h3+carry2;
  carry2=carry2<<26;
  h2-=carry2;


  carry3=h3>>25;  // h3
  h4=h4+carry3;
  carry3=carry3<<25;
  h3-=carry3;

  carry4=h4>>26;  // h4
  h5=h5+carry4;
  carry4=carry4<<26;
  h4-=carry4;

  carry5=h5>>25;  // h5
  h6=h6+carry5;
  carry5=carry5<<25;
  h5-=carry5;

  carry6=h6>>26;  // h6
  h7=h7+carry6;
  carry6=carry6<<26;
  h6-=carry6;

   carry7=h7>>25;  // h7
   h8=h8+carry7;
   carry7=carry7<<25;
   h7-=carry7;

   carry8=h8>>26;  // h8
   h9=h9+carry8;
   carry8=carry8<<26;
   h8-=carry8;

   carry9=h9>>25;  // h9
   h0=h0+19*carry9;
   carry9=carry9<<25;
   h9-=carry9;

   carry0=h0>>26;  //h0
   h1=h1+carry0;
   carry0=carry0<<26;
   h0-=carry0;
   carry1=h1>>25;    //h1
   h2=h2+carry1;
   carry1=carry1<<25;
   h1-=carry1;

  h[0] = h0;
  h[1] = h1;
  h[2] = h2;
  h[3] = h3;
  h[4] = h4;
  h[5] = h5;
  h[6] = h6;
  h[7] = h7;
  h[8] = h8;
  h[9] = h9;
}

/*
h = f * 121666
Can overlap h with f.

Preconditions:
   |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.

Postconditions:
   |h| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
*/

void fe_mul121666(fe h, fe f) {
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int64 h0 = f0 *  121666;
    crypto_int64 h1 = f1 *  121666;
    crypto_int64 h2 = f2 *  121666;
    crypto_int64 h3 = f3 *  121666;
    crypto_int64 h4 = f4 *  121666;
    crypto_int64 h5 = f5 *  121666;
    crypto_int64 h6 = f6 *  121666;
    crypto_int64 h7 = f7 *  121666;
    crypto_int64 h8 = f8 *  121666;
    crypto_int64 h9 = f9 *  121666;
    
  crypto_int64 carry0;
  crypto_int64 carry1;
  crypto_int64 carry2;
  crypto_int64 carry3;
  crypto_int64 carry4;
  crypto_int64 carry5;
  crypto_int64 carry6;
  crypto_int64 carry7;
  crypto_int64 carry8;
  crypto_int64 carry9;

  carry0=h0>>26;  // h0
  h1=h1+carry0;
  carry0=carry0<<26;
  h0-=carry0;


  carry1=h1>>25;  // h1
  h2=h2+carry1;
  carry1=carry1<<25;
  h1-=carry1;
 
  carry2=h2>>26;  // h2
  h3=h3+carry2;
  carry2=carry2<<26;
  h2-=carry2;


  carry3=h3>>25;  // h3
  h4=h4+carry3;
  carry3=carry3<<25;
  h3-=carry3;

  carry4=h4>>26;  // h4
  h5=h5+carry4;
  carry4=carry4<<26;
  h4-=carry4;

  carry5=h5>>25;  // h5
  h6=h6+carry5;
  carry5=carry5<<25;
  h5-=carry5;

  carry6=h6>>26;  // h6
  h7=h7+carry6;
  carry6=carry6<<26;
  h6-=carry6;

   carry7=h7>>25;  // h7
   h8=h8+carry7;
   carry7=carry7<<25;
   h7-=carry7;

   carry8=h8>>26;  // h8
   h9=h9+carry8;
   carry8=carry8<<26;
   h8-=carry8;

   carry9=h9>>25;  // h9
   h0=h0+19*carry9;
   carry9=carry9<<25;
   h9-=carry9;

   carry0=h0>>26;  //h0
   h1=h1+carry0;
   carry0=carry0<<26;
   h0-=carry0;
   carry1=h1>>25;    //h1
   h2=h2+carry1;
   carry1=carry1<<25;
   h1-=carry1;

  h[0] = h0;
  h[1] = h1;
  h[2] = h2;
  h[3] = h3;
  h[4] = h4;
  h[5] = h5;
  h[6] = h6;
  h[7] = h7;
  h[8] = h8;
  h[9] = h9;
}




/*
h = -f

Preconditions:
   |f| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.

Postconditions:
   |h| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
*/


void fe_neg(fe h,const fe f) {
    crypto_int32  d = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
    crypto_int32  m = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int32 h0 = 2*(m-19)-f0;
    crypto_int32 h1 = 2*(d-1)-f1;
    crypto_int32 h2 = 2*(m-1)-f2;
    crypto_int32 h3 = 2*(d-1)-f3;
    crypto_int32 h4 = 2*(m-1)-f4;
    crypto_int32 h5 = 2*(d-1)-f5;
    crypto_int32 h6 = 2*(m-1)-f6;
    crypto_int32 h7 = 2*(d-1)-f7;
    crypto_int32 h8 = 2*(m-1)-f8;
    crypto_int32 h9 = 2*(d-1)-f9;

    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
    h[5] = h5;
    h[6] = h6;
    h[7] = h7;
    h[8] = h8;
    h[9] = h9;
}
void fe_pow22523(fe out, const fe z) {
    fe t0;
    fe t1;
    fe t2;
    int i;
    fe_sq(t0, z);

    for (i = 1; i < 1; ++i) {
        fe_sq(t0, t0);
    }

    fe_sq(t1, t0);

    for (i = 1; i < 2; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, z, t1);
    fe_mul(t0, t0, t1);
    fe_sq(t0, t0);

    for (i = 1; i < 1; ++i) {
        fe_sq(t0, t0);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t1, t0);

    for (i = 1; i < 5; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t1, t0);

    for (i = 1; i < 10; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, t1, t0);
    fe_sq(t2, t1);

    for (i = 1; i < 20; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t1, t1);

    for (i = 1; i < 10; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t1, t0);

    for (i = 1; i < 50; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, t1, t0);
    fe_sq(t2, t1);

    for (i = 1; i < 100; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t1, t1);

    for (i = 1; i < 50; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t0, t0);

    for (i = 1; i < 2; ++i) {
        fe_sq(t0, t0);
    }

    fe_mul(out, t0, z);
    return;
}


/*
h = f * f
Can overlap h with f.

Preconditions:
   |f| bounded by 1.65*2^26,1.65*2^25,1.65*2^26,1.65*2^25,etc.

Postconditions:
   |h| bounded by 1.01*2^25,1.01*2^24,1.01*2^25,1.01*2^24,etc.
*/

/*
See fe_mul.c for discussion of implementation strategy.
*/

void fe_sq(fe h, const fe f) {
  crypto_int32 f0 = f[0];
  crypto_int32 f1 = f[1];
  crypto_int32 f2 = f[2];
  crypto_int32 f3 = f[3];
  crypto_int32 f4 = f[4];
  crypto_int32 f5 = f[5];
  crypto_int32 f6 = f[6];
  crypto_int32 f7 = f[7];
  crypto_int32 f8 = f[8];
  crypto_int32 f9 = f[9];
  crypto_int32 f1_19 = 19 * f1; /* 1.4*2^29 */
  crypto_int32 f2_19 = 19 * f2; /* 1.4*2^30; still ok */
  crypto_int32 f3_19 = 19 * f3;
  crypto_int32 f4_19 = 19 * f4;
  crypto_int32 f5_19 = 19 * f5;
  crypto_int32 f6_19 = 19 * f6;
  crypto_int32 f7_19 = 19 * f7;
  crypto_int32 f8_19 = 19 * f8;
  crypto_int32 f9_19 = 19 * f9;
  crypto_int32 f1_2 = 2 * f1;
  crypto_int32 f3_2 = 2 * f3;
  crypto_int32 f5_2 = 2 * f5;
  crypto_int32 f7_2 = 2 * f7;
  crypto_int32 f9_2 = 2 * f9;
  crypto_int64 f0f0    = f0   * (crypto_int64) f0;
  crypto_int64 f0f1    = f0   * (crypto_int64) f1;
  crypto_int64 f0f2    = f0   * (crypto_int64) f2;
  crypto_int64 f0f3    = f0   * (crypto_int64) f3;
  crypto_int64 f0f4    = f0   * (crypto_int64) f4;
  crypto_int64 f0f5    = f0   * (crypto_int64) f5;
  crypto_int64 f0f6    = f0   * (crypto_int64) f6;
  crypto_int64 f0f7    = f0   * (crypto_int64) f7;
  crypto_int64 f0f8    = f0   * (crypto_int64) f8;
  crypto_int64 f0f9    = f0   * (crypto_int64) f9;
  crypto_int64 f1f1_2  = f1_2 * (crypto_int64) f1;
  crypto_int64 f1f2    = f1   * (crypto_int64) f2;
  crypto_int64 f1f3_2  = f1_2 * (crypto_int64) f3;
  crypto_int64 f1f4    = f1   * (crypto_int64) f4;
  crypto_int64 f1f5_2  = f1_2 * (crypto_int64) f5;
  crypto_int64 f1f6    = f1   * (crypto_int64) f6;
  crypto_int64 f1f7_2  = f1_2 * (crypto_int64) f7;
  crypto_int64 f1f8    = f1   * (crypto_int64) f8;
  crypto_int64 f1f9_38 = f1_2 * (crypto_int64) f9_19;
  crypto_int64 f2f2    = f2   * (crypto_int64) f2;
  crypto_int64 f2f3    = f2   * (crypto_int64) f3;
  crypto_int64 f2f4    = f2   * (crypto_int64) f4;
  crypto_int64 f2f5    = f2   * (crypto_int64) f5;
  crypto_int64 f2f6    = f2   * (crypto_int64) f6;
  crypto_int64 f2f7    = f2   * (crypto_int64) f7;
  crypto_int64 f2f8_19 = f2   * (crypto_int64) f8_19;
  crypto_int64 f2f9_19 = f2   * (crypto_int64) f9_19;
  crypto_int64 f3f1_2  = f3_2 * (crypto_int64) f1;
  crypto_int64 f3f3_2  = f3_2 * (crypto_int64) f3;
  crypto_int64 f3f4    = f3   * (crypto_int64) f4;
  crypto_int64 f3f5_2  = f3_2 * (crypto_int64) f5;
  crypto_int64 f3f6    = f3   * (crypto_int64) f6;
  crypto_int64 f3f7_38 = f3_2 * (crypto_int64) f7_19;
  crypto_int64 f3f8_19 = f3   * (crypto_int64) f8_19;
  crypto_int64 f3f9_38 = f3_2 * (crypto_int64) f9_19;
  crypto_int64 f4f4    = f4   * (crypto_int64) f4;
  crypto_int64 f4f5    = f4   * (crypto_int64) f5;
  crypto_int64 f4f6_19 = f4   * (crypto_int64) f6_19;
  crypto_int64 f4f7_19 = f4   * (crypto_int64) f7_19;
  crypto_int64 f4f8_19 = f4   * (crypto_int64) f8_19;
  crypto_int64 f4f9_19 = f4   * (crypto_int64) f9_19;
  crypto_int64 f5f1_2  = f5_2 * (crypto_int64) f1;
  crypto_int64 f5f3_2  = f5_2 * (crypto_int64) f3;
  crypto_int64 f5f5_38 = f5_2 * (crypto_int64) f5_19;
  crypto_int64 f5f6_19 = f5   * (crypto_int64) f6_19;
  crypto_int64 f5f7_38 = f5_2 * (crypto_int64) f7_19;
  crypto_int64 f5f8_19 = f5   * (crypto_int64) f8_19;
  crypto_int64 f5f9_38 = f5_2 * (crypto_int64) f9_19;
  crypto_int64 f6f4_19 = f6   * (crypto_int64) f4_19;
  crypto_int64 f6f5_19 = f6   * (crypto_int64) f5_19;
  crypto_int64 f6f6_19 = f6   * (crypto_int64) f6_19;
  crypto_int64 f6f7_19 = f6   * (crypto_int64) f7_19;
  crypto_int64 f6f8_19 = f6   * (crypto_int64) f8_19;
  crypto_int64 f6f9_19 = f6   * (crypto_int64) f9_19;
  crypto_int64 f7f1_2  = f7_2 * (crypto_int64) f1;
  crypto_int64 f7f3_38 = f7_2 * (crypto_int64) f3_19;
  crypto_int64 f7f4_19 = f7   * (crypto_int64) f4_19;
  crypto_int64 f7f5_38 = f7_2 * (crypto_int64) f5_19;
  crypto_int64 f7f6_19 = f7   * (crypto_int64) f6_19;
  crypto_int64 f7f7_38 = f7_2 * (crypto_int64) f7_19;
  crypto_int64 f7f8_19 = f7   * (crypto_int64) f8_19;
  crypto_int64 f7f9_38 = f7_2 * (crypto_int64) f9_19;
  crypto_int64 f8f2_19 = f8   * (crypto_int64) f2_19;
  crypto_int64 f8f3_19 = f8   * (crypto_int64) f3_19;
  crypto_int64 f8f4_19 = f8   * (crypto_int64) f4_19;
  crypto_int64 f8f5_19 = f8   * (crypto_int64) f5_19;
  crypto_int64 f8f6_19 = f8   * (crypto_int64) f6_19;
  crypto_int64 f8f7_19 = f8   * (crypto_int64) f7_19;
  crypto_int64 f8f8_19 = f8   * (crypto_int64) f8_19;
  crypto_int64 f8f9_19 = f8   * (crypto_int64) f9_19;
  crypto_int64 f9f1_38 = f9_2 * (crypto_int64) f1_19;
  crypto_int64 f9f2_19 = f9   * (crypto_int64) f2_19;
  crypto_int64 f9f3_38 = f9_2 * (crypto_int64) f3_19;
  crypto_int64 f9f4_19 = f9   * (crypto_int64) f4_19;
  crypto_int64 f9f5_38 = f9_2 * (crypto_int64) f5_19;
  crypto_int64 f9f6_19 = f9   * (crypto_int64) f6_19;
  crypto_int64 f9f7_38 = f9_2 * (crypto_int64) f7_19;
  crypto_int64 f9f8_19 = f9   * (crypto_int64) f8_19;
  crypto_int64 f9f9_38 = f9_2 * (crypto_int64) f9_19;
  crypto_int64 h0 = f0f0+f1f9_38+f2f8_19+f3f7_38+f4f6_19+f5f5_38+f6f4_19+f7f3_38+f8f2_19+f9f1_38;
  crypto_int64 h1 = 2*f0f1+f2f9_19+f3f8_19+f4f7_19+f5f6_19+f6f5_19+f7f4_19+f8f3_19+f9f2_19;
  crypto_int64 h2 = 2*f0f2+f1f1_2 +f3f9_38+f4f8_19+f5f7_38+f6f6_19+f7f5_38+f8f4_19+f9f3_38;
  crypto_int64 h3 = 2*(f0f3+f1f2)  +f4f9_19+f5f8_19+f6f7_19+f7f6_19+f8f5_19+f9f4_19;
  crypto_int64 h4 = 2*f0f4+f1f3_2 +f2f2   +f3f1_2 +f5f9_38+f6f8_19+f7f7_38+f8f6_19+f9f5_38;
  crypto_int64 h5 = 2*(f0f5+f1f4   +f2f3)   +f6f9_19+f7f8_19+f8f7_19+f9f6_19;
  crypto_int64 h6 = 2*(f0f6+f2f4)+f1f5_2    +f3f3_2    +f5f1_2    +f7f9_38+f8f8_19+f9f7_38;
  crypto_int64 h7 = 2*(f0f7+f1f6   +f2f5   +f3f4)  +f8f9_19+f9f8_19;
  crypto_int64 h8 = 2*(f0f8+f2f6)+f1f7_2    +f3f5_2 +f4f4   +f5f3_2    +f7f1_2 +f9f9_38;
  crypto_int64 h9 = 2*(f0f9+f1f8   +f2f7   +f3f6   +f4f5 ) ;
  crypto_int64 carry0;
  crypto_int64 carry1;
  crypto_int64 carry2;
  crypto_int64 carry3;
  crypto_int64 carry4;
  crypto_int64 carry5;
  crypto_int64 carry6;
  crypto_int64 carry7;
  crypto_int64 carry8;
  crypto_int64 carry9;

  carry0=h0>>26;  // h0
  h1=h1+carry0;
  carry0=carry0<<26;
  h0-=carry0;


  carry1=h1>>25;  // h1
  h2=h2+carry1;
  carry1=carry1<<25;
  h1-=carry1;
 
  carry2=h2>>26;  // h2
  h3=h3+carry2;
  carry2=carry2<<26;
  h2-=carry2;


  carry3=h3>>25;  // h3
  h4=h4+carry3;
  carry3=carry3<<25;
  h3-=carry3;

  carry4=h4>>26;  // h4
  h5=h5+carry4;
  carry4=carry4<<26;
  h4-=carry4;

  carry5=h5>>25;  // h5
  h6=h6+carry5;
  carry5=carry5<<25;
  h5-=carry5;

  carry6=h6>>26;  // h6
  h7=h7+carry6;
  carry6=carry6<<26;
  h6-=carry6;

   carry7=h7>>25;  // h7
   h8=h8+carry7;
   carry7=carry7<<25;
   h7-=carry7;

   carry8=h8>>26;  // h8
   h9=h9+carry8;
   carry8=carry8<<26;
   h8-=carry8;

   carry9=h9>>25;  // h9
   h0=h0+19*carry9;
   carry9=carry9<<25;
   h9-=carry9;

   carry0=h0>>26;  //h0
   h1=h1+carry0;
   carry0=carry0<<26;
   h0-=carry0;
   carry1=h1>>25;    //h1
   h2=h2+carry1;
   carry1=carry1<<25;
   h1-=carry1;

  h[0] = h0;
  h[1] = h1;
  h[2] = h2;
  h[3] = h3;
  h[4] = h4;
  h[5] = h5;
  h[6] = h6;
  h[7] = h7;
  h[8] = h8;
  h[9] = h9;
}


/*
h = 2 * f * f
Can overlap h with f.

Preconditions:
   |f| bounded by 1.65*2^26,1.65*2^25,1.65*2^26,1.65*2^25,etc.

Postconditions:
   |h| bounded by 1.01*2^25,1.01*2^24,1.01*2^25,1.01*2^24,etc.
*/

/*
See fe_mul.c for discussion of implementation strategy.
*/

void fe_sq2(fe h, const fe f) {
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int32 f0_2 = 2 * f0;
    crypto_int32 f1_2 = 2 * f1;
    crypto_int32 f2_2 = 2 * f2;
    crypto_int32 f3_2 = 2 * f3;
    crypto_int32 f4_2 = 2 * f4;
    crypto_int32 f5_2 = 2 * f5;
    crypto_int32 f6_2 = 2 * f6;
    crypto_int32 f7_2 = 2 * f7;
    crypto_int32 f5_38 = 38 * f5; /* 1.959375*2^30 */
    crypto_int32 f6_19 = 19 * f6; /* 1.959375*2^30 */
    crypto_int32 f7_38 = 38 * f7; /* 1.959375*2^30 */
    crypto_int32 f8_19 = 19 * f8; /* 1.959375*2^30 */
    crypto_int32 f9_38 = 38 * f9; /* 1.959375*2^30 */
    crypto_int64 f0f0    = f0   * (crypto_int64) f0;
    crypto_int64 f0f1_2  = f0_2 * (crypto_int64) f1;
    crypto_int64 f0f2_2  = f0_2 * (crypto_int64) f2;
    crypto_int64 f0f3_2  = f0_2 * (crypto_int64) f3;
    crypto_int64 f0f4_2  = f0_2 * (crypto_int64) f4;
    crypto_int64 f0f5_2  = f0_2 * (crypto_int64) f5;
    crypto_int64 f0f6_2  = f0_2 * (crypto_int64) f6;
    crypto_int64 f0f7_2  = f0_2 * (crypto_int64) f7;
    crypto_int64 f0f8_2  = f0_2 * (crypto_int64) f8;
    crypto_int64 f0f9_2  = f0_2 * (crypto_int64) f9;
    crypto_int64 f1f1_2  = f1_2 * (crypto_int64) f1;
    crypto_int64 f1f2_2  = f1_2 * (crypto_int64) f2;
    crypto_int64 f1f3_4  = f1_2 * (crypto_int64) f3_2;
    crypto_int64 f1f4_2  = f1_2 * (crypto_int64) f4;
    crypto_int64 f1f5_4  = f1_2 * (crypto_int64) f5_2;
    crypto_int64 f1f6_2  = f1_2 * (crypto_int64) f6;
    crypto_int64 f1f7_4  = f1_2 * (crypto_int64) f7_2;
    crypto_int64 f1f8_2  = f1_2 * (crypto_int64) f8;
    crypto_int64 f1f9_76 = f1_2 * (crypto_int64) f9_38;
    crypto_int64 f2f2    = f2   * (crypto_int64) f2;
    crypto_int64 f2f3_2  = f2_2 * (crypto_int64) f3;
    crypto_int64 f2f4_2  = f2_2 * (crypto_int64) f4;
    crypto_int64 f2f5_2  = f2_2 * (crypto_int64) f5;
    crypto_int64 f2f6_2  = f2_2 * (crypto_int64) f6;
    crypto_int64 f2f7_2  = f2_2 * (crypto_int64) f7;
    crypto_int64 f2f8_38 = f2_2 * (crypto_int64) f8_19;
    crypto_int64 f2f9_38 = f2   * (crypto_int64) f9_38;
    crypto_int64 f3f3_2  = f3_2 * (crypto_int64) f3;
    crypto_int64 f3f4_2  = f3_2 * (crypto_int64) f4;
    crypto_int64 f3f5_4  = f3_2 * (crypto_int64) f5_2;
    crypto_int64 f3f6_2  = f3_2 * (crypto_int64) f6;
    crypto_int64 f3f7_76 = f3_2 * (crypto_int64) f7_38;
    crypto_int64 f3f8_38 = f3_2 * (crypto_int64) f8_19;
    crypto_int64 f3f9_76 = f3_2 * (crypto_int64) f9_38;
    crypto_int64 f4f4    = f4   * (crypto_int64) f4;
    crypto_int64 f4f5_2  = f4_2 * (crypto_int64) f5;
    crypto_int64 f4f6_38 = f4_2 * (crypto_int64) f6_19;
    crypto_int64 f4f7_38 = f4   * (crypto_int64) f7_38;
    crypto_int64 f4f8_38 = f4_2 * (crypto_int64) f8_19;
    crypto_int64 f4f9_38 = f4   * (crypto_int64) f9_38;
    crypto_int64 f5f5_38 = f5   * (crypto_int64) f5_38;
    crypto_int64 f5f6_38 = f5_2 * (crypto_int64) f6_19;
    crypto_int64 f5f7_76 = f5_2 * (crypto_int64) f7_38;
    crypto_int64 f5f8_38 = f5_2 * (crypto_int64) f8_19;
    crypto_int64 f5f9_76 = f5_2 * (crypto_int64) f9_38;
    crypto_int64 f6f6_19 = f6   * (crypto_int64) f6_19;
    crypto_int64 f6f7_38 = f6   * (crypto_int64) f7_38;
    crypto_int64 f6f8_38 = f6_2 * (crypto_int64) f8_19;
    crypto_int64 f6f9_38 = f6   * (crypto_int64) f9_38;
    crypto_int64 f7f7_38 = f7   * (crypto_int64) f7_38;
    crypto_int64 f7f8_38 = f7_2 * (crypto_int64) f8_19;
    crypto_int64 f7f9_76 = f7_2 * (crypto_int64) f9_38;
    crypto_int64 f8f8_19 = f8   * (crypto_int64) f8_19;
    crypto_int64 f8f9_38 = f8   * (crypto_int64) f9_38;
    crypto_int64 f9f9_38 = f9   * (crypto_int64) f9_38;
    crypto_int64 h0 = f0f0  + f1f9_76 + f2f8_38 + f3f7_76 + f4f6_38 + f5f5_38;
    crypto_int64 h1 = f0f1_2 + f2f9_38 + f3f8_38 + f4f7_38 + f5f6_38;
    crypto_int64 h2 = f0f2_2 + f1f1_2 + f3f9_76 + f4f8_38 + f5f7_76 + f6f6_19;
    crypto_int64 h3 = f0f3_2 + f1f2_2 + f4f9_38 + f5f8_38 + f6f7_38;
    crypto_int64 h4 = f0f4_2 + f1f3_4 + f2f2   + f5f9_76 + f6f8_38 + f7f7_38;
    crypto_int64 h5 = f0f5_2 + f1f4_2 + f2f3_2 + f6f9_38 + f7f8_38;
    crypto_int64 h6 = f0f6_2 + f1f5_4 + f2f4_2 + f3f3_2 + f7f9_76 + f8f8_19;
    crypto_int64 h7 = f0f7_2 + f1f6_2 + f2f5_2 + f3f4_2 + f8f9_38;
    crypto_int64 h8 = f0f8_2 + f1f7_4 + f2f6_2 + f3f5_4 + f4f4   + f9f9_38;
    crypto_int64 h9 = f0f9_2 + f1f8_2 + f2f7_2 + f3f6_2 + f4f5_2;
    crypto_int64 carry0;
    crypto_int64 carry1;
    crypto_int64 carry2;
    crypto_int64 carry3;
    crypto_int64 carry4;
    crypto_int64 carry5;
    crypto_int64 carry6;
    crypto_int64 carry7;
    crypto_int64 carry8;
    crypto_int64 carry9;
    h0 += h0;
    h1 += h1;
    h2 += h2;
    h3 += h3;
    h4 += h4;
    h5 += h5;
    h6 += h6;
    h7 += h7;
    h8 += h8;
    h9 += h9;
    carry0 = (h0 + (crypto_int64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    carry4 = (h4 + (crypto_int64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry1 = (h1 + (crypto_int64) (1 << 24)) >> 25;
    h2 += carry1;
    h1 -= carry1 << 25;
    carry5 = (h5 + (crypto_int64) (1 << 24)) >> 25;
    h6 += carry5;
    h5 -= carry5 << 25;
    carry2 = (h2 + (crypto_int64) (1 << 25)) >> 26;
    h3 += carry2;
    h2 -= carry2 << 26;
    carry6 = (h6 + (crypto_int64) (1 << 25)) >> 26;
    h7 += carry6;
    h6 -= carry6 << 26;
    carry3 = (h3 + (crypto_int64) (1 << 24)) >> 25;
    h4 += carry3;
    h3 -= carry3 << 25;
    carry7 = (h7 + (crypto_int64) (1 << 24)) >> 25;
    h8 += carry7;
    h7 -= carry7 << 25;
    carry4 = (h4 + (crypto_int64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry8 = (h8 + (crypto_int64) (1 << 25)) >> 26;
    h9 += carry8;
    h8 -= carry8 << 26;
    carry9 = (h9 + (crypto_int64) (1 << 24)) >> 25;
    h0 += carry9 * 19;
    h9 -= carry9 << 25;
    carry0 = (h0 + (crypto_int64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    h[0] = (crypto_int32) h0;
    h[1] = (crypto_int32) h1;
    h[2] = (crypto_int32) h2;
    h[3] = (crypto_int32) h3;
    h[4] = (crypto_int32) h4;
    h[5] = (crypto_int32) h5;
    h[6] = (crypto_int32) h6;
    h[7] = (crypto_int32) h7;
    h[8] = (crypto_int32) h8;
    h[9] = (crypto_int32) h9;
}


/*
h = f - g
Can overlap h with f or g.

Preconditions:
   |f| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
   |g| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.

Postconditions:
   |h| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

void fe_sub(fe h, const fe f, const fe g) {
    crypto_int32  d = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
    crypto_int32  m = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
    crypto_int32 f0 = f[0];
    crypto_int32 f1 = f[1];
    crypto_int32 f2 = f[2];
    crypto_int32 f3 = f[3];
    crypto_int32 f4 = f[4];
    crypto_int32 f5 = f[5];
    crypto_int32 f6 = f[6];
    crypto_int32 f7 = f[7];
    crypto_int32 f8 = f[8];
    crypto_int32 f9 = f[9];
    crypto_int32 g0 = g[0];
    crypto_int32 g1 = g[1];
    crypto_int32 g2 = g[2];
    crypto_int32 g3 = g[3];
    crypto_int32 g4 = g[4];
    crypto_int32 g5 = g[5];
    crypto_int32 g6 = g[6];
    crypto_int32 g7 = g[7];
    crypto_int32 g8 = g[8];
    crypto_int32 g9 = g[9];
    crypto_int64 h0 = f0+(m-19)-g0;
    crypto_int64 h1 = f1+(d-1)-g1;
    crypto_int64 h2 = f2+(m-1)-g2;
    crypto_int64 h3 = f3+(d-1)-g3;
    crypto_int64 h4 = f4+(m-1)-g4;
    crypto_int64 h5 = f5+(d-1)-g5;
    crypto_int64 h6 = f6+(m-1)-g6;
    crypto_int64 h7 = f7+(d-1)-g7;
    crypto_int64 h8 = f8+(m-1)-g8;
    crypto_int64 h9 = f9+(d-1)-g9;


  
    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
    h[5] = h5;
    h[6] = h6;
    h[7] = h7;
    h[8] = h8;
    h[9] = h9;
}



/*
Preconditions:
  |h| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.

Write p=2^255-19; q=floor(h/p).
Basic claim: q = floor(2^(-255)(h + 19 2^(-25)h9 + 2^(-1))).

Proof:
  Have |h|<=p so |q|<=1 so |19^2 2^(-255) q|<1/4.
  Also have |h-2^230 h9|<2^231 so |19 2^(-255)(h-2^230 h9)|<1/4.

  Write y=2^(-1)-19^2 2^(-255)q-19 2^(-255)(h-2^230 h9).
  Then 0<y<1.

  Write r=h-pq.
  Have 0<=r<=p-1=2^255-20.
  Thus 0<=r+19(2^-255)r<r+19(2^-255)2^255<=2^255-1.

  Write x=r+19(2^-255)r+y.
  Then 0<x<2^255 so floor(2^(-255)x) = 0 so floor(q+2^(-255)x) = q.

  Have q+2^(-255)x = 2^(-255)(h + 19 2^(-25) h9 + 2^(-1))
  so floor(2^(-255)(h + 19 2^(-25) h9 + 2^(-1))) = q.
*/
void fe_tobytes(unsigned char *s, const fe h) {
    int32_t h0 = h[0];
    int32_t h1 = h[1];
    int32_t h2 = h[2];
    int32_t h3 = h[3];
    int32_t h4 = h[4];
    int32_t h5 = h[5];
    int32_t h6 = h[6];
    int32_t h7 = h[7];
    int32_t h8 = h[8];
    int32_t h9 = h[9];

    s[0] = (unsigned char) (h0 >> 0);
    s[1] = (unsigned char) (h0 >> 8);
    s[2] = (unsigned char) (h0 >> 16);
    s[3] = (unsigned char) ((h0 >> 24) | (h1 << 2));
    s[4] = (unsigned char) (h1 >> 6);
    s[5] = (unsigned char) (h1 >> 14);
    s[6] = (unsigned char) ((h1 >> 22) | (h2 << 3));
    s[7] = (unsigned char) (h2 >> 5);
    s[8] = (unsigned char) (h2 >> 13);
    s[9] = (unsigned char) ((h2 >> 21) | (h3 << 5));
    s[10] = (unsigned char) (h3 >> 3);
    s[11] = (unsigned char) (h3 >> 11);
    s[12] = (unsigned char) ((h3 >> 19) | (h4 << 6));
    s[13] = (unsigned char) (h4 >> 2);
    s[14] = (unsigned char) (h4 >> 10);
    s[15] = (unsigned char) (h4 >> 18);
    s[16] = (unsigned char) (h5 >> 0);
    s[17] = (unsigned char) (h5 >> 8);
    s[18] = (unsigned char) (h5 >> 16);
    s[19] = (unsigned char) ((h5 >> 24) | (h6 << 1));
    s[20] = (unsigned char) (h6 >> 7);
    s[21] = (unsigned char) (h6 >> 15);
    s[22] = (unsigned char) ((h6 >> 23) | (h7 << 3));
    s[23] = (unsigned char) (h7 >> 5);
    s[24] = (unsigned char) (h7 >> 13);
    s[25] = (unsigned char) ((h7 >> 21) | (h8 << 4));
    s[26] = (unsigned char) (h8 >> 4);
    s[27] = (unsigned char) (h8 >> 12);
    s[28] = (unsigned char) ((h8 >> 20) | (h9 << 6));
    s[29] = (unsigned char) (h9 >> 2);
    s[30] = (unsigned char) (h9 >> 10);
    s[31] = (unsigned char) (h9 >> 18);
}

void fe_to64bit(argElement_1w s, const fe h)
{
     unsigned long long h0 = h[0];
     unsigned long long h1 = h[1];
     unsigned long long h2 = h[2];
     unsigned long long h3 = h[3];
     unsigned long long h4 = h[4];
     unsigned long long h5 = h[5];
     unsigned long long h6 = h[6];
     unsigned long long h7 = h[7];
     unsigned long long h8 = h[8];
     unsigned long long h9 = h[9];
    s[0] = h0|(h1<<26)|((h2&0x1fff)<<51);
    s[1] = (h2>>13)|(h3<<13)|(h4<<38);
    s[2] = h5|(h6<<25)|(h7&0x1fff)<<51;
    s[3] = (h7>>12)|(h8<<12)|h9;
   
}

void fe_64tobytes(unsigned char  *s, argElement_1w a)
{
    
    unsigned long long a0 = a[0];
    unsigned long long a1 = a[1];
    unsigned long long a2 = a[2];
    unsigned long long a3 = a[3];
    s[0] = (unsigned char)(a0>>0);
    s[1] = (unsigned char)(a0>>8);
    s[2] = (unsigned char)(a0>>16);
    s[3] = (unsigned char)(a0>>24);
    s[4] = (unsigned char)(a0>>32);
    s[5] = (unsigned char)(a0>>40);
    s[6] = (unsigned char)(a0>>48);
    s[7] = (unsigned char)(a0>>56);
    s[8] = (unsigned char)(a1>>0);
    s[9] = (unsigned char)(a1>>8);
    s[10] = (unsigned char)(a1>>16);
    s[11] = (unsigned char)(a1>>24);
    s[12] = (unsigned char)(a1>>32);
    s[13] = (unsigned char)(a1>>40);
    s[14] = (unsigned char)(a1>>48);
    s[15] = (unsigned char)(a1>>56);
    s[16] = (unsigned char)(a2>>0);
    s[17] = (unsigned char)(a2>>8);
    s[18] = (unsigned char)(a2>>16);
    s[19] = (unsigned char)(a2>>24);
    s[20] = (unsigned char)(a2>>32);
    s[21] = (unsigned char)(a2>>40);
    s[22] = (unsigned char)(a2>>48);
    s[23] = (unsigned char)(a2>>56);
    s[24] = (unsigned char)(a3>>0);
    s[25] = (unsigned char)(a3>>8);
    s[26] = (unsigned char)(a3>>16);
    s[27] = (unsigned char)(a3>>24);
    s[28] = (unsigned char)(a3>>32);
    s[29] = (unsigned char)(a3>>40);
    s[30] = (unsigned char)(a3>>48);
    s[31] = (unsigned char)(a3>>56);
}



void intmul_mulxadx(argElement_1w c, argElement_1w a, argElement_1w b) {
  __asm__ __volatile__(
  "movq   (%1), %%rdx; " /* A[0] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[0]*B[0] */    "xorl %%r10d, %%r10d ;"                           "movq  %%r8,  (%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[0]*B[1] */    "adox  %%r9, %%r10 ;"                             "movq %%r10, 8(%0) ;"
  "mulx 16(%2), %%r12, %%r13; " /* A[0]*B[2] */    "adox %%r11, %%r12 ;"
  "mulx 24(%2), %%r14, %%rdx; " /* A[0]*B[3] */    "adox %%r13, %%r14 ;"                                                       "movq $0, %%rax ;"
  /*******************************************/    "adox %%rdx, %%rax ;"

  "movq  8(%1), %%rdx; " /* A[1] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[1]*B[0] */    "xorl %%r10d, %%r10d ;"  "adcx 8(%0),  %%r8 ;"    "movq  %%r8,  8(%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[1]*B[1] */    "adox  %%r9, %%r10 ;"    "adcx %%r12, %%r10 ;"    "movq %%r10, 16(%0) ;"
  "mulx 16(%2), %%r12, %%r13; " /* A[1]*B[2] */    "adox %%r11, %%r12 ;"    "adcx %%r14, %%r12 ;"                              "movq $0, %%r8  ;"
  "mulx 24(%2), %%r14, %%rdx; " /* A[1]*B[3] */    "adox %%r13, %%r14 ;"    "adcx %%rax, %%r14 ;"                              "movq $0, %%rax ;"
  /*******************************************/    "adox %%rdx, %%rax ;"    "adcx  %%r8, %%rax ;"

  "movq 16(%1), %%rdx; " /* A[2] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[2]*B[0] */    "xorl %%r10d, %%r10d ;"  "adcx 16(%0), %%r8 ;"    "movq  %%r8, 16(%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[2]*B[1] */    "adox  %%r9, %%r10 ;"    "adcx %%r12, %%r10 ;"    "movq %%r10, 24(%0) ;"
  "mulx 16(%2), %%r12, %%r13; " /* A[2]*B[2] */    "adox %%r11, %%r12 ;"    "adcx %%r14, %%r12 ;"                              "movq $0, %%r8  ;"
  "mulx 24(%2), %%r14, %%rdx; " /* A[2]*B[3] */    "adox %%r13, %%r14 ;"    "adcx %%rax, %%r14 ;"                              "movq $0, %%rax ;"
  /*******************************************/    "adox %%rdx, %%rax ;"    "adcx  %%r8, %%rax ;"

  "movq 24(%1), %%rdx; " /* A[3] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[3]*B[0] */    "xorl %%r10d, %%r10d ;"  "adcx 24(%0), %%r8 ;"    "movq  %%r8, 24(%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[3]*B[1] */    "adox  %%r9, %%r10 ;"    "adcx %%r12, %%r10 ;"    "movq %%r10, 32(%0) ;"
  "mulx 16(%2), %%r12, %%r13; " /* A[3]*B[2] */    "adox %%r11, %%r12 ;"    "adcx %%r14, %%r12 ;"    "movq %%r12, 40(%0) ;"    "movq $0, %%r8  ;"
  "mulx 24(%2), %%r14, %%rdx; " /* A[3]*B[3] */    "adox %%r13, %%r14 ;"    "adcx %%rax, %%r14 ;"    "movq %%r14, 48(%0) ;"    "movq $0, %%rax ;"
  /*******************************************/    "adox %%rdx, %%rax ;"    "adcx  %%r8, %%rax ;"    "movq %%rax, 56(%0) ;"
  :
  : "r" (c), "r" (a), "r" (b)
  : "memory", "cc", "%rax", "%rdx", "%r8",
  "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"
  );
}

void intmul_mulx(argElement_1w c, argElement_1w a, argElement_1w b) 
{
  __asm__ __volatile__(
  "movq   (%1), %%rdx; " /* A[0] */
  "mulx   (%2),  %%r8, %%r12; " /* A[0]*B[0] */                           "movq %%r8,  (%0) ;"
  "mulx  8(%2), %%r10, %%rax; " /* A[0]*B[1] */    "addq %%r10, %%r12 ;"
  "mulx 16(%2),  %%r8, %%rbx; " /* A[0]*B[2] */    "adcq  %%r8, %%rax ;"
  "mulx 24(%2), %%r10, %%rcx; " /* A[0]*B[3] */    "adcq %%r10, %%rbx ;"
  /*******************************************/    "adcq    $0, %%rcx ;"

  "movq  8(%1), %%rdx; " /* A[1] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[1]*B[0] */    "addq %%r12,  %%r8 ;"  "movq %%r8, 8(%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[1]*B[1] */    "adcq %%r10,  %%r9 ;"
  "mulx 16(%2),  %%r8, %%r13; " /* A[1]*B[2] */    "adcq  %%r8, %%r11 ;"
  "mulx 24(%2), %%r10, %%r12; " /* A[1]*B[3] */    "adcq %%r10, %%r13 ;"
  /*******************************************/    "adcq    $0, %%r12 ;"

  "addq  %%r9, %%rax ;"
  "adcq %%r11, %%rbx ;"
  "adcq %%r13, %%rcx ;"
  "adcq    $0, %%r12 ;"

  "movq 16(%1), %%rdx; " /* A[2] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[2]*B[0] */    "addq %%rax,  %%r8 ;"  "movq %%r8, 16(%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[2]*B[1] */    "adcq %%r10,  %%r9 ;"
  "mulx 16(%2),  %%r8, %%r13; " /* A[2]*B[2] */    "adcq  %%r8, %%r11 ;"
  "mulx 24(%2), %%r10, %%rax; " /* A[2]*B[3] */    "adcq %%r10, %%r13 ;"
  /*******************************************/    "adcq    $0, %%rax ;"

  "addq  %%r9, %%rbx ;"
  "adcq %%r11, %%rcx ;"
  "adcq %%r13, %%r12 ;"
  "adcq    $0, %%rax ;"

  "movq 24(%1), %%rdx; " /* A[3] */
  "mulx   (%2),  %%r8,  %%r9; " /* A[3]*B[0] */    "addq %%rbx,  %%r8 ;"  "movq %%r8, 24(%0) ;"
  "mulx  8(%2), %%r10, %%r11; " /* A[3]*B[1] */    "adcq %%r10,  %%r9 ;"
  "mulx 16(%2),  %%r8, %%r13; " /* A[3]*B[2] */    "adcq  %%r8, %%r11 ;"
  "mulx 24(%2), %%r10, %%rbx; " /* A[3]*B[3] */    "adcq %%r10, %%r13 ;"
  /*******************************************/    "adcq    $0, %%rbx ;"

  "addq  %%r9, %%rcx ;"  "movq %%rcx, 32(%0) ;"
  "adcq %%r11, %%r12 ;"  "movq %%r12, 40(%0) ;"
  "adcq %%r13, %%rax ;"  "movq %%rax, 48(%0) ;"
  "adcq    $0, %%rbx ;"  "movq %%rbx, 56(%0) ;"
  :
  : "r" (c), "r" (a), "r" (b)
  : "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx",
  "%r8", "%r9", "%r10", "%r11", "%r12", "%r13"
  );
}


void intmul_mulq(argElement_1w c, argElement_1w a, argElement_1w b) {
  __asm__ __volatile__(
    "movq  0(%2), %%r8;"
	"movq  0(%1), %%rax;" "mulq %%r8;" "movq %%rax, 0(%0);" "movq %%rdx, %%r15;"
	"movq  8(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r13;" "movq %%rdx, %%r10;"
	"movq 16(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r14;" "movq %%rdx, %%r11;"
	"movq 24(%1), %%rax;" "mulq %%r8;"
	"addq %%r13, %%r15;"
	"adcq %%r14, %%r10;"  "movq %%r10, 16(%0);"
	"adcq %%rax, %%r11;"  "movq %%r11, 24(%0);"
	"adcq    $0, %%rdx;"  "movq %%rdx, 32(%0);"
	"movq  8(%2), %%r8;"
	"movq  0(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r12;" "movq %%rdx,  %%r9;"
	"movq  8(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r13;" "movq %%rdx, %%r10;"
	"movq 16(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r14;" "movq %%rdx, %%r11;"
	"movq 24(%1), %%rax;" "mulq %%r8;"
	"addq %%r12, %%r15;" "movq %%r15,  8(%0);"
	"adcq %%r13,  %%r9;"
	"adcq %%r14, %%r10;"
	"adcq %%rax, %%r11;"
	"adcq    $0, %%rdx;"
	"adcq 16(%0),  %%r9;"  "movq  %%r9,  %%r15;"
	"adcq 24(%0), %%r10;"  "movq %%r10, 24(%0);"
	"adcq 32(%0), %%r11;"  "movq %%r11, 32(%0);"
	"adcq     $0, %%rdx;"  "movq %%rdx, 40(%0);"
	"movq 16(%2), %%r8;"
	"movq  0(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r12;" "movq %%rdx,  %%r9;"
	"movq  8(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r13;" "movq %%rdx, %%r10;"
	"movq 16(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r14;" "movq %%rdx, %%r11;"
	"movq 24(%1), %%rax;" "mulq %%r8;"
	"addq %%r12, %%r15;"  "movq %%r15, 16(%0);"
	"adcq %%r13,  %%r9;"
	"adcq %%r14, %%r10;"
	"adcq %%rax, %%r11;"
	"adcq    $0, %%rdx;"
	"adcq 24(%0),  %%r9;"  "movq  %%r9,  %%r15;"
	"adcq 32(%0), %%r10;"  "movq %%r10, 32(%0);"
	"adcq 40(%0), %%r11;"  "movq %%r11, 40(%0);"
	"adcq     $0, %%rdx;"  "movq %%rdx, 48(%0);"
	"movq 24(%2), %%r8;"
	"movq  0(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r12;" "movq %%rdx,  %%r9;"
	"movq  8(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r13;" "movq %%rdx, %%r10;"
	"movq 16(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r14;" "movq %%rdx, %%r11;"
	"movq 24(%1), %%rax;" "mulq %%r8;"
	"addq %%r12, %%r15;" "movq %%r15, 24(%0);"
	"adcq %%r13,  %%r9;"
	"adcq %%r14, %%r10;"
	"adcq %%rax, %%r11;"
	"adcq    $0, %%rdx;"
	"adcq 32(%0),  %%r9;"  "movq  %%r9, 32(%0);"
	"adcq 40(%0), %%r10;"  "movq %%r10, 40(%0);"
	"adcq 48(%0), %%r11;"  "movq %%r11, 48(%0);"
    "adcq     $0, %%rdx;"  "movq %%rdx, 56(%0);"
  :
  : "r" (c), "r" (a), "r" (b)
  : "memory", "cc", "%rax", "%rdx", "%r8", "%r9",
  "%r10", "%r11", "%r12", "%r13", "%r14", "%r15"
  );
}

void intmul(argElement_1w c, argElement_1w a, argElement_1w b) {
#ifdef __BMI2__
#ifdef __ADX__
  intmul_mulxadx(c,a,b);
#else /* No __ADX__ */
  intmul_mulx(c, a, b);
#endif
#else /* No __BMI2__ */
  intmul_mulq(c,a,b);
#endif
}

void intsqr_mulxadx(argElement_1w c, argElement_1w a) {
  __asm__ __volatile__(
  "movq   (%1), %%rdx        ;" /* A[0]      */
  "mulx  8(%1),  %%r8, %%r14 ;" /* A[1]*A[0] */  "xorl %%r15d, %%r15d;"
  "mulx 16(%1),  %%r9, %%r10 ;" /* A[2]*A[0] */  "adcx %%r14,  %%r9 ;"
  "mulx 24(%1), %%rax, %%rcx ;" /* A[3]*A[0] */  "adcx %%rax, %%r10 ;"
  "movq 24(%1), %%rdx        ;" /* A[3]      */
  "mulx  8(%1), %%r11, %%r12 ;" /* A[1]*A[3] */  "adcx %%rcx, %%r11 ;"
  "mulx 16(%1), %%rax, %%r13 ;" /* A[2]*A[3] */  "adcx %%rax, %%r12 ;"
  "movq  8(%1), %%rdx        ;" /* A[1]      */  "adcx %%r15, %%r13 ;"
  "mulx 16(%1), %%rax, %%rcx ;" /* A[2]*A[1] */  "movq    $0, %%r14 ;"
  /*******************************************/  "adcx %%r15, %%r14 ;"

  "xorl %%r15d, %%r15d;"
  "adox %%rax, %%r10 ;"  "adcx  %%r8,  %%r8 ;"
  "adox %%rcx, %%r11 ;"  "adcx  %%r9,  %%r9 ;"
  "adox %%r15, %%r12 ;"  "adcx %%r10, %%r10 ;"
  "adox %%r15, %%r13 ;"  "adcx %%r11, %%r11 ;"
  "adox %%r15, %%r14 ;"  "adcx %%r12, %%r12 ;"
  "adcx %%r13, %%r13 ;"
  "adcx %%r14, %%r14 ;"

  "movq   (%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[0]^2 */
  /********************/  "movq %%rax,  0(%0) ;"
  "addq %%rcx,  %%r8 ;"   "movq  %%r8,  8(%0) ;"
  "movq  8(%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[1]^2 */
  "adcq %%rax,  %%r9 ;"   "movq  %%r9, 16(%0) ;"
  "adcq %%rcx, %%r10 ;"   "movq %%r10, 24(%0) ;"
  "movq 16(%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[2]^2 */
  "adcq %%rax, %%r11 ;"   "movq %%r11, 32(%0) ;"
  "adcq %%rcx, %%r12 ;"   "movq %%r12, 40(%0) ;"
  "movq 24(%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[3]^2 */
  "adcq %%rax, %%r13 ;"   "movq %%r13, 48(%0) ;"
  "adcq %%rcx, %%r14 ;"   "movq %%r14, 56(%0) ;"
  :
  : "r" (c), "r" (a)
  : "memory", "cc", "%rax", "%rcx", "%rdx",
  "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15"
  );
}


void intsqr_mulx(argElement_1w c, argElement_1w a) {
  __asm__ __volatile__(
  "movq  8(%1), %%rdx        ;" /* A[1]      */
  "mulx   (%1),  %%r8,  %%r9 ;" /* A[0]*A[1] */
  "mulx 16(%1), %%r10, %%r11 ;" /* A[2]*A[1] */
  "mulx 24(%1), %%rcx, %%r14 ;" /* A[3]*A[1] */

  "movq 16(%1), %%rdx        ;" /* A[2]      */
  "mulx 24(%1), %%r12, %%r13 ;" /* A[3]*A[2] */
  "mulx   (%1), %%rax, %%rdx ;" /* A[0]*A[2] */

  "addq %%rax,  %%r9 ;"
  "adcq %%rdx, %%r10 ;"
  "adcq %%rcx, %%r11 ;"
  "adcq %%r14, %%r12 ;"
  "adcq    $0, %%r13 ;"
  "movq    $0, %%r14 ;"
  "adcq    $0, %%r14 ;"

  "movq   (%1), %%rdx        ;" /* A[0]      */
  "mulx 24(%1), %%rax, %%rcx ;" /* A[0]*A[3] */

  "addq %%rax, %%r10 ;"
  "adcq %%rcx, %%r11 ;"
  "adcq    $0, %%r12 ;"
  "adcq    $0, %%r13 ;"
  "adcq    $0, %%r14 ;"

  "shldq $1, %%r13, %%r14 ;"
  "shldq $1, %%r12, %%r13 ;"
  "shldq $1, %%r11, %%r12 ;"
  "shldq $1, %%r10, %%r11 ;"
  "shldq $1,  %%r9, %%r10 ;"
  "shldq $1,  %%r8,  %%r9 ;"
  "shlq  $1,  %%r8        ;"

  /********************/  "mulx %%rdx, %%rax, %%rcx ;" /* A[0]^2 */
  /********************/  "movq %%rax,  0(%0) ;"
  "addq %%rcx,  %%r8 ;"   "movq  %%r8,  8(%0) ;"
  "movq  8(%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[1]^2 */
  "adcq %%rax,  %%r9 ;"   "movq  %%r9, 16(%0) ;"
  "adcq %%rcx, %%r10 ;"   "movq %%r10, 24(%0) ;"
  "movq 16(%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[2]^2 */
  "adcq %%rax, %%r11 ;"   "movq %%r11, 32(%0) ;"
  "adcq %%rcx, %%r12 ;"   "movq %%r12, 40(%0) ;"
  "movq 24(%1), %%rdx ;"  "mulx %%rdx, %%rax, %%rcx ;" /* A[3]^2 */
  "adcq %%rax, %%r13 ;"   "movq %%r13, 48(%0) ;"
  "adcq %%rcx, %%r14 ;"   "movq %%r14, 56(%0) ;"
  :
  : "r" (c), "r" (a)
  : "memory", "cc", "%rax", "%rcx", "%rdx",
  "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14"
  );
}

void intsqr_mulq(argElement_1w c, argElement_1w a) {
  __asm__ __volatile__(
  "movq  0(%1),  %%r8;"
  "movq  8(%1), %%rax;" "mulq %%r8;" "movq %%rax,  %%r9;" "movq %%rdx, %%r10;" /* a[0]*a[1] */
  "movq 16(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r14;" "movq %%rdx, %%r11;" /* a[0]*a[2] */
  "movq 24(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%r15;" "movq %%rdx, %%r12;" /* a[0]*a[3] */
  "movq 24(%1),  %%r8;"
  "movq  8(%1), %%rax;" "mulq %%r8;" "movq %%rax, %%rcx;" "movq %%rdx, %%r13;" /* a[3]*a[1] */
  "movq 16(%1), %%rax;" "mulq %%r8;" /* a[3]*a[2] */

  "addq %%r14, %%r10;"
  "adcq %%r15, %%r11;" "movl $0, %%r15d;"
  "adcq %%rcx, %%r12;"
  "adcq %%rax, %%r13;"
  "adcq    $0, %%rdx;" "movq %%rdx, %%r14;"
  "movq 8(%1), %%rax;" "mulq 16(%1);"

  "addq %%rax, %%r11;"
  "adcq %%rdx, %%r12;"
  "adcq    $0, %%r13;"
  "adcq    $0, %%r14;"
  "adcq    $0, %%r15;"

  "shldq $1, %%r14, %%r15;" "movq %%r15, 56(%0);"
  "shldq $1, %%r13, %%r14;" "movq %%r14, 48(%0);"
  "shldq $1, %%r12, %%r13;" "movq %%r13, 40(%0);"
  "shldq $1, %%r11, %%r12;" "movq %%r12, 32(%0);"
  "shldq $1, %%r10, %%r11;" "movq %%r11, 24(%0);"
  "shldq $1,  %%r9, %%r10;" "movq %%r10, 16(%0);"
  "shlq  $1,  %%r9; "       "movq  %%r9,  8(%0);"

  "movq  0(%1),%%rax;" "mulq %%rax;" "movq %%rax, 0(%0);" "movq %%rdx,  %%r9;"
  "movq  8(%1),%%rax;" "mulq %%rax;" "movq %%rax, %%r10;" "movq %%rdx, %%r11;"
  "movq 16(%1),%%rax;" "mulq %%rax;" "movq %%rax, %%r12;" "movq %%rdx, %%r13;"
  "movq 24(%1),%%rax;" "mulq %%rax;" "movq %%rax, %%r14;" "movq %%rdx, %%r15;"

  "addq  8(%0),  %%r9;" "movq  %%r9,  8(%0);"
  "adcq 16(%0), %%r10;" "movq %%r10, 16(%0);"
  "adcq 24(%0), %%r11;" "movq %%r11, 24(%0);"
  "adcq 32(%0), %%r12;" "movq %%r12, 32(%0);"
  "adcq 40(%0), %%r13;" "movq %%r13, 40(%0);"
  "adcq 48(%0), %%r14;" "movq %%r14, 48(%0);"
  "adcq 56(%0), %%r15;" "movq %%r15, 56(%0);"
  :
  : "r" (c), "r" (a)
  : "memory", "cc", "%rax", "%rcx", "%rdx",
  "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15"
  );
}

void intsqr(argElement_1w c, argElement_1w a)
{
#ifdef __BMI2__
#ifdef __ADX__
  intsqr_mulxadx(c, a);
#else /* No __ADX__ */
  intsqr_mulx(c, a);
#endif
#else /* No __BMI2__ */
  intsqr_mulq(c, a);
#endif
}

void reduce_mulxadx(argElement_1w c, argElement_1w a) {
  __asm__ __volatile__(
  "movl    $38, %%edx ;" /* 2*c = 38 = 2^256 */
  "mulx 32(%1),  %%r8, %%r10 ;" /* c*C[4] */  "xorl %%ebx, %%ebx ;"  "adox   (%1),  %%r8 ;"
  "mulx 40(%1),  %%r9, %%r11 ;" /* c*C[5] */  "adcx %%r10,  %%r9 ;"  "adox  8(%1),  %%r9 ;"
  "mulx 48(%1), %%r10, %%rax ;" /* c*C[6] */  "adcx %%r11, %%r10 ;"  "adox 16(%1), %%r10 ;"
  "mulx 56(%1), %%r11, %%rcx ;" /* c*C[7] */  "adcx %%rax, %%r11 ;"  "adox 24(%1), %%r11 ;"
  /****************************************/  "adcx %%rbx, %%rcx ;"  "adox  %%rbx, %%rcx ;"
  "imul %%rdx, %%rcx ;" /* c*C[4], cf=0, of=0 */
  "adcx %%rcx,  %%r8 ;"
  "adcx %%rbx,  %%r9 ;"  "movq  %%r9,  8(%0) ;"
  "adcx %%rbx, %%r10 ;"  "movq %%r10, 16(%0) ;"
  "adcx %%rbx, %%r11 ;"  "movq %%r11, 24(%0) ;"
  "mov     $0, %%ecx ;"
  "cmovc %%edx, %%ecx ;"
  "addq %%rcx,  %%r8 ;"  "movq  %%r8,   (%0) ;"
  :
  : "r" (c), "r" (a)
  : "memory", "cc", "%rax", "%rbx", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
  );
}

void reduce_mulx(argElement_1w c, argElement_1w a) {
  __asm__ __volatile__(
  "movl    $38, %%edx ;" /* 2*c = 38 = 2^256 */
  "mulx 32(%1),  %%r8, %%r10 ;" /* c*C[4] */
  "mulx 40(%1),  %%r9, %%r11 ;" /* c*C[5] */  "addq %%r10,  %%r9 ;"
  "mulx 48(%1), %%r10, %%rax ;" /* c*C[6] */  "adcq %%r11, %%r10 ;"
  "mulx 56(%1), %%r11, %%rcx ;" /* c*C[7] */  "adcq %%rax, %%r11 ;"
  /****************************************/  "adcq    $0, %%rcx ;"
  "addq   (%1),  %%r8 ;"
  "adcq  8(%1),  %%r9 ;"
  "adcq 16(%1), %%r10 ;"
  "adcq 24(%1), %%r11 ;"
  "adcq     $0, %%rcx ;"
  "imul %%rdx, %%rcx ;" /* c*C[4], cf=0 */
  "addq %%rcx,  %%r8 ;"
  "adcq    $0,  %%r9 ;"  "movq  %%r9,  8(%0) ;"
  "adcq    $0, %%r10 ;"  "movq %%r10, 16(%0) ;"
  "adcq    $0, %%r11 ;"  "movq %%r11, 24(%0) ;"
  "mov     $0, %%ecx ;"
  "cmovc %%edx, %%ecx ;"
  "addq %%rcx,  %%r8 ;"  "movq  %%r8,   (%0) ;"
  :
  : "r" (c), "r" (a)
  : "memory", "cc", "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10", "%r11"
  );
}


void reduce_mulq(argElement_1w c, argElement_1w a) {
  __asm__ __volatile__(
  /* 2*C = 38 = 2^256 */ \
    "movl $38, %%eax;" "mulq 32(%1);" "movq %%rax,  %%r8;" "movq %%rdx,  %%r9;" /* c*c[4] */
    "movl $38, %%eax;" "mulq 40(%1);" "movq %%rax, %%r12;" "movq %%rdx, %%r10;" /* c*c[5] */
    "movl $38, %%eax;" "mulq 48(%1);" "movq %%rax, %%r13;" "movq %%rdx, %%r11;" /* c*c[6] */
    "movl $38, %%eax;" "mulq 56(%1);" /* c*c[7] */
    "addq %%r12,  %%r9;"
    "adcq %%r13, %%r10;"
    "adcq %%rax, %%r11;"
    "adcq    $0, %%rdx;"
    "addq  0(%1),  %%r8;"
    "adcq  8(%1),  %%r9;"
    "adcq 16(%1), %%r10;"
    "adcq 24(%1), %%r11;"
    "adcq     $0, %%rdx;"
    "movl $38, %%eax;"
    "imulq %%rax, %%rdx;" /* c*c[4], cf=0, of=0 */
    "addq  %%rdx,  %%r8;"
    "adcq $0,  %%r9;" "movq  %%r9,  8(%0);"
    "adcq $0, %%r10;" "movq %%r10, 16(%0);"
    "adcq $0, %%r11;" "movq %%r11, 24(%0);"
    "movl $0, %%edx;"
    "cmovc %%rax, %%rdx;"
    "addq %%rdx, %%r8;" "movq %%r8, 0(%0)"
  :
  : "r" (c), "r" (a)
  : "memory", "cc", "%rax", "%rdx", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13"
  );
}
void reduce(argElement_1w c, argElement_1w a) {
#ifdef __BMI2__
#ifdef __ADX__
  reduce_mulxadx(c,a);
#else /* No __ADX__ */
  reduce_mulx(c, a);
#endif
#else /* No __BMI2__ */
  reduce_mulq(c,a);
#endif
}

void mul(argElement_1w c, argElement_1w a, argElement_1w b) {
  EltFp25519_1w_fullradix_buffer buffer_1w;
  intmul(buffer_1w, a, b);
  reduce(c, buffer_1w);
}

void sqr(argElement_1w a) {
  EltFp25519_1w_fullradix_buffer buffer_1w;
  intsqr(buffer_1w, a);
  reduce(a, buffer_1w);
}

void sqrn(argElement_1w a , unsigned int times)
{
  while(times-- >0)
{
   sqr(a);
}
}
void copy(argElement_1w c, argElement_1w a)
 {
  c[0] = a[0];
  c[1] = a[1];
  c[2] = a[2];
  c[3] = a[3];
}

void inv(argElement_1w c, argElement_1w a) {
  EltFp25519_1w_fullradix x0, x1, x2;
  argElement_1w T[5];
  int counter ;

  T[0] = x0;
  T[1] = c; /* x^(-1) */
  T[2] = x1;
  T[3] = x2;
  T[4] = a; /* x */

  copy(T[1], T[4]);
  sqrn(T[1], 1);
  copy(T[2], T[1]);
  sqrn(T[2], 2);
  mul(T[0], T[4], T[2]);
  mul(T[1], T[1], T[0]);
  copy(T[2], T[1]);
  sqrn(T[2], 1);
  mul(T[0], T[0], T[2]);
  copy(T[2], T[0]);
  sqrn(T[2], 5);
  mul(T[0], T[0], T[2]);
  copy(T[2], T[0]);
  sqrn(T[2], 10);
  mul(T[2], T[2], T[0]);
  copy(T[3], T[2]);
  sqrn(T[3], 20);
  mul(T[3], T[3], T[2]);
  sqrn(T[3], 10);
  mul(T[3], T[3], T[0]);
  copy(T[0], T[3]);
  sqrn(T[0], 50);
  mul(T[0], T[0], T[3]);
  copy(T[2], T[0]);
  sqrn(T[2], 100);
  mul(T[2], T[2], T[0]);
  sqrn(T[2], 50);
  mul(T[2], T[2], T[3]);
  sqrn(T[2], 5);
  mul(T[1], T[1], T[2]);
}







