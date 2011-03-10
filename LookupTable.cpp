#include "LookupTable.h"
#include "LuaFloat.h"
#include "LuaString.h"
#include "LuaFunction.h"
#include <iostream>
using namespace std;

void LookupTable::Add( ast* ptr)
{
	if(ptr == 0)
		return;
	
	if(ptr->tokType == (int)Function)//what ever the (int)Fucntion equals
	{
		cout << "Hello Function " << endl;
		//make a functin
		//to get the fucntions name go left
			//to get the rest of the shit go right
			
		char* str = ptr->left->m_Val.strVal;
		string funcName(str);
		cout << str << endl;
		addFunc(funcName, ptr->right);
		
	}else if(ptr->tokType == _STAT)//what ever the _STAT equals
	{
		cout << "Hello STAT" << endl;
		string var(ptr->left->m_Val.strVal);
		double dvalue = 0;
		string strvalue;
		
		if(ptr->right->tokType == (int) Number)
		{
			dvalue = ptr->right->m_Val.dVal;	
		}else if(ptr->right->tokType == (int) String)
		{
			strvalue = ptr->right->m_Val.strVal;
		}
		else if(ptr->right->tokType == (int) Name)
		{
			cout << "About to break" << endl;
			strvalue = ptr->right->m_Val.strVal;
		}
		else if(ptr->right->tokType == _EXP)
		{
			//strvalue = ptr->right->m_Val.strVal;
			strvalue = "expression";
		}
		
		if(dvalue != 0)
		{
			addVar(var, dvalue);
			cout << "Number " << dvalue << endl;
		}else
		{
			addVar(var, strvalue);
			cout << strvalue << endl;
		}
		
	}else if(ptr->tokType == _PARLIST)//(int)Name)
	{
		string s = ptr->left->m_Val.strVal;
		
		addVar(s, string("parameter"));
	}
	else
	{
		cout << "Skip " << endl;
		cout << "Go Left " << endl;
		Add(ptr->left);
		cout << "Go Right" << endl;
		Add(ptr->right);
	}
}

void LookupTable::addVar(string id, double value)
{
	table.push_back(new LuaFloat(id, value));
}
void LookupTable::addVar(string id, string value)
{
	table.push_back(new LuaString(id, value));
}
void LookupTable::addFunc(string id, ast* funcBody)
{
	table.push_back(new LuaFunction(id, funcBody));
}
vector<LuaObject *> & LookupTable::SymbolTable()
{
	return table;
}