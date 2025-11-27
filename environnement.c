#include "types.h"
#include "environnement.h"
#include "allocateur.h"
#include <stdio.h>

/*TP3 exo1 1.*/
sexpr ENV =NULL;
/*2*/
sexpr environnement_global(void){
    return ENV;
}

/*3*/
void initialiser_memoire(void){
    sexpr s = new_symbol("t");
    initialiser_memoire_dynamique();
    /*on cree un symbole t*/
    ENV = cons(cons(s,s),NULL);
    

}
/*exo 2 TP3*/
/*1*/
int trouver_variable(sexpr env , sexpr variable , sexpr *resultat){
    while (env != NULL) {
        sexpr paire = car(env); /*Chaque élément de la liste est une paire (symbole . valeur)*/
        sexpr nom = car(paire); /*symbole*/
        sexpr val = cdr(paire); /*valeur associée*/
        if (symbol_match_p(nom, get_symbol(variable))) {
            *resultat = val;
            return 0;
        }
        env = cdr(env); /*passer à la prochaine paire de l’environnement*/
    }
    return -1;

}
/*2*/
/*ici on peux la changer de while au for*/
int modifier_variable(sexpr env, sexpr variable, sexpr valeur) {
    while (env != NULL) {
        sexpr paire = car(env);
        sexpr nom = car(paire);
        if (symbol_match_p(nom, get_symbol(variable))) {
            set_cdr(paire, valeur); /*on modifie la valeur*/
            return 0;
        }
        env = cdr(env);
    }
    return -1;
}

void definir_variable_globale(sexpr variable, sexpr valeur) {
    sexpr paire;
    if (modifier_variable(ENV, variable, valeur) == 0) {
        return;
     } /*deja c'est modifié*/

    /*Sinon on ajoute (variable . valeur) à l’environnement*/
    paire = cons(variable, valeur);
    ENV = cons(paire, ENV); /*On ajoute a la fin de la liste chainée*/
}

/*4*/
/*a c'est de définir une primitive on le mettant dans l'environnement*/
void charger_une_primitive(char* nom, sexpr (*prim)(sexpr, sexpr)){
    definir_variable_globale(new_symbol(nom),new_primitive(prim));

}

/*b c'est de definir une spéciale en le mettant dans l'environnement*/

void charger_une_speciale(char* nom, sexpr(*prim)(sexpr,sexpr)){
    definir_variable_globale(new_symbol(nom),new_speciale(prim));
}

/*exercice5*/
/*1 pour calculer la longeur de l'environnement*/
int longeur_env(sexpr env){
    int longeur = 0;
    while(env!=NULL){
        longeur++;
        env = cdr(env);
    }
    return longeur;
}
/*2*/
void valisp_stat_memoire(void){
    afficher_stat_memoire();
    printf("-> %d variables\n",longeur_env(ENV));
}
/*3 une procédure qui affiche toute les liaison de l'envoironnement (une par ligne) avec en bleu les variables et en blanc les valeurs associés*/
void afficher_env(sexpr env){
    while(env!=NULL){
        sexpr paire = car(env);
        sexpr variable = car(paire);
        sexpr valeur = cdr(paire);
        /*ici on fait le print les variables on bleu et les valeur en blanc*/
        printf("\033[1;34m%s->\033[0m",get_symbol(variable));
        afficher(valeur);
        printf("\n");
        env = cdr(env);
    }

}


