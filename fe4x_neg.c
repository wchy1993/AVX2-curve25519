#include "fe4x.h"

#include "fe.h"


  
void fe4x_neg(fe4x h,const fe4x g)

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
		h[i] = SUB(_2P[i],g[i]);
	}
   

}
