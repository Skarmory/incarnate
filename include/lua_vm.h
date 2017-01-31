#ifndef lua_vm_h
#define lua_vm_h

#include <string>
#include "lua_inc.h"

class LuaVM
{
public:
	explicit LuaVM(void);
	~LuaVM(void);

	int call(std::string name);
	int load_script(std::string path);

private:
	lua_State* _vm;
	std::string _scripts_path;
};

#endif
