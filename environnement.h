#include "types.h"
#include "memoire.h"
#include "allocateur.h"


extern sexpr ENV;
sexpr environnement_global(void);
void initialiser_memoire(void);
int trouver_variable(sexpr env, sexpr variable,sexpr *resultat);
int modifier_variable(sexpr env, sexpr variable, sexpr valeur);
void definir_variable_globale(sexpr variable, sexpr valeur);
void charger_une_primitive(char* nom, sexpr (*prim)(sexpr, sexpr));
void charger_une_speciale(char* nom, sexpr (*prim)(sexpr, sexpr));
void afficher_env(sexpr env);
void valisp_stat_memoire(void);


