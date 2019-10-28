#include "helper.h"

#define SIZE_OF_CHAR 1
#define SIZE_OF_INT 4
#define SIZE_OF_FLOAT 8
#define SIZE_OF_BOOL 1

HashStack_t* hashStack = NULL;

HashTree_t* createHash(HashTree_t* parent, ValorSemantico_t* hashCreator){
    HashTree_t* newHashT = calloc(1,sizeof(HashTree_t));
    HashStack_t* newHashStack = calloc(1, sizeof(HashStack_t));
    newHashT->current = NULL;
    newHashT->parent = parent;
    newHashT->hashCreator = hashCreator;
    newHashStack->hash = newHashT;
    STACK_PUSH(hashStack,newHashStack);
    return newHashT;
}

void freeArgs(ArgsList_t* args){
    if(args->next == NULL){
        liberaValorLexico(args->arg->valorLexico);
        free(args->arg);
        args->arg= NULL;
        free(args);
        args = NULL;
        return;    
    }
    else
    {
        liberaValorLexico(args->arg->valorLexico);
        freeArgs(args->next);
        free(args->arg->name);
        args->arg->name = NULL;
        free(args->arg);
        args->arg= NULL;
        free(args);
        args = NULL;

    }
    

}

void deleteHash(HashTree_t* hashT){
    MyHash_t* temp = NULL;
    MyHash_t* currentValue = NULL;
    if(hashT != NULL){
        MyHash_t* current = hashT->current;
        HASH_ITER(hh, current, currentValue, temp){
            HASH_DEL(current,currentValue);
            
            
            if(currentValue->valorSemantico != NULL){
                if(currentValue->valorSemantico->args != NULL){
                freeArgs(currentValue->valorSemantico->args);
                }
                if(currentValue->valorSemantico->name != NULL){
                free( currentValue->valorSemantico->name);
                currentValue->valorSemantico->name = NULL;
                }
                else{
                    if(currentValue->identificador != NULL){
                    free(currentValue->identificador);
                    currentValue->identificador = NULL;
                    }
                }
                
                free( currentValue->valorSemantico);
                currentValue->valorSemantico= NULL;
                
            }else{
                if(currentValue->identificador != NULL){
                    free(currentValue->identificador);
                    currentValue->identificador = NULL;
                }
            }
            
            
            if(currentValue != NULL){
                free(currentValue);
                currentValue = NULL;
            }
            
            

        }
        free(hashT);
        hashT = NULL;
        HashStack_t* elt = NULL;
        STACK_POP(hashStack, elt);
        free(elt);
        elt = NULL;
    }
    
}

void addHashToList(HashTree_t* hashT){
    if(hashStack == NULL){
        hashStack = calloc(1,sizeof( HashStack_t));
        hashStack->hash = hashT;
        hashStack->next = NULL;
    }
    else{
        HashStack_t* newhash = calloc(1,sizeof(HashStack_t));
        newhash->hash = hashT;
        newhash->next = NULL;
        LL_APPEND( hashStack, newhash);
    }

}

HashTree_t* getCurrentHash(){
    HashStack_t* temp;
    temp= STACK_TOP(hashStack);
    return temp->hash;
}

MyHash_t* addToHash(HashTree_t* hashT, ValorSemantico_t* valorSemantico, char* identificadorVar){
    MyHash_t* newInput = calloc(1, sizeof(MyHash_t));
    newInput->identificador = identificadorVar;
    newInput->valorSemantico = valorSemantico;
    MyHash_t* current = hashT->current;
    ValorSemantico_t* found = findSemanticValue(hashT,identificadorVar);
    if(found != NULL){
        printf("variavel Ja declarada no escopo");
        exit(ERR_DECLARED);
    }
    HASH_ADD_STR( hashT->current, identificador, newInput);
    return newInput;
}


