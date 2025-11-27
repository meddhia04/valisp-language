#ifndef TYPES_H
#define TYPES_H

#include "allocateur.h"

/* 1. Alias booléen */
typedef int bool;
#define true 1
#define false 0

/* 2. Déclaration anticipée + alias */
typedef struct valisp_object valisp_object;
typedef valisp_object* sexpr;

/* 3. Enumération des types */
typedef enum {
    entier,
    chaine,
    symbole,
    couple,
    prim,
    spec
} valisp_type;

/* 4. Structure pour cons */
typedef struct valisp_cons {
    sexpr car;
    sexpr cdr;
} valisp_cons;

/* 5. Union des données */
typedef union valisp_data {
    int integer;
    char* str;
    valisp_cons cons;
    sexpr (*function)(sexpr, sexpr);
} valisp_data;

/* 6. Structure objet principal */
struct valisp_object {
    valisp_type type;
    valisp_data data;
};

/* 7. Fonctions */
sexpr new_integer(int i);
bool integer_p(sexpr val);
int get_integer(sexpr val);
char* chaine_vers_memoire(const char *c);
sexpr new_string(char * c);
sexpr new_symbol(char * c);
char* get_symbol(sexpr val);
char* get_string(sexpr val);
bool string_p(sexpr val);
bool symbol_p(sexpr val);
bool symbol_match_p(sexpr val, const char *chaine);

sexpr cons(sexpr e1, sexpr e2);
bool cons_p(sexpr e);
bool list_p(sexpr e);
sexpr car(sexpr e);
sexpr cdr(sexpr e);
void set_car(sexpr e, sexpr nouvelle);
void set_cdr(sexpr e, sexpr nouvelle);
sexpr new_primitive(sexpr (*p)(sexpr,sexpr));
sexpr new_speciale(sexpr (*p)(sexpr,sexpr));
void afficher_liste(sexpr e);
void afficher(sexpr val);
bool egalite_cons(sexpr e1,sexpr e2);
bool sexpr_equal(sexpr e1,sexpr e2);


#endif




