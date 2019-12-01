#include "helper.h"

OpData_t* genericBinaryOperationToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* loadToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* loadImediateToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* loadImediateToIlocValue(int value, int registerNumber, ComandsList_t* head);
OpData_t* storeToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* storeAHelper(NodoArvore_t* node, int registerNumber, int registerThree, ComandsList_t* head);
OpData_t* recursiveIndexCalc(NodoArvore_t* node, int registerNumber, int previousRegister, ComandsList_t* head);
OpData_t* storeAToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* genericCompareOperationToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* storeAToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* addIRfp( int deslocamento, int registerNumber, bool isLocal, ComandsList_t* head);
OpData_t* addRfp( int deslocamento, int registerNumber, bool isLocal, ComandsList_t* head);
OpData_t* orToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* andToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
OpData_t* cbrToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);
int createLabel(ComandsList_t* head);


int lastKnownRegister=0;
int lastKnownLabel =0;


ComandsList_t* commandsList=NULL;

int newRegister(){
    lastKnownRegister++;
    return lastKnownRegister;
}


OpData_t* createIloc(){
       OpData_t* newOp = calloc(1, sizeof(OpData_t));
       newOp->registerType = Rdefault;
       return newOp;
}

OpData_t* nodeToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
    if(registerNumber == -1){
        registerNumber = newRegister();
        ComandsList_t* newCommand = calloc(1,sizeof(ComandsList_t));
        head = newCommand;
        LL_APPEND(commandsList, newCommand);
    }
    switch (node->operation)
    {
  
    case Iadd: 
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Isub:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Imult:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Idiv:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Ilshift:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Irshift:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Iand:
        andToIloc(node,registerNumber, head);
        break;
    case Ior:
        orToIloc(node,registerNumber, head);
        break;
    case Ixor:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;
    case Iload:
        loadToIloc(node, registerNumber, head);
        break;
    case IloadI:
        loadImediateToIloc(node,registerNumber, head);
        break;
    case Istore:
        storeToIloc(node,registerNumber, head);
        break;
    case IstoreA:
        storeAToIloc(node,registerNumber, head);
        break;
    case IloadA:
        storeAToIloc(node,registerNumber, head);
        break;
    case IcmpLt:
        genericCompareOperationToIloc(node,registerNumber, head);
        break;
    case IcmpLe:
        genericCompareOperationToIloc(node,registerNumber, head);
        break;
    case IcmpEq:
        genericCompareOperationToIloc(node,registerNumber, head);
        break;
    case IcmpGe:
        genericCompareOperationToIloc(node,registerNumber, head);
        break;
    case IcmpGt:
        genericCompareOperationToIloc(node,registerNumber, head);
        break;
    case IcmpNe:
        genericCompareOperationToIloc(node,registerNumber, head);
        break;
    case Iliteral:
        loadImediateToIloc(node,registerNumber,head);
        break;
    case Icbr:
        cbrToIloc(node,registerNumber,head);
        break;
    case Iwhile:
        cbrToIloc(node,registerNumber,head);
        break;
    default:
        genericBinaryOperationToIloc(node,registerNumber, head);
        break;;
    }

    
    



}

OpData_t* genericBinaryOperationToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head ){
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
        LL_PREPEND(head->arg, newOpListElement);
        loadImediateToIloc(childOne, regUm, head);
    }
    else
    {
        if(childOne->valorLexico.isLiteral){
            newOp->registerNumberArg2 = childOne->valorLexico.intValue;
            newOp->registerNumberArg3 = registerNumber;
            OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
            newOpListElement->arg = newOp;
            LL_PREPEND(head->arg, newOpListElement);
            nodeToIloc(childTwo,regUm, head);


        }else if(childTwo->valorLexico.isLiteral){
            newOp->registerNumberArg2 = childTwo->valorLexico.intValue;
            newOp->registerNumberArg3 = registerNumber;
            OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
            newOpListElement->arg = newOp;
            LL_PREPEND(head->arg, newOpListElement);
            nodeToIloc(childOne,regUm, head);
        }
        if(!childTwo->valorLexico.isLiteral && !childOne->valorLexico.isLiteral){
            regDois = newRegister();
            newOp->registerNumberArg2 = regDois;
            newOp->registerNumberArg3 = registerNumber;
            OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
            newOpListElement->arg = newOp;
            LL_PREPEND(head->arg, newOpListElement);
            nodeToIloc(childOne,regUm, head);
            nodeToIloc(childOne,regDois, head);

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


OpData_t* loadToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
    OpData_t* newOp = createIloc();
    int registerOne = newRegister();
    
    newOp->operation = Iload;
    newOp->registerNumberArg3 = registerNumber;
    newOp->registerNumberArg1 = registerOne;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(head->arg, newOpListElement);

    addIRfp(node->valorLexico.memoryDeloc,registerOne, node->valorLexico.isLocal, head);
    
    return newOp;


}

OpData_t* loadImediateToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
    OpData_t* newOp = createIloc();
    newOp->operation = IloadI;
    newOp->registerNumberArg3 = registerNumber;
    switch (node->valorLexico.tipo)
    {
    case Tint:
        newOp->registerNumberArg1 = node->valorLexico.intValue;
        break;
    case Tbool:
        newOp->registerNumberArg1 = node->valorLexico.intValue;
        break;
    default:
        break;
    }
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(head->arg, newOpListElement);
    return newOp;
    

}
OpData_t* loadImediateToIlocValue(int value, int registerNumber, ComandsList_t* head){
    OpData_t* newOp = createIloc();
    newOp->operation = IloadI;
    newOp->registerNumberArg3 = registerNumber;
    newOp->registerNumberArg1 = value;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;

    LL_PREPEND(head->arg, newOpListElement);
    return newOp;
}

