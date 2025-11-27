#include "primitives.h"
#include <stdio.h>
#include "erreur.h"
#include "types.h"
#include "environnement.h"
#include "interpreteur.h"

/*test nb paramétres*/
void test_nb_parametres(sexpr lst ,sexpr symb, int n){
    int le=0;
    sexpr courant = lst;
    while(courant!=NULL && courant->type == couple){
        le++;
        courant = cdr(courant);
    }
    if(le!=n){
        erreur(ARITE,get_symbol(symb),"Nombre des paramétres insuffisant",courant);
    }
}
/*exercice 6 TP3*/
/*1*/
sexpr add_valisp(sexpr liste, sexpr env) {
    sexpr a;
    sexpr b;
    /* On vérifie l’arité */
   
    /* On récupère les deux paramètres */
    a = car(liste);
    b = car(cdr(liste));
    test_nb_parametres(liste, a, 2);
    /* On vérifie de typage */
    if (!integer_p(a)) erreur(TYPAGE, "+", "nécessite un entier", a);
    if (!integer_p(b)) erreur(TYPAGE, "+", "nécessite un entier", b);
    /* On fait le calcul */
    return new_integer(get_integer(a) + get_integer(b));
}
/*2*/
sexpr defvar_valisp(sexpr liste, sexpr env) {
    sexpr nom;
    sexpr exp;
    sexpr res;
    printf("1\n");
    nom = car(liste);
    exp = car(cdr(liste));
    printf("2\n");
    test_nb_parametres(liste,nom,2);
    printf("3\n");
    if (!symbol_p(nom) ) {
        erreur(TYPAGE,"defvar","Le 1er paramétre doit etre un symbole",nom);

    }
    printf("1\n");
    /*Il faut évaluer à la main le*/
    res = eval(exp, env); 
    printf("2\n");
    definir_variable_globale(nom,res); /* second paramètre */
    return res;
}
/*3*/
sexpr setq_valisp(sexpr liste,sexpr env){
    /*l'idée c'est trouver si la variable est définie ou pas si elle est définie on change .*/
    sexpr nom;
    sexpr exp;
    sexpr valeur;
    sexpr *res1;
    nom = car(liste);
    exp = car(cdr(liste));
    valeur = eval(exp,env);
    res1 = 0;
    if(trouver_variable(env,nom,res1)==0){
       modifier_variable(env,nom,valeur);
    }
    else{
        defvar_valisp(liste,env);
    }
    return valeur;
}