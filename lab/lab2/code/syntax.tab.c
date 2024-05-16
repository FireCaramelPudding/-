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
#line 1 "syntax.y"

    #include <stdio.h>
    #include "tree.h"
    #include "lex.yy.c"
    extern int yylineno;
    extern char* yytext;
    int yyerr_line=0;
    int yylex();
    void yyerror(char* s);
    node* root;
    int error2 = 0;
    extern int error1;

#line 85 "syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_DOT = 8,                        /* DOT  */
  YYSYMBOL_SEMI = 9,                       /* SEMI  */
  YYSYMBOL_RELOP = 10,                     /* RELOP  */
  YYSYMBOL_ASSIGNOP = 11,                  /* ASSIGNOP  */
  YYSYMBOL_PLUS = 12,                      /* PLUS  */
  YYSYMBOL_MINUS = 13,                     /* MINUS  */
  YYSYMBOL_STAR = 14,                      /* STAR  */
  YYSYMBOL_DIV = 15,                       /* DIV  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_LB = 21,                        /* LB  */
  YYSYMBOL_RB = 22,                        /* RB  */
  YYSYMBOL_LC = 23,                        /* LC  */
  YYSYMBOL_RC = 24,                        /* RC  */
  YYSYMBOL_IF = 25,                        /* IF  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_WHILE = 27,                     /* WHILE  */
  YYSYMBOL_STRUCT = 28,                    /* STRUCT  */
  YYSYMBOL_RETURN = 29,                    /* RETURN  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Program = 32,                   /* Program  */
  YYSYMBOL_ExtDefList = 33,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 34,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 35,                /* ExtDecList  */
  YYSYMBOL_Specifier = 36,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 37,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 38,                    /* OptTag  */
  YYSYMBOL_Tag = 39,                       /* Tag  */
  YYSYMBOL_VarDec = 40,                    /* VarDec  */
  YYSYMBOL_FunDec = 41,                    /* FunDec  */
  YYSYMBOL_VarList = 42,                   /* VarList  */
  YYSYMBOL_ParamDec = 43,                  /* ParamDec  */
  YYSYMBOL_CompSt = 44,                    /* CompSt  */
  YYSYMBOL_StmtList = 45,                  /* StmtList  */
  YYSYMBOL_Stmt = 46,                      /* Stmt  */
  YYSYMBOL_DefList = 47,                   /* DefList  */
  YYSYMBOL_Def = 48,                       /* Def  */
  YYSYMBOL_DecList = 49,                   /* DecList  */
  YYSYMBOL_Dec = 50,                       /* Dec  */
  YYSYMBOL_Exp = 51,                       /* Exp  */
  YYSYMBOL_Args = 52                       /* Args  */
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
typedef yytype_uint8 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    91,    91,    93,    94,    96,    97,    98,    99,   100,
     101,   102,   103,   105,   106,   109,   110,   112,   113,   114,
     116,   117,   119,   122,   123,   124,   126,   127,   128,   130,
     131,   133,   136,   138,   139,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   155,   156,   158,
     159,   160,   162,   163,   165,   166,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   202,   203,
     204
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "TYPE", "COMMA", "DOT", "SEMI", "RELOP", "ASSIGNOP", "PLUS", "MINUS",
  "STAR", "DIV", "AND", "OR", "NOT", "LP", "RP", "LB", "RB", "LC", "RC",
  "IF", "ELSE", "WHILE", "STRUCT", "RETURN", "LOWER_THAN_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-45)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,    10,   -45,    12,    14,   -45,     9,   344,   -45,   -45,
      -1,   -45,   -45,     1,    16,   -45,   -45,   -45,    55,    53,
     -45,    31,    11,    38,    95,    52,    -1,    -1,   -45,   -45,
      49,     6,   -45,    85,    65,   -45,    82,   -45,     2,    58,
      91,   105,   -45,   -45,    80,   185,   196,   207,    98,   100,
     108,   -45,    77,    52,   155,   -45,     7,   -45,   -45,    85,
     102,   118,   -45,   117,   121,   -45,   108,   131,   -45,    85,
     -45,   -45,   174,   -45,   340,   -45,    99,   129,    72,   218,
     229,   379,   -45,   -45,   -45,   147,   -45,   240,   251,   262,
     273,   284,   295,   306,   317,   328,   134,   -45,   139,   -45,
      -1,   -45,   -45,   419,   -45,   -45,   122,   -45,   352,   142,
     -45,   -45,   -45,   153,   391,   154,   405,   -45,   -45,   -45,
     449,   -45,   419,   -45,   133,   -45,   340,   -45,   123,   -45,
      99,   -45,   439,   -45,   429,   158,   364,   -45,   -45,   108,
     -45,   339,   -45,   132,   132,   132,   132,   -45,   -45,   419,
     146,   -45,   156,   157,   -45,   -45,   132,   132,   -45,   -45
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    15,    21,     0,     2,     0,     0,    16,    10,
      48,    11,     9,    22,     0,    18,     1,     3,     0,     0,
       6,     0,    13,     0,     0,     0,    48,    48,     8,    12,
       0,     0,     5,     0,     0,     7,     0,    23,    54,     0,
      52,     0,    72,    73,    71,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,    47,     0,    28,    27,     0,
       0,    30,    14,     0,     0,    51,     0,     0,    49,     0,
      41,    42,     0,    84,    65,    85,    66,     0,     0,     0,
       0,     0,    32,    33,    43,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    31,    26,
       0,    25,    24,    55,    50,    53,     0,    68,    89,     0,
      82,    83,    64,     0,     0,     0,     0,    37,    70,    77,
      59,    74,    56,    78,    60,    79,    61,    80,    62,    81,
      63,    75,    57,    76,    58,     0,     0,    19,    29,     0,
      86,     0,    67,     0,     0,     0,     0,    87,    69,    90,
       0,    88,    44,    38,    46,    40,     0,     0,    45,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -45,   -45,   175,   183,   152,    -6,   -45,   -45,   -45,   -17,
     -45,    96,   -45,    40,   138,   -41,     3,   -45,   126,   -45,
     -44,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    21,     7,     8,    14,    15,    22,
      23,    60,    61,    51,    52,    53,    25,    26,    39,    40,
      54,   109
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    74,    76,    78,    24,     2,    81,    38,    96,    -4,
       1,     1,     2,    66,    16,     2,     2,    13,    33,     9,
      24,    24,   103,    34,   -20,    59,    58,     3,   108,    55,
      56,    97,    34,    10,     3,   114,   116,     3,     3,    27,
      32,    12,    98,   120,   122,   124,   126,   128,   130,   132,
     134,   136,    38,    41,    30,    42,    43,    44,    29,    67,
     -23,    10,   -23,    35,    28,    45,    63,    68,    64,    57,
      46,    47,    31,   111,   -23,    10,   -34,    48,    10,    49,
      85,    50,    87,    88,    89,    90,    91,    92,    93,    94,
      37,    65,   112,    95,    59,   149,    36,   108,    69,    72,
      37,    82,   152,   153,   154,   155,    41,    85,    42,    43,
      44,    42,    43,    44,    70,   158,   159,    79,    45,    80,
      95,    45,    99,    46,    47,   100,    46,    47,    10,   139,
      48,    85,    49,    41,    50,    42,    43,    44,    92,   101,
     104,    85,   140,   102,    95,    45,    90,    91,    92,   110,
      46,    47,   118,   139,    95,    10,    84,    48,   137,    49,
      34,    50,   142,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,   143,   145,   106,    95,    42,    43,    44,
     147,    17,   156,   157,    11,    62,    73,    45,    42,    43,
      44,    83,    46,    47,   107,   105,   138,    75,    45,    42,
      43,    44,   151,    46,    47,     0,     0,     0,    77,    45,
      42,    43,    44,     0,    46,    47,     0,     0,     0,   113,
      45,    42,    43,    44,     0,    46,    47,     0,     0,     0,
     115,    45,    42,    43,    44,     0,    46,    47,     0,     0,
       0,   119,    45,    42,    43,    44,     0,    46,    47,     0,
       0,     0,   121,    45,    42,    43,    44,     0,    46,    47,
       0,     0,     0,   123,    45,    42,    43,    44,     0,    46,
      47,     0,     0,     0,   125,    45,    42,    43,    44,     0,
      46,    47,     0,     0,     0,   127,    45,    42,    43,    44,
       0,    46,    47,     0,     0,     0,   129,    45,    42,    43,
      44,     0,    46,    47,     0,     0,     0,   131,    45,    42,
      43,    44,     0,    46,    47,     0,     0,     0,   133,    45,
      42,    43,    44,     0,    46,    47,     0,     0,     0,   135,
      45,    42,    43,    44,     0,    46,    47,     0,     0,     0,
     150,    45,    42,    43,    44,    18,    46,    47,    85,    19,
       0,     0,    45,    20,    91,    92,     0,    46,    47,   141,
      85,    95,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,    85,    95,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,    95,   148,    85,   117,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,    85,
      95,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,   144,    95,    85,     0,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,   146,    95,    85,     0,    87,
      88,    89,    90,    91,    92,    93,    94,    85,     0,    87,
      95,    89,    90,    91,    92,    93,     0,    85,     0,    87,
      95,    89,    90,    91,    92,     0,     0,    85,     0,     0,
      95,    89,    90,    91,    92,     0,     0,     0,     0,     0,
      95
};

