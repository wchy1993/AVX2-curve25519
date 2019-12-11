#include "fe4x.h"

#include "fe4x.h"

/*
    Replace (f,g) with (g,f) if b == 1;
    replace (f,g) with (f,g) if b == 0.

    Preconditions: b in {0,1}.
*/

void fe4x_cswap(fe4x f , fe4x g , unsigned long long int  b  )
{
     __m256i * h ;
     b = (unsigned long long int)(0-b);
     int i ;
     for(i=0;i<10;i++)
{
      h[i] = f[i]^g[i];
      h[i] = h[i]&b;
      f[i] = f[i]^h[i];
      g[i] = g[i]^h[i];

}


}
