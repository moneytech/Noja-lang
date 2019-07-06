

%{

  extern int yylex();
  extern int yyparse(AST_Node**);
  extern FILE *yyin;
  void yyerror(AST_Node **, const char *s);

  #ifdef YYDEBUG
  yydebug = 1;
  #endif
%}

%parse-param {AST_Node **root}

%token <value_i64> INT
%token <value_f64> FLOAT
%token <value_string> STRING
%token <label> LABEL
%token ADD
%token SUB
%token MUL
%token DIV
%token EQL
%token NQL
%token LSS
%token GRT
%token LEQ
%token GEQ
%token AND
%token OR
%token XOR
%token ASSIGN
%token BRK_OP
%token BRK_CL
%token R_ARROW
%token COMMA
%token BRK_C_OP
%token BRK_C_CL
%token SEMICOLON
%token IMPORT
%token FROM
%token AS
%token CLASS

%token NOT
%token FOR
%token WHILE
%token DO
%token IF
%token ELSE
%token PRINT
%token BREAK
%token CONTINUE
%token RETURN
%token BRK_S_OP
%token BRK_S_CL
%token DOT
%token DDOTS
%token FUNCTION
%token DOLLA
%token TRUE
%token FALSE
%token BREAKPOINT;

%union {
  i64 value_i64;
  f64 value_f64;
  char *value_string;
  char *label;

  AST_Node *node;
}

%expect 0
%locations
%define parse.trace
%debug

%type <node> statement class_decl class_decl_inner import exp func_decl label_list if_statement statements while_statement ifelse_statement exp_list dict dict_inner term exp_logical exp_relational exp_additive exp_multiplicative

%%

everything: statements {*root = $1;};

statements
    : /**/ { $$ = AST_Node_Block_create(0); }
    | statements statement { $$ = $1; AST_Node_append($$, $2); }
    ;


statement
    : exp                           SEMICOLON     { $$ = $1; }
    | PRINT BRK_OP exp_list BRK_CL  SEMICOLON     { $$ = AST_Node_Print_create($3); }
    | BREAK                         SEMICOLON     { $$ = AST_Node_create(NODE_BREAK); }
    | CONTINUE                      SEMICOLON     { $$ = AST_Node_create(NODE_CONTINUE); }
    | BREAKPOINT                    SEMICOLON     { $$ = AST_Node_create(NODE_BREAKPOINT); }
    | RETURN exp                    SEMICOLON     { $$ = AST_Node_Return_create($2); }
    | ifelse_statement                            { $$ = $1; }
    | while_statement                             { $$ = $1; }
    | func_decl                                   { $$ = $1; }
    | import SEMICOLON                            { $$ = $1; }
    | class_decl
    ;

class_decl_inner
  : /**/  { $$ = AST_Node_Block_create(0); }
  | class_decl_inner func_decl { $$ = $1; AST_Node_append($1, $2); }
  ;

class_decl
  : CLASS LABEL BRK_C_OP class_decl_inner BRK_C_CL { $$ = AST_Node_Class_create($2, $4); }
  ;

import
  : IMPORT STRING                       { $$ = AST_Node_import_create($2, 0);  }
  | IMPORT STRING AS LABEL              { $$ = AST_Node_import_create($2, $4); }
  | IMPORT STRING AS LABEL FROM STRING  { $$ = AST_Node_import_create($2, $4); }
  ;

label_list
  : LABEL {$$ = AST_Node_LabelList_create(); AST_Node_LabelList_append($$, $1); }
  | label_list COMMA LABEL { $$ = $1; AST_Node_LabelList_append($$, $3); }
  ;

func_decl
  : FUNCTION LABEL BRK_OP BRK_CL BRK_C_OP statements BRK_C_CL             {$$ = AST_Node_ObjectFunction_create($2, 0, $6);}
  | FUNCTION LABEL BRK_OP label_list BRK_CL BRK_C_OP statements BRK_C_CL  {$$ = AST_Node_ObjectFunction_create($2, $4, $7);}
  ;

term
  : INT                           { $$ = AST_Node_i64($1);}
  | FLOAT                         { $$ = AST_Node_f64($1);}
  | STRING                        { $$ = AST_Node_string($1);}
  | TRUE                          { $$ = AST_Node_true();}
  | FALSE                         { $$ = AST_Node_false();}
  | BRK_S_OP BRK_S_CL             { $$ = AST_Node_array(0); }
  | BRK_S_OP exp_list BRK_S_CL    { $$ = AST_Node_array($2); }
  | BRK_OP exp BRK_CL             { $$ = $2; }
  | term BRK_OP BRK_CL               {$$ = AST_Node_operator(EXP_CALL, $1, 0);}
  | term BRK_OP exp_list BRK_CL      {$$ = AST_Node_operator(EXP_CALL, $1, $3);}
  | dict                          { $$ = AST_Node_dict($1);}
  | LABEL                         {$$ = AST_Node_label($1);}
  | term DOT LABEL                {$$ = AST_Node_operator(EXP_SELECT_ATTR, $1, AST_Node_label($3));}
  | term BRK_S_OP exp BRK_S_CL    {$$ = AST_Node_operator(EXP_SELECT, $1, $3);}
  ;

