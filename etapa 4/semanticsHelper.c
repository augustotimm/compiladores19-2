#include "helper.h"
#include "semanticsErrors.h"

HashList_t* hashList = NULL;

HashTree_t* createHash(HashTree_t* parent){
    HashTree_t* newHashT = calloc(1,sizeof(HashTree_t));
    newHashT->current = NULL;
    newHashT->parent = parent;
    addHashToList(newHashT);
    return newHashT;
}

void deleteHash(HashTree_t* hashT){
    MyHash_t* temp;
    MyHash_t* currentValue;
    MyHash_t* current = hashT->current;
    HASH_ITER(hh, current, currentValue, temp){
        HASH_DEL(current,currentValue);
        free(currentValue->valorSemantico);
        free(currentValue);

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
    if(found != NULL){
        return found->valorSemantico;
    }
    else{
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

ValorSemantico_t* createSemanticValueFromLexical(ValorLexico_t valorLexico, Nature_s nature){

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
        free(currentHashList);
        currentHashList = NULL;
        return;
    }
    else{
        freeListaHashRecursive(currentHashList->next);
        deleteHash(currentHashList->hash);
        free(currentHashList->hash);
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