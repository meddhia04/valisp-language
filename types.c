#include "types.h"
#include "allocateur.h"
#include "erreur.h"
#include <stdio.h>
#include "memoire.h"
#include <stdlib.h>
#include <string.h>


/*exercice 5*/
/* 1*/

sexpr new_integer(int i){
    sexpr p = allocateur_malloc(sizeof(struct valisp_object));
    p->type = entier;
    p->data.integer = i;
    return p;

}

/*2*/
bool integer_p(sexpr val){
    return val!=NULL && val->type == entier;
}

/*2*/

int get_integer(sexpr val){
    return val->data.integer;
}

/*4*/
/*
void afficher(sexpr val){
    valisp_type t = val->type;
    if(t==entier){printf("%d",get_integer(val));} 
}*/

/*exo6*/
/*1*/
char* chaine_vers_memoire(const char *c){
    int len = strlen(c);
    char* ch ;
    int i = 0;
    ch=valisp_malloc((sizeof(char)*(len+1)));
    while(c[i]!='\0'){
        ch[i] = c[i];
        i++;
    }
    ch[i]='\0';
    printf("test chaine %s: \n",ch);
    return ch;

}
/*2*/
/*a ici on fait un pointeur vers struct valisp_object car sizeof(sexpr) c'est la taille du pointeur pas l'objet*/
sexpr new_string(char * c){
    sexpr p = valisp_malloc(sizeof(struct valisp_object));
    p->type = chaine;
    p->data.str = chaine_vers_memoire(c);
    return p;
  
}

sexpr new_symbol(char * c){
    sexpr p = valisp_malloc(sizeof(struct valisp_object));
    p->type = symbole;
    p->data.str = chaine_vers_memoire(c);
    /*si le symbole est nil donc on retourne NULL*/
    if(strcmp(p->data.str,"nil")==0){return NULL;}
    return p;
}
/*b pour extraire le symbole et la chaine*/
char* get_symbol(sexpr val){
    char* sym = val->data.str ;
    if(val==NULL){return NULL;}
    if(val->type!=symbole){return NULL;}
    return sym;
    
}

char* get_string(sexpr val){
    char* ret = val->data.str;
    if(val==NULL){return NULL;}
    if(val->type != chaine){return NULL;}
    return ret;
}

/*c pour voir si c'est un type chaine ou untype symbole*/
bool string_p(sexpr val){
    if(val==NULL){return false;}
    if(val->type==chaine){return true;}
    return false;

}

bool symbol_p(sexpr val){
    if(val==NULL){return false;}
    if(val->type == symbole){return true;}
    return false;
}



/*3*/
bool symbol_match_p(sexpr val, const char *chaine){
    char* symb = get_symbol(val); 
    if(symb!=NULL && chaine!=NULL){
        int result = strcmp(symb,chaine);
        if(result==0){
            return true;
        }
        else{
            return false;
        }

    }
    return false;
}
/*exercice 7 Listes*/
/*1*/
sexpr cons(sexpr e1 , sexpr e2){
    sexpr p = valisp_malloc(sizeof(struct valisp_object));
    p->type = couple;
    p->data.cons.car = e1;
    p->data.cons.cdr = e2;
    return p;

}
/*2*/
bool cons_p(sexpr e){
    if(e==NULL){return false;}
    if(e->type ==couple){return true;}
    return false;
}
/*3*/
bool list_p(sexpr e){
    /*si e est nil et nil est un symbole*/
    if(e->type==symbole && strcmp(e->data.str,"nil")==0){return true;}
    /*si e est un cons dont le cdr est lui-meme un cons ou nil*/
    if(e->type == couple){
        sexpr c = e->data.cons.cdr;
        if(c==NULL){return true;}
        if(cons_p(c)==true){return true;}
        if(c->type == symbole && strcmp(c->data.str,"nil")==0){return true;}
    }
    return false;
}

/*4*/
sexpr car(sexpr e){
    if(e==NULL){ERREUR_FATALE(__FILE__,__LINE__,"e est NULL");}
    return e->data.cons.car;
}

sexpr cdr(sexpr e){
    if(e==NULL){ERREUR_FATALE(__FILE__,__LINE__,"e est NULL");}
    return e->data.cons.cdr;
}

/*5*/
void set_car(sexpr e,sexpr nouvelle){
    e->data.cons.car = nouvelle;
}

