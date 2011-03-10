#pragma once
#include "LuaParser.hpp"
#include <iostream>
using std::cout;
using std::endl;

#define _CHUNK 1
#define _BLOCK 2
#define _LASTSTAT 3
#define _STAT 4
#define _EXP 5
#define _COMPARE 6
#define _FUNCCALL 7
#define _ARGS 8
#define _ELSE 9
#define _FUNCBODY 10
#define _PARLIST 11

struct ast;

union value{
	double dVal;
	char op;
	char* strVal;
	ast* moreTree;
};

struct ast
{

	int tokType;
	ast* left;
	ast* right;
	value m_Val;
	
	ast(int type, ast* leftnode, ast* rightnode, value* val=0)
	{
		tokType = type; left = leftnode; right = rightnode;
		
		if(val != 0)
			m_Val = *val;
		
	}
	
	static void visit(ast * current)
	{
		if(current != 0)
		{
			current->DisplayType();
			visit(current->left);
			visit(current->right);
		}
	}
	
	void visit()
	{
		visit(this);
	}
	
	void DisplayType()
	{
		switch(tokType)
		{
			case _CHUNK:
				cout << "I'm a Chunk" << endl;
				break;
			case _BLOCK:
				cout << "I'm a Block" << endl;
				break;
			case _LASTSTAT:
				cout << "I'm LASTSTAT" << endl;
				break;
			case _STAT:
				cout << "I'm a STAT" << endl;
				break;
			case _EXP:
				cout << "I'm a EXP" << endl;
				break;
				
			case _COMPARE:
				cout << "I'm a Compare statement" << endl;
				break;
			case _FUNCCALL:
				cout << "I'm a Function Call" << endl;
				break;
			
			case _ARGS:
				cout << "I'm Arguments" << endl;
				break;
				
			case _ELSE:
				cout << "I'm an Else statement" << endl;
				break;
			case _FUNCBODY:
				cout << "I'm a function body" << endl;
				break;
				
			case _PARLIST:
				cout << "I'm a Parlist" << endl;
				break;
			
			case (int)Function:
				//We should write to the symbol table passing it this 
					//this should only occure when we are creating a funciton
				//Need to make sure to add the paramaters under this sumbtree
				cout << "Function stuff: " << endl;
				break;
			default:
				cout<< "Tok: " << tokType << endl;
				//cout << m_Val.strVal << endl;
				break;
		}
		
		cout << left << " " << right << endl;
	}
	
};

