#ifndef _BGC_GAS_H
#define _BGC_GAS_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_const_mksa.h>
#include "libbgc_vector.h"

#define BGC_GAS_DESCRIPTION_MAX_LENGTH 100

typedef char libbgc_gas_description[BGC_GAS_DESCRIPTION_MAX_LENGTH];
typedef struct _libbgc_gas libbgc_gas, *libbgc_gas_pointer;

typedef struct _libbgc_gas_tag
{
  libbgc_gas_description description;
  double mass;
  double charge;
  void *other_property;
}libbgc_gas_tag, *libbgc_gas_tag_pointer;

libbgc_gas_pointer libbgc_gas_create(const libbgc_gas_tag_pointer tag_pointer);
void libbgc_gas_destroy(libbgc_gas_pointer p);

double libbgc_gas_mass(const libbgc_gas_pointer p);
void libbgc_gas_get_velocity(const libbgc_gas_pointer p, libbgc_vector velocity);
void libbgc_gas_get_momentum(const libbgc_gas_pointer p, libbgc_vector momentum);
void libbgc_gas_get_position(const libbgc_gas_pointer p, libbgc_vector position);
void libbgc_gas_set_velocity(libbgc_gas_pointer p, const libbgc_vector velocity);
void libbgc_gas_set_momentum(libbgc_gas_pointer p, const libbgc_vector momentum);
void libbgc_gas_set_position(libbgc_gas_pointer p, const libbgc_vector position);
double libbgc_gas_kinetic_energy(const libbgc_gas_pointer p);

libbgc_gas_pointer libbgc_gas_make_copy(const libbgc_gas_pointer p);

#endif
