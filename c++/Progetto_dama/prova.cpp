#include <iostream>
#include <fstream>

using namespace std;

/* g++ -o nome_eseguibile nome_file.cpp        per compilare
   ./nome_eseguibile                           per eseguire
   cd nome-file                                per entrare in quel path
   ls                                          per leggere file nel dominio*/
   

enum piece {x, o, X, O, e};
struct Impl{
    struct piece_list{
        piece scacchiera [8][8];
        piece_list* next;
    }; typedef piece_list* list;

    list history; 
    int player_n;   

    void dealloc_history(){
        while (history) {
            list pc = history;
            history = history->next;
            delete pc;
        }
    }

    //funzione di stampa delle scacchiere
    void stampa (){
        list aux = history;
        while (aux){
            for(int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    if (aux->scacchiera[i][j] == 1) cout << "o ";
                    if (aux->scacchiera[i][j] == 2) cout << "X ";
                    if (aux->scacchiera[i][j] == 3) cout << "O ";
                    if (aux->scacchiera[i][j] == 0) cout << "x ";
                    if (aux->scacchiera[i][j] == 4) cout << "e ";
                }
                cout << endl;
            }
            aux = aux->next;
            cout << endl;
        }
    }

    void prepend(piece s[][8]){
        Impl::list nuovo = new Impl::piece_list;
        for(int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                nuovo->scacchiera[i][j] = s[i][j];
        nuovo->next = history;
        history = nuovo; 
    }

    void append(piece s[][8]){
        Impl::list nuovo = new Impl::piece_list;
        for(int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                nuovo->scacchiera[i][j] = s[i][j];
        nuovo->next=nullptr;
        if(!history) history=nuovo;
        else {
            list aux = history;
            while (aux->next) aux=aux->next;
            aux->next=nuovo;
        }
    }
};




int main(){
    Impl* pimpl = new Impl;
    pimpl->history = nullptr;
    piece s[8][8];
    // matrice con solo e
    for(int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            s[i][j] = (piece)4;
    pimpl->prepend(s);

    
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
    pimpl->prepend (s);

    fstream board;
    string filename = "prova.txt";
    board.open(filename, ios::out);
    piece scacchiera[8][8];
    
    if (board.is_open()){
        for(int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if ( (i+j)%2==0 ){
                    if (i>=0 and i<=2) board << "o";
                    else if (i>=5 and i<=7) board << "x";
                    else board << " ";
                }
                else board << " ";
            }
            if (i<7) board << "\n";
        }
        board.close();
    } 

    board.open(filename, ios::in);
    if (board.is_open()){
        string line;
        int i=0;
            while(getline(board, line)){
                for (int j=0; j<8; j++){
                    
                    switch (line[j])
                    {
                        case 'x':
                            s[i][j]=(piece)0;
                            break;
                        case 'o':
                            s[i][j]=(piece)1;
                            break;
                        case 'X':
                            s[i][j]=(piece)2;
                            break;
                        case 'O':
                            s[i][j]=(piece)3;
                            break;
                        case ' ':
                            s[i][j]=(piece)4;
                            break;
                    }
                }
                ++i;
            }
        board.close();
    }
    
    pimpl->prepend(s);
    pimpl->stampa();
    if(pimpl->history==nullptr) cout<<"not good"<<endl;
    pimpl->dealloc_history();
    cout<<"dopo la deallocazione"<<endl;
    pimpl->stampa();
    if (!pimpl->history) cout<<"good"<<endl;
    //pimpl->append(s);
    //pimpl->stampa();

    return 0;
}