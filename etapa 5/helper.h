#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h> 
#include "utlist.h"
#include "utstack.h"
#include "semanticsErrors.h"


#include "uthash.h"


#define NATUREZA_LITERAL_INT        1
#define NATUREZA_LITERAL_FLOAT      2
#define NATUREZA_LITERAL_CHAR       3
#define NATUREZA_LITERAL_STRING     4
#define NATUREZA_LITERAL_BOOL       5
#define NATUREZA_IDENTIFICADOR      6

struct NodoArvore_t;
struct ValorSemantico_t;

typedef enum {
    Tint,
    Tfloat,
    Tchar,
    Tbool,
    Tstring,
    Tvoid
} Tipo_t;

typedef enum {
    Iadd,
    IaddI,
    Inop,
    IloadI,
    Iload,
    Imult,
    ImultI,
    Idiv,
    IdivI,
    Iand,
    IandI,
    Isub,
    IsubI,
    Ilshift,
    IlshiftI,
    Irshift,
    IrshiftI,
    Ior,
    IorI,
    Ixor,
    IxorI,
    Istore,
    IstoreA,
    IstoreAI,
    IstoreA0,
    IloadA,
    IloadA0,
    IloadAI,
    IcmpLt,
    IcmpLe,
    IcmpEq,
    IcmpGe,
    IcmpGt,
    IcmpNe,
    Icbr,
    Ilabel,
    IjumpI,
    Iliteral,
    Iwhile,
}IlocOperations_t;

typedef struct ValorLexico_t {
    int numeroLinha;
    Tipo_t tipo;
    bool isVector;
    bool isLiteral;
    char *stringValue;
    bool boolValue;
    bool isLocal;
    char charValue;
    int intValue;
    float floatValue;
    int memoryDeloc;


} ValorLexico_t;




/*
Struct utilizada junto com a biblioteca uthash.h para poder utilizar os filhos como hash
*/
typedef struct NodoList_t{
    struct NodoArvore_t *nodo;
    struct NodoList_t* next;
} NodoList_t;





/*
 Struct Utilizada para a Arvore

*/
typedef struct NodoArvore_t{
    int childrenNumber;
    ValorLexico_t valorLexico;
    Tipo_t tipo;
    IlocOperations_t operation;
    NodoList_t *children;
} NodoArvore_t;



typedef enum {
    Rdefault,
    Rfp,
    Rbss,
} RegisterType_t;



typedef struct ArgsList_t{
    struct ValorSemantico_t *arg;
    struct ArgsList_t* next;
} ArgsList_t;

typedef struct OpData_t{
    IlocOperations_t operation;
    int registerNumberArg1;
    int registerNumberArg2;
    int registerNumberArg3;
    RegisterType_t registerType;
} OpData_t;

typedef struct OpDataList_t{
    struct OpData_t *arg;
    struct OpDataList_t* next;
} OpDataList_t;

typedef struct ComandsList_t{
    struct OpDataList_t* arg;
    struct ComandsList_t* next;
}ComandsList_t;

typedef struct ValorSemantico_t {
    int numeroLinha;
    Tipo_t tipo;
    bool isFunction;
    int nature;
    int size;
    char* name;
    int memoryDeloc;
    ArgsList_t* args;
    ValorLexico_t valorLexico;

} ValorSemantico_t;


typedef struct MyHash_t{
    char* identificador;
    ValorSemantico_t* valorSemantico;
    UT_hash_handle hh;

} MyHash_t;

typedef struct HashTree_t{
    MyHash_t* current;
    ValorSemantico_t* hashCreator;
    int memoryDeloc;
    struct HashTree_t* parent;
} HashTree_t;

typedef struct HashStack_t{
    struct HashTree_t *hash;
    struct HashStack_t* next;
} HashStack_t;



void printNodo(NodoArvore_t* nodo);
NodoArvore_t* criaNodo();
NodoArvore_t* addChildren(NodoArvore_t* parent,NodoArvore_t* child);
bool deletaNodo(NodoArvore_t* nodo);
void saveNodo(NodoArvore_t* nodo, FILE* file);
NodoArvore_t* criaNodoValorLexico( ValorLexico_t valor_lexico);
ValorLexico_t criaValorLexicoOP(char* valor);
void liberaValorLexico(ValorLexico_t valor);
void freeLista(NodoList_t* lista);

extern void libera(void *tree);
extern void exporta(void *tree);
void saveLonelyNodo(NodoArvore_t* nodo, FILE* file);

//Semantica

ValorSemantico_t* findSemanticValue( HashTree_t* hashT, char* key);
HashTree_t* createHash(HashTree_t* parent, ValorSemantico_t* hashCreator);
void deleteHash(HashTree_t* hashT);
MyHash_t* addToHash(HashTree_t* hashT, ValorSemantico_t* valorSemantico, char* identificador);
HashTree_t* getCurrentHash();
void addHashToList(HashTree_t* hashT);
ValorSemantico_t* createSemanticValueFromLexical(ValorLexico_t valorLexico, int nature);
void printHash(HashTree_t* HashT);
void dumpHashes();
void createArgsSemantics(ValorSemantico_t* func, NodoArvore_t* args);
ValorSemantico_t* checkIdentifierDeclared(HashTree_t* hashT, char* identificador);
Tipo_t typeInfer(Tipo_t tipoA, Tipo_t tipoB);
void getNameFromAddress(ValorSemantico_t* valorSemantico);
Tipo_t getParentFunctionType(HashTree_t* hashT);
bool verifyArgs(ArgsList_t* expected, NodoArvore_t* received);
bool canConvertType(Tipo_t expected, Tipo_t received);
void convertNodeBoolToInt(NodoArvore_t* nodo);
ValorSemantico_t* checkIdentifierDeclaredCurrentScope(HashTree_t* hashT, char* identificador);
ValorSemantico_t* findSemanticValueCurrentScope(HashTree_t* hashT, char* key);


//iloc

OpData_t* nodeToIloc(NodoArvore_t* node, int registerNumber, ComandsList_t* head);

void translateIloc();
void dumpAllInterface();