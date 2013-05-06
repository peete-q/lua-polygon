
#include <vector>

#include "lua.hpp"

#include "poly2tri.h"


#if (LUA_VERSION_NUM >= 502)
#define luaL_register(L,n,f)	luaL_newlib(L,f)
#endif

#define luaL_check(c, ...)		if (!(c)) luaL_error(L, __VA_ARGS__)

#define AUTHORS 	"Peter.Q"
#define VERSION		"LuaPolygon 1.0"
#define RELEASE		"LuaPolygon 1.0.1"

static int api_triangulate(lua_State *L)
{
	int args = lua_gettop(L);
	luaL_check(args >= 6, ("need more vertices '%d'", args));
	
	std::vector<p2t::Point*> verts;
	for (int i = 1; i <= args; i += 2)
		verts.push_back(new p2t::Point(lua_tonumber(L, i), lua_tonumber(L, i + 1)));

	p2t::CDT* cdt = new p2t::CDT(verts);
	cdt->Triangulate();
	std::vector<p2t::Triangle*> tris = cdt->GetTriangles();
	lua_newtable(L);
	for (size_t i = 0; i < tris.size(); ++i)
	{
		lua_newtable(L);
		
		lua_pushnumber(L, tris[i]->GetPoint(0)->x);
		lua_rawseti(L, -2, 1);
		lua_pushnumber(L, tris[i]->GetPoint(0)->y);
		lua_rawseti(L, -2, 2);
		lua_pushnumber(L, tris[i]->GetPoint(1)->x);
		lua_rawseti(L, -2, 3);
		lua_pushnumber(L, tris[i]->GetPoint(1)->y);
		lua_rawseti(L, -2, 4);
		lua_pushnumber(L, tris[i]->GetPoint(2)->x);
		lua_rawseti(L, -2, 5);
		lua_pushnumber(L, tris[i]->GetPoint(2)->y);
		lua_rawseti(L, -2, 6);
		
		lua_rawseti(L, -2, i + 1);
	}
	for (size_t i = 0; i < verts.size(); ++i)
		delete verts[i];
	delete cdt;
	return 1;
}

static const struct luaL_Reg thislib[] = {
	{"triangulate", api_triangulate},
	{NULL, NULL}
};

extern "C" {
	LUALIB_API int luaopen_polygon (lua_State *L);
}

LUALIB_API int luaopen_polygon (lua_State *L) {
	luaL_register(L, "polygon", thislib);
	
	lua_pushstring(L, "VERSION");
	lua_pushstring(L, VERSION);
	lua_settable(L, -3);
	
	lua_pushstring(L, "RELEASE");
	lua_pushstring(L, RELEASE);
	lua_settable(L, -3);
	
	lua_pushstring(L, "AUTHORS");
	lua_pushstring(L, AUTHORS);
	lua_settable(L, -3);
	return 1;
}

