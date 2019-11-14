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

void loadAITranslate(OpData_t* currentOp ){
    fprintf( stdout, "loadAI      r%d,%d    =>  r%d",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void loadA0Translate(OpData_t* currentOp ){
    fprintf( stdout, "loadA0      r%d,r%d    =>  r%d",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void storeAITranslate(OpData_t* currentOp ){
    fprintf( stdout, "storeAI      r%d,%d    =>  r%d",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void storeA0Translate(OpData_t* currentOp ){
    fprintf( stdout, "storeA0      r%d,r%d    =>  r%d",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void storeTranslate(OpData_t* currentOp ){
    fprintf( stdout, "store      r%d,    =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2 );
}

void cmpLTTranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_LT      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpLETranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_LE      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpEQTranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_EQ      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpGETranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_GE      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpGTranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_GT      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpNETranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_NE      r%d, %d   =>  r%d",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
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
            loadTranslate(current);
            break;
        case IloadI:
            loadITranslate(current);
            break;
        case Istore:
            storeTranslate(current);
            break;
        case IstoreA0:
            storeA0Translate(current);
            break;
        case IloadA0:
            loadA0Translate(current);
            break;
        case IloadAI:
            loadAITranslate(current);
            break;
        case IstoreAI:
            storeAITranslate(current);
            break;
        case IcmpLt:
            cmpLTranslate(current);
            break;
        case IcmpLe:
            cmpLETranslate(current);
            break;
        case IcmpEq:
            cmpEQTranslate(current);
            break;
        case IcmpGe:
            cmpGETranslate(current);
            break;
        case IcmpGt:
            cmpGTTranslate(current);
            break;
        case IcmpNe:
            cmpNETranslate(current);
            break;
        default:
            genericBinaryOperationToIloc(node,registerNumber);
            break;;
        }
    }
}