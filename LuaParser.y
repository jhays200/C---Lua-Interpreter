/*token literals*/
%{
#include "LookupTable.h"
#include "LexFun.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "publicInfo.h"
#include "LuaObject.h"
using std::cout;
using std::endl;


void yyerror(const char *s)
{
	cout << "error: " << s << endl;
}

extern "C"
{
	int yylex(void);
}

ast * global_head;

%}

%union {
	double floatval;
	char * strval;
	struct ast * tree;
}

/*Variable types*/
%token <strval> Name
%token <floatval> Number
%token <strval> String

/*End of line*/
//%token Eol

/*keywords*/
%token Function
%token If
%token Elseif
%token Else

%token While
%token Then
%token Do

%token True
%token False
%token Nil
%token End

%token Return
%token Break

/*comparison ops*/
%token IsEqual
%token NotEqual

%type <tree> CHUNK BLOCK LASTSTAT STAT EXP ARGS FUNCALL ELSE FUNCBODY PARLIST
%type <strval> COMPARE

%left '+' '-'
%left '*' '/'

%start CHUNK
%%

CHUNK: BLOCK LASTSTAT 
{
    cout << "Yay a Chunk" << endl;
	global_head = new ast(_CHUNK, $1, $2);
	$$ = global_head;
}
;

BLOCK: STAT BLOCK 
{

    cout << "Yay a block and more " << $1 << "  " << $2 <<endl;
    $$ = new ast(_BLOCK, $1, $2);
}
| {cout << "Yay a lambda" << endl; $$ = 0;}
;

LASTSTAT: Return EXP 
{
	value tmp;
    cout << "EXP returned" << endl;
    ast* stuff = new ast ((int)(Return), 0, 0);
    $$ = new ast(_LASTSTAT, stuff, $2);
}
|Break 
{
    cout << "Break found" << endl;
    ast* stuff = new ast ((int)(Break), 0, 0);
    $$ = new ast(_LASTSTAT, 0, stuff); 
}
|
{
	cout << "No Last Stat" << endl;
	$$ = 0;
}
;

STAT: Name '=' EXP 
{
	value tmp;
	tmp.strVal = $1;
    cout << "New variable " << $1 << "and i equal" << $3<< endl;

    ast* stuff = new ast ((int)(Name), 0,0, &tmp);
	tmp.op = '=';
    $$ = new ast(_STAT, stuff, $3, &tmp);
}
| FUNCALL 
{
    cout << "Function Call" << endl;
    $$ = new ast(_FUNCCALL, 0, $1);
}
| While EXP Do CHUNK End 
{
    cout << "While loop" << endl;
    $$ = new ast((int)While, $2, $4);
}
| If EXP Then CHUNK ELSE End 
{
    cout << "If statement" << endl;
    value tmp;
    tmp.moreTree = $5; //the else
    ast * ifExp = new ast ((int)If, $2, $4, &tmp);
    $$ = ifExp;
}
| Function Name FUNCBODY 
{
	value tmp;
	tmp.strVal = $2;
	
    cout << "Function definition " << $2 << endl;    
    ast* stuff = new ast((int)(Name), 0, 0, &tmp);
    $$ = new ast((int)Function, stuff, $3);
}    
;

EXP: Nil 
{
    cout << "Nil Found" << endl;
    $$ = new ast ((int)Nil,0,0);
}
| True 
{
    cout << "True Found" << endl;
    $$ = new ast ((int)True, 0,0);
}
| False 
{
    cout << "False Found" << endl;
    $$ = new ast ((int)False, 0,0);
}
| String 
{
	value tmp;
	tmp.strVal = $1;
    cout << "String Found " << $1 << endl;
    $$ = new ast ((int)String, 0, 0, &tmp);
}
| Number 
{
	value tmp;
	tmp.dVal = $1;
	cout << "I'm a number " << $1 << endl;
	$$ = new ast ((int)Number, 0, 0, &tmp);
		
}
	| Name 
	{
		value tmp;
		tmp.strVal = $1;
		$$ = new ast(int(Name), 0, 0, &tmp);
		cout << "Hi I'm var " << $1 << endl;
		
}
	| FUNCALL 
	{
		cout << "Hi function call" << endl;
		$$ = new ast(_FUNCCALL, 0, $1);
}
| EXP '+' EXP 
{
	value tmp;
	cout << "Add" << endl;
	tmp.op = '+';
	$$ = new ast(_EXP, $1, $3, &tmp);
}
| EXP '-' EXP 
{
	value tmp;
	cout << "Subtract" << endl;
	tmp.op = '-';
	$$ = new ast(_EXP, $1, $3, &tmp);
}
| EXP '*' EXP 
{
	value tmp;
	cout << "MULT" << endl;
	tmp.op = '*';
	$$ = new ast(_EXP, $1, $3, &tmp);
}
| EXP '/' EXP 
{
	value tmp;
	tmp.op = '/';
	$$ = new ast(_EXP, $1, $3, &tmp);
	cout << "DIV" << endl;
}
| EXP COMPARE EXP
{
	value tmp;
	tmp.op = $2[0];
	$$ = new ast(_EXP, $1, $3, &tmp);
	cout << "EXP COMPARE EXP" << endl;
		
}
;

