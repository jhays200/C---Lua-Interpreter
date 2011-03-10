#pragma once

#include "LuaObject.h"
#include "LookupTable.h"
//#include <string>
//using std::string;

class LuaFunction: public LuaObject
{
	private:
		LookupTable lt;
	public:
		LuaFunction();
		LuaFunction(string id, ast* funcBody);
		~LuaFunction();
		//virtual LuaObject& operator=(LuaObject& rhs);
		LookupTable& getLT();
		void DisplayValue();
		virtual int getType();
};
