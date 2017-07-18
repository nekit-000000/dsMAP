/* START OF "pair.cpp" FILE */

#include "pair.h"

void Swap(void *a, void *b, size_t size)
{
  unsigned char *p = (unsigned char *)a;
  unsigned char *q = (unsigned char *)b;
  unsigned char tmp;

  for (size_t i = 0; i != size; i++)
  {
    tmp = p[i];
    p[i] = q[i];
    q[i] = tmp;
  }
}

/* END OF "pair.cpp" FILE */