COMPARE: '<'{cout << "Less Then" << endl; $$ = "<";}
		| IsEqual 
		{
			cout << "Is Equal" << endl; 
			$$ = "=";
		}
		| '>'
		{
			cout << "Greater Then" << endl;
			$$ = ">";
		}
		| NotEqual {cout << "Not Equal" << endl; $$ = "!";}
; 

FUNCALL: Name '(' ARGS ')' 
		{
			cout << "Function Call with args: " << $1 << endl; //free($1);
			value tmp;
			tmp.strVal = $1;
			ast * namePtr = new ast( (int)Name, 0, 0, &tmp);
			$$ = new ast(_FUNCCALL, namePtr, $3);
		}
		| Name '(' ')' 
		{
			ast * stuff = 0;
			value tmp;
			tmp.strVal = $1;
			
			stuff = new ast( (int)Name, 0, 0, &tmp);
			$$ = new ast( _FUNCCALL, stuff, 0);
							 
			cout << "Function Call without args: " << $1 << endl;
			
		}
;

ARGS: Name ',' ARGS 
		{
			ast * stuff = 0;
			value tmp;
			tmp.strVal = $1;
			stuff = new ast( (int)Name, 0, 0, &tmp);
			cout << "String: " << $1 << endl;
			
			$$ = new ast(_ARGS, stuff, $3);
		}	
	| String ',' ARGS 
	{
		ast * stuff = 0;
		value tmp;
		tmp.strVal = $1;
		stuff = new ast( (int)String, 0, 0, &tmp);
		cout << "String: " << $1 << endl;
		
		$$ = new ast(_ARGS, stuff, $3);
	}
	| Number ',' ARGS 
	{
		ast * stuff = 0;
		value tmp;
		tmp.dVal = $1;
		stuff = new ast( (int)Number, 0, 0, &tmp);
		
		cout << "Number: " << $1 << endl;
		$$ = new ast( _ARGS, stuff, $3);
	}
	| Name 
	{
		value tmp;
		tmp.strVal = $1;
		cout << "Variable: " << $1 << endl;
		$$ = new ast( (int)Name, 0, 0, &tmp);
	}
	| String 
	{
		value tmp;
		tmp.strVal = $1;
		cout << "String: " << $1 << endl; 
		$$ = new ast( (int)String, 0, 0, &tmp);
	}
	| Number 
	{
		value tmp;
		cout << "Number: " << $1 << endl;
		tmp.dVal = $1;
		$$ = new ast( (int)Number, 0, 0, &tmp);
	}
;

ELSE: Elseif EXP Then CHUNK ELSE
		{
			value tmp;
			tmp.moreTree = $5;
			cout << "Elseif statement" << endl;
			$$ = new ast(_ELSE, $2, $4, &tmp)
		}
	| Else CHUNK
	{
		cout << "Else block" << endl;
		$$ = new ast(_ELSE, 0, $2)
	}
	|{cout << "No Else" << endl; $$=0}
;

FUNCBODY: '(' ')' CHUNK End 
			{
				cout << "Function body without parameters" << endl;
				$$ = new ast(_FUNCBODY, 0, $3);
			}
		|'(' PARLIST ')' CHUNK End 
		{
			cout << "Function body with parameters" << endl;
			$$ = new ast( _FUNCBODY, $2, $4);
		}
;

PARLIST: Name 
		{
			value tmp;
			tmp.strVal = $1;
			cout << "Param: " << $1 << endl;
			ast * stuff = new ast( (int)Name, 0, 0, &tmp);
			$$ = new ast( _PARLIST, stuff, 0);
		}
		| Name ',' PARLIST 
		{
			value tmp;
			tmp.strVal = $1;
			cout << "Param: " << $1 << endl; 
			ast * stuff = new ast( (int)Name, 0, 0, &tmp);
			$$ = new ast(_PARLIST, stuff, $3);
		}
;

%%

int main(void)
{
	LookupTable global_scope;
	SetYYIN("./lua.txt");
	yyparse();
	cout << "\n\n\n";
	CloseYYIN();
	
	global_head->visit();
	cout << "\n\n\n";
	
	global_scope.Add(global_head);
	cout << "I made it\n\n" << endl;
	
	//global_scope.DisplayValue();
	for(vector<LuaObject *>::iterator i = global_scope.SymbolTable().begin(); i != global_scope.SymbolTable().end();
			++i)
		{
			//cout << "HI Guys";
			(*i)->DisplayValue();
		}
}

