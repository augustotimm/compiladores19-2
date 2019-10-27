#include "helper.h"
#include "semanticsErrors.h"

#define SIZE_OF_CHAR 1
#define SIZE_OF_INT 4
#define SIZE_OF_FLOAT 8
#define SIZE_OF_BOOL 1

HashList_t* hashList = NULL;

HashTree_t* createHash(HashTree_t* parent, ValorSemantico_t* hashCreator){
    HashTree_t* newHashT = calloc(1,sizeof(HashTree_t));
    newHashT->current = NULL;
    newHashT->parent = parent;
    newHashT->hashCreator = hashCreator;
    addHashToList(newHashT);
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
        free(args->arg);
        args->arg= NULL;
        free(args);
        args = NULL;

    }
    

}

void deleteHash(HashTree_t* hashT){
    MyHash_t* temp;
    MyHash_t* currentValue;
    MyHash_t* current = hashT->current;
    HASH_ITER(hh, current, currentValue, temp){
        HASH_DEL(current,currentValue);
        if(currentValue->valorSemantico->args != NULL){
            freeArgs(currentValue->valorSemantico->args);
        }
        free( currentValue->valorSemantico);
        currentValue->valorSemantico= NULL;
        free(currentValue->identificador);
        currentValue->identificador = NULL;
        free(currentValue);
        currentValue = NULL;

    }
}

void addHashToList(HashTree_t* hashT){
    if(hashList == NULL){
        hashList = calloc(1,sizeof( HashList_t));
        hashList->hash = hashT;
        hashList->next = NULL;
    }
    else{
        HashList_t* newhash = calloc(1,sizeof(HashList_t));
        newhash->hash = hashT;
        newhash->next = NULL;
        LL_APPEND( hashList, newhash);
    }

}

HashTree_t* getCurrentHash(){
    HashList_t* tmp;
    LL_FOREACH(hashList,tmp){
        if(tmp->next== NULL){
            return tmp->hash;
        }
    }
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
    semanticValue->numeroLinha = valorLexico.numeroLinha;
    semanticValue->tipo = valorLexico.tipo;
    semanticValue->nature = nature;
    //todo definir sizeof
    semanticValue->args = NULL;
    semanticValue->valorLexico =valorLexico;

    return semanticValue;    
}


void freeListaHashRecursive(HashList_t* currentHashList){
    if(currentHashList->next == NULL){
        deleteHash(currentHashList->hash);
        free(currentHashList->hash);
        currentHashList->hash = NULL;
        free(currentHashList);
        currentHashList = NULL;
        return;
    }
    else{
        freeListaHashRecursive(currentHashList->next);
        deleteHash(currentHashList->hash);
        free(currentHashList->hash);
        currentHashList->hash = NULL;
        free(currentHashList);
        currentHashList = NULL;
    }
}

void dumpHashes(){
    
    freeListaHashRecursive(hashList);
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