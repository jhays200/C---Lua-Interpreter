#include "LuaFunction.h"
#include <cstdio>

LuaFunction::LuaFunction(): LuaObject()
{	}
LuaFunction::LuaFunction(string id, ast* funcBody): LuaObject(id)
{
	printf("Trying to make a new table\n");
	lt.Add(funcBody);
}
void LuaFunction::DisplayValue()
{
	//id value type
	printf("%s Function* Function\n", getID().c_str());
	vector<LuaObject *> & symbols = lt.SymbolTable();

	for(vector<LuaObject *>::iterator i = symbols.begin(); i != symbols.end(); ++i)
	{
		printf("\t");
		(*i)->DisplayValue();
	}
}
LookupTable& LuaFunction::getLT()
{
	return lt;
}
int LuaFunction::getType()
{
	return LuaObject::FUNCTION;
}