OpData_t* storeToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
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
    

    LL_PREPEND(head->arg, newOpListElement);
    addIRfp(valueDeloc,registerNumber, childTwo->valorLexico.isLocal, head);




    
    if(childTwo->valorLexico.isLiteral){
        loadImediateToIloc(childTwo,registerOne, head);
    }
    else{
        nodeToIloc(childTwo,registerOne, head);
    }    
    
    return newOp;
}

OpData_t* storeAToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
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

    LL_PREPEND(head->arg, newOpListElement);
    if(childTwo->valorLexico.isLiteral){
        addIRfp(childTwo->valorLexico.memoryDeloc,registerNumber, childTwo->valorLexico.isLocal, head);
    }
    else{
        addRfp(childTwo->valorLexico.memoryDeloc,registerNumber, childTwo->valorLexico.isLocal, head);
    }


    
    if(childTwo->valorLexico.isLiteral && childTwo->childrenNumber ==0){
        
        node->operation = IstoreAI;
        registerThree = childTwo->valorLexico.memoryDeloc;


    }
    else
    {
        storeAHelper(childOne, registerNumber, registerThree, head);    
        node->operation = IstoreA0;

        nodeToIloc(childTwo,registerOne, head);
    }
    
    
    
    return newOp;
}



OpData_t* loadAToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
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

    LL_PREPEND(head->arg, newOpListElement);
    if(childTwo->valorLexico.isLiteral){
        addIRfp(childTwo->valorLexico.memoryDeloc,registerOne, childTwo->valorLexico.isLocal, head);
    }
    else{
        addRfp(childTwo->valorLexico.memoryDeloc,registerOne, childTwo->valorLexico.isLocal, head);
    }


    
    if(childTwo->valorLexico.isLiteral && childTwo->childrenNumber ==0){
        
        node->operation = IstoreAI;
        registerTwo = childTwo->valorLexico.memoryDeloc;


    }
    else
    {
        storeAHelper(childOne, registerNumber, registerTwo, head);    
        node->operation = IstoreA0;

        nodeToIloc(childTwo,registerOne, head);
    }
    
    
    
    return newOp;
}


OpData_t* storeAHelper(NodoArvore_t* node, int registerNumber, int registerThree, ComandsList_t* head){
    NodoArvore_t* childTwo = node->children->next->nodo;
    NodoArvore_t* childOne = node->children->nodo;
    
    if(childTwo->childrenNumber >0){
        int registerNewDimension = newRegister();
        recursiveIndexCalc(childTwo,registerNewDimension, registerThree, head);
    }
    if(childTwo->valorLexico.isLiteral){
        loadImediateToIlocValue(childTwo->valorLexico.memoryDeloc,registerThree, head);

    }
    else
    {
        nodeToIloc(childTwo,registerThree, head);
    }
    

    loadImediateToIlocValue(childOne->valorLexico.memoryDeloc,registerNumber, head);
}

OpData_t* recursiveIndexCalc(NodoArvore_t* node, int registerNumber, int previousRegister, ComandsList_t* head){
    OpData_t* addEnd = createIloc();
    addEnd->registerNumberArg1 = registerNumber;
    addEnd->registerNumberArg2 = previousRegister;
    addEnd->registerNumberArg3 = previousRegister;
    NodoArvore_t* currentChild = node->children->nodo;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = addEnd;

    LL_PREPEND(head->arg, newOpListElement);

    if(currentChild->childrenNumber >0){
        recursiveIndexCalc(currentChild->children->nodo,newRegister(),previousRegister, head);
    }

    if(currentChild->valorLexico.isLiteral){
        addEnd->operation = IaddI;
        loadImediateToIlocValue(currentChild->valorLexico.memoryDeloc,registerNumber, head);

    }
    else{
        addEnd->operation = Iadd;
        nodeToIloc(currentChild,registerNumber, head);

    }
}


