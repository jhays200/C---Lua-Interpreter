#pragma once

#include "LuaObject.h"
//#include <string>
//using std::string;

;class LuaString: public LuaObject
{

	private:
		string m_value;
	public:
		LuaString();
		LuaString(string id, string value);
		~LuaString();
		virtual LuaObject& operator=(LuaObject & rhs);
		void setValue(string value);
		string getValue() const;
		void DisplayValue();
		virtual LuaObject operator+(LuaObject & rhs);
		virtual int getType();
};