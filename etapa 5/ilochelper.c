#include "helper.h"

OpData_t* genericBinaryOperationToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadImediateToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadImediateToIlocValue(int value, int registerNumber);
OpData_t* storeToIloc(NodoArvore_t* node, int registerNumber);


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
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Isub:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Imult:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Idiv:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Ilshift:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Irshift:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Iand:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Ior:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Ixor:
        genericBinaryOperationToIloc(node,registerNumber);
        break;
    case Iload:
        loadToIloc(node, registerNumber);
        break;
    case IloadI:
        loadImediateToIloc(node,registerNumber);
        break;
    case Istore:
        storeToIloc(node,registerNumber);
        break;
    default:
        genericBinaryOperationToIloc(node,registerNumber);
        break;;
    }

    
    



}

OpData_t* genericBinaryOperationToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    int regUm, regDois;

    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childTwo = node->children->next->nodo;
    newOp->operation = node->operation;
    regUm = newRegister();
    newOp->registerNumberArg1 = regUm;

    if(childTwo->valorLexico.isLiteral && childOne->valorLexico.isLiteral){
        newOp->registerNumberArg2 = childTwo->valorLexico.intValue;
        newOp->registerNumberArg3 = registerNumber;
        OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
        newOpListElement->arg = newOp;
        LL_PREPEND(operationsList, newOpListElement);
        loadImediateToIloc(childOne, regUm);
    }
    else
    {
        if(childOne->valorLexico.isLiteral){
            newOp->registerNumberArg2 = childOne->valorLexico.intValue;
            newOp->registerNumberArg3 = registerNumber;
            OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
            newOpListElement->arg = newOp;
            LL_PREPEND(operationsList, newOpListElement);
            nodeToIloc(childTwo,regUm);


        }else if(childTwo->valorLexico.isLiteral){
            newOp->registerNumberArg2 = childTwo->valorLexico.intValue;
            newOp->registerNumberArg3 = registerNumber;
            OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
            newOpListElement->arg = newOp;
            LL_PREPEND(operationsList, newOpListElement);
            nodeToIloc(childOne,regUm);
        }
        if(!childTwo->valorLexico.isLiteral && !childOne->valorLexico.isLiteral){
            regDois = newRegister();
            newOp->registerNumberArg2 = regDois;
            newOp->registerNumberArg3 = registerNumber;
            OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
            newOpListElement->arg = newOp;
            LL_PREPEND(operationsList, newOpListElement);
            nodeToIloc(childOne,regUm);
            nodeToIloc(childOne,regDois);

        }
    }
    if(childTwo->valorLexico.isLiteral || childOne->valorLexico.isLiteral ){
        switch (node->operation)
        {
        
        case Iadd: 
            newOp->operation = IaddI;
            break;
        case Isub:
            newOp->operation = IsubI;
            break;
        case Imult:
            newOp->operation = ImultI;
            break;
        case Idiv:
            newOp->operation = IdivI;
            break;
        case Ilshift:
            newOp->operation = IlshiftI;
            break;
        case Irshift:
            newOp->operation = IrshiftI;
            break;
        case Iand:
            newOp->operation = IandI;
            break;
        case Ior:
            newOp->operation = IorI;
            break;
        case Ixor:
            newOp->operation = IxorI;
            break;
        default:
            break;
        }
    }
    
    
    return newOp;

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

OpData_t* storeToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    OpData_t* operationRegisterOne;
    NodoArvore_t* childTwo = node->children->next->nodo;
    NodoArvore_t* childOne = node->children->nodo;
    int valueDeloc = childOne->valorLexico.memoryDeloc;

    int registerOne = newRegister();
    
    newOp->operation = node->operation;
    newOp->registerNumberArg2 = registerNumber;
    newOp->registerNumberArg1 = registerOne;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(operationsList, newOpListElement);
    loadImediateToIlocValue(valueDeloc, registerNumber);
    nodeToIloc(childTwo,registerOne);
    
    return newOp;
}