OpData_t* genericCompareOperationToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
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
    LL_PREPEND(head->arg, newOpListElement);

    if(childOne->valorLexico.isLiteral){
        loadImediateToIloc(childOne, regUm, head);

    }
    else
    {
        nodeToIloc(childOne,regUm, head);

    }
    

    if(childTwo->valorLexico.isLiteral){
               
        loadImediateToIloc(childTwo,regDois, head);
    }
    else{
        nodeToIloc(childTwo,regDois, head);

    }      
    
    return newOp;

}



OpData_t* andToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
    OpData_t* newOpTrue = createIloc();
    OpData_t* newOpFalse = createIloc();
    newOpTrue->registerNumberArg3 = registerNumber;
    newOpFalse->registerNumberArg3 = registerNumber;
    newOpTrue->registerNumberArg1 = 0;
    newOpFalse->registerNumberArg1 = 1;
    newOpFalse->operation = IloadI;
    newOpTrue->operation = IloadI;
    OpData_t* newOpBranch1 = createIloc();
    OpData_t* newOpbranch2 = createIloc();
    OpData_t* newOpJumpI = createIloc();
    newOpJumpI->operation= IjumpI;
    newOpBranch1->operation = Icbr;
    newOpbranch2->operation = Icbr;
    int regiterRightSide = newRegister();
    int registerLeftSide = newRegister();
    newOpbranch2->registerNumberArg1 = regiterRightSide;
    newOpBranch1->registerNumberArg1 = registerLeftSide;

    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childTwo = node->children->next->nodo;
    OpDataList_t* newOpListElementFalse = calloc(1, sizeof(OpDataList_t));

    int labelEnd = createLabel(head);

    newOpListElementFalse->arg = newOpFalse;
    LL_PREPEND(head->arg, newOpListElementFalse);
    int labelFalse = createLabel(head);
    
    newOpJumpI->registerNumberArg1 = labelEnd;
    OpDataList_t* newOpListjump = calloc(1, sizeof(OpDataList_t));
    newOpListjump->arg = newOpJumpI;
    LL_PREPEND(head->arg, newOpListjump);

    OpDataList_t* newOpListElementTrue = calloc(1, sizeof(OpDataList_t));
    newOpListElementTrue->arg = newOpTrue;
    LL_PREPEND(head->arg, newOpListElementTrue);
    int labelTrue = createLabel(head);

    newOpbranch2->registerNumberArg2 = labelTrue;
    newOpbranch2->registerNumberArg3 = labelFalse;
    OpDataList_t* newOpListElementBranch2 = calloc(1, sizeof(OpDataList_t));
    newOpListElementBranch2->arg= newOpbranch2;
    LL_PREPEND(head->arg, newOpListElementBranch2);
    
    nodeToIloc(childTwo,regiterRightSide,head);
    int labelBranch2 = createLabel(head);

    newOpBranch1->registerNumberArg2 = labelBranch2;
    newOpBranch1->registerNumberArg3 = labelFalse;
    OpDataList_t* newOpListElementBranch1 = calloc(1, sizeof(OpDataList_t));
    newOpListElementBranch1->arg = newOpBranch1;
    LL_PREPEND(head->arg, newOpListElementBranch1);

    nodeToIloc(childOne, registerLeftSide, head );

}

OpData_t* orToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
    OpData_t* newOpTrue = createIloc();
    OpData_t* newOpFalse = createIloc();
    newOpTrue->registerNumberArg3 = registerNumber;
    newOpFalse->registerNumberArg3 = registerNumber;
    newOpTrue->registerNumberArg1 = 0;
    newOpFalse->registerNumberArg1 = 1;
    newOpFalse->operation = IloadI;
    newOpTrue->operation = IloadI;
    OpData_t* newOpBranch1 = createIloc();
    OpData_t* newOpbranch2 = createIloc();
    OpData_t* newOpJumpI = createIloc();
    newOpJumpI->operation= IjumpI;
    newOpBranch1->operation = Icbr;
    newOpbranch2->operation = Icbr;
    int regiterRightSide = newRegister();
    int registerLeftSide = newRegister();
    newOpbranch2->registerNumberArg1 = regiterRightSide;
    newOpBranch1->registerNumberArg1 = registerLeftSide;

    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childTwo = node->children->next->nodo;
    OpDataList_t* newOpListElementFalse = calloc(1, sizeof(OpDataList_t));

    int labelEnd = createLabel(head);

    newOpListElementFalse->arg = newOpFalse;
    LL_PREPEND(head->arg, newOpListElementFalse);
    int labelFalse = createLabel(head);
    
    newOpJumpI->registerNumberArg1 = labelEnd;
    OpDataList_t* newOpListjump = calloc(1, sizeof(OpDataList_t));
    newOpListjump->arg = newOpJumpI;
    LL_PREPEND(head->arg, newOpListjump);

    OpDataList_t* newOpListElementTrue = calloc(1, sizeof(OpDataList_t));
    newOpListElementTrue->arg = newOpTrue;
    LL_PREPEND(head->arg, newOpListElementTrue);
    int labelTrue = createLabel(head);

    newOpbranch2->registerNumberArg2 = labelTrue;
    newOpbranch2->registerNumberArg3 = labelFalse;
    OpDataList_t* newOpListElementBranch2 = calloc(1, sizeof(OpDataList_t));
    newOpListElementBranch2->arg= newOpbranch2;
    LL_PREPEND(head->arg, newOpListElementBranch2);
    
    nodeToIloc(childTwo,regiterRightSide,head);
    int labelBranch2 = createLabel(head);

    newOpBranch1->registerNumberArg2 = labelTrue;
    newOpBranch1->registerNumberArg3 = labelBranch2;
    OpDataList_t* newOpListElementBranch1 = calloc(1, sizeof(OpDataList_t));
    newOpListElementBranch1->arg = newOpBranch1;
    LL_PREPEND(head->arg, newOpListElementBranch1);

    nodeToIloc(childOne, registerLeftSide, head );

}
int createLabel(ComandsList_t* head){
    OpData_t* newOp = createIloc();
    lastKnownLabel++;
    newOp->operation = Ilabel;
    newOp->registerNumberArg1  = lastKnownLabel;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;
    LL_PREPEND(head->arg, newOpListElement);
    return lastKnownLabel;
}


