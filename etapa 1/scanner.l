%{
  // Definitions
#include "tokens.h"
int lineNumber=1;
int get_line_number();
%}

%%
"int" {return TK_PR_INT;}

. {return TOKEN_ERRO; }
%%

int get_line_number() { return lineNumber; }