exp_multiplicative
  : term MUL term { $$ = AST_Node_operator(EXP_MUL, $1, $3); }
  | term DIV term { $$ = AST_Node_operator(EXP_DIV, $1, $3); }
  | term          { $$ = $1; }
  ;

exp_additive
  : exp_multiplicative ADD exp_multiplicative { $$ = AST_Node_operator(EXP_ADD, $1, $3); }
  | exp_multiplicative SUB exp_multiplicative { $$ = AST_Node_operator(EXP_SUB, $1, $3); }
  | exp_multiplicative { $$ = $1; }
  ;

exp_relational
  : exp_additive LSS exp_additive { $$ = AST_Node_operator(EXP_LSS, $1, $3); }
  | exp_additive GRT exp_additive { $$ = AST_Node_operator(EXP_GRT, $1, $3); }
  | exp_additive LEQ exp_additive { $$ = AST_Node_operator(EXP_LEQ, $1, $3); }
  | exp_additive GEQ exp_additive { $$ = AST_Node_operator(EXP_GEQ, $1, $3); }
  | exp_additive EQL exp_additive { $$ = AST_Node_operator(EXP_EQL, $1, $3); }
  | exp_additive NQL exp_additive { $$ = AST_Node_operator(EXP_NQL, $1, $3); }
  | exp_additive                  { $$ = $1; }
  ;

exp_logical
  : exp_relational AND exp_relational { $$ = AST_Node_operator(EXP_AND, $1, $3); }
  | exp_relational OR  exp_relational { $$ = AST_Node_operator(EXP_OR , $1, $3); }
  | exp_relational XOR exp_relational { $$ = AST_Node_operator(EXP_XOR, $1, $3); }
  | exp_relational                    { $$ = $1; }
  ;

exp
  : exp_logical ASSIGN exp_logical {

    if($1->flags & EXP_ASSIGNABLE) {
    } else {
      assert(0);
    }

    $$ = AST_Node_operator(EXP_ASSIGN , $1, $3);
  }
  | exp_logical                    { $$ = $1; }
  ;

dict_inner
  : STRING DDOTS exp                    {$$ = AST_Node_Dict_create(); AST_Node_Dict_append($$, $1, $3); }
  | LABEL DDOTS exp                     {$$ = AST_Node_Dict_create(); AST_Node_Dict_append($$, $1, $3); }
  | dict_inner COMMA STRING DDOTS exp   {$$ = $1;                     AST_Node_Dict_append($$, $3, $5); }
  | dict_inner COMMA LABEL  DDOTS exp   {$$ = $1;                     AST_Node_Dict_append($$, $3, $5); }
  ;
dict
  : BRK_C_OP BRK_C_CL                   {$$ = AST_Node_Dict_create();}
  | BRK_C_OP dict_inner BRK_C_CL        {$$ = $2;}
  ;
exp_list
  : exp                                 {$$=AST_Node_ExpList_create();AST_Node_ExpList_append($$, $1);}
  | exp_list COMMA exp                  {$$= $1; AST_Node_ExpList_append($1, $3);}
  ;

ifelse_statement
    : if_statement ELSE BRK_C_OP statements BRK_C_CL { $$ = $1; AST_Node_If_append_else($$, $4); }
    /*| if_statement ELSE statement { $$ = $1; AST_Node_If_append_else($$, AST_Node_Block_create($3)); }*/
    | if_statement {$$ = $1;}
    ;

if_statement
    : IF exp BRK_C_OP statements BRK_C_CL { $$ = AST_Node_If_create($2, $4, 0); }
    /*| IF exp statement { $$ = AST_Node_If_create($2, AST_Node_Block_create($3), 0); }*/
    ;

while_statement
    : WHILE exp BRK_C_OP statements BRK_C_CL { $$ = AST_Node_While_create($2, $4); }
    ;

/* End */

%%

AST_Node *AST_Build(char *path) {
  // lex through the input:

  FILE *fp = fopen(path, "r");

  if(!fp){
    printf("No target '%s'.\n", path);
    return 0;
  }

  yyin = fp;

  yylineno = 1;

  AST_Node *root = 0;

  char n = yyparse(&root);

  fclose(fp);

  if(n) {
    return 0;
  }

  return root;
}

void yyerror(AST_Node **root, const char *s) {
  printf("Syntax error on line %d.\n", yylineno);
}
