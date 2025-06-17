%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microex.h"

extern int token_line;
extern int token_col;

int yylex(void);

/* error report */
void yyerror(const char *s) {
    fprintf(stderr, "[Syntax error] line %d, %s\n", token_line, s);
}

/* symbol table storage */
struct symtab symtab[NSYMS];
struct symtab *var_table[NSYMS];
int var_count = 0;

/* lookup or insert symbol into table */
struct symtab *
symlook(char *s) {
    struct symtab *sp;
    for (sp = symtab; sp < &symtab[NSYMS]; sp++) {
        if (sp->name && !strcmp(sp->name, s)) {
            return sp;
        }
        if (!sp->name) {
            sp->name = strdup(s);
            sp->type = -1;
            sp->check_is_array = 0;
            sp->array_size = 0;
            sp->val.int_val = 0;
            return sp;
        }
    }
    yyerror("Too many symbols");
    exit(1);
}

/* temp register generation */
/* generate a new temporary register */
int temp_count = 0;
char *new_temp(void) {
    temp_count = temp_count + 1;
    char temp_name[100];
    snprintf(temp_name, sizeof(temp_name), "T&%d", temp_count);
    return strdup(temp_name);
}

/* record temporary variable information */
temp_information temp_pool[MAX_TEMP_SIZE];
int temp_pool_count = 0;
void record_temp(char *name, int temp) {
        int i;
        for(i = 0; i < temp_pool_count; i++)
        if(!strcmp(temp_pool[i].name, name)) {
            temp_pool[i].type = temp; 
            return; 
        }

    if (temp_pool_count < MAX_TEMP_SIZE) {
        temp_pool[temp_pool_count].name = strdup(name);
        temp_pool[temp_pool_count].type = temp;
        temp_pool_count = temp_pool_count + 1;
    }
}

/* create a new expression attribute */
expression_attribute *make_attribute(char *place, int type) {
    expression_attribute *e = malloc(sizeof(expression_attribute));
    e->place = place;
    e->type = type;

    if (place && place[0] == 'T' && place[1] == '&') {
        record_temp(place, type);
    }
    return e;
}

/* print all declared temporary variables */
void print_declare_temp(void) {
    putchar('\n');
    int i;
    for(i = 0; i < temp_pool_count; i++)
        printf("      Declare %s, %s\n", temp_pool[i].name, temp_pool[i].type == TYPE_INT ? "Integer" : "Float");
}

/* label generation */
int label_count = 0;
/* generate a new label */
char *new_label() {
    label_count = label_count + 1;
    char label_name[100];
    snprintf(label_name, sizeof(label_name), "lb&%d", label_count);
    return strdup(label_name);
}

/* global variables */
char *program_name = NULL; /* program name */
/* labels */
char *else_label = NULL;
char *exit_label = NULL;
char *for_loop_label = NULL;
int for_loop_direction = 0; /* 0 for TO, 1 for DOWNTO */
char *while_head = NULL;
char *while_exit = NULL;
%}

/* Union for semantic values */
%union {
    int int_val;
    float float_val;
    struct symtab *symp;
    expression_attribute *attr;
    int comp_op;
    char *str;
};

/* Token declarations */
%token <symp> NAME
%token <int_val> INT_NUMBER
%token <float_val> FLOAT_NUMBER

%token PROGRAM Begin END DECLARE AS INTEGER FLOAT ASSIGN
%token IF THEN ELSE ENDIF
%token GEQ LEQ EQ NEQ GT LT
%token FOR TO DOWNTO ENDFOR
%token WHILE ENDWHILE

/* Operator precedence */
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <attr> expression
%type <int_val> vartype
%type <comp_op> comp_op
%type <str> parameter_list parameter
%type <int_val> direction
%type <int_val> for_statement
%%

/* grammar rules */
prog:
    PROGRAM NAME Begin {
        program_name = strdup($2->name);
        printf("      START %s\n", program_name);
    }
    statement_list END {
        printf("      HALT %s\n", program_name);
        print_declare_temp();
    }
;

statement_list:
    | statement_list statement
;

statement:
      vardecl ';' { }
    | NAME ASSIGN expression ';' {
        struct symtab *var = $1;
        expression_attribute *rhs = $3;

        if (var->type != TYPE_INT && var->type != TYPE_FLOAT) {
            char buf[100];
            snprintf(buf, sizeof(buf),
                     "undeclared variable '%s' on left hand side",
                     var->name);
            yyerror(buf);
            exit(1);
        }

        if (var->type == TYPE_INT) {
            if (rhs->type == TYPE_INT) {
                /* store int result */
                printf("      I_STORE %s, %s\n", rhs->place, var->name);
            } 
            else {
                yyerror("assigning float to integer variable");
                exit(1);
            }
        } 
        else if (var->type == TYPE_FLOAT) {
            if (rhs->type == TYPE_FLOAT) {
                /* store float result */
                printf("      F_STORE %s, %s\n", rhs->place, var->name);
            } 
            else {
                yyerror("assigning integer to float variable");
                exit(1);
            }
        } 
        else {
            yyerror("assignment target not declared");
            exit(1);
        }
    }
    | expression ';' { }
    | function_call ';' { } 
    | if_statement { }
    | for_statement { }
    | while_statement { }
