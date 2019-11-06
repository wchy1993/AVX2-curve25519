#include "fe4x.h"
#include "fe.h"

void fe4x_add(fe4x h,const fe4x f,const fe4x g)
{
	h[0 ] = _mm256_add_epi64(f[0 ], g[0 ]);
	h[1 ] = _mm256_add_epi64(f[1 ], g[1 ]);
	h[2 ] = _mm256_add_epi64(f[2 ], g[2 ]);
	h[3 ] = _mm256_add_epi64(f[3 ], g[3 ]);
	h[4 ] = _mm256_add_epi64(f[4 ], g[4 ]);
	h[5 ] = _mm256_add_epi64(f[5 ], g[5 ]);
	h[6 ] = _mm256_add_epi64(f[6 ], g[6 ]);
	h[7 ] = _mm256_add_epi64(f[7 ], g[7 ]);
	h[8 ] = _mm256_add_epi64(f[8 ], g[8 ]);
	h[9 ] = _mm256_add_epi64(f[9 ], g[9 ]);

}
  


