#include "ed25519.h"
#include "sha512.h"
#include "ge.h"
#include <stdio.h>
#include <time.h>

void ed25519_create_keypair(unsigned char *public_key, unsigned char *private_key, const unsigned char *seed) {
    ge_p3 A;
    ge_p34x B;
    ge_p3 A1;
    int i ;
  
    sha512(seed, 32, private_key);
    
    private_key[0] &= 248;
    private_key[31] &= 63;
    private_key[31] |= 64;

printf("private_key orignal");
nl();
  for(i=0; i <32;i++)
{
   printf("%d,",private_key[i]);
}




    ge_scalarmult_base(&A1,private_key);
    ge_scalarmult_base4x(&A, &B,private_key);


    fe zina;
    fe zinb;
    fe testa;
    fe testb;
    fe_invert(zina,A.Z);
    fe_mul(testa,A.X,zina);
    printf("A=");
    fe_dump(testa);nl();
    //fe_invert(zinb,A1.Z);
    fe_mul(testb,A.Y,zina);
    printf("Y=");
    fe_dump(testb);nl();


for(i=0;i<10;i++)
{
    if(testa[i]==testb[i])
{
  
	printf("true");
	nl();
}
else
{
break;
}
} 
  
   fe tmp;
   fe_tobytes(public_key,testb);
   fe_frombytes(tmp,public_key);
   fe_dump(tmp);

   ge_p3_tobytes(public_key, &A);


   //nl();


  

}
