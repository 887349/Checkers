/*
Lista di stringhe

Data una lista (semplice) di string implementa la seguente funzione:

concat restituisce una stringa che è al concatenazione delle stringhe 
a partire dalla posizione pos per len celle. Per esempio nella lista: 
"hello", "world", "this", "is", "an", "example" se pos=1 e len=3 
restituiamo la stringa "worldthisis". La prima posizione della lista è la 0. 
Se pos non esiste nella lista, ritornare la stringa vuota. Tutte le cella che 
escono fuori dalla dimensione della lista è come se contenessero la stringa vuota. 
Nell'esempio precedente se pos=5 e len=10 si ritorna la stringa "example"

Super task: provate a farla ricorsiva!
Aiutatevi con le funzione già create
*/


#include<iostream>
#include<string>

using std::string;

struct Cella{
  string info;
  Cella* next;
};

typedef Cella* Lista;

void prepend(Lista& l, const string& s) {
  Lista nuova = new Cella;

  nuova->next=l;
  nuova->info = s;
  l=nuova;
}


void append(Lista& l, const string& s) {
  if (!l)
    prepend(l, s);
  else
    append(l->next, s);
}

void leggi(Lista& l) {
  int e;
  std::cin>>e;

  while (e>0) {
    string buffer;
    std::cin>>buffer;
    append(l, buffer);
    e--;
  }
}

void distruggi(Lista& l) {
  if (l) {
    distruggi(l->next);
    delete l;
    l=nullptr;
  }
}




string concat_it(Lista l, int pos, int len) {

    string res;

    int i = -1;

    while(l and ++i<pos) l = l->next;

    if(l){
        while(l and len){
            res += l->info;
            len--;
            l = l->next;
        }
    }

    return res;

}
    

string concat_rec(Lista l, int pos, int len) {

    if(not l or len == 0) return {};

    if(pos == 0) return l->info + concat_rec(l->next, 0, len-1);

    return concat_rec(l->next, pos-1, len);

}




string concat(Lista l, int pos, int len) {

    return concat_rec(l,pos,len);

}

int main() {
  Lista l = nullptr;
  int da, quanti;

  leggi(l);

  std::cin>>da;
  std::cin>>quanti;

  std::cout<<concat(l, da, quanti);

  distruggi(l);

  return 0;
}


