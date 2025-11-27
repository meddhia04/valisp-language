#include <stdio.h>
#include <setjmp.h>
#include "types.h"
#include "stdlib.h"
#include "couleurs.h"
#include "erreur.h"
#include "types.h"



/**********************/
/*                    */
/*  Erreurs Fatales   */
/*                   */
/**********************/

/*exo7 1.*/
jmp_buf buf;
/*exo7 2.*/
jmp_buf *jump_buffer(){
    return &buf;
}





/* Pour s’arrêter lorsque le développeur tombe sur cas qui ne devrait
   jamais arriver. Normalement, si le programme est écrit sans bugs,
   les erreurs fatales ne devrait jamais être rencontrées. */

void erreur_fatale(char  *fichier, int ligne, char* causes) {
    fprintf(stderr,"%s", couleur_rouge);
    fprintf(stderr,"\n   /!\\ Erreur fatale /!\\");
    fprintf(stderr,"%s", couleur_defaut);
    fprintf(stderr,"   %s ligne %d\n\n", fichier, ligne);
    fprintf(stderr,"%s\n", causes);
    /*modification tp2 exo2*/
    exit(1);
}

/*initialisation des variables globales*/

sexpr SEXPR_ERREUR = NULL;
char* FONCTION_ERREUR = NULL;
char* MESSAGE_ERREUR = NULL;
enum erreurs TYPE_ERREUR ;
/*d'aprés l'enum en retourne le nom en chaine de caractéres*/
const char* get_nom_erreur(enum erreurs type){
    switch(type){
        case TYPAGE : return "TYPAGE";
        case ARITE: return "ARITE";
        case NOM : return "NOM";
        case MEMOIRE: return "MEMOIRE";
        case DIVISION_PAR_ZERO: return "DIVISION_PAR_ZERO";
        case SYNTAXE: return "SYNTAXE";
        case MEMOIRE_PARSEUR: return "MEMOIRE_PARSEUR";
        case RUNTIME : return "RUNTIME";
        default : return "ERREUR INCONNUE";
    }
}

void afficher_erreur(void) {
    fprintf(stderr, "\033[1;31m");  /*Pour afficher en rouge*/
    fprintf(stderr, "Erreur d’exécution [%s] : %s\n", get_nom_erreur(TYPE_ERREUR), MESSAGE_ERREUR);
    fprintf(stderr, "Fonction fautive : \"%s\"\n", FONCTION_ERREUR);
    fprintf(stderr, "Valeur fautive : ");
    afficher(SEXPR_ERREUR);  /*Affiche la valeur fautive*/
    fprintf(stderr, "\033[0m");  /*Restaure la couleur par défaut*/
}

void erreur(enum erreurs type, char* fonction, char* explication , sexpr s){
    /*on modifie les variables globales*/
    SEXPR_ERREUR = s;
    FONCTION_ERREUR = fonction;
    MESSAGE_ERREUR = explication;
    TYPE_ERREUR = type ;
    /*exo 7 3. enlever l'affichage erreur*/
    /*afficher_erreur();
    exit(1);*/
    longjmp(*jump_buffer(),1);
}
