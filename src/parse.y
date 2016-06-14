/*
 * supoo2 parser
 */

%{
#define YYDEBUG 1
#define YYERROR_VERBOSE 1

#include "supoo.h"
%}

%union {
  node* nd;       // ノード
  node_string id; // 識別子、変数、ラベル
}

%type <nd> program stmts func pair list expr atom lit_num lit_str

%pure-parser
%parse-param {parser_state* p}
%lex-param   {p}

%{
int yylex(YYSTYPE* lval, parser_state* p);
static void yyerror(parser_state* p, const char *s);
%}

/*
 %defines
 %locations
 */

%token
  sym_begin
  sym_end

%token
  op_plus
  op_minus
  op_mult
  op_div

%token
  lit_num
  lit_str

%token
  func_echo
%%
program : term stmts term { $$ = $2; }
;
stmts : { $$ = NULL; }
     | stmts expr { $$ = $2; }
;
expr : pair
     | atom
;
pair : sym_begin func sym_end  { $$ = $2; }
;
func : list
     | op_plus  expr expr { $$ = new_node($2->val.d + $3->val.d); }
     | op_minus expr expr { $$ = new_node($2->val.d - $3->val.d); }
     | op_mult  expr expr { $$ = new_node($2->val.d * $3->val.d); }
     | op_div   expr expr { $$ = new_node($2->val.d / $3->val.d); }
     | func_echo expr     {
        if ($2->type == 0) {
          fprintf(stdout, "%lf\n", $2->val.d);
        }
        else if ($2->type == 1 ) {
          fprintf(stdout, "%s\n", $2->val.s);
        }
        else {
          fprintf(stdout, "nil\n");
        }
        // fflush(stdout);
        $$ = NULL;
      }
;
list :           { $$ = new_node(0.0); }
     | list expr { $$ = new_node(0.0); }
;
atom : lit_num
     | lit_str
;
term :
     | term '\n'
;
%%

#include "lex.yy.c"

int
main()
{
  parser_state p;
  p.lineno = 1;
  p.fname = "stdin";
  yyparse(&p);
  return 0;
}

static void
yyerror(parser_state* p, const char *s)
{
  p->nerr++;
  if (p->fname) {
    fprintf(stderr, "%s:%d:%s\n", p->fname, p->lineno, s);
  }
  else {
    fprintf(stderr, "%d:%s\n", p->lineno, s);
  }
}

