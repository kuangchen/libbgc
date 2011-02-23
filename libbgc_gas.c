#include "libbgc_gas.h"
#include "libbgc_vector.h"
#include "libbgc_collision.h"
#include <stdlib.h>
#include <string.h>


struct _libbgc_gas
{
  libbgc_gas_description description;
  double mass;
  double charge;
  libbgc_vector position;
  libbgc_vector velocity;
  void* other_property;
};

libbgc_gas_pointer libbgc_gas_create(const libbgc_gas_tag_pointer tag_pointer)
{
  libbgc_gas_pointer p = malloc(sizeof(libbgc_gas));
  strncpy(p->description, tag_pointer->description, BGC_GAS_DESCRIPTION_MAX_LENGTH);
  p->mass = tag_pointer->mass;
  p->charge = tag_pointer->charge;
  p->other_property = tag_pointer->other_property;
  return p;
}

void libbgc_gas_destroy(libbgc_gas_pointer p)
{
  free(p);
}

void libbgc_gas_lab_to_com(libbgc_gas_pointer p1, libbgc_gas_pointer p2, libbgc_vector v_com, libbgc_vector v_rel)
{
  double total_mass = p1->mass + p2->mass;
  double q1 = p1->mass / total_mass;
  double q2 = p2->mass / total_mass;
  int i=0;
  for(i=0;i<3;i++)
    {
      v_com[i] = p1->velocity[i]*q1 + p2->velocity[i]*q2;
      v_rel[i] = p1->velocity[i] - p2->velocity[i];
      p1->velocity[i] = q2 * v_rel[i];
      p2->velocity[i] =-q1 * v_rel[i];
    }
}

double libbgc_gas_mass(const libbgc_gas_pointer p)
{
  return p->mass;
}

void libbgc_gas_get_velocity(const libbgc_gas_pointer p, libbgc_vector velocity)
{
  memcpy(velocity, p->velocity, sizeof(libbgc_vector));
}

void libbgc_gas_get_momentum(const libbgc_gas_pointer p, libbgc_vector momentum)
{
  libbgc_vector v;
  memcpy(v, p->velocity, sizeof(libbgc_vector));
  libbgc_vector_multiply(v, p->mass, momentum);
}

void libbgc_gas_get_position(const libbgc_gas_pointer p, libbgc_vector position)
{
  memcpy(position, p->position, sizeof(libbgc_vector));
}

void libbgc_gas_set_velocity(libbgc_gas_pointer p, const libbgc_vector velocity)
{
  memcpy(p->velocity, velocity, sizeof(libbgc_vector));
}

void libbgc_gas_set_position(libbgc_gas_pointer p, const libbgc_vector position)
{
  memcpy(p->position, position, sizeof(libbgc_vector));
}

void libbgc_gas_set_momentum(libbgc_gas_pointer p, const libbgc_vector momentum)
{
  libbgc_vector v;
  libbgc_vector_multiply(momentum, 1/p->mass, v);
  memcpy(p->velocity, v, sizeof(libbgc_vector));
}

void libbgc_gas_com_to_lab(libbgc_gas_pointer p1, libbgc_gas_pointer p2, libbgc_vector v_com)
{
  int i=0;
  for(i=0;i<3;i++)
    {
      p1->velocity[i] += v_com[i];
      p2->velocity[i] += v_com[i];
    }
}

double libbgc_gas_kinetic_energy(const libbgc_gas_pointer p)
{
  return 0.5*p->mass*libbgc_vector_sqr(p->velocity);
}

libbgc_gas_pointer libbgc_gas_make_copy(const libbgc_gas_pointer p)
{
  libbgc_gas_pointer pnew = malloc(sizeof(libbgc_gas));  
  memcpy(pnew, p, sizeof(libbgc_gas));
  return pnew;
}
