// api.c modding api for modding minecraft
// custom syntaxes

 //* Lua side is accessed via the global table  "mlua"  which contains
// * sub-tables for every domain:
//*
 //*   mlua.world.*      – block / chunk / time / weather
 //*   mlua.entity.*     – spawn / move / health / AI
// *   mlua.player.*     – inventory / message / teleport
// *   mlua.item.*       – query registered items
 //*   mlua.block.*      – query registered blocks
 //*   mlua.registry.*   – register blocks, items, entities, recipes
 //*   mlua.event.*      – listen to game events
 //*   mlua.physics.*    – rigid-body simulation helpers
 //*   mlua.vec3.*       – 3-D vector math
 //*   mlua.combat.*     – weapons, damage, projectiles
 //*   mlua.effects.*    – particles, sounds, explosions
 //*   mlua.game.*       – tick count, version, logging
 
#include "api.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <assert.h>

// iternal helpers

// retrieve the MluaState pointer stored in the lua registry
static MluaState *_get_state(lua_State *L)
{
    lua_pushlightuserdata(L, (void *)&_get_state);
    lua_gettable(L, LUA_REGISTRYINDEX);
    MLuaState *s = (MLuaState *)lua_touserdata(L, -1);
    lua_pop(L, 1);
    return s;
}

// push a mluavec3 as a lua table {x,yz}
void _mlua_push_vec3(lua_State *L, MLuaVec3 v)
{
    lua_createtable(L, 0, 3);
    lua_pushnumber(L, v.x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, v.y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, v.z); lua_setfield(L, -2, "z");
}

// read a mluavec3 from a lua table at stack index idx stuff
int _mlua_check_vec3(lua_State *L, int idx, MLuaVec3 *out)
{
    if (!lua_istable(L, idx)) return 0;
    lua_getfield(L, idx, "x"); out->x = lua_tonumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, idx, "y"); out->y = lua_tonumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, idx, "z"); out->z = lua_tonumber(L, -1); lua_pop(L, 1);
    return 1;
}

// push an inventory slot as a lua table thingys
void _mlua_push_hit(lua_State *L, const MLuaRayHit *h)
{
    lua_createtable(L, 0, 8);
    _mlua_push_vec3(L, h->point);  lua_setfield(L, -2, "point");
    _mlua_push_vec3(L, h->normal); lua_setfield(L, -2, "normal");
    lua_pushnumber (L, h->distance);   lua_setfield(L, -2, "distance");
    lua_pushinteger(L, h->block_x);    lua_setfield(L, -2, "block_x");
    lua_pushinteger(L, h->block_y);    lua_setfield(L, -2, "block_y");
    lua_pushinteger(L, h->block_z);    lua_setfield(L, -2, "block_z");
    lua_pushinteger(L, h->block_id);   lua_setfield(L, -2, "block_id");
    lua_pushinteger(L, h->entity_id);  lua_setfield(L, -2, "entity_id");
    lua_pushboolean(L, h->hit_block);  lua_setfield(L, -2, "hit_block");
    lua_pushboolean(L, h->hit_entity); lua_setfield(L, -2, "hit_entity");
}

void _mlua_set_error(MLuaState *state, const char *fmt, ...)