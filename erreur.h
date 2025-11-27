#include "types.h"
#include <setjmp.h>

#ifndef VALISP_ERREUR_H
#define VALISP_ERREUR_H

void erreur_fatale(char*  fichier, int ligne, char* causes);



#define ERREUR_FATALE(FICHIER, LIGNE, CAUSE) \
 erreur_fatale ((FICHIER),(LIGNE),(CAUSE))

/*exo10*/
typedef enum erreurs {
    TYPAGE, /* Paramètre du mauvais type */
    ARITE, /* Mauvais nombres de paramètres */
    NOM, /* Variables non définie */
    MEMOIRE, /* Plus de mémoire */
    DIVISION_PAR_ZERO, /* Tentative d’invocation de l’infinie */
    SYNTAXE, /* Parseur : le code écrit n’est pas du Lisp */
    MEMOIRE_PARSEUR, /* Parseur : la sexpr est trop grosse */
    RUNTIME /* Vos propres erreurs lancée depuis valisp */
} erreurs;

extern sexpr SEXPR_ERREUR;
extern char* FONCTION_ERREUR;
extern char*  MESSAGE_ERREUR;
extern enum erreurs TYPE_ERREUR;

const char* get_nom_erreur(enum erreurs type);
void afficher_erreur(void);
void erreur(enum erreurs type, char* fonction, char* explication , sexpr s);
jmp_buf *jump_buffer();


#endif

