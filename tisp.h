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

    int val; // kind が TK_NUM の場合に使う

    char *str; // king が TK_PRIM, TK_SYMBOL の場合に使う
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
    PK_EQ,
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
    PK_LT,
    PK_GT,
};

struct Cell {
    enum CellKind kind;
    enum PrimKind pkind;

    int val; // kind が CK_NUM の場合に使う
    char *str; // kind が CK_PRIM, CK_SYMBOL の場合に使う

    struct Cell *data; // kind が CK_LIST の場合に使う
    struct Cell *next; // リストの次要素を指す場合に使う

    struct Cell *car; // kind が CK_DOT の場合に使う
    struct Cell *cdr; // kind が CK_DOT の場合に使う
};

struct FuncNode {
    struct Cell *fn;
    struct FuncNode *next;
};

struct SymbolNode {
    struct Cell *sy;
    struct SymbolNode *next;
};

struct Env {
    struct FuncNode *funcs;
    struct SymbolNode *symbols;
};

struct Cell *new_cell(enum CellKind kind);
struct Cell *new_num_cell(int val);
struct Cell *new_list_cell(struct Cell *data);
struct Cell *new_dot_cell(struct Cell *car, struct Cell *cdr);
struct Cell *new_symbol_cell(char *name);
void init_env();
struct Cell *gen_cell(struct Token *tokens);

// eval.c
struct Cell *eval(struct Cell *c);

// util.c
bool is_integer(char c);
bool is_alpha(char c);
bool equal_strings(const char *str1, const char *str2);
void assert(bool result, char *fmt, ...);
void error(char *fmt, ...);
