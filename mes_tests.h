#include "types.h"
#include "allocateur.h"
#include "environnement.h"
#include "primitives.h"
/*
 * Ce fichier décrit tous les tests à votre disposition pour tester
 * vos fonctions.
 *
 * Pour pouvoir lancer un test, il faut d’abord le décommenter daans
 * ce fichier ainsi que le #define le précédant puis de l’ajouter dans
 * votre fonction main.
 *
 */





/****************************************/
/*                                      */
/*  Tests pour le fichier allocateur.c  */
/*                                      */
/****************************************/


/* TP 1 */
#define TEST_ALLOCATEUR_EX1
void test_memoire_vide();

#define TEST_ALLOCATEUR_EX2
void test_allocateurs_fonctions_de_base();

#define TEST_ALLOCATEUR_EX3
void test_allocateur_malloc();



/* TP 3 */
#define TEST_RAMASSE_MIETTE_1
void test_pointeur_vers_indice();


/************************************/
/*                                  */
/*  Tests pour le fichier types.c   */
/*                                  */
/************************************/


#define TEST_TYPES_ENTIER
void test_entiers();



#define TEST_TYPES_CHAINE
void test_chaines();



#define TEST_TYPES_SYMBOLE
void test_symboles();


#define TEST_TYPES_LISTE
void test_cons();
void test_listes();
void test_affichage_liste_cons();

/* Tous les tests précédents sur les types en une fonction*/

#define TEST_TYPES
void test_types();





/****************************************/
/*                                      */
/*  Tests pour le fichier primitives.c  */
/*                                      */
/****************************************/


#define TEST_PRIMITIVES_ADD
void test_add();



/********************************************/
/*                                          */
/*  Tests pour le fichier environnement.c   */
/*                                          */
/********************************************/



#define TEST_ENV_INIT
void test_initialiser_environnement();

#define TEST_ENV_MANIP
void test_manipuler_environnement();


