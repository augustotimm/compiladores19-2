#include "helper.h"

void libera(void *tree){
    printNodo(tree);
    if( tree != NULL){
        deletaNodo(tree);
    }
    
    
}

void exporta(void *tree){
    if( tree != NULL){
        FILE *file = fopen("./OUT.csv", "w");
        saveNodo(tree,file);
        fclose(file);
    }
    
}

ValorLexico_t criaValorLexicoOP(char* valor){
    ValorLexico_t novoValor;
    novoValor.tipo = Top;
    novoValor.charValue = '\0'; 
    novoValor.boolValue = false; 
    novoValor.floatValue = 0; 
    novoValor.stringValue = strdup(valor);
    novoValor.intValue = 0;

    return novoValor;
}

void saveNodo(NodoArvore_t* nodo, FILE* file){
    NodoList_t* elt;
    if(nodo->childrenNumber > 0 ){
        LL_FOREACH(nodo->children,elt){
            saveNodo(elt->nodo, file);
            fprintf(file,"%p,%p\n", nodo, elt->nodo);
        }
    }
}

void printNodo(NodoArvore_t* nodo){
    
    if(nodo->childrenNumber > 0){
        NodoList_t* elt;
        LL_FOREACH(nodo->children,elt){
            printNodo(elt->nodo);
            printf("%s:%s\n", nodo->valorLexico.stringValue , elt->nodo->valorLexico.stringValue);
        }
    }
    else{
         //printf("%s\n", nodo->valorLexico.stringValue);
    }
    
    
}

NodoArvore_t* criaNodo(){
    NodoArvore_t* novoNodo = calloc(1, sizeof(NodoArvore_t));
    novoNodo->childrenNumber = 0;
    
    return novoNodo;
}

NodoArvore_t* criaNodoValorLexico( ValorLexico_t valor_lexico){
    NodoArvore_t* novoNodo = calloc(1, sizeof(NodoArvore_t));
    novoNodo->childrenNumber = 0;
    novoNodo->valorLexico = valor_lexico;
    
    return novoNodo;
}

NodoArvore_t* addChildren(NodoArvore_t* parent,NodoArvore_t* child){
    if( child == NULL && parent != NULL) {
        return parent;
    }
    if( parent == NULL && child != NULL) {
        return child;
    }
    if( parent == NULL && child == NULL){
        return NULL;
    }
    if(parent->childrenNumber ==0){
        NodoList_t * head = NULL;
        parent->children = head;
    }
    
    NodoList_t * newChild = calloc(1, sizeof(NodoList_t));
    newChild->nodo =child;
    LL_APPEND( parent->children, newChild);

    parent->childrenNumber++;
    return parent;
    
}

bool deletaNodo(NodoArvore_t* nodo){
    NodoList_t* elt;
    if(nodo->childrenNumber != 0 ){
        LL_FOREACH(nodo->children,elt){
            deletaNodo(elt->nodo);            
        }
        free(nodo->valorLexico.stringValue);
        free(nodo->children);

    }
    free(nodo);
    return true;
    
}

void liberaValorLexico(ValorLexico_t valor){
    free(valor.stringValue);
}