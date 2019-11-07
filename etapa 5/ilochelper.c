#include "helper.h"

#define IS_IF(str) strcmp(str,"if") ==0
#define IS_SUM(str) strcmp(str,"+") ==0
#define IS_SUB(str) strcmp(str,"-") ==0
#define IS_DIV(str) strcmp(str,"/") ==0
#define IS_MULT(str) strcmp(str,"*") ==0


void nodeToIloc(NodoArvore_t* node, int registerNumber){
    if(IS_IF(node->valorLexico.stringValue)){

    }


}