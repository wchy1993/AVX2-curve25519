#include "fe4x.h"
#include "fe.h"

void fe4x_sq(fe4x h,const fe4x f)
{

  h[0] = _mm256_mul_epu32 (f[0],f[0]) +_mm256_mul_epu32 (f[1],38*f[9])+_mm256_mul_epu32 (f[2],19*f[8])+_mm256_mul_epu32 (f[3],38*f[7])+_mm256_mul_epu32 (f[4],19*f[6])+_mm256_mul_epu32 (f[5],38*f[5])+_mm256_mul_epu32 (f[6],19*f[4])+_mm256_mul_epu32 (f[7],38*f[3])+_mm256_mul_epu32 (f[8],19*f[2])+_mm256_mul_epu32 (f[9],38*f[1]);
  
  h[1] = _mm256_mul_epu32 (2*f[0],f[1]) +_mm256_mul_epu32 (f[2],19*f[9])+_mm256_mul_epu32 (f[3],19*f[8])+_mm256_mul_epu32 (f[4],19*f[7])+_mm256_mul_epu32 (f[5],19*f[6])+_mm256_mul_epu32 (f[6],19*f[5])+_mm256_mul_epu32 (f[7],19*f[4])+_mm256_mul_epu32 (f[8],19*f[3])+_mm256_mul_epu32 (f[9],19*f[2]);
  

  h[2] = _mm256_mul_epu32 (2*f[0],f[2]) +_mm256_mul_epu32 (f[1],2*f[1])+_mm256_mul_epu32 (f[3],38*f[9])+_mm256_mul_epu32 (f[4],19*f[8])+_mm256_mul_epu32 (f[5],38*f[7])+_mm256_mul_epu32 (f[6],19*f[6])+_mm256_mul_epu32 (f[7],38*f[5])+_mm256_mul_epu32 (f[8],19*f[4])+_mm256_mul_epu32 (f[9],38*f[3]);
 
  h[3] = _mm256_mul_epu32 (2*f[0],f[3]) +_mm256_mul_epu32 (2*f[1],f[2])+_mm256_mul_epu32 (f[4],19*f[9])+_mm256_mul_epu32 (f[5],19*f[8])+_mm256_mul_epu32 (f[6],19*f[7])+_mm256_mul_epu32 (f[7],19*f[6])+_mm256_mul_epu32 (f[8],19*f[5])+_mm256_mul_epu32 (f[9],19*f[4]);
  
  h[4] = _mm256_mul_epu32 (2*f[0],f[4]) +_mm256_mul_epu32 (f[1],2*f[3])+_mm256_mul_epu32 (f[2],f[2])+_mm256_mul_epu32 (f[3],2*f[1])+_mm256_mul_epu32 (f[5],38*f[9])+_mm256_mul_epu32 (f[6],19*f[8])+_mm256_mul_epu32 (f[7],38*f[7])+_mm256_mul_epu32 (f[8],19*f[6])+_mm256_mul_epu32 (f[9],38*f[5]);
  
  h[5] = _mm256_mul_epu32 (2*f[0],f[5]) +_mm256_mul_epu32 (2*f[1],f[4])+_mm256_mul_epu32 (2*f[2],f[3])+_mm256_mul_epu32 (f[6],19*f[9])+_mm256_mul_epu32 (f[7],19*f[8])+_mm256_mul_epu32 (f[8],19*f[7])+_mm256_mul_epu32 (f[9],19*f[6]);
  
  h[6] = _mm256_mul_epu32 (2*f[0],f[6]) +_mm256_mul_epu32 (f[1],2*f[5])+_mm256_mul_epu32 (2*f[2],f[4])+_mm256_mul_epu32 (f[3],2*f[3])+_mm256_mul_epu32 (f[5],2*f[1])+_mm256_mul_epu32 (f[7],38*f[9])+_mm256_mul_epu32 (f[8],19*f[8])+_mm256_mul_epu32 (f[9],38*f[7]);
  
  h[7] = _mm256_mul_epu32 (2*f[0],f[7]) +_mm256_mul_epu32 (2*f[1],f[6])+_mm256_mul_epu32 (2*f[2],f[5])+_mm256_mul_epu32 (2*f[3],f[4])+_mm256_mul_epu32 (f[8],19*f[9])+_mm256_mul_epu32 (f[9],19*f[8]);
  
  h[8] = _mm256_mul_epu32 (2*f[0],f[8]) +_mm256_mul_epu32 (f[1],2*f[7])+_mm256_mul_epu32 (2*f[2],f[6])+_mm256_mul_epu32 (f[3],2*f[5])+_mm256_mul_epu32 (f[4],f[4])+_mm256_mul_epu32 (f[5],2*f[3])+_mm256_mul_epu32 (f[7],2*f[1])+_mm256_mul_epu32 (f[9],38*f[9]);
  
  h[9] = _mm256_mul_epu32 (2*f[0],f[9]) +_mm256_mul_epu32 (2*f[1],f[8])+_mm256_mul_epu32 (2*f[2],f[7])+_mm256_mul_epu32 (2*f[3],f[6])+_mm256_mul_epu32 (2*f[4],f[5]);
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




void fe4x_sq2(fe4x h,fe4x f)
{

  h[0] = _mm256_mul_epu32 (f[0],f[0]) +_mm256_mul_epu32 (f[1],76*f[9])+_mm256_mul_epu32 (f[2],38*f[8])+_mm256_mul_epu32 (f[3],76*f[7])+_mm256_mul_epu32 (f[4],38*f[6])+_mm256_mul_epu32 (f[5],38*f[5]);
  
  h[1] = _mm256_mul_epu32 (f[0],2*f[1]) +_mm256_mul_epu32 (f[2],38*f[9])+_mm256_mul_epu32 (f[3],38*f[8])+_mm256_mul_epu32 (f[4],38*f[7])+_mm256_mul_epu32 (f[5],38*f[6]);
  

  h[2] = _mm256_mul_epu32 (f[0],2*f[2]) +_mm256_mul_epu32 (f[1],2*f[1])+_mm256_mul_epu32 (f[3],76*f[9])+_mm256_mul_epu32 (f[4],38*f[8])+_mm256_mul_epu32 (f[5],76*f[7])+_mm256_mul_epu32 (f[6],19*f[6]);
 
  h[3] = _mm256_mul_epu32 (f[0],2*f[3]) +_mm256_mul_epu32 (f[1],2*f[2])+_mm256_mul_epu32 (f[4],38*f[9])+_mm256_mul_epu32 (f[5],38*f[8])+_mm256_mul_epu32 (f[6],38*f[7]);
  
  h[4] = _mm256_mul_epu32 (f[0],2*f[4]) +_mm256_mul_epu32 (f[1],4*f[3])+_mm256_mul_epu32 (f[2],f[2])+_mm256_mul_epu32 (f[5],76*f[9])+_mm256_mul_epu32 (f[6],38*f[8])+_mm256_mul_epu32 (f[7],38*f[7]);
  
  h[5] = _mm256_mul_epu32 (f[0],2*f[5]) +_mm256_mul_epu32 (f[1],2*f[4])+_mm256_mul_epu32 (f[2],2*f[3])+_mm256_mul_epu32 (f[6],38*f[9])+_mm256_mul_epu32 (f[7],38*f[8]);
  
  h[6] = _mm256_mul_epu32 (f[0],2*f[6]) +_mm256_mul_epu32 (f[1],4*f[5])+_mm256_mul_epu32 (f[2],2*f[4])+_mm256_mul_epu32 (f[3],2*f[3])+_mm256_mul_epu32 (f[7],76*f[9])+_mm256_mul_epu32 (f[8],19*f[8]);
  
  h[7] = _mm256_mul_epu32 (f[0],2*f[7]) +_mm256_mul_epu32 (f[1],2*f[6])+_mm256_mul_epu32 (f[2],2*f[5])+_mm256_mul_epu32 (f[3],2*f[4])+_mm256_mul_epu32 (f[8],38*f[9]);
  
  h[8] = _mm256_mul_epu32 (f[0],2*f[8]) +_mm256_mul_epu32 (f[1],4*f[7])+_mm256_mul_epu32 (f[2],2*f[6])+_mm256_mul_epu32 (f[3],4*f[5])+_mm256_mul_epu32 (f[4],f[4])+_mm256_mul_epu32 (f[9],38*f[9]);

  h[9] = _mm256_mul_epu32 (f[0],2*f[9]) +_mm256_mul_epu32 (f[1],2*f[8])+_mm256_mul_epu32 (f[2],2*f[7])+_mm256_mul_epu32 (f[3],2*f[6])+_mm256_mul_epu32 (f[4],2*f[5]);


  
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