;

/* DECLARE varlist AS vartype */
vardecl:
    DECLARE varlist AS vartype {
        int i;
        for (i = 0; i < var_count; i++) {
            if (var_table[i]->check_is_declared) {
                char buf[100];
                sprintf(buf, "duplicate declaration of variable '%s'", var_table[i]->name);
                yyerror(buf); 
                exit(1);
            }
            var_table[i]->check_is_declared = 1; /* mark as declared */
            var_table[i]->type = $4;  /* $4 holds type int or float */
            if (var_table[i]->check_is_array) {
                /* print array declaration */
                printf("      Declare %s, %s_array, %d\n", 
                var_table[i]->name, 
                $4 == TYPE_INT ? "Integer" : "Float", 
                var_table[i]->array_size);
            } 
            else {
                /* print variable declaration */
                printf("      Declare %s, %s\n",
                    var_table[i]->name,
                    $4 == TYPE_INT ? "Integer" : "Float");
            }
        }
        var_count = 0;
    }
;

/* list of variables in declaration */
varlist:
    varlist ',' var
  | var
;

/* variable or array with integer size only */
var:
    NAME {
        if ($1->check_is_declared) {
            char buf[128];
            sprintf(buf, "duplicate declaration of variable '%s'", $1->name);
            yyerror(buf); 
            exit(1);
        }
        if (var_count < NSYMS) {
            var_table[var_count] = $1;
            var_table[var_count]->check_is_array = 0;
            var_table[var_count]->array_size = 0;
            var_count = var_count + 1;
        }
    }
    | NAME '[' INT_NUMBER ']' {
        if ($1->check_is_declared) {
            char buf[128];
            sprintf(buf, "duplicate declaration of variable '%s'", $1->name);
            yyerror(buf); 
            exit(1);
        }
        if (var_count < NSYMS) {
            int size = $3;
            if (size <= 0) {
                yyerror("array size must be positive integer");
                exit(1);
            }
            var_table[var_count] = $1;
            var_table[var_count]->check_is_array = 1;
            var_table[var_count]->array_size = size;
            var_count = var_count + 1;
        }
    }
    | NAME '[' FLOAT_NUMBER ']' {
        /* reject float as array size */
        yyerror("array size must be positive integer not float");
        exit(1);
    }
;

/* vartype: INTEGER or FLOAT */
vartype:
    INTEGER { $$ = TYPE_INT; }
    | FLOAT   { $$ = TYPE_FLOAT; }
;

function_call:
    NAME '(' parameter_list ')' {
        printf("      CALL %s%s\n", $1->name, $3);
        free($3);
    }

parameter_list:
    { 
        yyerror("function call requires parameters");
        exit(1);
    }
    | parameter { }
;

parameter:
    expression { 
        char buf[100];
        sprintf(buf, ", %s", $1->place);
        $$ = strdup(buf);
    }
    | parameter ',' expression {
        char buf[100];
        sprintf(buf, "%s, %s", $1, $3->place);
        free($1);  /* free previous parameter list */
        $$ = strdup(buf);
    }
;

comp_op: 
    GEQ { $$ = GEQ; }
  | LEQ { $$ = LEQ; }
  | EQ  { $$ = EQ; }
  | NEQ { $$ = NEQ; }
  | GT  { $$ = GT; }
  | LT  { $$ = LT; }
;


if_statement:
    IF '(' expression comp_op expression ')' THEN { 
        else_label = new_label();
        exit_label = new_label();

        printf("\n      %c_CMP %s, %s\n", 
        $3->type == TYPE_INT ? 'I' : 'F', 
        $3->place, 
        $5->place);

        switch ($4) {
        case GEQ:
            printf("      JL %s\n", else_label);
            break;
        case LEQ:
            printf("      JG %s\n", else_label);
            break;
        case EQ:
            printf("      JNE %10s\n", else_label);
            break;
        case NEQ:
            printf("      JE %s\n", else_label);
            break;
        case GT:
            printf("      JLE %s\n", else_label);
            break;
        case LT:
            printf("      JGE %s\n", else_label);
            break;
        }
    }
    statement_list {
        printf("      J %s\n", exit_label);
        printf("%s:\n", else_label);
    }
    ELSE
    statement_list
    ENDIF {
        printf("%s:\n", exit_label);
    }
;

direction: 
    TO { $$ = 0; }
    | DOWNTO  { $$ = 1; }
;

