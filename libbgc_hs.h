#ifndef _BGC_HS_H
#define _BGC_HS_H
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_const_mksa.h>
#include "libbgc_gas.h"

void libbgc_hs_process(libbgc_gas_pointer p_alien, libbgc_gas_pointer p_buffer, gsl_rng* dice, void* collision_parameter);
int libbgc_hs_timer(libbgc_gas_pointer p_alien, libbgc_gas_pointer p_buffer, gsl_rng* dice, void* collision_parameter, double time);

typedef struct _libbgc_hs_parameter
{
  double buffer_temperature;
  double buffer_pressure;
  double cross_section;

  double buffer_density;
  double buffer_mean_velocity;

}libbgc_hs_parameter;

#endif
