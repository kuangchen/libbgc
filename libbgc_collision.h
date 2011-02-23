#ifndef _BGC_COLLSION_H
#define _BGC_COLLSION_H

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_const_mksa.h>
#include "libbgc_gas.h"

typedef void (*libbgc_collision_process)(libbgc_gas_pointer p_alien, libbgc_gas_pointer p_buffer, gsl_rng* dice, void* collision_parameter);
typedef int (*libbgc_collision_timer)(libbgc_gas_pointer p_alien, libbgc_gas_pointer p_buffer, gsl_rng* dice, void* collision_parameter, double time);

typedef struct _libbgc_collision libbgc_collision, *libbgc_collision_pointer;
typedef struct _libbgc_collision_tag
{
  libbgc_gas_tag alien_tag;
  libbgc_gas_tag buffer_tag;
  libbgc_collision_process collision_process;
  libbgc_collision_timer collision_timer;
  void* collision_parameter;
}libbgc_collision_tag, *libbgc_collision_tag_pointer;

libbgc_collision_pointer libbgc_collision_create(const libbgc_collision_tag_pointer tag_pointer);
void libbgc_collision_run(libbgc_collision_pointer p, double time);
void libbgc_collision_destroy(libbgc_collision_pointer p);

libbgc_gas_pointer libbgc_collision_get_alien(const libbgc_collision_pointer p);
libbgc_gas_pointer libbgc_collision_get_buffer(const libbgc_collision_pointer p);

void libbgc_collision_assert_energy_conservation(const libbgc_gas_pointer p_alien_in, const libbgc_gas_pointer p_buffer_in, const libbgc_gas_pointer p_alien_out, const libbgc_gas_pointer p_buffer_out, double precision);

void libbgc_collision_assert_momentum_conservation(const libbgc_gas_pointer p_alien_in, const libbgc_gas_pointer p_buffer_in, const libbgc_gas_pointer p_alien_out, const libbgc_gas_pointer p_buffer_out, double precision);

#endif
