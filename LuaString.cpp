#include "LuaString.h"
#include <cstdio>

LuaString::LuaString(): LuaObject()
{	}
LuaString::LuaString(string id, string value): LuaObject(id), m_value(value)
{	}
LuaString::~LuaString()
{	}
LuaObject& LuaString::operator=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
	{
		this->setValue(dynamic_cast<LuaString*>(&rhs)->getValue());
	}else
	{
		//ERRORS
	}
	return *this;
}
void LuaString::setValue(string value)
{
	m_value = value;
}
string LuaString::getValue() const
{
	return m_value;
}
void LuaString::DisplayValue()
{
	//id value type
	printf("%s %s string\n", getID().c_str(), getValue().c_str());
}
LuaObject LuaString::operator+(LuaObject & rhs)
{
	LuaString tString("","");

	if(rhs.getType() == LuaObject::STRING)
	{
		string temp = this->getValue();
		temp += dynamic_cast<LuaString*>(&rhs)->getValue();
		tString.setValue(temp);
	}else
	{
		//ERRORS
	}

	return tString;
}
int LuaString::getType()
{
	return LuaObject::STRING;
}