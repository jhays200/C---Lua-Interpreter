#pragma once

#include "LuaObject.h"

class LuaFloat: public LuaObject
{
private:
	double m_value;

public:
	LuaFloat();
	LuaFloat(string id, double value);
	~LuaFloat();
	virtual LuaObject& operator=(LuaObject & rhs);
	void DisplayValue();
	double getValue() const;
	void setValue(double value);
	virtual LuaObject operator+(LuaObject & rhs);
	virtual LuaObject operator-(LuaObject & rhs);
	virtual LuaObject operator/(LuaObject & rhs);
	virtual LuaObject operator*(LuaObject & rhs);
	virtual int getType();
};