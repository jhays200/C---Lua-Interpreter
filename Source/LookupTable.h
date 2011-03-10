#pragma once

#include <string>
#include <vector>
#include "publicInfo.h"
using std::vector;
using std::string;

class LuaObject;


class LookupTable
{
	public:
		void Add( ast* ptr);
		vector<LuaObject *> & SymbolTable();
		//data members
	private:
		vector<LuaObject *> table;
		void addVar(string varname, double value);
		void addVar(string varname, string value);
		void addFunc(string id, ast* funcBody);

};