#include <math.h>
#include "libbgc_hs.h"
#include "libbgc_gas.h"
#include "libbgc_vector.h"

void libbgc_hs_process(libbgc_gas_pointer p_alien, libbgc_gas_pointer p_buffer, gsl_rng* dice, void* collision_parameter)
{
  libbgc_vector v_com, v_rel, p, q, qq;
  libbgc_gas_lab_to_com(p_alien, p_buffer, &v_com, &v_rel);

  libbgc_gas_get_momentum(p_alien, p);
  double p_mag = libbgc_vector_norm(p);
  gsl_ran_dir_3d(dice, &q[0], &q[1], &q[2]);

  libbgc_vector_multiply(q, p_mag, qq);
  libbgc_gas_set_momentum(p_alien,qq);

  libbgc_vector_multiply(q, -p_mag, qq);
  libbgc_gas_set_momentum(p_buffer,qq);
  libbgc_gas_com_to_lab(p_alien, p_buffer, &v_com);
}

int libbgc_hs_timer(libbgc_gas_pointer p_alien, libbgc_gas_pointer p_buffer, gsl_rng* dice, void* collision_parameter, double time)
{
  libbgc_hs_parameter* p = (libbgc_hs_parameter*)collision_parameter;
  libbgc_vector alien_velocity;
  libbgc_gas_get_velocity(p_alien, alien_velocity);
  double s = libbgc_vector_norm(alien_velocity) / p->buffer_mean_velocity;
  double relative_velocity = ((s+1/2/s)*0.886226925*erf(s) + 0.5* exp(-s*s));
  return gsl_rng_uniform(dice)<1-exp(-relative_velocity*time*p->buffer_density*p->cross_section)?1:0;
}
