#include "semanticsHelper.h"



HashTree_t* createHash(HashTree_t* parent){
    HashTree_t* newHashT = calloc(1,sizeof(HashTree_t));
    MyHash_t* newHash = calloc(1,sizeof(MyHash_t));
    newHashT->current =newHash;
    newHashT->parent = parent;
    return newHashT;
}

void deleteHash(HashTree_t* hashT){
    MyHash_t* temp;
    MyHash_t* currentValue;
    MyHash_t* current = hashT->current;
    UT_hash_handle hh = current->hh;
    HASH_ITER(hh, current, currentValue, temp){
        HASH_DEL(current,currentValue);
        free(currentValue->valorSemantico);
        free(currentValue);

    }
    free(hashT->current);
}

MyHash_t* addToHash(HashTree_t* hashT, ValorSemantico_t* valorSemantico){
    MyHash_t* newInput = calloc(1, sizeof(MyHash_t));
    newInput->identificador = valorSemantico->valorLexico_t.stringValue;
    newInput->valorSemantico = valorSemantico;
    MyHash_t* current = hashT->current;
    UT_hash_handle hh = current->hh;
    HASH_ADD_KEYPTR( hh, current,newInput, strlen(newInput->identificador), newInput);
    return newInput;
}


ValorSemantico_t* findSemanticValue(HashTree_t* hashT, char* key){
    MyHash_t* found = NULL;
    HASH_FIND_STR( hashT->current,key,found );
    if(found){
        return found->valorSemantico;
    }
    else{
        if (hashT->parent != NULL)
        {
            return findSemanticValue(hashT->parent, key);
        }
        else{
            //todo Not Found key
            return NULL;
        }
        
    }
    return NULL;    
}