ValorSemantico_t* findSemanticValue(HashTree_t* hashT, char* key){
    MyHash_t* found = NULL;
    HASH_FIND_STR( hashT->current,key,found );
    if(found != NULL ){
        return found->valorSemantico;
    }
    else{
        if(hashT->hashCreator != NULL){
            ArgsList_t* arg;
            LL_FOREACH(hashT->hashCreator->args, arg){
                if (strcmp(key,arg->arg->valorLexico.stringValue)==0)
                {
                    return arg->arg;
                }
                
            }
        }
        if (hashT->parent != NULL)
        {
            return findSemanticValue(hashT->parent, key);
        }
        else{
            return NULL;
        }
        
    }
    return NULL;    
}

ValorSemantico_t* createSemanticValueFromLexical(ValorLexico_t valorLexico, int  nature){

    ValorSemantico_t* semanticValue = calloc(1, sizeof(ValorSemantico_t));
    semanticValue->name = NULL;
    semanticValue->numeroLinha = valorLexico.numeroLinha;
    semanticValue->tipo = valorLexico.tipo;
    semanticValue->nature = nature;
    //todo definir sizeof
    semanticValue->args = NULL;
    semanticValue->valorLexico =valorLexico;

    return semanticValue;    
}


void freeListaHashRecursive(HashStack_t* currentHashList){
    if(currentHashList->next == NULL){
        if(currentHashList->hash != NULL){
            deleteHash(currentHashList->hash);
        }
        
        free(currentHashList);
        currentHashList = NULL;
        return;
    }
    else{
        freeListaHashRecursive(currentHashList->next);
        if(currentHashList->hash != NULL){
            deleteHash(currentHashList->hash);
        }
        free(currentHashList);
        currentHashList = NULL;
    }
}

void dumpHashes(){
    
    freeListaHashRecursive(hashStack);
}

void printHash(HashTree_t* hashT){
    MyHash_t* temp;
    MyHash_t* currentValue;
    MyHash_t* current = hashT->current;
    UT_hash_handle hh = current->hh;

    HASH_ITER(hh, current, currentValue, temp){
       
       printf("%s\n",currentValue->identificador);

    }
}
void createArgsSemantics_recursive(ValorSemantico_t* func, NodoArvore_t* args){
    if(args == NULL){
        return;
    }
    else{
        ValorLexico_t argsLexico = args->valorLexico;
        argsLexico.stringValue = strdup(args->valorLexico.stringValue);
        ValorSemantico_t* argSemantics = createSemanticValueFromLexical(argsLexico, NATUREZA_IDENTIFICADOR);
        ArgsList_t* currentArgument = calloc(1, sizeof(ArgsList_t));
        currentArgument->arg = argSemantics;
        currentArgument->next = NULL;
        LL_APPEND(func->args, currentArgument);
        if(args->childrenNumber > 1 ){
            //ERRO NA AST
        }
        if(args->childrenNumber > 0){
            NodoList_t* child = NULL;
            LL_FOREACH(args->children, child){
                createArgsSemantics_recursive(func, child->nodo);

            }
        }
        return;
    }
}

void createArgsSemantics(ValorSemantico_t* func, NodoArvore_t* args){
    createArgsSemantics_recursive(func, args);
}

ValorSemantico_t* checkIdentifierDeclared(HashTree_t* hashT, char* identificador){
    ValorSemantico_t* found = findSemanticValue(hashT, identificador);
    if(found == NULL){
        exit(ERR_UNDECLARED);
    }
    else{
        return found;
    }
}

