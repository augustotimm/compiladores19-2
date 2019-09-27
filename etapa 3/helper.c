#include "helper.h"

void libera(void *tree){
    
    NodoArvore_t* nodo, *nodoDois, *nodoTres;
    nodo = criarNodo();
    nodoDois = criarNodo();
    nodoTres = criarNodo();
    addChildren(nodo,nodoDois);
    addChildren(nodoDois, nodoTres );
    printNodo(nodo);
    deletaNodo(nodo);
    
}

void exporta(void *tree){
}

void printNodo(NodoArvore_t* nodo){
    printf("Nodo: %p\n",nodo);
    printf("numero de filhos: %d\n", nodo->childrenNumber);
    if(nodo->childrenNumber > 0){
        NodoList_t* elt;
        LL_FOREACH(nodo->children,elt){
            printf("Nodo: %p\n",elt);
            printf("numero de filhos: %d\n", nodo->childrenNumber);
        }
    }
    
}

NodoArvore_t* criarNodo(){
    NodoArvore_t* novoNodo = calloc(1, sizeof(NodoArvore_t));
    novoNodo->childrenNumber = 0;
    
    return novoNodo;
}

NodoArvore_t* addChildren(NodoArvore_t* parent,NodoArvore_t* child){
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
        free(nodo->children);

    }
    free(nodo);
    return true;
    
}