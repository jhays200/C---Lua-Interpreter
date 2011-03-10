#pragma once

#include "publicInfo.h"
#include <string>
using std::string;

class LuaObject
{
	private:

		string m_id;

	public:

		const static int STRING = 1;
		const static int DOUBLE = 2;
		const static int FUNCTION = 3;
		const static int NIL = 0;

		LuaObject();
		LuaObject(string id);
		~LuaObject();
		virtual LuaObject& operator=( LuaObject& rhs);
		string getID();
		void setID(string id);
		bool operator==(const string & rhs);
		virtual void DisplayValue();
		virtual LuaObject operator+( LuaObject & rhs);
		virtual int getType();
};