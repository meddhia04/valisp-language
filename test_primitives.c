#include <stdio.h>
#include "allocateur.h"
#include "types.h"
#include "tests.h"
#include "primitives.h"
#include "mes_tests.h"



/****************/
/*              */
/*  Primitives  */
/*              */
/****************/

#ifdef TEST_PRIMITIVES_ADD
void test_add() {
    sexpr a;
    sexpr b;
    sexpr c;
    sexpr liste;
    sexpr env;
    afficher_titre("Test Additions");
    initialiser_memoire_dynamique();
    a = new_integer(10);
    b = new_integer(5);
    liste = cons(a, cons(b, NULL));
    env = NULL;
    c = add_valisp(liste,env);
    printf("%d + %d = ", 10, 5);
    afficher(c);
    printf("\n");
}
#endif
