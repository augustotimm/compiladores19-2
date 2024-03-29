

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror (char const *s);
extern int get_line_number();
extern char *yytext;
extern void *arvore;

%}
%error-verbose
%code requires {
  #include "helper.h"
}

%union{
       NodoArvore_t* nodo; 
       ValorLexico_t valor_lexico;
}




//Types

//Tokens

//Literals
%type <valor_lexico> TK_LIT_CHAR TK_LIT_FALSE TK_LIT_TRUE TK_LIT_FLOAT TK_LIT_INT TK_LIT_STRING

//Palavras Reservadas
%type <valor_lexico> TK_PR_INT TK_PR_FLOAT TK_PR_BOOL TK_PR_CHAR TK_PR_STRING TK_PR_IF TK_PR_THEN TK_PR_ELSE
%type <valor_lexico> TK_PR_WHILE TK_PR_DO TK_PR_INPUT TK_PR_OUTPUT TK_PR_RETURN TK_PR_CONST TK_PR_STATIC
%type <valor_lexico> TK_PR_FOREACH TK_PR_FOR TK_PR_SWITCH TK_PR_CASE TK_PR_BREAK TK_PR_CONTINUE TK_PR_CLASS
%type <valor_lexico> TK_PR_PRIVATE TK_PR_PUBLIC TK_PR_PROTECTED TK_PR_END TK_PR_DEFAULT

//Operadores
%type <valor_lexico> TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE TK_OC_AND TK_OC_OR TK_OC_SL TK_OC_SR TK_OC_FORWARD_PIPE TK_OC_BASH_PIPE

//Identificador
%type <valor_lexico> TK_IDENTIFICADOR

//Tipo nontokens
%type <valor_lexico> '+' '-' '*' '/' '%' '|' '&' '^' '?' '!' '#' '=' '<' '>'

//Nao terminais
%type <nodo> variavel literal expressao chamada_funcao lista_expressao atribuicao

%type <nodo> comando_shift comando_entrada comando_saida controle_fluxo if_declaracao else_declaracao

%type <nodo> for_declaracao for_comandos for_lista_comandos declaracao_local inicializacao declaracao_local_simples

%type <nodo> while_declaracao comando_simples comando_return bloco_comandos_start bloco_comandos

%type <nodo> cabecalho_funcao def_funcao comandos_funcao elemento lista_elementos programa entry declaracao_var_global 

//Destructors


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

%left '?'
%left '^'
%left ':' 

%left '|' '&' 
%left TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE '<' '>'
%left  TK_OC_AND TK_OC_OR 
%left TK_OC_SL TK_OC_SR

%left '-' 
%left '+' 

%left '*' '/' '%'


%right UNARIO




%%

entry: programa {$$ = $1; arvore = $1;};

programa: lista_elementos  {$$ =$1;   }
        | %empty {$$ = NULL;}
        ; 

lista_elementos:   elemento  lista_elementos
        {
                if($1 == NULL){
                        $$ = $2;
                }
                else{

                        addChildren($1,$2);
                        $$ = $1;
                }
                
        }
        | elemento {$$ = $1; } 
        ;

elemento: declaracao_var_global { $$ = $1; }
        | def_funcao {$$=$1; }
;


declaracao_var_global: tipo variavel ';' 
        {       

                if($2 != NULL){
                        
                        if($2->childrenNumber == 0){
                                libera($2); 
                                $2 = NULL;
                        }
                        
                
                }
               
                $$ = $2;
                
                        
        }
        |  TK_PR_STATIC tipo variavel ';'
        {
                if($3->childrenNumber == 0){
                        libera($3); 
                        $3=NULL;
                }
                liberaValorLexico($1); 
                $$ = $3;
                
        } 
;

def_funcao: cabecalho_funcao comandos_funcao 
        {       
                addChildren($1,$2);
                $$=$1;                        
        }
;

comandos_funcao: '{' bloco_comandos '}' 
        {
                $$ = $2;
                
        }
        | '{' '}'
        {
                $$ = NULL;
        }
        ;
;
cabecalho_funcao: tipo TK_IDENTIFICADOR parametros_funcao 
        {
                $$ = criaNodoValorLexico($2);
                
        }
        | TK_PR_STATIC tipo TK_IDENTIFICADOR parametros_funcao 
        {
                liberaValorLexico($1);
                $$ = criaNodoValorLexico($3);
        }                
        
        ;

parametros_funcao: '(' lista_parametros ')' | '(' ')';

lista_parametros: parametro ','  lista_parametros | parametro;

parametro: tipo TK_IDENTIFICADOR
        {
                liberaValorLexico($2);
        }
        | TK_PR_CONST tipo TK_IDENTIFICADOR
        {
                liberaValorLexico($1);
                liberaValorLexico($3);
        }
        ;

