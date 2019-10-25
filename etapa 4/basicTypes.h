#include <stdbool.h>


typedef enum {
    Tint,
    Tfloat,
    Tchar,
    Tbool,
    Tstring,
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


typedef struct ArgsList_t{
    struct ValorSemantico_t *arg;
    struct ArgsList_t* next;
} ArgsList_t;

typedef enum {
    Nliteral,
    Nvar,
    Nfunc,
} Nature_s;



typedef struct ValorSemantico_t {
    int numeroLinha;
    Tipo_t tipo;
    Nature_s nature;
    int size;
    ArgsList_t* args;
    ValorLexico_t valorLexico_t;


} ValorSemantico_t;