void set_cdr(sexpr e,sexpr nouvelle){
    e->data.cons.cdr = nouvelle;
}

/*6*/
void afficher_liste(sexpr e) {
    if(e==NULL){
        printf("()");
        return;
    }
    printf("(");
    while (e != NULL && e->type == couple) {
        afficher(e->data.cons.car);
        e = e->data.cons.cdr;
        if (e != NULL && e->type == couple) {
            printf(" ");
        }
    }
    if (e != NULL && !(e->type == symbole && strcmp(e->data.str, "nil") == 0)) {
        printf(" . ");
        afficher(e);
    }
    printf(")");
}

/*7 on a changé l'ancienne fonction pour gérér l'affichage de la liste*/

/*exercice 8 Primitives*/

/*1*/
sexpr new_primitive(sexpr (*p)(sexpr,sexpr)){
    sexpr v = valisp_malloc(sizeof(struct valisp_object));
    v->type = prim;
    v->data.function=p;
    return v;
}

sexpr new_speciale(sexpr (*p)(sexpr,sexpr)){
    sexpr v = valisp_malloc(sizeof(struct valisp_object));
    v->type = spec;
    v->data.function=p;
    return v;
}

/*2*/

bool prim_p(sexpr val){
    if(val==NULL){return false;}
    if(val->type == prim){return true;}
    return false;
}

bool spec_p(sexpr val){
    if(val==NULL){return false;}
    if(val->type == spec){return true;}
    return false;

}

/*3*/
sexpr run_prim(sexpr p , sexpr liste , sexpr env){
    if(p==NULL){ERREUR_FATALE(__FILE__,__LINE__,"Primitive NULL");}
    if(prim_p(p)==false){ERREUR_FATALE(__FILE__,__LINE__,"type ne convient pas");}
    return p->data.function(liste,env);
}


/*d afficher de tous les types*/
void afficher(sexpr val){
    if (val == NULL) {
        printf("nil");
        return;
    }

    if (string_p(val)) {
        printf("%s", get_string(val));
    }
    else if (symbol_p(val)) {
        printf("%s", get_symbol(val));
    }
    else if (integer_p(val)) {
        printf("%d", get_integer(val));
    }
    else if (cons_p(val)) {
        afficher_liste(val);
    }
    else if(prim_p(val)){
        printf("#<primitive>");

    }
    else if(spec_p(val)){
        printf("#<special>");
    }
    else {
        ERREUR_FATALE(__FILE__, __LINE__, "Type inconnu dans afficher");
    }
}

/*exercice 9: a faire aprés l'exo 10*/
/*fonction pour tester l'egalité des cons*/


bool sexpr_equal(sexpr e1,sexpr e2){
    /*si c'est deux types différent on retourne faux direct */
    if(e1->type != e2->type){return false;}
    /*si c'est un entier on compare leur valeur*/
    /*j'ai pas fait le and ici pour e2 car si il sont de meme type on peux voir seulement si */
    if(integer_p(e1)){
        if(get_integer(e1)==get_integer(e2)){return true;}
        return false;
    }
    /*si c'est une chaine de caractéres*/
    if(string_p(e1)){
        if(strcmp(get_string(e1),get_string(e2))==0){return true;}
        return false;
    }
     /*si c'est un symbole*/
    if(symbol_p(e1)){
        if(strcmp(get_symbol(e1),get_symbol(e2))==0){return true;}
        return false;
    }
    /*cons_p*/
    if(cons_p(e1)){
        return egalite_cons(e1,e2);

    }
    /*si c'est une primitive*/
    if(prim_p(e1)){
        return e1->data.function == e2->data.function;
    }
    /*si c'est une speciale*/
    if(spec_p(e1)){
        return e1->data.function == e2->data.function;
    }
    /*par défaut , les éléments ne sont pas égaux*/
    return false;
}

bool egalite_cons(sexpr e1,sexpr e2){
    /*si les deux sont null donc les deux sont égaux*/
    if(e1==NULL && e2==NULL){return true;}
    /*si l'un entre eux est null donc ne sont pas egaux*/
    if(e1==NULL || e2==NULL){return false;}
    /*on utilise la fonction ici sexpr_equal et on compare leur car si c'est différent ca implique ils ne sont pas egaux*/
    if(!sexpr_equal(car(e1),car(e2))){return false;}
    /*si c'est pas les cas précédent on va récursivement compare leur cdr*/
    return egalite_cons(cdr(e1),cdr(e2));
}










