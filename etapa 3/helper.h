#include <stdio.h>
#include "uthash.h"
#include <stdbool.h>

struct NodoArvore_t;

typedef struct MyString
{
    char valor[512];
}MyString;


/*
Struct utilizada junto com a biblioteca uthash.h para poder utilizar os filhos como hash
*/
typedef struct NodoHash_t{
    struct NodoArvore_t *nodo;
    int id;
} NodoHash_t;

typedef enum {
    Tint,
    Tfloat,
    Tchar,
    Tbool,
    Tstring,
} Tipo_t;


typedef struct ValorLexico_t {
    int numeroLinha;
    char tokenText[20];
    Tipo_t tipo;
    bool isLiteral;
    MyString *stringValue;
    bool boolValue;
    char charValue;

} ValorLexico_t;


/*
 Struct Utilizada para a Arvore

*/
typedef struct NodoArvore_t{
    int childrenNumber;
    ValorLexico_t valorLexico;
    NodoHash_t *children;
} NodoArvore_t;


extern void libera(void *tree);
extern void exporta(void *tree);
