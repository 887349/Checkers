#include <iostream>
#include <cassert>

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

void sum_reverse_it(Lista A, Lista& B) {

	if(not A) return;

	int len = 0;
	Lista supp = A;
	while(supp){
		len++;
		supp = supp->next;
	}

	Lista supp_b = B;
	
	for(int i=0;i<len;++i){
		
		Lista supp_a = A;
		int j = len-i-1;
		while(j>0){
			j--;
			supp_a = supp_a->next;
		}
		
		supp_b->info += supp_a->info;
		supp_b = supp_b->next;
		
	}
	
}

// in general, this function works when length(A) <= length(B). It does these things:
// 1) reverse(A) is added to the prefix of B of length length(A),
// 2) if length(A) < length(B), B is modified to point to the first unaffected cell of B. Otherwise, B is unaffected.
void sum_reverse_rec(Lista A, Lista& B) { 
    if (A) { // if not A: nothing to do.
    	Lista supp = B;
        sum_reverse_rec(A->next, supp);
        supp->info += A->info;
        if (supp->next) {
            B = supp->next;
        }
    }
}

void sum_reverse(Lista A, Lista& B) {
    sum_reverse_rec(A,B);
}   


int main() {
    Lista A = nullptr;
    Lista B = nullptr;
    leggi(A);
    leggi(B);
    sum_reverse(A,B);
    std::cout << std::endl;
    stampa_lista(B);
    distruggi(A);
    distruggi(B);
    return 0;
}
