#include "fe4x.h"

#include "fe.h"


crypto_int64 d = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
crypto_int64 m = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;   
void fe4x_sub(fe4x h,const fe4x f,const fe4x g)

{
   
   h[0] = _mm256_sub_epi64 (f[0]+2*(m-19), g[0]);
   h[1] = _mm256_sub_epi64 (f[1]+2*(d-1), g[1]);
   h[2] = _mm256_sub_epi64 (f[2]+2*(m-1), g[2]);
   h[3] = _mm256_sub_epi64 (f[3]+2*(d-1), g[3]);
   h[4] = _mm256_sub_epi64 (f[4]+2*(m-1), g[4]);
   h[5] = _mm256_sub_epi64 (f[5]+2*(d-1), g[5]);
   h[6] = _mm256_sub_epi64 (f[6]+2*(m-1), g[6]);
   h[7] = _mm256_sub_epi64 (f[7]+2*(d-1), g[7]);
   h[8] = _mm256_sub_epi64 (f[8]+2*(m-1), g[8]);
   h[9] = _mm256_sub_epi64 (f[9]+2*(d-1), g[9]); 


fe4x carry;
carry[0] = _mm256_srli_epi64(h[0], 26);

h[1] = _mm256_add_epi64(h[1],carry[0]);
carry[0]=_mm256_slli_epi64(carry[0], 26);

h[0]=_mm256_sub_epi64(h[0],carry[0]);

carry[1] = _mm256_srli_epi64(h[1], 25);  //carry1
h[2] = _mm256_add_epi64(h[2],carry[1]);
carry[1]=_mm256_slli_epi64(carry[1], 25);
h[1]=_mm256_sub_epi64(h[1],carry[1]);


carry[2] = _mm256_srli_epi64(h[2], 26); //carry2
h[3] = _mm256_add_epi64(h[3],carry[2]);
carry[2]=_mm256_slli_epi64 (carry[2], 26);
h[2]=_mm256_sub_epi64(h[2],carry[2]);

carry[3] = _mm256_srli_epi64(h[3], 25); //carry3
h[4] = _mm256_add_epi64(h[4],carry[3]);
carry[3]=_mm256_slli_epi64 (carry[3], 25);
h[3]=_mm256_sub_epi64(h[3],carry[3]);

carry[4] = _mm256_srli_epi64(h[4], 26); //carry4
h[5] = _mm256_add_epi64(h[5],carry[4]);
carry[4]=_mm256_slli_epi64 (carry[4], 26);
h[4]=_mm256_sub_epi64(h[4],carry[4]);

carry[5] = _mm256_srli_epi64(h[5], 25);  //carry5
h[6] = _mm256_add_epi64(h[6],carry[5]);
carry[5]=_mm256_slli_epi64 (carry[5], 25);
h[5]=_mm256_sub_epi64(h[5],carry[5]);


carry[6] = _mm256_srli_epi64(h[6], 26); //carry6
h[7] = _mm256_add_epi64(h[7],carry[6]);
carry[6]=_mm256_slli_epi64 (carry[6], 26);
h[6]=_mm256_sub_epi64(h[6],carry[6]);

carry[7] = _mm256_srli_epi64(h[7], 25);  //carry7
h[8] = _mm256_add_epi64(h[8],carry[7]);
carry[7]=_mm256_slli_epi64 (carry[7], 25);
h[7]=_mm256_sub_epi64(h[7],carry[7]);

carry[8] = _mm256_srli_epi64(h[8], 26);  //carry8
h[9] = _mm256_add_epi64(h[9],carry[8]);
carry[8]=_mm256_slli_epi64 (carry[8], 26);
h[8]=_mm256_sub_epi64(h[8],carry[8]);

carry[9] = _mm256_srli_epi64(h[9], 25);  //carry9
h[0] = _mm256_add_epi64(h[0],19*carry[9]);
carry[9]= _mm256_slli_epi64(carry[9],25);
h[9]=_mm256_sub_epi64(h[9],carry[9]);

carry[0] = _mm256_srli_epi64(h[0], 26); //carry0
h[1] = _mm256_add_epi64(h[1],carry[0]);
carry[0]=_mm256_slli_epi64 (carry[0], 26);
h[0]=_mm256_sub_epi64(h[0],carry[0]);

carry[1] = _mm256_srli_epi64(h[1], 25);
h[2] = _mm256_add_epi64(h[2],carry[1]);
carry[1]=_mm256_slli_epi64(carry[1], 25);
h[1]=_mm256_sub_epi64(h[1],carry[1]);

}



