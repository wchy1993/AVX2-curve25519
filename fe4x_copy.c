#include "fe4x.h"
#include "fe.h"

void fe4x_copy(fe4x h, const fe4x f) 
{    
     //fe htmp[4];
     fe4xd fd;
     fe4xd hd;
     int i;
     
for(i=0;i<10;i++)
{
   fd[i]= _mm256_castsi256_pd(f[i]);
   hd[i]= _mm256_castsi256_pd(h[i]);

  hd[i] = _mm256_blend_pd (fd[i],hd[i],0);
 
   h[i]= _mm256_castpd_si256(hd[i]);
  
 }   
   
}
