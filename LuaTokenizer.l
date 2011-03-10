%option noyywrap
%{
  extern "C"
  {
	int yylex(void);
  }
#include "LuaParser.tab.h"
#include "LexFun.h"
#include <stdio.h>
%}

%%

"function " {return Function;}
"if" {return If;}
"elseif" {return Elseif;}
"else" {return Else;}

"while" {return While;}
"then" {return Then;}
"do" {return Do;}

"true" {return True;}
"false" {return False;}
"nil" {return Nil;} 

"return" {return Return;} /*{printf("return Token\n");}*/
"break" {return Break;} /*{printf("break Token\n");}*/

"end" {return End;} /*{printf("end Token\n");}*/

"==" {return IsEqual;} /*{printf("Is Equal Token\n");}*/
"~=" {return NotEqual;} /*{printf("Not Equal Token\n");}*/

"<" {return '<';} /*{printf("Less Than Token\n");}*/
">" {return '>';} /*{printf("Gater Than Token\n");}*/

"=" {return '=';} /*{printf("Equals Token\n");}*/
"+" {return '+';} /*{printf("Add Token\n");}*/
"-" {return '-';} /*{printf("Sub Token\n");}*/
"*" {return '*';} /*{printf("Mult Token\n");}*/
"/" {return '/';} /*{printf("Div Token\n");}*/
"(" {return '(';}
")" {return ')';}

\n|\; {/*return Eol;*/} /*{printf("Eol Token\n");}*/
\"[^\"]\" {yylval.strval = strdup(yytext); return String;} /*{printf("String Literal Token\n");}*/
[0-9]+ {yylval.floatval = atof(yytext); return Number;} /*{printf("A Number Token\n");}*/
[a-zA-Z_][a-zA-Z0-9_]* {yylval.strval = strdup(yytext); return Name;} /*{printf("Name Token\n");}*/
. {;}

%%

void SetYYIN(const char * filePath)
{
  yyin = fopen(filePath, "r");
}

void CloseYYIN()
{
  fclose(yyin);
}

// int main(void)
// {
//   yylex();
// 
//   return 0;
// }

/////////////////////////////////////////////////////////////////////////////
// programs section
