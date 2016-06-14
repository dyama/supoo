/*
 * supoo2 lexer
 */

%{
#include "supoo.h"

#define YY_DECL int yylex(YYSTYPE *lval, parser_state* p)

static int
lex_return(parser_state* p, int c)
{
  p->lineno = p->tline;
  p->tline = yylineno;
  return c;
}

#define LEX_RETURN(c) return lex_return(p, c);
%}

%option noyywrap
%option yylineno

%%
"+"  LEX_RETURN(op_plus);
"-"  LEX_RETURN(op_minus);
"*"  LEX_RETURN(op_mult);
"/"  LEX_RETURN(op_div);
"("  LEX_RETURN(sym_begin);
")"  LEX_RETURN(sym_end);

";"[^\n]*"\n" LEX_RETURN('\n');

(([1-9][0-9]*)|0) {
  lval->nd = new_node(atol(yytext));
  LEX_RETURN(lit_num);
};

(([1-9][0-9]*)|0)(\.[0-9][0-9]*)? {
  double temp;
  sscanf(yytext, "%lf", &temp);
  lval->nd = new_node(temp);
  LEX_RETURN(lit_num);
};

0x[0-9a-fA-F]+ {
  unsigned long temp;
  sscanf(yytext+2, "%lx", &temp);
  lval->nd = new_node(temp);
  LEX_RETURN(lit_num);
};

0o[0-7]+ {
  unsigned long temp;
  sscanf(yytext+2, "%lo", &temp);
  lval->nd = new_node(temp);
  LEX_RETURN(lit_num);
};

\"([^\\\"]|\\.)*\" {
  lval->nd = node_str_new(yytext+1, yyleng-2);
  LEX_RETURN(lit_str);
};

[ \t\n] ;

"echo" LEX_RETURN(func_echo);

[a-zA-Z_][a-zA-Z_0-9]* {
  lval->id = node_id_new(yytext, yyleng);
  LEX_RETURN(sym_id);
}

. {
  char c = yytext[0];
  fprintf(stderr, "%s:%d:lexical error", p->fname, yylineno);
  if ((c & 0x80) || !isprint(c)) {
    fprintf(stderr, "('\\%03o').\n", c);
  }
  else if (c == '\\') {
    fprintf(stderr, "('\\\\').\n");
  }
  else {
    fprintf(stderr, "('%c').\n", c);
  }
  exit(1);
};
%%
