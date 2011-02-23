#include "libbgc_collision.h"
#include "libbgc_hs.h"
#include "libbgc_gas.h"

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_const_mksa.h>

int main()
{
  libbgc_hs_parameter param = {300, 1, 1e-19, 1, 1};
  libbgc_collision_tag collision_tag = { 
    .alien_tag = {
      .description = "BaCl", 
      .mass = 173*GSL_CONST_MKSA_UNIFIED_ATOMIC_MASS, 
      .charge = 1, 
      .other_property = NULL},

    .buffer_tag = {
      .description = "He", 
      .mass = 4*GSL_CONST_MKSA_UNIFIED_ATOMIC_MASS, 
      .charge = 0, 
      .other_property = NULL},
    
    .collision_process = libbgc_hs_process,
    .collision_timer = libbgc_hs_timer,
    .collision_parameter = &param
  };
  
  libbgc_collision_pointer p = libbgc_collision_create(&collision_tag);
  libbgc_vector v_bacl = {0,0,100};
  libbgc_vector v_he = {0,20,0};
  libbgc_gas_set_velocity(libbgc_collision_get_alien(p), v_bacl);
  libbgc_gas_set_velocity(libbgc_collision_get_buffer(p), v_he);
  int i = 0;
  for(i=0;i<1e6;i++)
    libbgc_collision_run(p, -1);
  libbgc_collision_destroy(p);
  return 0;
}
