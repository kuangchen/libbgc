#include "libbgc_vector.h"
#include <math.h>

inline double libbgc_vector_sqr(const libbgc_vector v)
{
  return (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

inline double libbgc_vector_norm(const libbgc_vector v)
{
  return sqrt(libbgc_vector_sqr(v));
}

void libbgc_vector_multiply(libbgc_vector v, double a, libbgc_vector w)
{
  int i=0;
  for(i=0;i<3;i++)
    w[i] = v[i]*a;
}

void libbgc_vector_add(const libbgc_vector v1, double a1, const libbgc_vector v2, double a2, libbgc_vector b)
{
  int i=0;
  for(i=0;i<3;i++)
    b[i] = v1[i]*a1 + v2[i]*a2;
}
