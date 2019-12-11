#include "fe4x.h"

#include "fe.h"


  
void fe4x_sub(fe4x C,const fe4x A,const fe4x B)

{
   
   const __m256i _2P[10] = {
			_mm256_set1_epi64x(0x7ffffda),	_mm256_set1_epi64x(0x3fffffe),
			_mm256_set1_epi64x(0x3fffffe),	_mm256_set1_epi64x(0x7fffffe),
			_mm256_set1_epi64x(0x7fffffe),	_mm256_set1_epi64x(0x3fffffe),
			_mm256_set1_epi64x(0x3fffffe),	_mm256_set1_epi64x(0x7fffffe),
			_mm256_set1_epi64x(0x7fffffe),	_mm256_set1_epi64x(0x3fffffe)
	};
	int i=0;
	for(i=0;i<10;i++)
	{
		C[i] = _mm256_add_epi64(A[i],_mm256_sub_epi64(_2P[i],B[i]));
	}


}

void fe4x_addsub(fe4x  C,fe4x  D, fe4x  A, fe4x  B)
 {
	const __m256i _2P[10] = {
			_mm256_set1_epi64x(0x7ffffda),	_mm256_set1_epi64x(0x3fffffe),
			_mm256_set1_epi64x(0x3fffffe),	_mm256_set1_epi64x(0x7fffffe),
			_mm256_set1_epi64x(0x7fffffe),	_mm256_set1_epi64x(0x3fffffe),
			_mm256_set1_epi64x(0x3fffffe),	_mm256_set1_epi64x(0x7fffffe),
			_mm256_set1_epi64x(0x7fffffe),	_mm256_set1_epi64x(0x3fffffe)
	};
	int i=0;
	for(i=0;i<10;i++)
	{
		C[i] = _mm256_add_epi64(A[i],B[i]);
		D[i] = _mm256_add_epi64(A[i],_mm256_sub_epi64(_2P[i],B[i]));
	}
}

void fe4x_addsublar(fe4x  A, fe4x  B) {
	const __m256i _2_to_35P[10] = {
			_mm256_set1_epi64x(0x1fffff6800000000),	_mm256_set1_epi64x(0x0ffffff800000000),
			_mm256_set1_epi64x(0x0ffffff800000000),	_mm256_set1_epi64x(0x1ffffff800000000),
			_mm256_set1_epi64x(0x1ffffff800000000),	_mm256_set1_epi64x(0x0ffffff800000000),
			_mm256_set1_epi64x(0x0ffffff800000000),	_mm256_set1_epi64x(0x1ffffff800000000),
			_mm256_set1_epi64x(0x1ffffff800000000),	_mm256_set1_epi64x(0x0ffffff800000000)
	};
	int i=0;
	for(i=0;i<10;i++)
	{
		__m256i add = _mm256_add_epi64(A[i],B[i]);
		__m256i sub = _mm256_add_epi64(A[i],_mm256_sub_epi64(_2_to_35P[i], B[i]));
		A[i] = add;
		B[i] = sub;
	}
}

void fe4x_negmon(fe4x C,fe4x A )
{
    const __m256i negmon[10] = 
{
     _mm256_set_epi64x(0x7ffffda,A[3][0],0x7ffffda,A[1][0]),
     _mm256_set_epi64x(0x3fffffe,A[3][1],0x3fffffe,A[1][1]),
     _mm256_set_epi64x(0x7fffffe,A[3][2],0x7fffffe,A[1][2]), 
     _mm256_set_epi64x(0x3fffffe,A[3][3],0x3fffffe,A[1][3]),
     _mm256_set_epi64x(0x7fffffe,A[3][4],0x7fffffe,A[1][4]),
     _mm256_set_epi64x(0x3fffffe,A[3][5],0x3fffffe,A[1][5]),
     _mm256_set_epi64x(0x7fffffe,A[3][6],0x7fffffe,A[1][6]),
     _mm256_set_epi64x(0x3fffffe,A[3][7],0x3fffffe,A[1][7]),
     _mm256_set_epi64x(0x7fffffe,A[3][8],0x7fffffe,A[1][8]),
     _mm256_set_epi64x(0x3fffffe,A[3][9],0x3fffffe,A[1][9])
};
   int i ;
   for(i=0;i<10;i++)
	{
           C[i] = _mm256_sub_epi64(negmon[i],A[i]);
 
       }
}


