#include <iostream>

struct Cella{
  int info;
  struct Cella* next;
};


typedef struct Cella* Lista;


//aggiunta in testa alla lista
void prepend(Lista& lista, int x) {
  Lista nuovo = new Cella;
  nuovo->info = x;
  nuovo->next = lista;
  lista = nuovo;
}

//aggiunta in coda alla lista
void append(Lista& l, int data) {
  if (!l)            
    l = new Cella{data, nullptr};
  else append(l->next, data);
}

//stampa lista
void stampa_lista(Lista l) {
  if (l) {
    std::cout<<l->info<<std::endl;
    stampa_lista(l->next);
  }
}

//distruggi lista
void distruggi(Lista& l) {
  Lista supp;
  while(l) {
    supp = l;
    l = l->next;
    delete supp;
  }
}

void leggi(Lista& l) {
    distruggi(l);
    int elem;
    std::cin>>elem;
    
    while (elem > 0) {
        int e;
        std::cin >> e;
        append(l, e);
        elem--;
    }
}

void fold_it(Lista& A, Lista B) {

    Lista A_iter = A;
    //I use B to iterate over B: why can I do that?

    // while both nonempty: alternate
    while(A_iter and B){

        prepend(A_iter->next,B->info);
        A_iter = A_iter->next->next;
        B = B->next;

    }

    //now at least one between A_iter and B is empty

    if(not B) return;

    //then A_iter is empty and B is not empty

    while(B){
        append(A,B->info); //is append(A_iter,B->info) the same?
        B = B->next;
    }

}

void fold_rec(Lista& A, Lista B) {

    // 4 cases:

    if(not A and not B) return; // both empty: nothing to do

    if(A and not B) return; // non-empty A, empty B: nothing to do

    if(not A and B){ // A empty, B non-empty

        prepend(A,B->info);
        fold_rec(A->next, B->next);

    }else{ // A non-empty, B non-empty

        prepend(A->next,B->info);
        fold_rec(A->next->next, B->next);

    }

}   

void fold(Lista& A, Lista B) {
    fold_it(A,B);
}   


int main() {
    Lista A = nullptr;
    Lista B = nullptr;
    leggi(A);
    leggi(B);
    fold(A,B);
    std::cout << std::endl;
    stampa_lista(A);
    distruggi(A);
    distruggi(B);
    return 0;
}
