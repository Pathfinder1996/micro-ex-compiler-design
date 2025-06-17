/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "microex.y"

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

#line 182 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NAME = 258,                    /* NAME  */
    INT_NUMBER = 259,              /* INT_NUMBER  */
    FLOAT_NUMBER = 260,            /* FLOAT_NUMBER  */
    PROGRAM = 261,                 /* PROGRAM  */
    Begin = 262,                   /* Begin  */
    END = 263,                     /* END  */
    DECLARE = 264,                 /* DECLARE  */
    AS = 265,                      /* AS  */
    INTEGER = 266,                 /* INTEGER  */
    FLOAT = 267,                   /* FLOAT  */
    ASSIGN = 268,                  /* ASSIGN  */
    IF = 269,                      /* IF  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    ENDIF = 272,                   /* ENDIF  */
    GEQ = 273,                     /* GEQ  */
    LEQ = 274,                     /* LEQ  */
    EQ = 275,                      /* EQ  */
    NEQ = 276,                     /* NEQ  */
    GT = 277,                      /* GT  */
    LT = 278,                      /* LT  */
    FOR = 279,                     /* FOR  */
    TO = 280,                      /* TO  */
    DOWNTO = 281,                  /* DOWNTO  */
    ENDFOR = 282,                  /* ENDFOR  */
    WHILE = 283,                   /* WHILE  */
    ENDWHILE = 284,                /* ENDWHILE  */
    UMINUS = 285                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NAME 258
#define INT_NUMBER 259
#define FLOAT_NUMBER 260
#define PROGRAM 261
#define Begin 262
#define END 263
#define DECLARE 264
#define AS 265
#define INTEGER 266
#define FLOAT 267
#define ASSIGN 268
#define IF 269
#define THEN 270
#define ELSE 271
#define ENDIF 272
#define GEQ 273
#define LEQ 274
#define EQ 275
#define NEQ 276
#define GT 277
#define LT 278
#define FOR 279
#define TO 280
#define DOWNTO 281
#define ENDFOR 282
#define WHILE 283
#define ENDWHILE 284
#define UMINUS 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 113 "microex.y"

    int int_val;
    float float_val;
    struct symtab *symp;
    expression_attribute *attr;
    int comp_op;
    char *str;

