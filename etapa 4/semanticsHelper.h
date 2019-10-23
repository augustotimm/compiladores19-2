#include "uthash.h"
#include "utlist.h"
#include "helper.h"

typedef struct ArgsList_t{
    struct ValorSemantico_t *arg;
    struct ArgsList_t* next;
} ArgsList_t;



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
    struct ValorLexico_t valorLexico_t;


} ValorLexico_t;