OpData_t* cbrToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head){
    OpData_t* newOp = createIloc();
    newOp->operation = Icbr;
    newOp->registerNumberArg1 = registerNumber;

    
    
    OpData_t* jumpOpWhile;

    NodoArvore_t* childTwo = node->children->next->nodo;
    NodoArvore_t* childOne = node->children->nodo;
    NodoArvore_t* childThree = NULL;
    int endLabel = createLabel(head);
    int elseLabel;
    int thenLabel;

    
    if(node->childrenNumber > 2){
        OpData_t* jumpOpThen = createIloc();
        jumpOpThen->operation = IjumpI;
        jumpOpThen->registerNumberArg1 = endLabel;

        childThree =  node->children->next->next->nodo;
        nodeToIloc(childThree, newRegister(), head);
        elseLabel = createLabel(head);
        
        OpDataList_t* jumpList = calloc(1, sizeof(OpDataList_t));
        jumpList->arg = jumpOpThen;
        LL_PREPEND(head->arg, jumpList);
    }
    else{
        elseLabel = endLabel;
    }

   if(node->operation == Iwhile){
        jumpOpWhile = createIloc();
        jumpOpWhile->operation = IjumpI;
        OpDataList_t* jumpList = calloc(1, sizeof(OpDataList_t));
        jumpList->arg = jumpOpWhile;
        LL_PREPEND(head->arg, jumpList);
    }
    
    nodeToIloc(childTwo,newRegister(),head);
    thenLabel = createLabel(head);
    newOp->registerNumberArg2 = thenLabel;
    newOp->registerNumberArg3 = elseLabel;
    OpDataList_t* newOpListElement = calloc(1, sizeof(OpDataList_t));
    newOpListElement->arg = newOp;
    LL_PREPEND(head->arg, newOpListElement);

    nodeToIloc(childOne, registerNumber, head);
    if(node->operation == Iwhile){
        jumpOpWhile->registerNumberArg1 = createLabel(head);
    }






}


OpData_t* addRfp( int registerDeslocamento, int registerNumber, bool isLocal, ComandsList_t* head){
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
    LL_PREPEND(head->arg, newOpListElement);
    return newOp;
}

OpData_t* addIRfp( int deslocamento, int registerNumber, bool isLocal, ComandsList_t* head){
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
    LL_PREPEND(head->arg, newOpListElement);
    return newOp;
}


void dumpAllOperations(OpDataList_t* listOperations){
    if(listOperations == NULL){
        return;
    }
    else{
        dumpAllOperations(listOperations->next);
        free(listOperations->arg);
        listOperations->arg = NULL;
        if(listOperations->next != NULL){
            free(listOperations->next);
            listOperations->next = NULL;
        }
        

        return;
    }
}



void dumpAllCommands(ComandsList_t* listCommands){
    if(listCommands == NULL){
        return;
    }
    else
    {   
        dumpAllCommands(listCommands->next);
        dumpAllOperations(listCommands->arg);
        if(listCommands->arg != NULL){
            free(listCommands->arg);
            listCommands->arg = NULL;
        }
        if(listCommands->next != NULL){
            free(listCommands->next);
            listCommands->next = NULL;
        }
        return;
    };
    

}



void dumpAllInterface(){
    dumpAllCommands(commandsList);
    free(commandsList);
    commandsList = NULL;
}