#line 304 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NAME = 3,                       /* NAME  */
  YYSYMBOL_INT_NUMBER = 4,                 /* INT_NUMBER  */
  YYSYMBOL_FLOAT_NUMBER = 5,               /* FLOAT_NUMBER  */
  YYSYMBOL_PROGRAM = 6,                    /* PROGRAM  */
  YYSYMBOL_Begin = 7,                      /* Begin  */
  YYSYMBOL_END = 8,                        /* END  */
  YYSYMBOL_DECLARE = 9,                    /* DECLARE  */
  YYSYMBOL_AS = 10,                        /* AS  */
  YYSYMBOL_INTEGER = 11,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 12,                     /* FLOAT  */
  YYSYMBOL_ASSIGN = 13,                    /* ASSIGN  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_ENDIF = 17,                     /* ENDIF  */
  YYSYMBOL_GEQ = 18,                       /* GEQ  */
  YYSYMBOL_LEQ = 19,                       /* LEQ  */
  YYSYMBOL_EQ = 20,                        /* EQ  */
  YYSYMBOL_NEQ = 21,                       /* NEQ  */
  YYSYMBOL_GT = 22,                        /* GT  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_TO = 25,                        /* TO  */
  YYSYMBOL_DOWNTO = 26,                    /* DOWNTO  */
  YYSYMBOL_ENDFOR = 27,                    /* ENDFOR  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_ENDWHILE = 29,                  /* ENDWHILE  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_UMINUS = 34,                    /* UMINUS  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* '['  */
  YYSYMBOL_38_ = 38,                       /* ']'  */
  YYSYMBOL_39_ = 39,                       /* '('  */
  YYSYMBOL_40_ = 40,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_prog = 42,                      /* prog  */
  YYSYMBOL_43_1 = 43,                      /* $@1  */
  YYSYMBOL_statement_list = 44,            /* statement_list  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_vardecl = 46,                   /* vardecl  */
  YYSYMBOL_varlist = 47,                   /* varlist  */
  YYSYMBOL_var = 48,                       /* var  */
  YYSYMBOL_vartype = 49,                   /* vartype  */
  YYSYMBOL_function_call = 50,             /* function_call  */
  YYSYMBOL_parameter_list = 51,            /* parameter_list  */
  YYSYMBOL_parameter = 52,                 /* parameter  */
  YYSYMBOL_comp_op = 53,                   /* comp_op  */
  YYSYMBOL_if_statement = 54,              /* if_statement  */
  YYSYMBOL_55_2 = 55,                      /* $@2  */
  YYSYMBOL_56_3 = 56,                      /* $@3  */
  YYSYMBOL_direction = 57,                 /* direction  */
  YYSYMBOL_for_statement = 58,             /* for_statement  */
  YYSYMBOL_59_4 = 59,                      /* $@4  */
  YYSYMBOL_while_statement = 60,           /* while_statement  */
  YYSYMBOL_61_5 = 61,                      /* $@5  */
  YYSYMBOL_expression = 62                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   180

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  105

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,    32,    30,    36,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   148,   158,   159,   163,   164,   202,   203,
     204,   205,   206,   211,   242,   243,   248,   262,   281,   290,
     291,   295,   301,   305,   309,   314,   323,   324,   325,   326,
     327,   328,   333,   363,   333,   375,   376,   380,   380,   409,
     409,   450,   454,   460,   466,   479,   501,   515,   535,   555,
     575
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "INT_NUMBER",
  "FLOAT_NUMBER", "PROGRAM", "Begin", "END", "DECLARE", "AS", "INTEGER",
  "FLOAT", "ASSIGN", "IF", "THEN", "ELSE", "ENDIF", "GEQ", "LEQ", "EQ",
  "NEQ", "GT", "LT", "FOR", "TO", "DOWNTO", "ENDFOR", "WHILE", "ENDWHILE",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'", "','", "'['", "']'", "'('",
  "')'", "$accept", "prog", "$@1", "statement_list", "statement",
  "vardecl", "varlist", "var", "vartype", "function_call",
  "parameter_list", "parameter", "comp_op", "if_statement", "$@2", "$@3",
  "direction", "for_statement", "$@4", "while_statement", "$@5",
  "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,     9,    21,    23,   -80,   -80,   -80,    24,     3,   -80,
     -80,   -80,    32,     7,    11,    12,     0,     0,   -80,     6,
      18,   -80,   -80,   -80,   139,     0,     0,     0,    28,    -2,
     -80,     0,    64,     0,    33,   -80,    26,   -80,   -80,     0,
       0,     0,     0,   -80,   145,   101,    37,    42,   122,     2,
       8,    32,   126,    60,   126,   -80,     4,     4,   -80,   -80,
     -80,   -80,   -80,     0,    52,    55,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,     0,     0,     0,   122,
     -80,   -80,    51,   135,    73,    74,   -80,   -80,     0,   -80,
     -80,    97,   -80,   -80,   -80,    40,   112,   -80,   -80,    78,
      71,   -80,   -80,    83,   -80
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     4,     0,    44,    42,
      43,     3,     0,     0,     0,     0,     0,     0,     5,     0,
       0,    10,    11,    12,     0,     0,     0,    22,    16,     0,
      15,     0,     0,     0,    44,    46,     0,     6,     9,     0,
       0,     0,     0,     8,     0,     0,     0,    23,    24,     0,
       0,     0,     0,     0,     0,    41,    49,    50,    47,    48,
       7,    45,    21,     0,     0,     0,    19,    20,    13,    14,
      26,    27,    28,    29,    30,    31,     0,     0,     0,    25,
      17,    18,     0,     0,     0,     0,    35,    36,     0,    39,
      32,     0,     4,     4,    37,     0,    33,     4,    40,     0,
       0,     4,    38,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,   -80,   -79,   -80,   -80,   -80,    45,   -80,   -80,
     -80,   -80,    47,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     7,    18,    19,    29,    30,    68,    20,
      46,    47,    76,    21,    93,    99,    88,    22,    97,    23,
      92,    24
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      35,    36,     1,    34,     9,    10,    64,    65,    50,    44,
      45,    48,     3,    95,    96,    52,    25,    54,   100,    66,
      67,     4,   103,    56,    57,    58,    59,     8,     9,    10,
       5,    16,    11,    12,    51,    28,    41,    42,    13,    17,
      26,    37,    27,     8,     9,    10,    31,    79,    14,    12,
      32,    33,    15,    38,    13,    16,    39,    40,    41,    42,
      82,    83,    84,    17,    14,    49,    55,    53,    15,    98,
      26,    16,    91,    77,     8,     9,    10,    62,    63,    17,
      12,    39,    40,    41,    42,    13,     8,     9,    10,    90,
      80,    85,    12,    81,   101,    14,    69,    13,   102,    15,
     104,    78,    16,    39,    40,    41,    42,    14,     0,     0,
      17,    15,     0,    89,    16,     8,     9,    10,     0,     0,
       0,    12,    17,     0,     0,     0,    13,    39,    40,    41,
      42,    39,    40,    41,    42,     0,    14,    94,     0,    61,
      15,     0,     0,    16,    70,    71,    72,    73,    74,    75,
       0,    17,    39,    40,    41,    42,    39,    40,    41,    42,
      86,    87,     0,     0,     0,    39,    40,    41,    42,    39,
      40,    41,    42,     0,    43,    39,    40,    41,    42,     0,
      60
};

