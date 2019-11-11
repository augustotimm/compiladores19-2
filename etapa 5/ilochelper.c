#include "helper.h"

#define IS_IF(str) strcmp(str,"if") ==0
#define IS_SUM(str) strcmp(str,"+") ==0
#define IS_SUB(str) strcmp(str,"-") ==0
#define IS_DIV(str) strcmp(str,"/") ==0
#define IS_MULT(str) strcmp(str,"*") ==0


OpData_t nodeToIloc(NodoArvore_t* node, int registerNumber){
    if(IS_IF(node->valorLexico.stringValue)){

    }else if(IS_SUM(node->valorLexico.stringValue)){

    }else if(IS_SUB(node->valorLexico.stringValue)){

    }else if(IS_DIV(node->valorLexico.stringValue)){

    }else if(IS_MULT(node->valorLexico.stringValue)){

    }


}