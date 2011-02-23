#include <stdlib.h>

#include "lualibbgc_hs.h"
#include "../c/libbgc_collision.h"
#include "../c/libbgc_gas.h"

static void lualibbgc_hs_parse_alien_tag(lua_State *L, libbgc_gas_tag_pointer p_tag)
{
  luaL_getfield(L, -1, "description");
  strncpy(p_tag->description, lua_tostring(L, -1), BGC_GAS_DESCRIPTION_MAX_LENGTH);

  luaL_getfield(L, -2, "mass");
  p_tag->mass = lua_tonumber(L, -1);

  luaL_getfield(L, -3, "charge");
  p_tag->charge = lua_tonumber(L, -1);
  
  lua_pop(L, 3);
}

static void lualibbgc_hs_parse_buffer_tag(lua_State *L, libbgc_gas_tag_pointer p_tag)
{
  luaL_getfield(L, -1, "description");
  strncpy(p_tag->description, lua_tostring(L, -1), BGC_GAS_DESCRIPTION_MAX_LENGTH);

  luaL_getfield(L, -2, "mass");
  p_tag->mass = lua_tonumber(L, -1);

  luaL_getfield(L, -3, "charge");
  p_tag->charge = lua_tonumber(L, -1);
  
  lua_pop(L, 3);
}

static void lualibbgc_hs_parse_collision_parameter(lua_State *L, libbgc_hs_parameter* p_parameter)
{
  luaL_getfield(L, -1, "buffer_temperature");
  p_parameter->buffer_temperature = lua_tonumber(L, -1);

  luaL_getfield(L, -1, "buffer_pressure");
  p_parameter->buffer_pressure = lua_tonumber(L, -1);

  luaL_getfield(L, -1, "cross_section");
  p_parameter->cross_section = lua_tonumber(L, -1);
  
  lua_pop(L, 3);
}

int lualibbgc_hs_create(lua_State* L)
{
  //hs.create({alien_tag={}, buffer_tag={}, parameter={})
  libbgc_collision_pointer p = (libbgc_collision_pointer)lua_newuserdata(L, sizeof(libbgc_collision));

  libbgc_gas_tag alien_tag, buffer_tag;
  libbgc_hs_parameter hs_parameter;
  luaL_getfield(L, 1, "alien_tag");
  lualibbgc_hs_parse_alien_tag(L, &alien_tag);

  luaL_getfield(L, 1, "buffer_tag");
  lualibbgc_hs_parse_buffer_tag(L, &buffer_tag);

  luaL_getfield(L, 1, "collision_parameter");
  lualibbgc_hs_parse_collision_parameter(L, &collision_parameter);

  libbgc_collision_tag collision_tag = {
      .alien_tag = alien_tag, 
      .buffer_tag = buffer_tag,
      .collision_process = libbgc_collision_hard_sphere_process,
      .collision_timer = libbgc_collision_hard_sphere_timer,
      .collision_parameter = collision_parameter
  };

  libbgc_collision_create(&collision_tag);
  
  
  return 1;  /* new userdatum is already on the stack */
}
