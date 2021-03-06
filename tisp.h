#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

// token.c
enum TokenKind {
    TK_NUM,
    TK_LPARENT, // (
    TK_RPARENT, // )
    TK_PRIM,
    TK_T,
    TK_NIL,
    TK_SYMBOL,
    TK_QUOTE,   // '
    TK_EOF,
};

struct Token {
    enum TokenKind kind;
    struct Token *next;
    int val;   // kind が TK_NUM の場合に使う
    char *str; // kind が TK_PRIM, TK_SYMBOL の場合に使う
};

struct Token *tokenize(char *input);

// cell.c
enum CellKind {
    CK_LIST,
    CK_NUM,
    CK_DOT,
    CK_T,
    CK_NIL,
    CK_PRIM,
    CK_SYMBOL,
};

enum PrimKind {
    PK_NONE,
    PK_QUOTE,
    PK_EQ,     // Both 'eq' and '=' primitives have the same kind, 'PK_EQ'.
    PK_ATOM,
    PK_CAR,
    PK_CDR,
    PK_CONS,
    PK_COND,
    PK_APPEND,
    PK_DEFUN,
    PK_LENGTH,
    PK_LIST,
    PK_SETQ,
    PK_IF,
    PK_ADD,
    PK_SUB,
    PK_MUL,
    PK_DIV,
    PK_MOD,
    PK_LT,
    PK_GT,
};

struct Cell {
    enum CellKind kind;
    enum PrimKind pkind;

    int val;   // kind が CK_NUM の場合に使う
    char *str; // kind が CK_PRIM, CK_SYMBOL の場合に使う

    struct Cell *data; // kind が CK_LIST の場合に使う
    struct Cell *next; // リストの次要素を指す場合に使う

    struct Cell *car; // kind が CK_DOT の場合に使う
    struct Cell *cdr; // kind が CK_DOT の場合に使う

    struct Cell *binded_cell; // kind が CK_SYMBOL の場合に使う
};

struct VarNode {
    struct Cell *var;
    struct VarNode *next;
};

struct Env {
    struct Env *up;
    struct VarNode *vars;
};

struct Cell *new_cell(enum CellKind kind);
struct Cell *new_num_cell(int val);
struct Cell *new_list_cell(struct Cell *data);
struct Cell *new_dot_cell(struct Cell *car, struct Cell *cdr);
struct Cell *new_symbol_cell(char *name);
struct Cell *gen_cell(struct Token *tokens);

// eval.c
struct Env *new_env();
struct Cell *eval(struct Cell *c, struct Env *g_env);

// util.c
bool is_integer(char c);
bool is_alpha(char c);
bool equal_strings(const char *str1, const char *str2);
void assert(bool result, char *fmt, ...);
void error(char *fmt, ...);
