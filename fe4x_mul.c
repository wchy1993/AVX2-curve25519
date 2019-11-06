#include "fe4x.h"
#include "fe.h"

void fe4x_mul(fe4x h,const fe4x f,const fe4x g)

{


  h[0] = _mm256_mul_epu32 (f[0],g[0]) +_mm256_mul_epu32 (f[1],38*g[9])+_mm256_mul_epu32 (f[2],19*g[8])+_mm256_mul_epu32 (f[3],38*g[7])+_mm256_mul_epu32 (f[4],19*g[6])+_mm256_mul_epu32 (f[5],38*g[5])+_mm256_mul_epu32 (f[6],19*g[4])+_mm256_mul_epu32 (f[7],38*g[3])+_mm256_mul_epu32 (f[8],19*g[2])+_mm256_mul_epu32 (f[9],38*g[1]);
  
  h[1] = _mm256_mul_epu32 (f[0],g[1]) +_mm256_mul_epu32 (f[1],g[0])+_mm256_mul_epu32 (f[2],19*g[9])+_mm256_mul_epu32 (f[3],19*g[8])+_mm256_mul_epu32 (f[4],19*g[7])+_mm256_mul_epu32 (f[5],19*g[6])+_mm256_mul_epu32 (f[6],19*g[5])+_mm256_mul_epu32 (f[7],19*g[4])+_mm256_mul_epu32 (f[8],19*g[3])+_mm256_mul_epu32 (f[9],19*g[2]);
  

  h[2] = _mm256_mul_epu32 (f[0],g[2]) +_mm256_mul_epu32 (f[1],2*g[1])+_mm256_mul_epu32 (f[2],g[0])+_mm256_mul_epu32 (f[3],38*g[9])+_mm256_mul_epu32 (f[4],19*g[8])+_mm256_mul_epu32 (f[5],38*g[7])+_mm256_mul_epu32 (f[6],19*g[6])+_mm256_mul_epu32 (f[7],38*g[5])+_mm256_mul_epu32 (f[8],19*g[4])+_mm256_mul_epu32 (f[9],38*g[3]);
 
  h[3] = _mm256_mul_epu32 (f[0],g[3]) +_mm256_mul_epu32 (f[1],g[2])+_mm256_mul_epu32 (f[2],g[1])+_mm256_mul_epu32 (f[3],g[0])+_mm256_mul_epu32 (f[4],19*g[9])+_mm256_mul_epu32 (f[5],19*g[8])+_mm256_mul_epu32 (f[6],19*g[7])+_mm256_mul_epu32 (f[7],19*g[6])+_mm256_mul_epu32 (f[8],19*g[5])+_mm256_mul_epu32 (f[9],19*g[4]);
  
  h[4] = _mm256_mul_epu32 (f[0],g[4]) +_mm256_mul_epu32 (f[1],2*g[3])+_mm256_mul_epu32 (f[2],g[2])+_mm256_mul_epu32 (f[3],2*g[1])+_mm256_mul_epu32 (f[4],g[0])+_mm256_mul_epu32 (f[5],38*g[9])+_mm256_mul_epu32 (f[6],19*g[8])+_mm256_mul_epu32 (f[7],38*g[7])+_mm256_mul_epu32 (f[8],19*g[6])+_mm256_mul_epu32 (f[9],38*g[5]);
  
  h[5] = _mm256_mul_epu32 (f[0],g[5]) +_mm256_mul_epu32 (f[1],g[4])+_mm256_mul_epu32 (f[2],g[3])+_mm256_mul_epu32 (f[3],g[2])+_mm256_mul_epu32 (f[4],g[1])+_mm256_mul_epu32 (f[5],g[0])           +_mm256_mul_epu32 (f[6],19*g[9])+_mm256_mul_epu32 (f[7],19*g[8])+_mm256_mul_epu32 (f[8],19*g[7])+_mm256_mul_epu32 (f[9],19*g[6]);
  
  h[6] = _mm256_mul_epu32 (f[0],g[6]) +_mm256_mul_epu32 (f[1],2*g[5])+_mm256_mul_epu32 (f[2],g[4])+_mm256_mul_epu32 (f[3],2*g[3])+_mm256_mul_epu32 (f[4],g[2])+_mm256_mul_epu32 (f[5],2*g[1])+_mm256_mul_epu32 (f[6],g[0])+_mm256_mul_epu32 (f[7],38*g[9])+_mm256_mul_epu32 (f[8],19*g[8])+_mm256_mul_epu32 (f[9],38*g[7]);
  
  h[7] = _mm256_mul_epu32 (f[0],g[7]) +_mm256_mul_epu32 (f[1],g[6])+_mm256_mul_epu32 (f[2],g[5])+_mm256_mul_epu32 (f[3],g[4])+_mm256_mul_epu32 (f[4],g[3])+_mm256_mul_epu32 (f[5],g[2])+_mm256_mul_epu32 (f[6],g[1])+_mm256_mul_epu32 (f[7],g[0])+_mm256_mul_epu32 (f[8],19*g[9])+_mm256_mul_epu32 (f[9],19*g[8]);
  
  h[8] = _mm256_mul_epu32 (f[0],g[8]) +_mm256_mul_epu32 (f[1],2*g[7])+_mm256_mul_epu32 (f[2],g[6])+_mm256_mul_epu32 (f[3],2*g[5])+_mm256_mul_epu32 (f[4],g[4])+_mm256_mul_epu32 (f[5],2*g[3])
+_mm256_mul_epu32 (f[6],g[2])+_mm256_mul_epu32 (f[7],2*g[1])+_mm256_mul_epu32 (f[8],g[0])+_mm256_mul_epu32 (f[9],38*g[9]);
  
  h[9] = _mm256_mul_epu32 (f[0],g[9]) +_mm256_mul_epu32 (f[1],g[8])+_mm256_mul_epu32 (f[2],g[7])+_mm256_mul_epu32 (f[3],g[6])+_mm256_mul_epu32 (f[4],g[5])+_mm256_mul_epu32 (f[5],g[4])
+_mm256_mul_epu32 (f[6],g[3])+_mm256_mul_epu32 (f[7],g[2])+_mm256_mul_epu32 (f[8],g[1])+_mm256_mul_epu32 (f[9],g[0]);
  
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