Tipo_t typeInfer(Tipo_t tipoA, Tipo_t tipoB){
    switch (tipoA)
    {
    case  Tint:
        switch (tipoB)
        {
        case Tint: return Tint;
        
        case Tfloat: return Tfloat;
        
        case Tbool: return Tint;

        case Tchar: exit( ERR_CHAR_TO_X );
        
        case Tstring: exit( ERR_STRING_TO_X );
        
        }break;

        
    
    case Tfloat:
        switch (tipoB)
        {
        case Tint: return Tfloat;
        
        case Tfloat: return Tfloat;
        
        case Tbool: return Tfloat;
        
        case Tchar: exit( ERR_CHAR_TO_X );
        
        case Tstring: exit( ERR_STRING_TO_X );
        }break;

    case Tbool:
        switch (tipoB)
        {
        case Tint: return Tint;
        
        case Tfloat: return Tfloat;
        
        case Tbool: return Tbool;
        
        case Tchar: exit( ERR_CHAR_TO_X );
        
        case Tstring: exit( ERR_STRING_TO_X );
        }break;

    case Tchar:
        switch (tipoB)
        {
        case Tint: exit( ERR_CHAR_TO_X );
        
        case Tfloat: exit( ERR_CHAR_TO_X );
        
        case Tbool: exit( ERR_CHAR_TO_X );
        
        case Tchar: return Tchar;
        
        case Tstring: exit( ERR_CHAR_TO_X );
        } break;

    case Tstring:
        switch (tipoB)
        {
        case Tint: exit( ERR_STRING_TO_X );
        
        case Tfloat: exit( ERR_STRING_TO_X );
        
        case Tbool: exit( ERR_STRING_TO_X );
        
        case Tchar: exit( ERR_STRING_TO_X );
        
        case Tstring: return Tstring;
        } break;

    default:
        break;
    }

}

char* createNameFromAddress(ValorSemantico_t* valorSemantico) {
    
    char* a = calloc(16, sizeof(char));
    
    snprintf(a, 16, "%p", valorSemantico );
    return a;
}

void getNameFromAddress(ValorSemantico_t* valorSemantico){
    if( valorSemantico->name != NULL){
        free(valorSemantico->name);
    }
    valorSemantico->name = createNameFromAddress(valorSemantico);

}

Tipo_t getParentFunctionType(HashTree_t* hashT){
    if(hashT->hashCreator == NULL){
        if( hashT->parent ==NULL){
            exit( ERR_WRONG_PAR_RETURN);
        }
        getParentFunctionType(hashT->parent);
    }
    else{
        
        return hashT->hashCreator->tipo;
    }
}


bool canConvertType(Tipo_t expected, Tipo_t received){
    switch (expected)
    {
    case Tint: switch (received)
        {
        case Tint:
            return true;
        case Tfloat:
            return true;
        case Tbool:
            return true;
        
        default:
            return false;
            break;
        }
        break;
    
    case Tfloat: switch (received)
        {
        case Tint:
            return true;
        case Tbool:
            return true;
        case Tfloat:
            return true;
        default:
            return false;
            break;
        }

    case Tbool:switch (received)
        {
        case Tint:
            return true;
        case Tbool:
            return true;
        case Tfloat:
            return true;
        default:
            return false;
            break;
        }

    case Tchar:
        if(received == Tchar){
            return true;
        }
        else{
            return false;
        }
    case Tstring:
        if(received == Tstring){
            return true;
        }
        else{
            return false;
        }

    default:
        break;
    }
}

bool verifyArgs(ArgsList_t* expected, NodoArvore_t* received){
    if(expected != NULL && received != NULL){
        if( canConvertType(expected->arg->tipo, received->tipo) ){
            if( expected->next == NULL && received->children != NULL){
                exit(ERR_EXCESS_ARGS );
            }
            if(expected->next != NULL && received->children == NULL) {
                exit(ERR_MISSING_ARGS);
            }
            if(expected->next == NULL && received->children== NULL){
                return true;
            }
            verifyArgs(expected->next, received->children->nodo);
        }
        else{
            exit(ERR_WRONG_TYPE_ARGS);
        }
    }

    if(expected == NULL && received != NULL ){
        exit(ERR_EXCESS_ARGS );
    }

    if(expected != NULL && received == NULL){
        exit(ERR_MISSING_ARGS);
    }
    if(expected == NULL && received == NULL){
        return true;
    }
    
}

void convertNodeBoolToInt(NodoArvore_t* nodo){
    if( nodo->tipo == Tbool){
        nodo->tipo = Tint;
    }
}