static const yytype_int8 yycheck[] =
{
      16,    17,     6,     3,     4,     5,     4,     5,    10,    25,
      26,    27,     3,    92,    93,    31,    13,    33,    97,    11,
      12,     0,   101,    39,    40,    41,    42,     3,     4,     5,
       7,    31,     8,     9,    36,     3,    32,    33,    14,    39,
      37,    35,    39,     3,     4,     5,    39,    63,    24,     9,
      39,    39,    28,    35,    14,    31,    30,    31,    32,    33,
      76,    77,    78,    39,    24,    37,    40,     3,    28,    29,
      37,    31,    88,    13,     3,     4,     5,    40,    36,    39,
       9,    30,    31,    32,    33,    14,     3,     4,     5,    15,
      38,    40,     9,    38,    16,    24,    51,    14,    27,    28,
      17,    54,    31,    30,    31,    32,    33,    24,    -1,    -1,
      39,    28,    -1,    40,    31,     3,     4,     5,    -1,    -1,
      -1,     9,    39,    -1,    -1,    -1,    14,    30,    31,    32,
      33,    30,    31,    32,    33,    -1,    24,    40,    -1,    38,
      28,    -1,    -1,    31,    18,    19,    20,    21,    22,    23,
      -1,    39,    30,    31,    32,    33,    30,    31,    32,    33,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    30,
      31,    32,    33,    -1,    35,    30,    31,    32,    33,    -1,
      35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    42,     3,     0,     7,    43,    44,     3,     4,
       5,     8,     9,    14,    24,    28,    31,    39,    45,    46,
      50,    54,    58,    60,    62,    13,    37,    39,     3,    47,
      48,    39,    39,    39,     3,    62,    62,    35,    35,    30,
      31,    32,    33,    35,    62,    62,    51,    52,    62,    37,
      10,    36,    62,     3,    62,    40,    62,    62,    62,    62,
      35,    38,    40,    36,     4,     5,    11,    12,    49,    48,
      18,    19,    20,    21,    22,    23,    53,    13,    53,    62,
      38,    38,    62,    62,    62,    40,    25,    26,    57,    40,
      15,    62,    61,    55,    40,    44,    44,    59,    29,    56,
      44,    16,    27,    44,    17
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    43,    42,    44,    44,    45,    45,    45,    45,
      45,    45,    45,    46,    47,    47,    48,    48,    48,    49,
      49,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    55,    56,    54,    57,    57,    59,    58,    61,
      60,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     2,     2,     4,     2,     2,
       1,     1,     1,     4,     3,     1,     1,     4,     4,     1,
       1,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     0,    13,     1,     1,     0,    11,     0,
       9,     3,     1,     1,     1,     4,     2,     3,     3,     3,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 148 "microex.y"
                       {
        program_name = strdup((yyvsp[-1].symp)->name);
        printf("      START %s\n", program_name);
    }
#line 1430 "y.tab.c"
    break;

  case 3: /* prog: PROGRAM NAME Begin $@1 statement_list END  */
#line 152 "microex.y"
                       {
        printf("      HALT %s\n", program_name);
        print_declare_temp();
    }
#line 1439 "y.tab.c"
    break;

  case 6: /* statement: vardecl ';'  */
#line 163 "microex.y"
                  { }
#line 1445 "y.tab.c"
    break;

  case 7: /* statement: NAME ASSIGN expression ';'  */
#line 164 "microex.y"
                                 {
        struct symtab *var = (yyvsp[-3].symp);
        expression_attribute *rhs = (yyvsp[-1].attr);

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
#line 1488 "y.tab.c"
    break;

  case 8: /* statement: expression ';'  */
#line 202 "microex.y"
                     { }
#line 1494 "y.tab.c"
    break;

  case 9: /* statement: function_call ';'  */
#line 203 "microex.y"
                        { }
#line 1500 "y.tab.c"
    break;

  case 10: /* statement: if_statement  */
#line 204 "microex.y"
                   { }
#line 1506 "y.tab.c"
    break;

  case 11: /* statement: for_statement  */
#line 205 "microex.y"
                    { }
#line 1512 "y.tab.c"
    break;

  case 12: /* statement: while_statement  */
#line 206 "microex.y"
                      { }
#line 1518 "y.tab.c"
    break;

  case 13: /* vardecl: DECLARE varlist AS vartype  */
#line 211 "microex.y"
                               {
        int i;
        for (i = 0; i < var_count; i++) {
            if (var_table[i]->check_is_declared) {
                char buf[100];
                sprintf(buf, "duplicate declaration of variable '%s'", var_table[i]->name);
                yyerror(buf); 
                exit(1);
            }
            var_table[i]->check_is_declared = 1; /* mark as declared */
            var_table[i]->type = (yyvsp[0].int_val);  /* $4 holds type int or float */
            if (var_table[i]->check_is_array) {
                /* print array declaration */
                printf("      Declare %s, %s_array, %d\n", 
                var_table[i]->name, 
                (yyvsp[0].int_val) == TYPE_INT ? "Integer" : "Float", 
                var_table[i]->array_size);
            } 
            else {
                /* print variable declaration */
                printf("      Declare %s, %s\n",
                    var_table[i]->name,
                    (yyvsp[0].int_val) == TYPE_INT ? "Integer" : "Float");
            }
        }
        var_count = 0;
    }
#line 1550 "y.tab.c"
    break;

  case 16: /* var: NAME  */
#line 248 "microex.y"
         {
        if ((yyvsp[0].symp)->check_is_declared) {
            char buf[128];
            sprintf(buf, "duplicate declaration of variable '%s'", (yyvsp[0].symp)->name);
            yyerror(buf); 
            exit(1);
        }
        if (var_count < NSYMS) {
            var_table[var_count] = (yyvsp[0].symp);
            var_table[var_count]->check_is_array = 0;
            var_table[var_count]->array_size = 0;
            var_count = var_count + 1;
        }
    }
#line 1569 "y.tab.c"
    break;

  case 17: /* var: NAME '[' INT_NUMBER ']'  */
#line 262 "microex.y"
                              {
        if ((yyvsp[-3].symp)->check_is_declared) {
            char buf[128];
            sprintf(buf, "duplicate declaration of variable '%s'", (yyvsp[-3].symp)->name);
            yyerror(buf); 
            exit(1);
        }
        if (var_count < NSYMS) {
            int size = (yyvsp[-1].int_val);
            if (size <= 0) {
                yyerror("array size must be positive integer");
                exit(1);
            }
            var_table[var_count] = (yyvsp[-3].symp);
            var_table[var_count]->check_is_array = 1;
            var_table[var_count]->array_size = size;
            var_count = var_count + 1;
        }
    }
#line 1593 "y.tab.c"
    break;

  case 18: /* var: NAME '[' FLOAT_NUMBER ']'  */
#line 281 "microex.y"
                                {
        /* reject float as array size */
        yyerror("array size must be positive integer not float");
        exit(1);
    }
#line 1603 "y.tab.c"
    break;

  case 19: /* vartype: INTEGER  */
#line 290 "microex.y"
            { (yyval.int_val) = TYPE_INT; }
#line 1609 "y.tab.c"
    break;

  case 20: /* vartype: FLOAT  */
#line 291 "microex.y"
              { (yyval.int_val) = TYPE_FLOAT; }
#line 1615 "y.tab.c"
    break;

  case 21: /* function_call: NAME '(' parameter_list ')'  */
#line 295 "microex.y"
                                {
        printf("      CALL %s%s\n", (yyvsp[-3].symp)->name, (yyvsp[-1].str));
        free((yyvsp[-1].str));
    }
#line 1624 "y.tab.c"
    break;

  case 22: /* parameter_list: %empty  */
#line 301 "microex.y"
    { 
        yyerror("function call requires parameters");
        exit(1);
    }
#line 1633 "y.tab.c"
    break;

  case 23: /* parameter_list: parameter  */
#line 305 "microex.y"
                { }
#line 1639 "y.tab.c"
    break;

  case 24: /* parameter: expression  */
#line 309 "microex.y"
               { 
        char buf[100];
        sprintf(buf, ", %s", (yyvsp[0].attr)->place);
        (yyval.str) = strdup(buf);
    }
#line 1649 "y.tab.c"
    break;

  case 25: /* parameter: parameter ',' expression  */
#line 314 "microex.y"
                               {
        char buf[100];
        sprintf(buf, "%s, %s", (yyvsp[-2].str), (yyvsp[0].attr)->place);
        free((yyvsp[-2].str));  /* free previous parameter list */
        (yyval.str) = strdup(buf);
    }
#line 1660 "y.tab.c"
    break;

  case 26: /* comp_op: GEQ  */
#line 323 "microex.y"
        { (yyval.comp_op) = GEQ; }
#line 1666 "y.tab.c"
    break;

  case 27: /* comp_op: LEQ  */
#line 324 "microex.y"
        { (yyval.comp_op) = LEQ; }
#line 1672 "y.tab.c"
    break;

  case 28: /* comp_op: EQ  */
#line 325 "microex.y"
        { (yyval.comp_op) = EQ; }
#line 1678 "y.tab.c"
    break;

  case 29: /* comp_op: NEQ  */
#line 326 "microex.y"
        { (yyval.comp_op) = NEQ; }
#line 1684 "y.tab.c"
    break;

  case 30: /* comp_op: GT  */
#line 327 "microex.y"
        { (yyval.comp_op) = GT; }
#line 1690 "y.tab.c"
    break;

  case 31: /* comp_op: LT  */
#line 328 "microex.y"
        { (yyval.comp_op) = LT; }
#line 1696 "y.tab.c"
    break;

  case 32: /* $@2: %empty  */
#line 333 "microex.y"
                                                  { 
        else_label = new_label();
        exit_label = new_label();

        printf("\n      %c_CMP %s, %s\n", 
        (yyvsp[-4].attr)->type == TYPE_INT ? 'I' : 'F', 
        (yyvsp[-4].attr)->place, 
        (yyvsp[-2].attr)->place);

        switch ((yyvsp[-3].comp_op)) {
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
#line 1731 "y.tab.c"
    break;

  case 33: /* $@3: %empty  */
#line 363 "microex.y"
                   {
        printf("      J %s\n", exit_label);
        printf("%s:\n", else_label);
    }
#line 1740 "y.tab.c"
    break;

  case 34: /* if_statement: IF '(' expression comp_op expression ')' THEN $@2 statement_list $@3 ELSE statement_list ENDIF  */
#line 369 "microex.y"
          {
        printf("%s:\n", exit_label);
    }
#line 1748 "y.tab.c"
    break;

  case 35: /* direction: TO  */
#line 375 "microex.y"
       { (yyval.int_val) = 0; }
#line 1754 "y.tab.c"
    break;

  case 36: /* direction: DOWNTO  */
#line 376 "microex.y"
              { (yyval.int_val) = 1; }
#line 1760 "y.tab.c"
    break;

  case 37: /* $@4: %empty  */
#line 380 "microex.y"
                                                            {
        if ((yyvsp[-5].symp)->type != TYPE_INT) {
            yyerror("for loop variable must be integer");
            exit(1);
        }

        printf("\n      I_STORE %s, %s\n", (yyvsp[-3].attr)->place, (yyvsp[-5].symp)->name);

        for_loop_label = new_label();
        printf("%s:\n", for_loop_label);

        for_loop_direction = (yyvsp[-2].int_val);
    }
#line 1778 "y.tab.c"
    break;

  case 38: /* for_statement: FOR '(' NAME ASSIGN expression direction expression ')' $@4 statement_list ENDFOR  */
#line 394 "microex.y"
           {
        if (for_loop_direction == 0) { /* TO */
            printf("      INC %s\n",  (yyvsp[-8].symp)->name);
            printf("      I_CMP %s, %s\n", (yyvsp[-8].symp)->name, (yyvsp[-4].attr)->place);
            printf("      JLE %s\n", for_loop_label);
        } 
        else { /* DOWNTO */
            printf("      DEC %s\n",  (yyvsp[-8].symp)->name);
            printf("      I_CMP %s, %s\n", (yyvsp[-8].symp)->name, (yyvsp[-4].attr)->place);
            printf("      JGE %s\n", for_loop_label);
        }
    }
#line 1795 "y.tab.c"
    break;

  case 39: /* $@5: %empty  */
#line 409 "microex.y"
                                                {
        while_head = new_label();
        while_exit = new_label();

        printf("\n%s:\n", while_head);

        printf("      %c_CMP %s, %s\n",
               (yyvsp[-3].attr)->type == TYPE_INT ? 'I' : 'F',
               (yyvsp[-3].attr)->place,
               (yyvsp[-1].attr)->place);

        switch ((yyvsp[-2].comp_op)) {
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
#line 1832 "y.tab.c"
    break;

  case 40: /* while_statement: WHILE '(' expression comp_op expression ')' $@5 statement_list ENDWHILE  */
#line 442 "microex.y"
             {
        printf("      J %s\n", while_head);
        printf("%s:\n", while_exit);
    }
#line 1841 "y.tab.c"
    break;

  case 41: /* expression: '(' expression ')'  */
#line 450 "microex.y"
                       {
        (yyval.attr) = (yyvsp[-1].attr);
    }
#line 1849 "y.tab.c"
    break;

  case 42: /* expression: INT_NUMBER  */
#line 454 "microex.y"
                 {
        char buf[100];
        snprintf(buf, sizeof(buf), "%d", (yyvsp[0].int_val));
        (yyval.attr) = make_attribute(strdup(buf), TYPE_INT);
    }
#line 1859 "y.tab.c"
    break;

  case 43: /* expression: FLOAT_NUMBER  */
#line 460 "microex.y"
                   {
        char buf[100];
        snprintf(buf, sizeof(buf), "%f", (yyvsp[0].float_val));
        (yyval.attr) = make_attribute(strdup(buf), TYPE_FLOAT);
    }
#line 1869 "y.tab.c"
    break;

  case 44: /* expression: NAME  */
#line 466 "microex.y"
            {
        struct symtab *var = (yyvsp[0].symp);
        if (var->type != TYPE_INT && var->type != TYPE_FLOAT) {
            char buf[100];
            snprintf(buf, sizeof(buf),
                     "undeclared variable '%s' in expression",
                     var->name);
            yyerror(buf);
            exit(1);
        }
        (yyval.attr) = make_attribute(strdup(var->name), var->type);
    }
#line 1886 "y.tab.c"
    break;

  case 45: /* expression: NAME '[' expression ']'  */
#line 479 "microex.y"
                              {
        struct symtab *v = (yyvsp[-3].symp);
        expression_attribute *idx = (yyvsp[-1].attr);
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
        (yyval.attr) = make_attribute(mem, v->type);
    }
#line 1912 "y.tab.c"
    break;

  case 46: /* expression: '-' expression  */
#line 501 "microex.y"
                                  {
        expression_attribute *e = (yyvsp[0].attr);
        if (e->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_UMINUS %s, %s\n", e->place, t);
            (yyval.attr) = make_attribute(t, TYPE_INT);
        } 
        else if (e->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_UMINUS %s, %s\n", e->place, t);
            (yyval.attr) = make_attribute(t, TYPE_FLOAT);
        }
    }
#line 1930 "y.tab.c"
    break;

  case 47: /* expression: expression '*' expression  */
#line 515 "microex.y"
                                {
        expression_attribute *l = (yyvsp[-2].attr);
        expression_attribute *r = (yyvsp[0].attr);
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_MUL %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_MUL %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in multiplication operation");
            char *td = new_temp();
            (yyval.attr) = make_attribute(td, TYPE_INT);
        }
    }
#line 1954 "y.tab.c"
    break;

  case 48: /* expression: expression '/' expression  */
#line 535 "microex.y"
                                {
        expression_attribute *l = (yyvsp[-2].attr);
        expression_attribute *r = (yyvsp[0].attr);
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_DIV %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_DIV %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in division operation");
            char *td = new_temp();
            (yyval.attr) = make_attribute(td, TYPE_INT);
        }
    }
#line 1978 "y.tab.c"
    break;

  case 49: /* expression: expression '+' expression  */
#line 555 "microex.y"
                                {
        expression_attribute *l = (yyvsp[-2].attr);
        expression_attribute *r = (yyvsp[0].attr);
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_ADD %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_ADD %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in addition operation");
            char *td = new_temp();
            (yyval.attr) = make_attribute(td, TYPE_INT);
        }
    }
#line 2002 "y.tab.c"
    break;

  case 50: /* expression: expression '-' expression  */
#line 575 "microex.y"
                                {
        expression_attribute *l = (yyvsp[-2].attr);
        expression_attribute *r = (yyvsp[0].attr);
        if (l->type == TYPE_INT && r->type == TYPE_INT) {
            char *t = new_temp();
            printf("      I_SUB %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_INT);
        } 
        else if (l->type == TYPE_FLOAT && r->type == TYPE_FLOAT) {
            char *t = new_temp();
            printf("      F_SUB %s, %s, %s\n", l->place, r->place, t);
            (yyval.attr) = make_attribute(t, TYPE_FLOAT);
        }
        else {
            yyerror("data type mismatch in subtraction operation");
            char *td = new_temp();
            (yyval.attr) = make_attribute(td, TYPE_INT);
        }
    }
#line 2026 "y.tab.c"
    break;


#line 2030 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 595 "microex.y"


int main(void) {
    yyparse();
    return 0;
}

