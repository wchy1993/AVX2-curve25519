#include "fe4x.h"
#include "fe.h"
#include <stdio.h>



void fe4x_cmov(fe4x f, const fe4x g,  fe4 b ) 
{
    
   
    //const uint8_t  a;
   
    int i ;
    
    fe4xd fd;
    fe4xd gd;
    fe4d bd;
    fe4 b4x;
   
    //b4x =  _mm256_set_epi64x(x3,x2,x1,x0);
    b4x =  _mm256_slli_epi64(b,63);
    //fe4x x;
    bd= _mm256_castsi256_pd(b4x);

  for(i=0;i<10;i++)
{
   fd[i]= _mm256_castsi256_pd(f[i]);
   gd[i]= _mm256_castsi256_pd(g[i]);
 }   
    
    
   
  
    fd[0] = _mm256_blendv_pd (fd[0],gd[0],bd);
    fd[1] = _mm256_blendv_pd (fd[1],gd[1],bd);
    fd[2] = _mm256_blendv_pd (fd[2],gd[2],bd);
    fd[3] = _mm256_blendv_pd (fd[3],gd[3],bd);
    fd[4] = _mm256_blendv_pd (fd[4],gd[4],bd);
    fd[5] = _mm256_blendv_pd (fd[5],gd[5],bd);
    fd[6] = _mm256_blendv_pd (fd[6],gd[6],bd);
    fd[7] = _mm256_blendv_pd (fd[7],gd[7],bd);
    fd[8] = _mm256_blendv_pd (fd[8],gd[8],bd);
    fd[9] = _mm256_blendv_pd (fd[9],gd[9],bd);

 
      for(i=0;i<10;i++)
{
   f[i]= _mm256_castpd_si256(fd[i]);
   //gd[i]= _mm256_castsi256_pd(g[i]);
 }   
}
