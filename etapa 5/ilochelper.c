#include "helper.h"

OpData_t* addToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadImediateToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadImediateToIlocValue(int value, int registerNumber);


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
    switch (node->operation)
    {
    case Iadd:
        addToIloc(node,registerNumber);
        break;
    case Iload:
        loadToIloc(node, registerNumber);
        break;
    case IloadI:
        loadImediateToIloc(node,registerNumber);
        break;
    default:
        break;
    }

    
    



}

OpData_t* addToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    int regUm, regDois;
    regUm = newRegister();
    regDois = newRegister();
    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childTwo = node->children->next->nodo;
    if(childOne->valorLexico.isLiteral){

    }else if(childTwo->valorLexico.isLiteral){

    }

    newOp->operation = Iadd;
    newOp->registerNumberArg1 = regUm;
    newOp->registerNumberArg2 = regDois;
    newOp->registerNumberArg3 = registerNumber;

    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;
    LL_PREPEND(operationsList, newOpListElement);
    
    nodeToIloc(childOne,regUm);
    nodeToIloc(childTwo,regDois);


}

OpData_t* loadToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    OpData_t* operationRegisterOne;
    int registerOne = newRegister();
    operationRegisterOne = loadImediateToIlocValue(node->valorLexico.memoryDeloc, registerOne);
    newOp->operation = Iload;
    newOp->registerNumberArg3 = registerNumber;
    newOp->registerNumberArg1 = registerOne;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(operationsList, newOpListElement);
    
    return newOp;


}

OpData_t* loadImediateToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    newOp->operation = IloadI;
    newOp->registerNumberArg3 = registerNumber;
    switch (node->valorLexico.tipo)
    {
    case Tint:
        newOp->registerNumberArg1 = node->valorLexico.intValue;
        break;
    
    default:
        break;
    }
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(operationsList, newOpListElement);
    return newOp;
    

}
OpData_t* loadImediateToIlocValue(int value, int registerNumber){
    OpData_t* newOp = createIloc();
    newOp->operation = IloadI;
    newOp->registerNumberArg3 = registerNumber;
    newOp->registerNumberArg1 = value;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(operationsList, newOpListElement);
    return newOp;
}

