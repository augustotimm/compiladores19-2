#include "helper.h"

extern ComandsList_t* commandsList;



void addTranslate(OpData_t* currentOp ){
    if(currentOp->registerType == Rfp){
        fprintf( stdout, "add      rfp, r%d   =>  r%d\n",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rbss) {
        fprintf( stdout, "add      rbss, r%d   =>  r%d\n",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rdefault) {
        fprintf( stdout, "add      r%d, r%d   =>  r%d\n",
         currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }
    
}

void subTranslate(OpData_t* currentOp ){
    fprintf( stdout, "sub      r%d, r%d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void multTranslate(OpData_t* currentOp ){
    fprintf( stdout, "mult      r%d, r%d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void divTranslate(OpData_t* currentOp ){
    fprintf( stdout, "div      r%d, r%d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}
    

void addITranslate(OpData_t* currentOp ){
    if(currentOp->registerType == Rfp){
        fprintf( stdout, "addI      rfp, %d   =>  r%d\n",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rbss) {
        fprintf( stdout, "addI      rbss, %d   =>  r%d\n",
         currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }

    if(currentOp->registerType == Rdefault) {
        fprintf( stdout, "addI      r%d, %d   =>  r%d\n",
         currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
    }
}

void subITranslate(OpData_t* currentOp ){
    fprintf( stdout, "sub      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void multITranslate(OpData_t* currentOp ){
    fprintf( stdout, "mult      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void divITranslate(OpData_t* currentOp ){
    fprintf( stdout, "div      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void andTranslate(OpData_t* currentOp ){
    fprintf( stdout, "and      r%d, r%d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void andITranslate(OpData_t* currentOp ){
    fprintf( stdout, "and      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void orTranslate(OpData_t* currentOp ){
    fprintf( stdout, "or      r%d, r%d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void orITranslate(OpData_t* currentOp ){
    fprintf( stdout, "or      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void xorTranslate(OpData_t* currentOp ){
    fprintf( stdout, "xor      r%d, r%d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void xorITranslate(OpData_t* currentOp ){
    fprintf( stdout, "xorI      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void loadITranslate(OpData_t* currentOp ){
    fprintf( stdout, "loadI      %d,    =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg3 );
}

void loadTranslate(OpData_t* currentOp ){
    fprintf( stdout, "load      r%d,    =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg3 );
}

void loadAITranslate(OpData_t* currentOp ){
    fprintf( stdout, "loadAI      r%d,%d    =>  r%d\n",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void loadA0Translate(OpData_t* currentOp ){
    fprintf( stdout, "loadA0      r%d,r%d    =>  r%d\n",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void storeAITranslate(OpData_t* currentOp ){
    fprintf( stdout, "storeAI      r%d,%d    =>  r%d\n",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void storeA0Translate(OpData_t* currentOp ){
    fprintf( stdout, "storeA0      r%d,r%d    =>  r%d\n",
     currentOp->registerNumberArg1,currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void storeTranslate(OpData_t* currentOp ){
    fprintf( stdout, "store      r%d,    =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2 );
}

void cmpLTTranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_LT      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpLETranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_LE      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpEQTranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_EQ      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpGETranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_GE      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpGTranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_GT      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void cmpNETranslate(OpData_t* currentOp ){
    fprintf( stdout, "cmp_NE      r%d, %d   =>  r%d\n",
     currentOp->registerNumberArg1, currentOp->registerNumberArg2, currentOp->registerNumberArg3 );
}

void translateIloc(){
    ComandsList_t* currentCommand;
    LL_FOREACH(commandsList, currentCommand){
        OpDataList_t* current;

        LL_FOREACH(currentCommand->arg, current){
            switch (current->arg->operation)
            {
            
                case Iadd: 
                    addTranslate(current->arg );
                    break;
                case Isub:
                    subTranslate(current->arg);
                    break;
                case Imult:
                    multTranslate(current->arg);
                    break;
                case Idiv:
                    divTranslate(current->arg);
                    break;
                case IaddI: 
                    addITranslate(current->arg );
                    break;
                case IsubI:
                    subITranslate(current->arg);
                    break;
                case ImultI:
                    multITranslate(current->arg);
                    break;
                case IdivI:
                    divITranslate(current->arg);
                    break;
                case Iand:
                    andTranslate(current->arg);
                    break;
                case IandI:
                    andITranslate(current->arg);
                    break;
                case Ior:
                    orTranslate(current->arg);
                    break;
                case IorI:
                    orITranslate(current->arg);
                    break;
                case Ixor:
                    xorTranslate(current->arg);
                    break;
                case IxorI:
                    xorITranslate(current->arg);
                    break;
                case Iload:
                    loadTranslate(current->arg);
                    break;
                case IloadI:
                    loadITranslate(current->arg);
                    break;
                case Istore:
                    storeTranslate(current->arg);
                    break;
                case IstoreA0:
                    storeA0Translate(current->arg);
                    break;
                case IloadA0:
                    loadA0Translate(current->arg);
                    break;
                case IloadAI:
                    loadAITranslate(current->arg);
                    break;
                case IstoreAI:
                    storeAITranslate(current->arg);
                    break;
                case IcmpLt:
                    cmpLTTranslate(current->arg);
                    break;
                case IcmpLe:
                    cmpLETranslate(current->arg);
                    break;
                case IcmpEq:
                    cmpEQTranslate(current->arg);
                    break;
                case IcmpGe:
                    cmpGETranslate(current->arg);
                    break;
                case IcmpGt:
                    cmpGTranslate(current->arg);
                    break;
                    cmpNETranslate(current->arg);
                    break;
                default:
                    break;;
            }
        }
        
    }
}