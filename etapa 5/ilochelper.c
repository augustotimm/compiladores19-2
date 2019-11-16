#include "helper.h"

OpData_t* genericBinaryOperationToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadImediateToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* loadImediateToIlocValue(int value, int registerNumber);
OpData_t* storeToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* storeAHelper(NodoArvore_t* node, int registerNumber, int registerThree);
OpData_t* recursiveIndexCalc(NodoArvore_t* node, int registerNumber, int previousRegister);
OpData_t* storeAToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* genericCompareOperationToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* storeAToIloc(NodoArvore_t* node, int registerNumber);
OpData_t* addIRfp( int deslocamento, int registerNumber, bool isLocal);
OpData_t* addRfp( int deslocamento, int registerNumber, bool isLocal);



int lastKnownRegister=0;


OpDataList_t* operationsList=NULL;

int newRegister(){
    lastKnownRegister++;
    return lastKnownRegister;
}


OpData_t* createIloc(){
       OpData_t* newOp = calloc(1, sizeof(OpData_t));
       newOp->registerType = Rdefault;
       return newOp;
}

OpData_t* nodeToIloc(NodoArvore_t* node, int registerNumber){
    if(registerNumber == -1){
        registerNumber = newRegister();
    }
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
    case IstoreA:
        storeAToIloc(node,registerNumber);
        break;
    case IloadA:
        storeAToIloc(node,registerNumber);
        break;
    case IcmpLt:
        genericCompareOperationToIloc(node,registerNumber);
        break;
    case IcmpLe:
        genericCompareOperationToIloc(node,registerNumber);
        break;
    case IcmpEq:
        genericCompareOperationToIloc(node,registerNumber);
        break;
    case IcmpGe:
        genericCompareOperationToIloc(node,registerNumber);
        break;
    case IcmpGt:
        genericCompareOperationToIloc(node,registerNumber);
        break;
    case IcmpNe:
        genericCompareOperationToIloc(node,registerNumber);
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
    if(childOne->valorLexico.isLocal){
        newOp->registerType = Rfp;
    }
    else{
        newOp->registerType = Rbss;
    }
    

    LL_PREPEND(operationsList, newOpListElement);
    addIRfp(valueDeloc,registerNumber, childTwo->valorLexico.isLocal);




    
    if(childTwo->valorLexico.isLiteral){
        loadImediateToIloc(childTwo,registerOne);
    }
    else{
        nodeToIloc(childTwo,registerOne);
    }    
    
    return newOp;
}

OpData_t* storeAToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    OpData_t* operationRegisterOne;
    NodoArvore_t* childTwo = node->children->next->nodo;
    NodoArvore_t* childOne = node->children->nodo;
    int registerThree = newRegister();
    int registerOne = newRegister();
    
    newOp->operation = node->operation;
    newOp->registerNumberArg2 = registerNumber;
    newOp->registerNumberArg1 = registerOne;
    newOp->registerNumberArg3 = registerThree;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(operationsList, newOpListElement);
    if(childTwo->valorLexico.isLiteral){
        addIRfp(childTwo->valorLexico.memoryDeloc,registerNumber, childTwo->valorLexico.isLocal);
    }
    else{
        addRfp(childTwo->valorLexico.memoryDeloc,registerNumber, childTwo->valorLexico.isLocal);
    }


    
    if(childTwo->valorLexico.isLiteral && childTwo->childrenNumber ==0){
        
        node->operation = IstoreAI;
        registerThree = childTwo->valorLexico.memoryDeloc;


    }
    else
    {
        storeAHelper(childOne, registerNumber, registerThree);    
        node->operation = IstoreA0;

        nodeToIloc(childTwo,registerOne);
    }
    
    
    
    return newOp;
}



