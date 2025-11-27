#ifndef ALLOCATEUR_H
#define ALLOCATEUR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
typedef uint32_t bloc;
void initialiser_memoire_dynamique();
void afficher_memoire();
void afficher_stat_memoire(void);
void *allocateur_malloc(size_t size);
int pointeur_vers_indice(void *ptr);
int ramasse_miette_lire_marque(void * ptr);
int ramasse_miette_poser_marque(void * ptr);
void ramasse_miette_liberer();
void allocateur_free (void * ptr);





/*ajoute*/


#endif