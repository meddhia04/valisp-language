#include "allocateur.h"
#include "erreur.h"
#include "environnement.h"
#include "memoire.h"
#include"types.h"
#include <stddef.h>
#include <stdlib.h>
#include<stdio.h>
#include <stdint.h>

void *valisp_malloc(size_t size){
    int *ret_malloc = allocateur_malloc(size);
    if(ret_malloc == NULL){
        ERREUR_FATALE(__FILE__,__LINE__,"y'a pas de bloc libre!");
    }
    return ret_malloc;
}
/*exo4 tp3*/
/*1*/
void ramasse_miette_parcourir_et_marquer(sexpr s){
    if(s==NULL){
        return; /*si l'element est null en fait rien */
    }
    /*si l'élément est déja marqué on arréte le parcours*/
    if(ramasse_miette_lire_marque(s)==1){
        return;

    }
    ramasse_miette_poser_marque(s);
    /*si l'element est du cons on parcours récursivement l'environnement car les car et les cdr peuvent etre des cons aussi*/
    if(cons_p(s)){
        ramasse_miette_parcourir_et_marquer(car(s));
        ramasse_miette_parcourir_et_marquer(cdr(s));
    }


}

void valisp_ramasse_miettes(sexpr env){
    ramasse_miette_parcourir_et_marquer(env);
    ramasse_miette_liberer();

}