comando_simples: atribuicao {$$ = $1;};
            | chamada_funcao {$$ = $1;};
            | comando_shift {$$ = $1;};
            | comando_entrada {$$ = $1;};
            | comando_saida {$$ = $1;};
            | comando_return {$$ = $1;};
            | TK_PR_BREAK {$$ = criaNodoValorLexico($1);}
            | TK_PR_CONTINUE {$$ = criaNodoValorLexico($1);}
            | controle_fluxo {$$ = $1;};
            | declaracao_local {$$ = $1;};
            | bloco_comandos_start {$$ = $1 ;}
            ;


declaracao_local: declaracao_local_simples inicializacao 
        {
                if( $2 != NULL){
                        addChildren($2,$1);
                        $$=$2;
                }
                else{
                        libera($1);
                        $$ = NULL;
                }
        }
        | TK_PR_STATIC declaracao_local_simples inicializacao
         {
                liberaValorLexico($1);
                
                if( $3 != NULL){
                        addChildren($3,$2);
                        $$=$2;
                }
                else{
                        libera($2);
                        $$ = NULL;
                }
        }
        ;

inicializacao: TK_OC_LE literal 
        {
                
                $$ = criaNodoValorLexico($1);
                addChildren($$,$2);
        }
        | TK_OC_LE variavel 
        {
                $$ = criaNodoValorLexico($1);
                addChildren($$,$2);
        }
        | %empty {$$=NULL;};
        
        ;

declaracao_local_simples: tipo TK_IDENTIFICADOR 
        {
                $$ = criaNodoValorLexico($2);
        }
        | TK_PR_CONST tipo TK_IDENTIFICADOR
        {
                liberaValorLexico($1);

                $$ = criaNodoValorLexico($3);
        }
        ;


atribuicao: variavel '=' expressao 
        {
                NodoArvore_t* atrNodo = criaNodoValorLexico($2);
                addChildren(atrNodo,$1);
                addChildren(atrNodo,$3);
                $$ = atrNodo;
        }
;
chamada_funcao: TK_IDENTIFICADOR '(' ')' 
        {
                $$ = criaNodoValorLexico($1);
                
        }
        |  TK_IDENTIFICADOR '(' lista_expressao ')' 
        {
                NodoArvore_t* chamadaNodo = criaNodoValorLexico($1);
                addChildren(chamadaNodo,$3);
                $$ = chamadaNodo;
        }
        ;

comando_entrada: TK_PR_INPUT expressao 
        {
                NodoArvore_t* inputNodo = criaNodoValorLexico($1);
                addChildren(inputNodo,$2);
                $$ = inputNodo;
        }
;

comando_saida: TK_PR_OUTPUT lista_expressao
        {
                NodoArvore_t* outputNodo = criaNodoValorLexico($1);
                addChildren(outputNodo,$2);
                $$ = outputNodo;
        }
;

comando_return: TK_PR_RETURN expressao
        {
                $$ = criaNodoValorLexico($1);
                addChildren($$,$2);
        }
;

comando_shift: TK_IDENTIFICADOR TK_OC_SL expressao 
        {
                NodoArvore_t* slNodo = criaNodoValorLexico($2);
                NodoArvore_t* identificador = criaNodoValorLexico($1);
                addChildren(slNodo,identificador);
                addChildren(slNodo, $3);
                $$ = slNodo;
        }
        |  TK_IDENTIFICADOR TK_OC_SR expressao 
        {
                NodoArvore_t* srNodo = criaNodoValorLexico($2);
                NodoArvore_t* identificador = criaNodoValorLexico($1);
                addChildren(srNodo,identificador);
                addChildren(srNodo, $3);
                $$ = srNodo;
        }
        ;

controle_fluxo: if_declaracao
        {
                $$ = $1;
        }
        | for_declaracao 
        {
                $$ = $1;
        }
        | while_declaracao
        {
                $$ = $1;
        };

if_declaracao: TK_PR_IF '(' expressao ')' bloco_comandos_start else_declaracao
        {
                NodoArvore_t* ifNodo = criaNodoValorLexico($1);
                addChildren(ifNodo,$3);
                addChildren(ifNodo,$5);
                addChildren(ifNodo,$6);
                $$ = ifNodo;
        }
;

else_declaracao: %empty { $$ =NULL;}
        | TK_PR_ELSE bloco_comandos_start
        {
                $$=$2;
        }
;

