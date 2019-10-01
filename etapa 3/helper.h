#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utlist.h"

struct NodoArvore_t;




/*
Struct utilizada junto com a biblioteca uthash.h para poder utilizar os filhos como hash
*/
typedef struct NodoList_t{
    struct NodoArvore_t *nodo;
    struct NodoList_t* next;
} NodoList_t;

typedef enum {
    Tint,
    Tfloat,
    Tchar,
    Tbool,
    Tstring,
    Tpr,
    Top,
    Tid,
} Tipo_t;


typedef struct ValorLexico_t {
    int numeroLinha;
    Tipo_t tipo;
    Tipo_t tipoOperador;
    bool isLiteral;
    char *stringValue;
    bool boolValue;
    char charValue;
    int intValue;
    float floatValue;


} ValorLexico_t;


/*
 Struct Utilizada para a Arvore

*/
typedef struct NodoArvore_t{
    int childrenNumber;
    ValorLexico_t* valorLexico;
    NodoList_t *children;
} NodoArvore_t;

void printNodo(NodoArvore_t* nodo);
NodoArvore_t* criaNodo();
NodoArvore_t* addChildren(NodoArvore_t* parent,NodoArvore_t* child);
bool deletaNodo(NodoArvore_t* nodo);
void saveNodo(NodoArvore_t* nodo, FILE* file);

extern void libera(void *tree);
extern void exporta(void *tree);
