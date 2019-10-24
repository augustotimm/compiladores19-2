#include "semanticsHelper.h"



HashTree_t* createHash(HashTree_t* parent){
    HashTree_t* newHashT = calloc(1,sizeof(HashTree_t));
    MyHash_t* newHash = calloc(1,sizeof(MyHash_t));
    newHashT->current =newHash;
    newHashT->parent = parent;
    return newHashT;
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


