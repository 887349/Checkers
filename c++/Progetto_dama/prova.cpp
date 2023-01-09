#include <iostream>

using namespace std;

/* g++ -o nome_eseguibile nome_file.cpp        per compilare
   ./nome_eseguibile                           per eseguire
   cd nome-file                                per entrare in quel path
   ls                                          per leggere file nel dominio*/
   

enum piece {x, o, X, O, e};
struct piece_list{
            piece scacchiera [8][8];
            piece_list* next;
}; typedef piece_list list;

/* void Stack_int::push(int elem) { //Prepend
	Cella* nuova = new Cella;
	nuova->info = elem;
	nuova->next = pimpl->head;
	pimpl->head=nuova;
    } */

void push(list *history, piece scacchiera[][8]) {
    list* nuovo = new list;
    for(int i=0; i<2; i++)
        for (int j=0; j<2; j++)
            nuovo->scacchiera[i][j] = scacchiera[i][j];
    nuovo->next = history;
    history = nuovo;
}

void stampa (list *history){
    while (history){
        for(int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (history->scacchiera[i][j] == 0) cout << "x ";
                if (history->scacchiera[i][j] == 1) cout << "o ";
                if (history->scacchiera[i][j] == 2) cout << "X ";
                if (history->scacchiera[i][j] == 3) cout << "O ";
                if (history->scacchiera[i][j] == 4) cout << "e ";
            }
            cout << endl;
        }
        history = history->next;
        cout << endl;
    }
}

int main(){

    list* history = nullptr;

    // matrice con solo e
    history = new list;
    for(int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            history->scacchiera[i][j] = (piece)4;

    cout << "Inserire dati della nuova scacchiera:"<<endl;
    piece s[8][8];
    int p;

    // matrice scacchiera esatta
    for(int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if ( (i+j)%2==0 ){
                if (i>=0 and i<=2) s[i][j] = o;
                else if (i>=5 and i<=7) s[i][j] = x;
                else s[i][j] = e;
            }
            else s[i][j] = e;
        }
    }
    // push (history, s);

    // prepend della seconda matrice nella lista history
    list* nuovo = new list;
    for(int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            nuovo->scacchiera[i][j] = s[i][j];
    nuovo->next = history;
    history = nuovo;

    stampa (history);


    /* int* vettore = new int(10);

     cout << "Inserire dati nel primo vettore"<<endl;
    for(int i=0; i<5; i++) cin >> vettore [i];

    cout << "Inserito: ";
    for(int i=0; i<5; i++) cout << vettore [i] << " ";
    cout << endl; */

    /* piece* scacchiera[4][4];
    for(int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (j%2==0) scacchiera[i][j] = (piece*)4;
            else  scacchiera[i][j] = (piece*)3;
        }
    }

    cout << "I dati della scacchiera sono:"<<endl;
    for(int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (scacchiera[i][j]==(piece*)4) cout << "e";
            else cout << "O";
        }
        cout<<endl;
    } */

    return 0;
}