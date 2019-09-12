%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *s);
%}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_PR_END
%token TK_PR_DEFAULT
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_OC_FORWARD_PIPE
%token TK_OC_BASH_PIPE
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%left '+' '-'
%left '*' '/' '%'
%left '^'
%left ':'
%left '?'
%left '|' '&'

%right UNARIO




%%

entry: programa;

programa: lista_elementos | %empty;

lista_elementos: lista_elementos elemento | elemento;

elemento: declaracao_var_global | def_funcao;


declaracao_var_global: tipo TK_IDENTIFICADOR ';'
                    |  '['TK_LIT_INT ']' tipo TK_IDENTIFICADOR  ';'
                    |  TK_PR_STATIC tipo TK_IDENTIFICADOR  ';'
                    |  TK_PR_STATIC '['TK_LIT_INT ']' tipo  TK_IDENTIFICADOR ';' ;

def_funcao: cabecalho_funcao bloco_comandos_start ;

cabecalho_funcao: tipo TK_IDENTIFICADOR parametros_funcao | TK_PR_STATIC TK_IDENTIFICADOR parametros_funcao ;

parametros_funcao: '(' lista_parametros ')' | '(' ')';

lista_parametros: lista_parametros ',' parametro | parametro;

parametro: tipo TK_IDENTIFICADOR | TK_PR_CONST tipo TK_IDENTIFICADOR;

comando_simples:  declaracao_local
            | atribuicao
            | chamada_funcao
            | comando_shift
            | comando_entrada
            | comando_saida
            | comando_return
            | TK_PR_BREAK
            | TK_PR_CONTINUE
            | controle_fluxo
            ;


declaracao_local: tipo TK_IDENTIFICADOR | TK_PR_STATIC tipo TK_IDENTIFICADOR;

atribuicao: TK_IDENTIFICADOR '=' expressao
    | TK_IDENTIFICADOR '[' expressao ']' '=' expressao
;
chamada_funcao: TK_IDENTIFICADOR '(' ')' |  TK_IDENTIFICADOR '(' lista_expressao ')' ;

comando_entrada: TK_PR_INPUT expressao;

comando_saida: TK_PR_OUTPUT lista_expressao;

comando_return: TK_PR_RETURN expressao;

comando_shift: TK_IDENTIFICADOR '<''<' expressao |  TK_IDENTIFICADOR '>''>' expressao ;

controle_fluxo: if_declaracao | for_declaracao | while_declaracao;

if_declaracao: TK_PR_IF '(' expressao ')' bloco_comandos_start else_declaracao;

else_declaracao: %empty | TK_PR_ELSE bloco_comandos_start;

for_declaracao: TK_PR_FOR '(' for_lista_comandos ':' expressao ':'  for_lista_comandos ')' bloco_comandos_start;

while_declaracao: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_comandos_start;

for_lista_comandos: for_comandos | for_lista_comandos ',' for_comandos ;

for_comandos: atribuicao
            | comando_shift
            | declaracao_local;

lista_expressao: expressao | lista_expressao ',' expressao;


bloco_comandos_start: '{' bloco_comandos '}' | '{' '}' ;


bloco_comandos: bloco_comandos comando_simples ';' | comando_simples ';';

tipo: TK_PR_INT
    |   TK_PR_BOOL
    |   TK_PR_CHAR
    |   TK_PR_FLOAT
    |   TK_PR_STRING;

expressao: '(' expressao ')'
        | expressao '+' expressao 
        | expressao '-' expressao 
        | expressao '*' expressao 
        | expressao '/' expressao 
        | expressao '%' expressao 
        | expressao '|' expressao 
        | expressao '&' expressao 
        | expressao '^' expressao 
        | '+' expressao %prec UNARIO
        | '?' expressao %prec UNARIO
        | '-' expressao %prec UNARIO
        | '!' expressao %prec UNARIO
        | '&' expressao %prec UNARIO
        | '*' expressao %prec UNARIO
        | expressao '?'  expressao ':' expressao
        | '#' expressao %prec UNARIO
        | literal
        | variavel;

literal: TK_LIT_CHAR
        | TK_LIT_FALSE
        | TK_LIT_FLOAT
        | TK_LIT_INT
        | TK_LIT_STRING
        | TK_LIT_TRUE;

variavel: TK_IDENTIFICADOR;
%%

void yyerror (char const *s) {
    printf("erro %s",s);
};