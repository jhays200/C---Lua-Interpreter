#include "LuaFloat.h"
#include <cstdio>

LuaFloat::LuaFloat(): LuaObject(), m_value(0)
{	}
LuaFloat::LuaFloat(string id, double value):LuaObject(id), m_value(value)
{	}
LuaFloat::~LuaFloat()
{	}
LuaObject& LuaFloat::operator=(LuaObject& rhs)
{//Assuming the scope is correct
	if(rhs.getType() == LuaObject::DOUBLE)
	{
		this->setValue(dynamic_cast<LuaFloat*>(&rhs)->getValue());
	}else
	{
		//nope, this shit is not a float
			//error out?
	}

	return *this;
}
double LuaFloat::getValue() const
{
	return m_value;
}
void LuaFloat::DisplayValue()
{
	//id value type
	printf("%s %f Double\n", getID().c_str(), m_value);
}
void LuaFloat::setValue(double value)
{
	m_value = value;
}
LuaObject LuaFloat::operator+(LuaObject& rhs)
{
	LuaFloat tFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp += dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat.setValue(temp);
	}else
	{
		//nope, this shit is not a float
			//error out?
	}
	return tFloat;
}
LuaObject LuaFloat::operator-(LuaObject & rhs)
{
	LuaFloat tFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp -= dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat.setValue(temp);
	}else
	{
		//nope, this shit is not a float
			//error out?
	}
	return tFloat;
}
LuaObject LuaFloat::operator/(LuaObject & rhs)
{
	LuaFloat tFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp /= dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat.setValue(temp);
	}else
	{
		//nope, this shit is not a float
			//error out?
	}
	return tFloat;
}
LuaObject LuaFloat::operator*(LuaObject & rhs)
{
	LuaFloat tFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp *= dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat.setValue(temp);
	}else
	{
		//nope, this shit is not a float
			//error out?
	}
	return tFloat;
}
int LuaFloat::getType()
{
	return LuaObject::DOUBLE;
}