static const yytype_int16 yycheck[] =
{
      41,    45,    46,    47,    10,     6,    50,    24,     1,     0,
       1,     1,     6,    11,     0,     6,     6,     5,     7,     9,
      26,    27,    66,    21,    23,    31,    20,    28,    72,    26,
      27,    24,    21,    23,    28,    79,    80,    28,    28,    23,
       9,     1,    59,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    69,     1,     1,     3,     4,     5,    18,     1,
       7,    23,     9,    23,     9,    13,     1,     9,     3,    20,
      18,    19,    19,     1,    21,    23,    24,    25,    23,    27,
       8,    29,    10,    11,    12,    13,    14,    15,    16,    17,
       5,     9,    20,    21,   100,   139,     1,   141,     7,    19,
       5,    24,   143,   144,   145,   146,     1,     8,     3,     4,
       5,     3,     4,     5,     9,   156,   157,    19,    13,    19,
      21,    13,    20,    18,    19,     7,    18,    19,    23,     7,
      25,     8,    27,     1,    29,     3,     4,     5,    15,    22,
       9,     8,    20,    22,    21,    13,    13,    14,    15,    20,
      18,    19,     5,     7,    21,    23,     1,    25,    24,    27,
      21,    29,    20,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    20,    20,     1,    21,     3,     4,     5,
      22,     6,    26,    26,     1,    33,     1,    13,     3,     4,
       5,    53,    18,    19,    20,    69,   100,     1,    13,     3,
       4,     5,   141,    18,    19,    -1,    -1,    -1,     1,    13,
       3,     4,     5,    -1,    18,    19,    -1,    -1,    -1,     1,
      13,     3,     4,     5,    -1,    18,    19,    -1,    -1,    -1,
       1,    13,     3,     4,     5,    -1,    18,    19,    -1,    -1,
      -1,     1,    13,     3,     4,     5,    -1,    18,    19,    -1,
      -1,    -1,     1,    13,     3,     4,     5,    -1,    18,    19,
      -1,    -1,    -1,     1,    13,     3,     4,     5,    -1,    18,
      19,    -1,    -1,    -1,     1,    13,     3,     4,     5,    -1,
      18,    19,    -1,    -1,    -1,     1,    13,     3,     4,     5,
      -1,    18,    19,    -1,    -1,    -1,     1,    13,     3,     4,
       5,    -1,    18,    19,    -1,    -1,    -1,     1,    13,     3,
       4,     5,    -1,    18,    19,    -1,    -1,    -1,     1,    13,
       3,     4,     5,    -1,    18,    19,    -1,    -1,    -1,     1,
      13,     3,     4,     5,    -1,    18,    19,    -1,    -1,    -1,
       1,    13,     3,     4,     5,     1,    18,    19,     8,     5,
      -1,    -1,    13,     9,    14,    15,    -1,    18,    19,     7,
       8,    21,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,     8,    21,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    21,    22,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,     8,
      21,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    20,    21,     8,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,     8,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,     8,    -1,    10,
      21,    12,    13,    14,    15,    16,    -1,     8,    -1,    10,
      21,    12,    13,    14,    15,    -1,    -1,     8,    -1,    -1,
      21,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,    28,    32,    33,    34,    36,    37,     9,
      23,    34,    44,     5,    38,    39,     0,    33,     1,     5,
       9,    35,    40,    41,    36,    47,    48,    23,     9,    44,
       1,    19,     9,     7,    21,    44,     1,     5,    40,    49,
      50,     1,     3,     4,     5,    13,    18,    19,    25,    27,
      29,    44,    45,    46,    51,    47,    47,    20,    20,    36,
      42,    43,    35,     1,     3,     9,    11,     1,     9,     7,
       9,    46,    19,     1,    51,     1,    51,     1,    51,    19,
      19,    51,    24,    45,     1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    21,     1,    24,    40,    20,
       7,    22,    22,    51,     9,    49,     1,    20,    51,    52,
      20,     1,    20,     1,    51,     1,    51,     9,     5,     1,
      51,     1,    51,     1,    51,     1,    51,     1,    51,     1,
      51,     1,    51,     1,    51,     1,    51,    24,    42,     7,
      20,     7,    20,    20,    20,    20,    20,    22,    22,    51,
       1,    52,    46,    46,    46,    46,    26,    26,    46,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    34,    34,    35,    35,    36,    36,    37,    37,    37,
      38,    38,    39,    40,    40,    40,    41,    41,    41,    42,
      42,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    52,
      52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       2,     2,     3,     1,     3,     1,     1,     5,     2,     6,
       1,     0,     1,     1,     4,     4,     4,     3,     3,     3,
       1,     2,     4,     2,     0,     2,     1,     3,     5,     7,
       5,     2,     2,     2,     5,     7,     5,     2,     0,     3,
       4,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     3,     4,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     4,     3,     1,
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 91 "syntax.y"
                        {(yyval.Node) = not_token_node("Program", (yyloc).first_line, 1, (yyvsp[0].Node));root = (yyval.Node);}
#line 1405 "syntax.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 93 "syntax.y"
                                {(yyval.Node) = not_token_node("ExtDefList", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1411 "syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 94 "syntax.y"
        {(yyval.Node)=NULL;/*空串将节点置空即可*/}
#line 1417 "syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 96 "syntax.y"
                                    {(yyval.Node) = not_token_node("ExtDef", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1423 "syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 97 "syntax.y"
                    {(yyval.Node) = not_token_node("ExtDef", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1429 "syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 98 "syntax.y"
                                {(yyval.Node) = not_token_node("ExtDef", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1435 "syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier error SEMI  */
#line 99 "syntax.y"
                           { yyerrok; }
#line 1441 "syntax.tab.c"
    break;

  case 9: /* ExtDef: error CompSt  */
#line 100 "syntax.y"
                   {/*错误的函数类型*/yyerrok; }
#line 1447 "syntax.tab.c"
    break;

  case 10: /* ExtDef: error SEMI  */
#line 101 "syntax.y"
                   {/*错误的类型*/yyerrok; }
#line 1453 "syntax.tab.c"
    break;

  case 11: /* ExtDef: error ExtDef  */
#line 102 "syntax.y"
                   {/*错误的类型定义*/}
#line 1459 "syntax.tab.c"
    break;

  case 12: /* ExtDef: Specifier error CompSt  */
#line 103 "syntax.y"
                               {/*错误的函数名*/yyerrok;}
#line 1465 "syntax.tab.c"
    break;

  case 13: /* ExtDecList: VarDec  */
#line 105 "syntax.y"
                    {(yyval.Node) = not_token_node("ExtDecList", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1471 "syntax.tab.c"
    break;

  case 14: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 106 "syntax.y"
                                {(yyval.Node) = not_token_node("ExtDecList", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1477 "syntax.tab.c"
    break;

  case 15: /* Specifier: TYPE  */
#line 109 "syntax.y"
                    {(yyval.Node) = not_token_node("Specifier", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1483 "syntax.tab.c"
    break;

  case 16: /* Specifier: StructSpecifier  */
#line 110 "syntax.y"
                        {(yyval.Node) = not_token_node("Specifier", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1489 "syntax.tab.c"
    break;

  case 17: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 112 "syntax.y"
                                                {(yyval.Node) = not_token_node("StructSpecifier", (yyloc).first_line, 5, (yyvsp[-4].Node), (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1495 "syntax.tab.c"
    break;

  case 18: /* StructSpecifier: STRUCT Tag  */
#line 113 "syntax.y"
                {(yyval.Node) = not_token_node("StructSpecifier", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1501 "syntax.tab.c"
    break;

  case 19: /* StructSpecifier: STRUCT OptTag LC DefList error RC  */
#line 114 "syntax.y"
                                                   {/*在右括号前添加error*/yyerrok;}
#line 1507 "syntax.tab.c"
    break;

  case 20: /* OptTag: ID  */
#line 116 "syntax.y"
            {(yyval.Node) = not_token_node("OptTag", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1513 "syntax.tab.c"
    break;

  case 21: /* OptTag: %empty  */
#line 117 "syntax.y"
        {(yyval.Node) = NULL;}
#line 1519 "syntax.tab.c"
    break;

  case 22: /* Tag: ID  */
#line 119 "syntax.y"
            {(yyval.Node) = not_token_node("Tag", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1525 "syntax.tab.c"
    break;

  case 23: /* VarDec: ID  */
#line 122 "syntax.y"
            {(yyval.Node) = not_token_node("VarDec", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1531 "syntax.tab.c"
    break;

  case 24: /* VarDec: VarDec LB INT RB  */
#line 123 "syntax.y"
                        {(yyval.Node) = not_token_node("VarDec", (yyloc).first_line, 4, (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1537 "syntax.tab.c"
    break;

  case 25: /* VarDec: VarDec LB error RB  */
#line 124 "syntax.y"
                        {/*在右括号前添加error*/yyerrok;}
#line 1543 "syntax.tab.c"
    break;

  case 26: /* FunDec: ID LP VarList RP  */
#line 126 "syntax.y"
                            {(yyval.Node) = not_token_node("FunDec", (yyloc).first_line, 4, (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1549 "syntax.tab.c"
    break;

  case 27: /* FunDec: ID LP RP  */
#line 127 "syntax.y"
                {(yyval.Node) = not_token_node("FunDec", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1555 "syntax.tab.c"
    break;

  case 28: /* FunDec: ID error RP  */
#line 128 "syntax.y"
                 {/*在右括号前添加error*/yyerrok;}
#line 1561 "syntax.tab.c"
    break;

  case 29: /* VarList: ParamDec COMMA VarList  */
#line 130 "syntax.y"
                                    {(yyval.Node) = not_token_node("VarList", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1567 "syntax.tab.c"
    break;

  case 30: /* VarList: ParamDec  */
#line 131 "syntax.y"
                {(yyval.Node) = not_token_node("VarList", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1573 "syntax.tab.c"
    break;

  case 31: /* ParamDec: Specifier VarDec  */
#line 133 "syntax.y"
                            {(yyval.Node) = not_token_node("ParamDec", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1579 "syntax.tab.c"
    break;

  case 32: /* CompSt: LC DefList StmtList RC  */
#line 136 "syntax.y"
                                {(yyval.Node) = not_token_node("CompSt", (yyloc).first_line, 4, (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1585 "syntax.tab.c"
    break;

  case 33: /* StmtList: Stmt StmtList  */
#line 138 "syntax.y"
                            {(yyval.Node) = not_token_node("StmtList", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1591 "syntax.tab.c"
    break;

  case 34: /* StmtList: %empty  */
#line 139 "syntax.y"
        {(yyval.Node) = NULL;}
#line 1597 "syntax.tab.c"
    break;

  case 35: /* Stmt: Exp SEMI  */
#line 141 "syntax.y"
                {(yyval.Node) = not_token_node("Stmt", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1603 "syntax.tab.c"
    break;

  case 36: /* Stmt: CompSt  */
#line 142 "syntax.y"
                {(yyval.Node) = not_token_node("Stmt", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1609 "syntax.tab.c"
    break;

  case 37: /* Stmt: RETURN Exp SEMI  */
#line 143 "syntax.y"
                        {(yyval.Node) = not_token_node("Stmt", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1615 "syntax.tab.c"
    break;

  case 38: /* Stmt: IF LP Exp RP Stmt  */
#line 144 "syntax.y"
                        {(yyval.Node) = not_token_node("Stmt", (yyloc).first_line, 5, (yyvsp[-4].Node), (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1621 "syntax.tab.c"
    break;

  case 39: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 145 "syntax.y"
                                    {(yyval.Node) = not_token_node("Stmt", (yyloc).first_line, 7, (yyvsp[-6].Node), (yyvsp[-5].Node), (yyvsp[-4].Node), (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1627 "syntax.tab.c"
    break;

  case 40: /* Stmt: WHILE LP Exp RP Stmt  */
#line 146 "syntax.y"
                            {(yyval.Node) = not_token_node("Stmt", (yyloc).first_line, 5, (yyvsp[-4].Node), (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1633 "syntax.tab.c"
    break;

  case 41: /* Stmt: error SEMI  */
#line 147 "syntax.y"
                    {yyerrok;}
#line 1639 "syntax.tab.c"
    break;

  case 42: /* Stmt: error Stmt  */
#line 148 "syntax.y"
                    {yyerrok;}
#line 1645 "syntax.tab.c"
    break;

  case 43: /* Stmt: Exp error  */
#line 149 "syntax.y"
                {}
#line 1651 "syntax.tab.c"
    break;

  case 44: /* Stmt: IF LP error RP Stmt  */
#line 150 "syntax.y"
                                                {}
#line 1657 "syntax.tab.c"
    break;

  case 45: /* Stmt: IF LP error RP Stmt ELSE Stmt  */
#line 151 "syntax.y"
                                    {}
#line 1663 "syntax.tab.c"
    break;

  case 46: /* Stmt: WHILE LP error RP Stmt  */
#line 152 "syntax.y"
                                {yyerrok;}
#line 1669 "syntax.tab.c"
    break;

  case 47: /* DefList: Def DefList  */
#line 155 "syntax.y"
                        {(yyval.Node) = not_token_node("DefList", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1675 "syntax.tab.c"
    break;

  case 48: /* DefList: %empty  */
#line 156 "syntax.y"
        {(yyval.Node) = NULL;}
#line 1681 "syntax.tab.c"
    break;

  case 49: /* Def: Specifier DecList SEMI  */
#line 158 "syntax.y"
                                {(yyval.Node) = not_token_node("Def", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1687 "syntax.tab.c"
    break;

  case 50: /* Def: Specifier DecList error SEMI  */
#line 159 "syntax.y"
                                    {yyerrok;}
#line 1693 "syntax.tab.c"
    break;

  case 51: /* Def: Specifier error SEMI  */
#line 160 "syntax.y"
                            {yyerrok;}
#line 1699 "syntax.tab.c"
    break;

  case 52: /* DecList: Dec  */
#line 162 "syntax.y"
                {(yyval.Node) = not_token_node("DecList", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1705 "syntax.tab.c"
    break;

  case 53: /* DecList: Dec COMMA DecList  */
#line 163 "syntax.y"
                        {(yyval.Node) = not_token_node("DecList", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1711 "syntax.tab.c"
    break;

  case 54: /* Dec: VarDec  */
#line 165 "syntax.y"
                {(yyval.Node) = not_token_node("Dec", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1717 "syntax.tab.c"
    break;

  case 55: /* Dec: VarDec ASSIGNOP Exp  */
#line 166 "syntax.y"
                            {(yyval.Node) = not_token_node("Dec", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1723 "syntax.tab.c"
    break;

  case 56: /* Exp: Exp ASSIGNOP Exp  */
#line 169 "syntax.y"
                        {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1729 "syntax.tab.c"
    break;

  case 57: /* Exp: Exp AND Exp  */
#line 170 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1735 "syntax.tab.c"
    break;

  case 58: /* Exp: Exp OR Exp  */
#line 171 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1741 "syntax.tab.c"
    break;

  case 59: /* Exp: Exp RELOP Exp  */
#line 172 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1747 "syntax.tab.c"
    break;

  case 60: /* Exp: Exp PLUS Exp  */
#line 173 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1753 "syntax.tab.c"
    break;

  case 61: /* Exp: Exp MINUS Exp  */
#line 174 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1759 "syntax.tab.c"
    break;

  case 62: /* Exp: Exp STAR Exp  */
#line 175 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1765 "syntax.tab.c"
    break;

  case 63: /* Exp: Exp DIV Exp  */
#line 176 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1771 "syntax.tab.c"
    break;

  case 64: /* Exp: LP Exp RP  */
#line 177 "syntax.y"
                {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1777 "syntax.tab.c"
    break;

  case 65: /* Exp: MINUS Exp  */
#line 178 "syntax.y"
                {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1783 "syntax.tab.c"
    break;

  case 66: /* Exp: NOT Exp  */
#line 179 "syntax.y"
                {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 2, (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1789 "syntax.tab.c"
    break;

  case 67: /* Exp: ID LP Args RP  */
#line 180 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 4, (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1795 "syntax.tab.c"
    break;

  case 68: /* Exp: ID LP RP  */
#line 181 "syntax.y"
                {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1801 "syntax.tab.c"
    break;

  case 69: /* Exp: Exp LB Exp RB  */
#line 182 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 4, (yyvsp[-3].Node), (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1807 "syntax.tab.c"
    break;

  case 70: /* Exp: Exp DOT ID  */
#line 183 "syntax.y"
                    {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1813 "syntax.tab.c"
    break;

  case 71: /* Exp: ID  */
#line 184 "syntax.y"
            {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1819 "syntax.tab.c"
    break;

  case 72: /* Exp: INT  */
#line 185 "syntax.y"
            {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1825 "syntax.tab.c"
    break;

  case 73: /* Exp: FLOAT  */
#line 186 "syntax.y"
            {(yyval.Node) = not_token_node("Exp", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1831 "syntax.tab.c"
    break;

  case 74: /* Exp: Exp ASSIGNOP error  */
#line 187 "syntax.y"
                            {}
#line 1837 "syntax.tab.c"
    break;

  case 75: /* Exp: Exp AND error  */
#line 188 "syntax.y"
                    {}
#line 1843 "syntax.tab.c"
    break;

  case 76: /* Exp: Exp OR error  */
#line 189 "syntax.y"
                    {}
#line 1849 "syntax.tab.c"
    break;

  case 77: /* Exp: Exp RELOP error  */
#line 190 "syntax.y"
                        {}
#line 1855 "syntax.tab.c"
    break;

  case 78: /* Exp: Exp PLUS error  */
#line 191 "syntax.y"
                        {}
#line 1861 "syntax.tab.c"
    break;

  case 79: /* Exp: Exp MINUS error  */
#line 192 "syntax.y"
                        {}
#line 1867 "syntax.tab.c"
    break;

  case 80: /* Exp: Exp STAR error  */
#line 193 "syntax.y"
                        {}
#line 1873 "syntax.tab.c"
    break;

  case 81: /* Exp: Exp DIV error  */
#line 194 "syntax.y"
                    {}
#line 1879 "syntax.tab.c"
    break;

  case 82: /* Exp: LP error RP  */
#line 195 "syntax.y"
                    {yyerrok;}
#line 1885 "syntax.tab.c"
    break;

  case 83: /* Exp: LP Exp error  */
#line 196 "syntax.y"
                    {}
#line 1891 "syntax.tab.c"
    break;

  case 84: /* Exp: MINUS error  */
#line 197 "syntax.y"
                    {}
#line 1897 "syntax.tab.c"
    break;

  case 85: /* Exp: NOT error  */
#line 198 "syntax.y"
                {}
#line 1903 "syntax.tab.c"
    break;

  case 86: /* Exp: ID LP error RP  */
#line 199 "syntax.y"
                        {yyerrok;}
#line 1909 "syntax.tab.c"
    break;

  case 87: /* Exp: Exp LB error RB  */
#line 200 "syntax.y"
                        {yyerrok;}
#line 1915 "syntax.tab.c"
    break;

  case 88: /* Args: Exp COMMA Args  */
#line 202 "syntax.y"
                        {(yyval.Node) = not_token_node("Args", (yyloc).first_line, 3, (yyvsp[-2].Node), (yyvsp[-1].Node), (yyvsp[0].Node));}
#line 1921 "syntax.tab.c"
    break;

  case 89: /* Args: Exp  */
#line 203 "syntax.y"
            {(yyval.Node) = not_token_node("Args", (yyloc).first_line, 1, (yyvsp[0].Node));}
#line 1927 "syntax.tab.c"
    break;

  case 90: /* Args: error COMMA Exp  */
#line 204 "syntax.y"
                        {/*错误的表达式*/}
#line 1933 "syntax.tab.c"
    break;


#line 1937 "syntax.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 206 "syntax.y"

void yyerror(char* s){
    if(yyerr_line==yylineno){
        return;/*如果已经在该行报错则退出*/
    }
    yyerr_line=yylineno;
    error2 = 1;
    if(!error1)
    {
        printf("Error type B at Line %d : %s, near \"%s\".\n",yylineno,s,yytext);
    }
    
}
