#include "helper.h"

extern OpDataList_t* operationsList;



void addTranslate(OpData_t* addop ){
    fprintf( stdout, "add      r%d, r%d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void subTranslate(OpData_t* addop ){
    fprintf( stdout, "sub      r%d, r%d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void multTranslate(OpData_t* addop ){
    fprintf( stdout, "mult      r%d, r%d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void divTranslate(OpData_t* addop ){
    fprintf( stdout, "div      r%d, r%d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}
    

void addITranslate(OpData_t* addop ){
    fprintf( stdout, "add      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void subITranslate(OpData_t* addop ){
    fprintf( stdout, "sub      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void multITranslate(OpData_t* addop ){
    fprintf( stdout, "mult      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void divITranslate(OpData_t* addop ){
    fprintf( stdout, "div      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void andTranslate(OpData_t* addop ){
    fprintf( stdout, "and      r%d, r%d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void andITranslate(OpData_t* addop ){
    fprintf( stdout, "and      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void orTranslate(OpData_t* addop ){
    fprintf( stdout, "or      r%d, r%d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void orITranslate(OpData_t* addop ){
    fprintf( stdout, "or      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void xorITranslate(OpData_t* addop ){
    fprintf( stdout, "xor      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
}

void xorITranslate(OpData_t* addop ){
    fprintf( stdout, "xor      r%d, %d   =>  r%d",
     addop->registerNumberArg1, addop->registerNumberArg2, addop->registerNumberArg3 );
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