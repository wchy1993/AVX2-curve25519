#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ed25519.h"
#include "ge.h"
#include "sc.h"
#include "fe.h"

#include <sys/resource.h>
#include <assert.h>


#ifdef __i386
__inline__ uint64_t rdtsc() {
    uint64_t x;
    __asm__ volatile ("rdtsc" : "=A" (x));
    return x;
}
#elif __amd64
__inline__ uint64_t rdtsc() {
    uint64_t a, d;
    __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
    return (d<<32) | a;
}
#endif

static inline uint64_t microseconds()
{
    struct rusage res[1];
    getrusage(RUSAGE_SELF,res);
    uint64_t r;
    r  = (uint64_t) res->ru_utime.tv_sec;
    r *= (uint64_t) 1000000UL;
    r += (uint64_t) res->ru_utime.tv_usec;
    return r;
}
double mhz()
{
    char line[512];
    FILE * f = fopen("/proc/cpuinfo","r");
    double res = 0;
    if (f == NULL)
        return 0;
    while (fgets(line, sizeof(line), f) != NULL) {
        if (sscanf(line, "cpu MHz         : %lf", &res) == 1) {
            break;
        }
    }
    fclose(f);
    return res;
}

int main() {
   
    unsigned char public_key[32], private_key[64], seed[32], scalar[32];

    unsigned char other_public_key[32], other_private_key[64];
    unsigned char shared_secret[32], other_shared_secret[32];
    unsigned char signature[64];
    uint64_t r0,r1;
    int i;
    double mhz0, mhz1;
    double delta;
    clock_t start;
    clock_t end;
    uint64_t t;

    const unsigned char message[] = "Hello, world!";
    const int message_len = strlen((char*) message);

    /* create a random seed, and a keypair out of that seed */
   // ed25519_create_seed(seed);


    //ed25519_create_keypair(public_key, private_key, seed);
  /* create signature on the message with the keypair */

   
    /* generate two keypairs for testing key exchange */
    ed25519_create_seed(seed);
    ed25519_create_keypair(public_key, private_key, seed);
    ed25519_create_seed(seed);
    ed25519_create_keypair(other_public_key, other_private_key, seed);
   
    /* create two shared secrets - from both perspectives - and check if they're equal */
    //ed25519_key_exchange(shared_secret, other_public_key, private_key);

   // ed25519_key_exchange(other_shared_secret, public_key, other_private_key);
/*
  for (i = 0; i < 32; ++i) {
        if (shared_secret[i] != other_shared_secret[i]) {
            printf("key exchange was incorrect\n");
            break;
        }
    }

    if (i == 32) {
        printf("key exchange was correct\n");
    }

  
    printf("testing seed generation performance: ");
    start = clock();
    for (i = 0; i < 10000; ++i) {
        ed25519_create_seed(seed);
    }
    end = clock();

    printf("%fus per seed\n", ((double) ((end - start) * 1000)) / CLOCKS_PER_SEC / i * 1000);
*/

    printf("testing key generation performance: ");
restart:
    r0 = microseconds();
    mhz0 = mhz();
    if (mhz0 > 0) {
        printf("CPU freq : %.2f MHz\n", mhz0);
    }

    
    for (i = 0; i < 10000; ++i) {
        ed25519_create_keypair(public_key, private_key, seed);
    }
   


    
    r1 = microseconds();
    mhz1 = mhz();
  if (mhz0 != mhz1) {
        printf("CPU freq changed, restarting\n");
        goto restart;
    }
    delta = (double) (r1-r0)/1000;

    printf("%d in %.2f ms\n", i, delta);
    if (mhz1 != 0) {
        printf("%d cycles on average\n", (int) (delta * mhz0 * 1000 / i));
    }

/* 
   printf("testing sign performance: ");
    start = clock();
    for (i = 0; i < 10000; ++i) {
        ed25519_sign(signature, message, message_len, public_key, private_key);
    }
    end = clock();

    printf("%fus per signature\n", ((double) ((end - start) * 1000)) / CLOCKS_PER_SEC / i * 1000);

    printf("testing verify performance: ");
    start = clock();
    for (i = 0; i < 10000; ++i) {
        ed25519_verify(signature, message, message_len, public_key);
    }
    end = clock();

    printf("%fus per signature\n", ((double) ((end - start) * 1000)) / CLOCKS_PER_SEC / i * 1000);
    

    printf("testing keypair scalar addition performance: ");
    start = clock();
    for (i = 0; i < 10000; ++i) {
        ed25519_add_scalar(public_key, private_key, scalar);
    }
    end = clock();

    printf("%fus per keypair\n", ((double) ((end - start) * 1000)) / CLOCKS_PER_SEC / i * 1000);

    printf("testing public key scalar addition performance: ");
    start = clock();
    for (i = 0; i < 10000; ++i) {
        ed25519_add_scalar(public_key, NULL, scalar);
    }
    end = clock();

    printf("%fus per key\n", ((double) ((end - start) * 1000)) / CLOCKS_PER_SEC / i * 1000);
*/
    printf("testing key exchange performance: ");
    t = rdtsc();
    for (i = 0; i < 10000; ++i) {
        ed25519_key_exchange(shared_secret, other_public_key, private_key);
    }
     t = rdtsc() - t;

    printf("%dcycles per key\n", ((int) (t /i)));

    return 0;
}
