#include"allocateur.h"
#include "erreur.h"
#include <stddef.h>
#include <stdlib.h>
#include<stdio.h>
#include <stdint.h>
#define TAILLE_MEMOIRE_DYNAMIQUE (1<<15)
/*libre = 0 paslibre = 1*/

/*exo3 q1*/
bloc cons_bloc(int rm, int precedent , int libre , int suivant){
    return rm<<31 | precedent<<16 | libre << 15 | suivant; /*le or pour fussioner les bits*/
}
/*question 3 exo 1*/
bloc MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE];
void initialiser_memoire_dynamique(){
    MEMOIRE_DYNAMIQUE[0] = cons_bloc(0, 0, 0, TAILLE_MEMOIRE_DYNAMIQUE - 1);
    MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE-1] =cons_bloc(0, 0, 1, TAILLE_MEMOIRE_DYNAMIQUE - 1);

}

/*q2 a*/

int bloc_suivant(int i){
    bloc masque = (1<<15)-1;
    return MEMOIRE_DYNAMIQUE[i] & masque;
}

/*q2 b*/
int bloc_precedant(int i){
    bloc masque = (1<<15)-1;
    return (MEMOIRE_DYNAMIQUE[i]>>16 & masque);
}
/*q2 c*/
int usage_bloc(int i){
    return (MEMOIRE_DYNAMIQUE[i]>>15) &1;
}

/*q2 d*/
int rm_bloc(int i){
    return (MEMOIRE_DYNAMIQUE[i]>>31)&1;
}
/*q3*/
int taille_bloc(int i) {
    int suivant = bloc_suivant(i);
    /*si le bloc suivant est lui meme ou le bloc suivant est le bloc dernier*/
    if(suivant == i  ){return 0;}
    return suivant - i - 1;

}
/*exo 4 rechercher_bloc_libre*/
int rechercher_bloc_libre(size_t size) {
    /*on convertit le size on nombre de cases*/

    int i;
    
    for (i = 0; i != bloc_suivant(i); i = bloc_suivant(i)) {
        /*taille du bloc*/
        int taille_b = taille_bloc(i);
        /*si le bloc non utilsable et libre et sa taille plus grand ou égale a la taille souhaité en retourne l'indice*/
        if ((!usage_bloc(i)) && taille_b>=size) {
            return i;
        }
    }
    return -1;
}
/*exo4 q2*/
void *allocateur_malloc(size_t size){
   int i, p,j,k;
   if (size % sizeof(bloc)==0){
    size = size / sizeof(bloc);
   }
   else{
    size = size / sizeof(bloc) +1;
   }
   i = rechercher_bloc_libre(size);
   if(i==-1){
    return NULL;
   }


   p = bloc_precedant(i);
   j = bloc_suivant(i);
   k = bloc_suivant(j);

   if(size==taille_bloc(i)){
    /* p  i j  */
    MEMOIRE_DYNAMIQUE[i] = cons_bloc(0,p,1,j);
   } else {
    /* p i j k */
    /* p i n j k */
    int n =i+size+1;
    MEMOIRE_DYNAMIQUE[i] = cons_bloc(0,p,1,n);
    MEMOIRE_DYNAMIQUE[n] = cons_bloc(0,i,0,j);
    MEMOIRE_DYNAMIQUE[j] = cons_bloc(0,n,1,k);
   }


    return &(MEMOIRE_DYNAMIQUE[i+1]);
}

void info_bloc(size_t i) {
    int t = taille_bloc(i);
    int p = bloc_precedant(i);
    int s = bloc_suivant(i);
    char * u = usage_bloc(i) ? "[x]" : "[ ]";

    printf("%s %p %5d → %ld → %-5d (%u)\n",
           u, (void *) &MEMOIRE_DYNAMIQUE[i], p, i, s, t);
}

void afficher_memoire() {
    int i;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
	printf("[%5d] ",i);
	info_bloc(i);
    }
    printf("[%5d] ",i);
    info_bloc(i);
}

