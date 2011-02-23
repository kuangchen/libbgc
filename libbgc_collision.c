#include "libbgc_collision.h"
#include "libbgc_gas.h"
#include <assert.h>
#define DEBUG

struct _libbgc_collision
{
  const gsl_rng_type* dice_type;
  gsl_rng* dice;

  libbgc_gas_pointer p_alien;
  libbgc_gas_pointer p_buffer;
  libbgc_collision_process collision_process;
  libbgc_collision_timer collision_timer;
  void* collision_parameter;
};

libbgc_collision_pointer libbgc_collision_create(const libbgc_collision_tag_pointer tag_pointer)
{
  libbgc_collision_pointer p = malloc(sizeof(libbgc_collision));

  p->p_alien = libbgc_gas_create(&(tag_pointer->alien_tag));
  p->p_buffer = libbgc_gas_create(&(tag_pointer->buffer_tag));
  p->collision_process = tag_pointer->collision_process;
  p->collision_timer = tag_pointer->collision_timer;
  p->collision_parameter = tag_pointer->collision_parameter;

  gsl_rng_env_setup();
  p->dice_type = gsl_rng_default;
  p->dice = gsl_rng_alloc (p->dice_type);
  return p;
}

void libbgc_collision_run(libbgc_collision_pointer p, double time)
{
  if(time<0 || p->collision_timer(p->p_alien, p->p_buffer, p->dice, p->collision_parameter, time))
    {

#ifdef DEBUG
      libbgc_gas_pointer p_alien_in = libbgc_gas_make_copy(p->p_alien);
      libbgc_gas_pointer p_buffer_in = libbgc_gas_make_copy(p->p_buffer);
#endif

      p->collision_process(p->p_alien, p->p_buffer, p->dice, p->collision_parameter);

#ifdef DEBUG
      libbgc_collision_assert_energy_conservation(p_alien_in, p_buffer_in, p->p_alien, p->p_buffer, 1e-5);

      libbgc_collision_assert_momentum_conservation(p_alien_in, p_buffer_in, p->p_alien, p->p_buffer, 1e-5);
      libbgc_gas_destroy(p_alien_in);
      libbgc_gas_destroy(p_buffer_in);
#endif
    }
}

void libbgc_collision_destroy(libbgc_collision_pointer p)
{
  gsl_rng_free(p->dice);
  libbgc_gas_destroy(p->p_alien);
  libbgc_gas_destroy(p->p_buffer);
}

void libbgc_collision_assert_energy_conservation(const libbgc_gas_pointer p_alien_in, const libbgc_gas_pointer p_buffer_in, const libbgc_gas_pointer p_alien_out, const libbgc_gas_pointer p_buffer_out, double precision)
{
  double energy_in = libbgc_gas_kinetic_energy(p_alien_in) + libbgc_gas_kinetic_energy(p_buffer_in);
  double energy_out = libbgc_gas_kinetic_energy(p_alien_out) + libbgc_gas_kinetic_energy(p_buffer_out);

  double error = energy_in - energy_out;
  if(error<0) error*=-1;
  assert(error/energy_in < precision);

}

void libbgc_collision_assert_momentum_conservation(const libbgc_gas_pointer p_alien_in, const libbgc_gas_pointer p_buffer_in, const libbgc_gas_pointer p_alien_out, const libbgc_gas_pointer p_buffer_out, double precision)
{
  libbgc_vector v_com_1, v_com_2, v_rel, v_err;
  libbgc_gas_lab_to_com(p_alien_in, p_buffer_in, v_com_1, v_rel);
  libbgc_gas_lab_to_com(p_alien_out, p_buffer_out, v_com_2, v_rel);
  
  libbgc_vector_add(v_com_1, 1, v_com_2, -1, v_err);
  assert(libbgc_vector_norm(v_err)/libbgc_vector_norm(v_com_1) < precision);

  libbgc_gas_com_to_lab(p_alien_in, p_buffer_in, v_com_1);
  libbgc_gas_com_to_lab(p_alien_out, p_buffer_out, v_com_2);

}

libbgc_gas_pointer libbgc_collision_get_alien(const libbgc_collision_pointer p)
{
  return p->p_alien;
}

libbgc_gas_pointer libbgc_collision_get_buffer(const libbgc_collision_pointer p)
{
  return p->p_buffer;
}
