#include "helper.h"

OpData_t* addToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* ldaToIloc(NodoArvore_t* node, int registerNumber);

int lastKnownRegister=0;


OpDataList_t* operationsList=NULL;

int newRegister(){
    lastKnownRegister++;
    return lastKnownRegister;
}


OpData_t* createIloc(){
       OpData_t* newOp = calloc(1, sizeof(OpData_t));
       return newOp;
}

OpData_t* nodeToIloc(NodoArvore_t* node, int registerNumber){
    if(node->operation == Iadd){
        addToIloc(node,registerNumber);
    }else if(node->operation == Ilda){
        ldaToIloc(node, registerNumber);
    }
    /*else if(IS_SUM(node->valorLexico.stringValue)){

    }else if(IS_SUB(node->valorLexico.stringValue)){

    }else if(IS_DIV(node->valorLexico.stringValue)){

    }else if(IS_MULT(node->valorLexico.stringValue)){

    }*/


}

OpData_t* addToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    int regUm, regDois;
    regUm = newRegister();
    regDois = newRegister();
    newOp->operation = Iadd;
    newOp->registerNumberArg1 = regUm;
    newOp->registerNumberArg2 = regDois;
    newOp->registerNumberArg3 = registerNumber;
    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childTwo = node->children->next->nodo;
    nodeToIloc(childOne,regUm);
    nodeToIloc(childTwo,regDois);


}

OpData_t* ldaToIloc(NodoArvore_t* node, int registerNumber){

}