void afficher_stat_memoire() {
    size_t i = 0;
    int t = TAILLE_MEMOIRE_DYNAMIQUE;
    int n = 0;
    int b = 0;
    int a = 0;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        n+=1;
        if (usage_bloc(i)) {
            a += taille_bloc(i) + 1;
            b += 1;
        }
    }
    printf("%d/%d (%.2f %%) %d/%d blocs alloués", a, t, (100.*a)/t, b,n);
}

void afficher_stat_memoire_bref() {
    size_t i = 0;
    int t = TAILLE_MEMOIRE_DYNAMIQUE;
    int n = 0;
    int b = 0;
    int a = 0;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        n+=1;
        if (usage_bloc(i)) {
            a += taille_bloc(i) + 1;
            b += 1;
        }
    }
    printf("%.2f%%", (100.*a)/t);
}

/*exercice 3 TP3*/
/*1*/
int pointeur_vers_indice(void *ptr){
    /*on calcul la différence d'octet entre le premier element de tableau et pt "l'indice" et on le converti vers une indice int*/
    int indice = ((uintptr_t)ptr - (uintptr_t)MEMOIRE_DYNAMIQUE) / sizeof(uint32_t);
    int bp = bloc_precedant(indice);
    if(bp>TAILLE_MEMOIRE_DYNAMIQUE || bp<0){
        ERREUR_FATALE(__FILE__,__LINE__,"indice n'est pas valide");
    }
    return bp;
}

/*2*/
int ramasse_miette_lire_marque(void *ptr){
    /*on récupére l'indice du pointeur a partir de la fonction précédente et si n'a aucun erreur on utilise la fonction ramasse miettes pour ne retourner le rm du bloc*/
    
    int blocp = pointeur_vers_indice(ptr);
    return rm_bloc(blocp);

}
/*3*/

int ramasse_miette_poser_marque(void * ptr){
    int lire_marque = ramasse_miette_lire_marque(ptr);
    int indice = pointeur_vers_indice(ptr);
    if(lire_marque==1){
        ERREUR_FATALE(__FILE__,__LINE__,"Bloc est déja marqué");
    }
    MEMOIRE_DYNAMIQUE[indice] = cons_bloc(1,bloc_precedant(indice),0,bloc_suivant(indice));
    return 0;
}
/*4*/

int bloc_libre(int i){
    /*si c'est le dernier bloc (lui meme est son propre successeur on le supprime pas)*/
    if(bloc_suivant(i)==i){return 0;}
    /*si le bloc a une ramasse miette a 1 il attend qu'il soit libérer et il est libre on supprime*/
    if(rm_bloc(i)==1 && usage_bloc(i)==0){return 1;}
    return 0;

}

/*5*/

void ramasse_miette_liberer(){
    int i;
    /*on parcours la mémoire et si on trouve un bloc libre on va voir si les blocs adjacents sont libres pour les fussionner*/
    for(i=0 ; i<TAILLE_MEMOIRE_DYNAMIQUE ; i=bloc_suivant(i)){
        if(bloc_libre(i)){
            /*on essaie de fussioner des bloc libres tant que on peux*/
            int suivant = bloc_suivant(i);
            while(suivant!=i && bloc_libre(suivant) && suivant < TAILLE_MEMOIRE_DYNAMIQUE){
                /*on accumule la taille jusqu'au on tombe sur un bloc occupé */
                suivant= bloc_suivant(suivant);
            }
            /*Mettre a Jour le bloc i avec le nouveau suivant aprés fusion*/
            MEMOIRE_DYNAMIQUE[i] = cons_bloc(0,bloc_precedant(i),0,suivant);
            /*mettre a jour le bloc suivant si il n'est pas le dernier*/
            
            if(suivant < TAILLE_MEMOIRE_DYNAMIQUE){
                MEMOIRE_DYNAMIQUE[suivant] = cons_bloc(rm_bloc(suivant),i,usage_bloc(suivant),bloc_suivant(suivant));
            }
        
        }

    }
}


int main_alloc(){
    return 0;
}