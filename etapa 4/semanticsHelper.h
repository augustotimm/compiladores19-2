#include "uthash.h"
#include "utlist.h"
#include "helper.h"



typedef enum {
    Tint,
    Tfloat,
    Tchar,
    Tbool,
    Tstring,
} Tipo_s;

typedef enum {
    Nliteral,
    Nvar,
    Nfunc,
} Nature_s;

typedef struct ValorSemantico_t {
    int numeroLinha;
    Tipo_s tipo;
    Nature_s nature;
    int size;
    ArgsList_t* args;
    ValorLexico_t valorLexico_t;


} ValorSemantico_t;

typedef struct ArgsList_t{
    struct ValorSemantico_t *arg;
    struct ArgsList_t* next;
} ArgsList_t;


typedef struct MyHash_t{
    const char* identificador;
    ValorSemantico_t* valorSemantico;
    UT_hash_handle hh;

} MyHash_t;

typedef struct HashTree_t{
    MyHash_t* current;
    MyHash_t* parent;
} HashTree_t;

ValorSemantico_t* findSemanticValue( HashTree_t* hashT, char* key);
HashTree_t* createHash(HashTree_t* parent);
void deleteHash(HashTree_t* hashT);
MyHash_t* addToHash(HashTree_t* hashT, ValorSemantico_t* valorSemantico);