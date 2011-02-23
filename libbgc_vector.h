#ifndef _BGC_VECTOR_H
#define _BGC_VECTOR_H

typedef double libbgc_vector[3];
typedef libbgc_vector* libbgc_vector_pointer;

double libbgc_vector_sqr(const libbgc_vector v);
double libbgc_vector_norm(const libbgc_vector v);
void libbgc_vector_scale(libbgc_vector v, double a);
void libbgc_vector_add(const libbgc_vector v1, double a1, const libbgc_vector v2, double a2, libbgc_vector b);
#endif