OpData_t* loadAToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    OpData_t* operationRegisterOne;
    NodoArvore_t* childTwo = node->children->next->nodo;
    NodoArvore_t* childOne = node->children->nodo;
    int registerTwo = newRegister();
    int registerOne = newRegister();
    
    newOp->operation = node->operation;
    newOp->registerNumberArg2 = registerTwo;
    newOp->registerNumberArg1 = registerOne;
    newOp->registerNumberArg3 = registerNumber;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(operationsList, newOpListElement);
    if(childTwo->valorLexico.isLiteral){
        addIRfp(childTwo->valorLexico.memoryDeloc,registerOne, childTwo->valorLexico.isLocal);
    }
    else{
        addRfp(childTwo->valorLexico.memoryDeloc,registerOne, childTwo->valorLexico.isLocal);
    }


    
    if(childTwo->valorLexico.isLiteral && childTwo->childrenNumber ==0){
        
        node->operation = IstoreAI;
        registerTwo = childTwo->valorLexico.memoryDeloc;


    }
    else
    {
        storeAHelper(childOne, registerNumber, registerTwo);    
        node->operation = IstoreA0;

        nodeToIloc(childTwo,registerOne);
    }
    
    
    
    return newOp;
}


OpData_t* storeAHelper(NodoArvore_t* node, int registerNumber, int registerThree){
    NodoArvore_t* childTwo = node->children->next->nodo;
    NodoArvore_t* childOne = node->children->nodo;
    
    if(childTwo->childrenNumber >0){
        int registerNewDimension = newRegister();
        recursiveIndexCalc(childTwo,registerNewDimension, registerThree);
    }
    if(childTwo->valorLexico.isLiteral){
        loadImediateToIlocValue(childTwo->valorLexico.memoryDeloc,registerThree);

    }
    else
    {
        nodeToIloc(childTwo,registerThree);
    }
    

    loadImediateToIlocValue(childOne->valorLexico.memoryDeloc,registerNumber);
}

OpData_t* recursiveIndexCalc(NodoArvore_t* node, int registerNumber, int previousRegister){
    OpData_t* addEnd = createIloc();
    addEnd->registerNumberArg1 = registerNumber;
    addEnd->registerNumberArg2 = previousRegister;
    addEnd->registerNumberArg3 = previousRegister;
    NodoArvore_t* currentChild = node->children->nodo;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = addEnd;

    LL_PREPEND(operationsList, newOpListElement);

    if(currentChild->childrenNumber >0){
        recursiveIndexCalc(currentChild->children->nodo,newRegister(),previousRegister);
    }

    if(currentChild->valorLexico.isLiteral){
        addEnd->operation = IaddI;
        loadImediateToIlocValue(currentChild->valorLexico.memoryDeloc,registerNumber);

    }
    else{
        addEnd->operation = Iadd;
        nodeToIloc(currentChild,registerNumber);

    }
}


OpData_t* genericCompareOperationToIloc(NodoArvore_t* node, int registerNumber){
    OpData_t* newOp = createIloc();
    int regUm, regDois;

    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childTwo = node->children->next->nodo;
    newOp->operation = node->operation;
    regUm = newRegister();
    regDois = newRegister();
    newOp->registerNumberArg1 = regUm;
    newOp->registerNumberArg2 = regDois;
    newOp->registerNumberArg3 = registerNumber;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;
    LL_PREPEND(operationsList, newOpListElement);

    if(childOne->valorLexico.isLiteral){
        loadImediateToIloc(childOne, regUm);

    }
    else
    {
        nodeToIloc(childOne,regUm);

    }
    

    if(childTwo->valorLexico.isLiteral){
               
        loadImediateToIloc(childTwo,regDois);
    }
    else{
        nodeToIloc(childTwo,regDois);

    }      
    
    return newOp;

}

OpData_t* addRfp( int registerDeslocamento, int registerNumber, bool isLocal){
    OpData_t* newOp = createIloc();
    newOp->operation = Iadd;
    if(isLocal){
        newOp->registerType = Rfp;
    }
    else{
        newOp->registerType = Rbss;
    }

    newOp->registerNumberArg2 = registerDeslocamento;
    newOp->registerNumberArg3 = registerNumber;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;
    LL_PREPEND(operationsList, newOpListElement);
    return newOp;
}

OpData_t* addIRfp( int deslocamento, int registerNumber, bool isLocal){
    OpData_t* newOp = createIloc();
    newOp->operation = IaddI;
     if(isLocal){
        newOp->registerType = Rfp;
    }
    else{
        newOp->registerType = Rbss;
    }
    newOp->registerNumberArg2 = deslocamento;
    newOp->registerNumberArg3 = registerNumber;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;
    LL_PREPEND(operationsList, newOpListElement);
    return newOp;
}