for_declaracao: TK_PR_FOR '(' for_lista_comandos ':' expressao ':'  for_lista_comandos ')' bloco_comandos_start
        {
                NodoArvore_t* forNodo = criaNodoValorLexico($1);
                addChildren(forNodo, $3);
                addChildren(forNodo, $5);
                addChildren(forNodo, $7);
                addChildren(forNodo, $9);
                $$ = forNodo;
        }
;

while_declaracao: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_comandos_start
        {

                $$ = criaNodoValorLexico($1);
                addChildren($$,$3);
                addChildren($$,$6);
                liberaValorLexico($5);
        }
;

for_lista_comandos: for_comandos 
        {
                $$ = $1;
        }
        | for_comandos ','  for_lista_comandos
        {
                addChildren($1,$3);
                $$ = $1;
        }
        ;

for_comandos: atribuicao { $$ = $1;}
            | comando_shift {$$=$1;}
            | declaracao_local {$$=$1;}
            ;

lista_expressao: expressao 
        {
                
                $$ = $1;
        }
        |  expressao ','  lista_expressao
        {
                addChildren($1, $3);
                $$ = $1;
        }
        ;


bloco_comandos_start: '{' bloco_comandos '}' 
        {
                $$ = $2;
        }
        | '{' '}'  {$$ = criaNodoValorLexico(criaValorLexicoOP("{}"));}
        ;


bloco_comandos:  comando_simples ';' 
        {
                   $$ = $1;
        }
        |  comando_simples ';' bloco_comandos   
        {
                if($1 == NULL){
                        $$ = $3;
                }
                else{
                        addChildren($1,$3);
                        $$ = $1;
                }             
        }

        ;


tipo: TK_PR_INT
        {
                liberaValorLexico($1);
        }
    |   TK_PR_BOOL
    {
        liberaValorLexico($1);
    }
    |   TK_PR_CHAR
    {
        liberaValorLexico($1);
    }
    |   TK_PR_FLOAT
    {
        liberaValorLexico($1);    
        }
    |   TK_PR_STRING
    {
        liberaValorLexico($1);    
    }
    ;

