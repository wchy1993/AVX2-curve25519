#include "fe4x.h"
#include "fe.h"

void fe4x_copy(fe4x c, fe4x a) 
{

  int i = 0;
  for (i = 0; i < 10; i++)
 {
    c[i] = a[i];
  }
}
