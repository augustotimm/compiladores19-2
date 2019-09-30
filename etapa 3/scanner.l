%{
  // Definitions
#include "parser.tab.h"

#define DEF_LINENUMBER yylval.valor_lexico.numeroLinha = lineNumber;

#define DEF_ISLITERAL yylval.valor_lexico.isLiteral = true;

#define DEF_NOTLITERAL yylval.valor_lexico.isLiteral = false;


#define DEF_TYPE_CHAR yylval.valor_lexico.tipo  = Tchar; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue[0] = '\0';

#define DEF_TYPE_INT yylval.valor_lexico.tipo  = Tint; \
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue[0] = '\0';

#define DEF_TYPE_FLOAT yylval.valor_lexico.tipo  = Tfloat;\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.stringValue[0] = '\0';

#define DEF_TYPE_BOOL yylval.valor_lexico.tipo  = Tbool;\
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \
  yylval.valor_lexico.stringValue[0] = '\0';

#define DEF_TYPE_STRING yylval.valor_lexico.tipo  = Tstring; \
  yylval.valor_lexico.charValue = '\0'; \
  yylval.valor_lexico.boolValue = false; \
  yylval.valor_lexico.intValue = 0; \
  yylval.valor_lexico.floatValue = 0; \

#define DEF_LIT_CHAR DEF_TYPE_CHAR; \
  DEF_ISLITERAL\
  yylval.valor_lexico.charValue = yytext[1]; \

#define DEF_LIT_TRUE DEF_TYPE_BOOL; \
  DEF_ISLITERAL\
  yylval.valor_lexico.boolValue = true;

#define DEF_LIT_FALSE DEF_TYPE_BOOL; \
  DEF_ISLITERAL\
  yylval.valor_lexico.boolValue = false;

#define DEF_LIT_INT DEF_TYPE_INT; \
  DEF_ISLITERAL\
  yylval.valor_lexico.intValue = atoi(yytext);\

#define DEF_LIT_STRING DEF_TYPE_STRING; \
  DEF_ISLITERAL\
  yylval.valor_lexico.stringValue= strdup(yytext);\

#define DEF_LIT_FLOAT DEF_TYPE_FLOAT; \
  DEF_ISLITERAL\
  yylval.valor_lexico.floatValue = atof(yytext);\


int lineNumber=1;
int get_line_number();




%}

%x COMMENT_MULT_LINE


%%
[\t]+ {}
\n  {lineNumber++;}

"//".*  {}
"/*".*                   BEGIN(COMMENT_MULT_LINE);
<COMMENT_MULT_LINE>.*"*/"    BEGIN(INITIAL);
<COMMENT_MULT_LINE>\n        { lineNumber++; }
<COMMENT_MULT_LINE>.         {  }


[,;:()\[\]{}+\-|?*/<>=!&%#^.$~`@] {
    return yytext[0];
}

"int"       { return TK_PR_INT; }
"float"     { return TK_PR_FLOAT; }
"bool"      { return TK_PR_BOOL; }
"char"      { return TK_PR_CHAR; }
"string"    { return TK_PR_STRING; }
"if"        { return TK_PR_IF; }
"then"      { return TK_PR_THEN; }
"else"      { return TK_PR_ELSE; }
"while"     { return TK_PR_WHILE; }
"do"        { return TK_PR_DO; }
"input"     { return TK_PR_INPUT; }
"output"    { return TK_PR_OUTPUT; }
"return"    { return TK_PR_RETURN; }
"const"     { return TK_PR_CONST; }
"static"    { return TK_PR_STATIC; }
"foreach"   { return TK_PR_FOREACH; }
"for"       { return TK_PR_FOR; }
"switch"    { return TK_PR_SWITCH; }
"case"      { return TK_PR_CASE; }
"break"     { return TK_PR_BREAK; }
"continue"  { return TK_PR_CONTINUE; }
"class"     { return TK_PR_CLASS; }
"private"   { return TK_PR_PRIVATE; }
"public"    { return TK_PR_PUBLIC; }
"protected" { return TK_PR_PROTECTED; }
"end" { return TK_PR_END; }
"default" { return TK_PR_DEFAULT; }


" " {}
"<="  { return TK_OC_LE; }
">="  { return TK_OC_GE; }
"=="  { return TK_OC_EQ; }
"!="  { return TK_OC_NE; }
"&&"  { return TK_OC_AND; }
"||"  { return TK_OC_OR; }
"<<"  { return TK_OC_SL; }
">>"  { return TK_OC_SR; }
"%>%" { return TK_OC_FORWARD_PIPE; }
"%|%" { return TK_OC_BASH_PIPE; }

"false" {DEF_LINENUMBER; DEF_LIT_FALSE; return TK_LIT_FALSE; }
"true"  { DEF_LINENUMBER; DEF_LIT_TRUE; return TK_LIT_TRUE; }
'.'               { DEF_LINENUMBER; DEF_LIT_CHAR; return TK_LIT_CHAR; }
\"([^\\"]|\\.)*\" {DEF_LINENUMBER; DEF_LIT_STRING; return TK_LIT_STRING; }

[a-zA-Z_][a-zA-Z_0-9]* { return TK_IDENTIFICADOR; }

[0-9]+   { DEF_LINENUMBER; DEF_LIT_INT; return TK_LIT_INT; }
[-+]?[0-9]+"."[0-9]+([eE][-+]?[0-9]+)? {DEF_LINENUMBER; DEF_LIT_FLOAT; return TK_LIT_FLOAT; }



. {return TOKEN_ERRO; }

%%

int get_line_number() { return lineNumber; }
