%{
  // Definitions
#include "parser.tab.h"

#define DEF_LINENUMBER yylval.valor_lexico.numeroLinha = lineNumber;

#define DEF_ISLITERAL yylval.valor_lexico.isLiteral = true;

#define DEF_NOTLITERAL yylval.valor_lexico.isLiteral = false;

#define DEF_PALAVRA_RESERVADA yylval.valor_lexico.tipo  = Tvoid;\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);\

#define DEF_OPERACAO yylval.valor_lexico.tipo  = Tvoid;\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);

#define DEF_TYPE_CHAR  yylval.valor_lexico.tipo  = Tchar; 

#define DEF_TYPE_INT yylval.valor_lexico.tipo  = Tint; 

#define DEF_TYPE_IDENTIFICADOR yylval.valor_lexico.tipo  = Tvoid; 

#define DEF_TYPE_FLOAT yylval.valor_lexico.tipo  = Tfloat;

#define DEF_TYPE_BOOL yylval.valor_lexico.tipo  = Tbool;

#define DEF_TYPE_STRING yylval.valor_lexico.tipo  = Tstring; 

#define DEF_LIT_CHAR DEF_TYPE_CHAR; \
  DEF_ISLITERAL\
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = calloc(2, sizeof(char));\
  yylval.valor_lexico.stringValue[0] =  yytext[1];\
  yylval.valor_lexico.stringValue[1] =  '\0';\
  yylval.valor_lexico.charValue = yytext[1]; 

#define DEF_LIT_TRUE DEF_TYPE_BOOL; \
  DEF_ISLITERAL\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);\
  yylval.valor_lexico.boolValue = true;

#define DEF_LIT_FALSE DEF_TYPE_BOOL; \
  DEF_ISLITERAL\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);\
  yylval.valor_lexico.boolValue = false;

#define DEF_LIT_INT DEF_TYPE_INT; \
  DEF_ISLITERAL\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);\
  yylval.valor_lexico.intValue = atoi(yytext);\

#define DEF_LIT_STRING DEF_TYPE_STRING; \
  DEF_ISLITERAL\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);\

#define DEF_LIT_FLOAT DEF_TYPE_FLOAT; \
  DEF_ISLITERAL\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.stringValue =strdup(yytext);\
  yylval.valor_lexico.floatValue = atof(yytext);\

#define DEF_IDENTIFICADOR \
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue = strdup(yytext);\

int lineNumber=1;
int get_line_number();




%}

%x COMMENT_MULT_LINE


%%
[\t]+ {}
\n  {lineNumber++;}

"//".*  {}
"/*".                        BEGIN(COMMENT_MULT_LINE);
<COMMENT_MULT_LINE>.*"*/"    BEGIN(INITIAL);
<COMMENT_MULT_LINE>\n        { lineNumber++; }
<COMMENT_MULT_LINE>.         {  }


[,;:()\[\]{}.$~`@] {
    return yytext[0];
}
"?" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"=" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"<" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
">" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"+" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"%" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"|" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"^" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"-" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"*" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"/" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"!" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"&" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}
"#" {    DEF_LINENUMBER; DEF_OPERACAO; return yytext[0];}

"int"       { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_INT; }
"float"     { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_FLOAT; }
"bool"      { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_BOOL; }
"char"      { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_CHAR; }
"string"    { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_STRING; }
"if"        { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_IF; }
"then"      { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_THEN; }
"else"      { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_ELSE; }
"while"     { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_WHILE; }
"do"        { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_DO; }
"input"     { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_INPUT; }
"output"    { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_OUTPUT; }
"return"    { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_RETURN; }
"const"     { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_CONST; }
"static"    { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_STATIC; }
"foreach"   { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_FOREACH; }
"for"       { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_FOR; }
"switch"    { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_SWITCH; }
"case"      { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_CASE; }
"break"     { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_BREAK; }
"continue"  { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_CONTINUE; }
"class"     { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_CLASS; }
"private"   { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_PRIVATE; }
"public"    { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_PUBLIC; }
"protected" { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_PROTECTED; }
"end" { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_END; }
"default" { DEF_LINENUMBER; DEF_PALAVRA_RESERVADA; return TK_PR_DEFAULT; }


" " {}
"<="  {DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_LE; }
">="  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_GE; }
"=="  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_EQ; }
"!="  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_NE; }
"&&"  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_AND; }
"||"  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_OR; }
"<<"  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_SL; }
">>"  { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_SR; }
"%>%" { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_FORWARD_PIPE; }
"%|%" { DEF_LINENUMBER; DEF_OPERACAO; return TK_OC_BASH_PIPE; }

"false" {DEF_LINENUMBER; DEF_LIT_FALSE; return TK_LIT_FALSE; }
"true"  { DEF_LINENUMBER; DEF_LIT_TRUE; return TK_LIT_TRUE; }
'.'               { DEF_LINENUMBER; DEF_LIT_CHAR; return TK_LIT_CHAR; }
\"([^\\"]|\\.)*\" {DEF_LINENUMBER; DEF_LIT_STRING; return TK_LIT_STRING; }

[a-zA-Z_][a-zA-Z_0-9]* {DEF_LINENUMBER; DEF_TYPE_IDENTIFICADOR; DEF_IDENTIFICADOR; return TK_IDENTIFICADOR; }

[0-9]+   { DEF_LINENUMBER; DEF_LIT_INT; return TK_LIT_INT; }
[-+]?[0-9]+"."[0-9]+([eE][-+]?[0-9]+)? {DEF_LINENUMBER; DEF_LIT_FLOAT; return TK_LIT_FLOAT; }



. {return TOKEN_ERRO; }

%%

int get_line_number() { return lineNumber; }
