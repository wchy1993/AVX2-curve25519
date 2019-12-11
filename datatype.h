#ifndef __DATATYPE_25519_H__
#define __DATATYPE_25519_H__

#define LIMBS 4

typedef unsigned char uchar8;
typedef unsigned long long int uint64;

typedef struct {
  uint64 l[LIMBS]; 
}
gfe25519;


#endif