expressao: '(' expressao ')' {
                $$ = $2;
}
        | literal 
        {
                $$ = $1;
        }
        | variavel
        {
                $$ = $1;
        }
         | expressao '-' expressao 
        {
                NodoArvore_t* minusNodo = criaNodoValorLexico($2);
                addChildren(minusNodo, $1);
                addChildren(minusNodo, $3);
                $$=minusNodo;
        }
        | expressao '+'  expressao
        {
                NodoArvore_t* plusNodo = criaNodoValorLexico($2);
                
                addChildren(plusNodo, $1);
                addChildren(plusNodo, $3);
                $$=plusNodo;
        }       
        | expressao '*' expressao
        {
                NodoArvore_t* multNodo = criaNodoValorLexico($2);
                addChildren(multNodo, $1);
                addChildren(multNodo, $3);
                $$=multNodo;
        }
        | expressao '/' expressao 
        {
                NodoArvore_t* divNodo = criaNodoValorLexico($2);
                addChildren(divNodo, $1);
                addChildren(divNodo, $3);
                $$=divNodo;
        }
        | expressao '%' expressao 
        {       
                
                NodoArvore_t* restoNodo = criaNodoValorLexico($2);
                
                addChildren(restoNodo, $1);
                addChildren(restoNodo, $3);

                $$=restoNodo;
        }
        | expressao '|' expressao 
        {
                NodoArvore_t* orNodo = criaNodoValorLexico($2);
                addChildren(orNodo, $1);
                addChildren(orNodo, $3);
                $$=orNodo;
        }
        | expressao '&' expressao 
        {
                NodoArvore_t* andNodo = criaNodoValorLexico($2);
                addChildren(andNodo, $1);
                addChildren(andNodo, $3);
                $$=andNodo;
        }
        | expressao '^' expressao 
        {
                NodoArvore_t* powNodo = criaNodoValorLexico($2);
                addChildren(powNodo, $1);
                addChildren(powNodo, $3);
                $$=powNodo;
        }
        | expressao TK_OC_LE expressao
        {
                NodoArvore_t* leNodo = criaNodoValorLexico($2);
                addChildren(leNodo, $1);
                addChildren(leNodo, $3);
                $$=leNodo;
        }
        | expressao '<' expressao
        {
                NodoArvore_t* leNodo = criaNodoValorLexico($2);
                addChildren(leNodo, $1);
                addChildren(leNodo, $3);
                $$=leNodo;
        }
        | expressao '>' expressao
        {
                NodoArvore_t* leNodo = criaNodoValorLexico($2);
                addChildren(leNodo, $1);
                addChildren(leNodo, $3);
                $$=leNodo;
        }
        | expressao TK_OC_GE expressao
        {
                NodoArvore_t* geNodo = criaNodoValorLexico($2);
                addChildren(geNodo, $1);
                addChildren(geNodo, $3);
                $$=geNodo;
        }
        | expressao TK_OC_EQ expressao
        {
                NodoArvore_t* eqNodo = criaNodoValorLexico($2);
                addChildren(eqNodo, $1);
                addChildren(eqNodo, $3);
                $$=eqNodo;
        }
        | expressao TK_OC_NE expressao
        {
                NodoArvore_t* neNodo = criaNodoValorLexico($2);
                addChildren(neNodo, $1);
                addChildren(neNodo, $3);
                $$=neNodo;
        }
        | expressao TK_OC_AND expressao
        {
                NodoArvore_t* andNodo = criaNodoValorLexico($2);
                addChildren(andNodo, $1);
                addChildren(andNodo, $3);
                $$=andNodo;
        }
        | expressao TK_OC_OR expressao
        {
                NodoArvore_t* orNodo = criaNodoValorLexico($2);
                addChildren(orNodo, $1);
                addChildren(orNodo, $3);
                $$=orNodo;
        }
        | expressao TK_OC_SL expressao
        {
                NodoArvore_t* slNodo = criaNodoValorLexico($2);
                addChildren(slNodo, $1);
                addChildren(slNodo, $3);
                $$=slNodo;
        }
        | expressao TK_OC_SR expressao
        {
                NodoArvore_t* srNodo = criaNodoValorLexico($2);
                addChildren(srNodo, $1);
                addChildren(srNodo, $3);
                $$=srNodo;
        }
        | '+' expressao %prec UNARIO
        {
                NodoArvore_t* plusNodo = criaNodoValorLexico($1);
                addChildren(plusNodo, $2);         
                $$=plusNodo;
        }        
        | '?' expressao %prec UNARIO
        {
                NodoArvore_t* interrogNodo = criaNodoValorLexico($1);
                addChildren(interrogNodo, $2);         
                $$=interrogNodo;
        }        
        | '-' expressao %prec UNARIO
        {
                NodoArvore_t* minusNodo = criaNodoValorLexico($1);
                addChildren(minusNodo, $2);         
                $$=minusNodo;
        }
        | '!' expressao %prec UNARIO
        {
                NodoArvore_t* notNodo = criaNodoValorLexico($1);
                addChildren(notNodo, $2);         
                $$=notNodo;
        }
        | '&' expressao %prec UNARIO
        {
                NodoArvore_t* addressNodo = criaNodoValorLexico($1);
                addChildren(addressNodo, $2);         
                $$=addressNodo;
        }
        | '*' expressao %prec UNARIO
        {
                NodoArvore_t* pointerNodo = criaNodoValorLexico($1);
                addChildren(pointerNodo, $2);         
                $$=pointerNodo;
        }
        | expressao '?'  expressao ':' expressao
        {
                NodoArvore_t* tercNodo = criaNodoValorLexico($2);
                
                addChildren(tercNodo, $1);
                addChildren(tercNodo, $3);
                addChildren(tercNodo, $5);
                $$=tercNodo;
                
        }
        | '#' expressao %prec UNARIO
        {
                NodoArvore_t* hashNodo = criaNodoValorLexico($1);
                addChildren(hashNodo, $2);         
                $$=hashNodo;
        }
        |chamada_funcao
        {
                $$ =  $1;
        }
;

literal: TK_LIT_CHAR {
        $$ = criaNodoValorLexico( $1);
}
        | TK_LIT_FALSE{
        $$ = criaNodoValorLexico( $1);
}
        | TK_LIT_FLOAT{
        $$ = criaNodoValorLexico( $1);
}
        | TK_LIT_INT{
        $$ = criaNodoValorLexico( $1);
}
        | TK_LIT_STRING{
        $$ = criaNodoValorLexico( $1);
}
        | TK_LIT_TRUE{
        $$ = criaNodoValorLexico( $1);
}
        ;

variavel: TK_IDENTIFICADOR { 
        NodoArvore_t* idNodo = criaNodoValorLexico( $1 );
        $$ = idNodo;
 }
        | TK_IDENTIFICADOR '[' expressao ']'{ 
        NodoArvore_t* idNodo = criaNodoValorLexico( $1 );
        NodoArvore_t* bracketNodo = criaNodoValorLexico( criaValorLexicoOP("[]") );
        addChildren(idNodo,bracketNodo);
        addChildren(idNodo, $3);
        $$ = idNodo;
 }
;
%%

void yyerror(const char *s) {
    printf(" %s \nErro  na linha de numero: %d \t ultimo token lido: %c\n",s, get_line_number(), yytext[0]);
    
    
}