#include "LuaObject.h"
#include <cstdio>

LuaObject::LuaObject(): m_id("")
{	}
LuaObject::LuaObject(string id): m_id(id)
{	}
LuaObject::~LuaObject()
{	}
LuaObject& LuaObject::operator=( LuaObject& rhs)
{
	//error

	return *this;
}
void LuaObject::setID(string id)
{
	m_id = id;
}
string LuaObject::getID()
{
	return m_id;
}
bool LuaObject::operator==(const string & rhs)
{
	return m_id == rhs;
}
void LuaObject::DisplayValue()
{
	//id value type
	printf("%s Nil LuaObject\n", m_id.c_str());
}
int LuaObject::getType()
{
	return NIL;
}
LuaObject LuaObject::operator+( LuaObject& rhs)
{
	//ERROR
	return *this;
}