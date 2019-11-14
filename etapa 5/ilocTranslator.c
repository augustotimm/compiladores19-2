#include "helper.h"

extern OpDataList_t* operationsList;



void addTranslate(OpData_t* currentOp ){
    if(currentOp->registerType == Rfp){
        fprintf( stdout, "add      rfp, r%d   =>  r%d",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rbss) {
        fprintf( stdout, "add      rbss, r%d   =>  r%d",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rdefault) {
        fprintf( stdout, "add      r%d, r%d   =>  r%d",
         currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }
    
}

void subTranslate(OpData_t* currentOp ){
    fprintf( stdout, "sub      r%d, r%d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void multTranslate(OpData_t* currentOp ){
    fprintf( stdout, "mult      r%d, r%d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void divTranslate(OpData_t* currentOp ){
    fprintf( stdout, "div      r%d, r%d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}
    

void addITranslate(OpData_t* currentOp ){
    if(currentOp->registerType == Rfp){
        fprintf( stdout, "add      rfp, %d   =>  r%d",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rbss) {
        fprintf( stdout, "add      rbss, %d   =>  r%d",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rdefault) {
        fprintf( stdout, "add      r%d, %d   =>  r%d",
         currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }
}

void subITranslate(OpData_t* currentOp ){
    fprintf( stdout, "sub      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void multITranslate(OpData_t* currentOp ){
    fprintf( stdout, "mult      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void divITranslate(OpData_t* currentOp ){
    fprintf( stdout, "div      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void andTranslate(OpData_t* currentOp ){
    fprintf( stdout, "and      r%d, r%d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void andITranslate(OpData_t* currentOp ){
    fprintf( stdout, "and      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void orTranslate(OpData_t* currentOp ){
    fprintf( stdout, "or      r%d, r%d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void orITranslate(OpData_t* currentOp ){
    fprintf( stdout, "or      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void xorITranslate(OpData_t* currentOp ){
    fprintf( stdout, "xor      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void xorITranslate(OpData_t* currentOp ){
    fprintf( stdout, "xor      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void loadITranslate(OpData_t* currentOp ){
    fprintf( stdout, "loadI      %d,    =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg3 );
}

void loadTranslate(OpData_t* currentOp ){
    fprintf( stdout, "load      r%d,    =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg3 );
}


void translateIloc(){
    OpDataList_t* current;
    LL_FOREACH(operationsList, current){
        switch (operationsList->arg->operation)
        {
    
        case Iadd: 
            addTranslate(current );
            break;
        case Isub:
            subTranslate(current);
            break;
        case Imult:
            multTranslate(current);
            break;
        case Idiv:
            divTranslate(current);
            break;
        case IaddI: 
            addITranslate(current );
            break;
        case IsubI:
            subITranslate(current);
            break;
        case ImultI:
            multITranslate(current);
            break;
        case IdivI:
            divITranslate(current);
            break;
        case Iand:
            andTranslate(current);
            break;
        case IandI:
            andITranslate(current);
            break;
        case Ior:
            orTranslate(current);
            break;
        case IorI:
            orITranslate(current);
            break;
        case Ixor:
            xorTranslate(current);
            break;
        case IxorI:
            xorITranslate(current);
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
}