for_statement:
    FOR '(' NAME ASSIGN expression direction expression ')' {
        if ($3->type != TYPE_INT) {
            yyerror("for loop variable must be integer");
            exit(1);
        }

        printf("\n      I_STORE %s, %s\n", $5->place, $3->name);

        for_loop_label = new_label();
        printf("%s:\n", for_loop_label);

        for_loop_direction = $6;
    }
    statement_list
    ENDFOR {
        if (for_loop_direction == 0) { /* TO */
            printf("      INC %s\n",  $3->name);
            printf("      I_CMP %s, %s\n", $3->name, $7->place);
            printf("      JLE %s\n", for_loop_label);
        } 
        else { /* DOWNTO */
            printf("      DEC %s\n",  $3->name);
            printf("      I_CMP %s, %s\n", $3->name, $7->place);
            printf("      JGE %s\n", for_loop_label);
        }
    }
;

while_statement:
    WHILE '(' expression comp_op expression ')' {
        while_head = new_label();
        while_exit = new_label();

        printf("\n%s:\n", while_head);

        printf("      %c_CMP %s, %s\n",
               $3->type == TYPE_INT ? 'I' : 'F',
               $3->place,
               $5->place);

        switch ($4) {
        case GEQ:
            printf("      JL %s\n", while_exit);
            break;
        case LEQ:
            printf("      JG %s\n", while_exit);
            break;
        case EQ:
            printf("      JNE %s\n", while_exit);
            break;
        case NEQ:
            printf("      JE %s\n", while_exit);
            break;
        case GT:
            printf("      JLE %s\n", while_exit);
            break;
        case LT:
            printf("      JGE %s\n", while_exit);
            break;
        }
    }
    statement_list
    ENDWHILE {
        printf("      J %s\n", while_head);
        printf("%s:\n", while_exit);
    }
;

/* expression grammar with same type only */
expression:
    '(' expression ')' {
        $$ = $2;
    }
    /* INT literal */
    | INT_NUMBER {
        char buf[100];
        snprintf(buf, sizeof(buf), "%d", $1);
        $$ = make_attribute(strdup(buf), TYPE_INT);
    }
    /* FLOAT literal */
    | FLOAT_NUMBER {
        char buf[100];
        snprintf(buf, sizeof(buf), "%f", $1);
        $$ = make_attribute(strdup(buf), TYPE_FLOAT);
    }
    /* Variable reference */
    | NAME  {
        struct symtab *var = $1;
        if (var->type != TYPE_INT && var->type != TYPE_FLOAT) {
            char buf[100];
            snprintf(buf, sizeof(buf),
                     "undeclared variable '%s' in expression",
                     var->name);
            yyerror(buf);
            exit(1);
        }
        $$ = make_attribute(strdup(var->name), var->type);
    }
    /* array access */
    | NAME '[' expression ']' {
        struct symtab *v = $1;
        expression_attribute *idx = $3;
        if (v->type != TYPE_INT && v->type != TYPE_FLOAT) {
            char buf[100];
            snprintf(buf, sizeof(buf),
                     "undeclared array variable '%s' in expression",
                     v->name);
            yyerror(buf);
            exit(1);
        }
        if (!v->check_is_array) {
            yyerror("variable is not an array");
            exit(1);
        }

        int n = strlen(v->name) + strlen(idx->place) + 3;
        char *mem = malloc(n);
        snprintf(mem, n, "%s[%s]", v->name, idx->place);
        $$ = make_attribute(mem, v->type);
    }
    /* UMINUS */
    | '-' expression %prec UMINUS {
        expression_attribute *e = $2;
        if (e->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_UMINUS %s, %s\n", e->place, t);
            $$ = make_attribute(t, TYPE_INT);
        } 
        else if (e->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_UMINUS %s, %s\n", e->place, t);
            $$ = make_attribute(t, TYPE_FLOAT);
        }
    }
    /* MUL */
    | expression '*' expression {
        expression_attribute *l = $1;
        expression_attribute *r = $3;
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_MUL %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_MUL %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in multiplication operation");
            char *td = new_temp();
            $$ = make_attribute(td, TYPE_INT);
        }
    }
    /* DIV */
    | expression '/' expression {
        expression_attribute *l = $1;
        expression_attribute *r = $3;
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_DIV %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_DIV %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in division operation");
            char *td = new_temp();
            $$ = make_attribute(td, TYPE_INT);
        }
    }
    /* ADD */
    | expression '+' expression {
        expression_attribute *l = $1;
        expression_attribute *r = $3;
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_ADD %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_ADD %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in addition operation");
            char *td = new_temp();
            $$ = make_attribute(td, TYPE_INT);
        }
    }
    /* SUB */
    | expression '-' expression {
        expression_attribute *l = $1;
        expression_attribute *r = $3;
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_SUB %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_SUB %s, %s, %s\n", l->place, r->place, t);
            $$ = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in subtraction operation");
            char *td = new_temp();
            $$ = make_attribute(td, TYPE_INT);
        }
    }
;
%%

int main(void) {
    yyparse();
    return 0;
}

