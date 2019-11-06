#ifndef GE_H
#define GE_H

#include "fe.h"
#include "fe4x.h"

/*
ge means group element.

Here the group is the set of pairs (x,y) of field elements (see fe.h)
satisfying -x^2 + y^2 = 1 + d x^2y^2
where d = -121665/121666.

Representations:
  ge_p2 (projective): (X:Y:Z) satisfying x=X/Z, y=Y/Z
  ge_p3 (extended): (X:Y:Z:T) satisfying x=X/Z, y=Y/Z, XY=ZT
  ge_p1p1 (completed): ((X:Z),(Y:T)) satisfying x=X/Z, y=Y/T
  ge_precomp (Duif): (y+x,y-x,2dxy)
*/

typedef struct {
  fe X;
  fe Y;
  fe Z;
} ge_p2;

typedef struct {
  fe X;
  fe Y;
  fe Z;
  fe T;
} ge_p3;

typedef struct {
  fe X;
  fe Y;
  fe Z;
  fe T;
} ge_p1p1;

typedef struct {
  fe yplusx;
  fe yminusx;
  fe xy2d;
} ge_precomp;

typedef struct {
  fe YplusX;
  fe YminusX;
  fe Z;
  fe T2d;
} ge_cached;
typedef struct {
  fe4x X4x;
  fe4x Y4x;
  fe4x Z4x;
} ge_p24x;

typedef struct {
  fe4x X4x;
  fe4x Y4x;
  fe4x Z4x;
  fe4x T4x;
} ge_p34x;

typedef struct {
  fe4x X4x;
  fe4x Y4x;
  fe4x Z4x;
  fe4x T4x;
} ge_p1p14x;

typedef struct {
  fe4x yplusx4x;
  fe4x yminusx4x;
  fe4x xy2d4x;
} ge_precomp4x;

typedef struct {
  fe4x YplusX4x;
  fe4x YminusX4x;
  fe4x Z4x;
  fe4x T2d4x;
} ge_cached4x;


typedef struct {
  fe yplusx1;
  fe yplusx2;
  fe yplusx3;
  fe yplusx4;
  fe yminusx1;
  fe yminusx2;
  fe yminusx3;
  fe yminusx4;
  fe xy2d1;
  fe xy2d2;
  fe xy2d3;
  fe xy2d4;
} ge_precomp4;


void ge_p3_tobytes(unsigned char *s, const ge_p3 *h);
void ge_tobytes(unsigned char *s, const ge_p2 *h);
int ge_frombytes_negate_vartime(ge_p3 *h, const unsigned char *s);

void ge_add(ge_p1p1 *r, const ge_p3 *p, const ge_cached *q);
void ge_sub(ge_p1p1 *r, const ge_p3 *p, const ge_cached *q);
void ge_double_scalarmult_vartime(ge_p2 *r, const unsigned char *a, const ge_p3 *A, const unsigned char *b);
void ge_madd(ge_p1p1 *r, const ge_p3 *p, const ge_precomp *q);
void ge_madd4x(ge_p1p14x *r, const ge_p34x *p, const ge_precomp4x *q);
void ge_msub(ge_p1p1 *r, const ge_p3 *p, const ge_precomp *q);
//void ge_msub4x(ge_p1p14x *r, const ge_p34x *p, const ge_precomp4x *q);
void ge_scalarmult_base(ge_p3 *h, const unsigned char *a);
void ge_scalarmult_base4x(ge_p3 *m,  ge_p34x *h, const unsigned char *a);

void ge_p1p1_to_p2(ge_p2 *r, const ge_p1p1 *p);
void ge_p1p14x_to_p24x(ge_p24x *r, const ge_p1p14x *p);
void ge_p1p1_to_p3(ge_p3 *r, const ge_p1p1 *p);
void ge_p1p14x_to_p34x(ge_p34x *r, const ge_p1p14x *p);
void ge_p2_0(ge_p2 *h);
void ge_p2_04x(ge_p24x *h);
void ge_p2_dbl(ge_p1p1 *r, const ge_p2 *p);
void ge_p2_dbl4x(ge_p1p14x *r, const ge_p24x *p);
void ge_p3_0(ge_p3 *h);
void ge_p3_04x(ge_p34x *h);
void ge_p3_dbl(ge_p1p1 *r, const ge_p3 *p);
void ge_p3_dbl4x(ge_p1p14x *r, const ge_p34x *p);
void ge_p3_to_cached(ge_cached *r, const ge_p3 *p);
void ge_p3_to_p2(ge_p2 *r, const ge_p3 *p);
void ge_p34x_to_p24x(ge_p24x *r, const ge_p34x *p);
void pt();
void fe_dump(fe );
void nl();
#endif
