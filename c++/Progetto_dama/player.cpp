// Do not include anything else! all other #include's will be deleted.
#include "player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cassert>

using namespace std;

/* Suggerimento: dato che la history prevede di dover “appendere” nuove scacchiere, 
codificatela con una struttura opportuna! 
un array di scacchiere può avere senso, 
ma in questo caso dovreste implementare una strategia di doubling 
per non perdere troppo tempo in ri-allocazioni */
/* COMPLETATO */
struct Player::Impl{
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

    void prepend(piece s[][8]){
        list nuovo = new piece_list;
        for(int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                nuovo->scacchiera[i][j] = s[i][j];
        nuovo->next = history;
        history = nuovo; 
    }

    void append(piece s[][8]){
        list nuovo = new piece_list;
        for(int i=0; i<8; i++)
            for (int j=0; j<8; j++)
                nuovo->scacchiera[i][j] = s[i][j];
        nuovo->next=nullptr;
        if (!history) history=nuovo;
        else{
            list aux = history;
            while (aux->next) aux=aux->next;
            aux->next=nuovo;
        }
    }

    char check_above(int r, int c){
        int r1 = r-1;
        int c1;
        char res = 'n';
        piece op, OP;
        if (history->scacchiera[r][c] == x or history->scacchiera[r][c] == X){
            op = o;
            OP = O;
        }
        else {
            op = x;
            OP = X;
        }

        if (c>0) {
            c1 = c-1;
            if (history->scacchiera[r1][c1] == e) return 's';
            if (c1>0){
                if (history->scacchiera[r1][c1] == op or (history->scacchiera[r1][c1] == OP and 
                    (history->scacchiera[r][c] == X or history->scacchiera[r][c] == O)))
                    if (history->scacchiera[r1-1][c1-1] == e) return 'S';
            }      
        }
        if (c<7) {
            c1 = c+1;
            if (history->scacchiera[r1][c1] == e) return 'd';
            if (c<7){
                if (history->scacchiera[r1][c1] == op or (history->scacchiera[r1][c1] == OP and 
                    (history->scacchiera[r][c]== X or history->scacchiera[r][c]== O)))
                    if (history->scacchiera[r1-1][c1+1] == e) return 'D';
            } 
        }
        return res;
    }

    char check_below(int r, int c){
        int r1 = r+1;
        int c1;
        char res = 'n';
        piece op, OP;
        if (history->scacchiera[r][c] == x or history->scacchiera[r][c] == X){
            op = o;
            OP = O;
        }
        else {
            op = x;
            OP = X;
        }

        if (c>0) {
            c1 = c-1;
            if (history->scacchiera[r1][c1] == e) return 's';
            if (c1>0){
                if (history->scacchiera[r1][c1] == op or (history->scacchiera[r1][c1] == OP and 
                    (history->scacchiera[r][c] == X or history->scacchiera[r][c] == O)))
                    if (history->scacchiera[r1+1][c1-1] == e) return 'S';
            }      
        }
        if (c<7) {
            c1 = c+1;
            if (history->scacchiera[r1][c1] == e) return 'd';
            if (c<7){
                if (history->scacchiera[r1][c1] == op or (history->scacchiera[r1][c1] == OP and 
                    (history->scacchiera[r][c]== X or history->scacchiera[r][c]== O)))
                    if (history->scacchiera[r1+1][c1+1] == e) return 'D';
            } 
        }
        return res;
    }

    void move_ped(int i1, int j1, int r, int c){
        piece s[8][8];
        s[r][c] = history->scacchiera[i1][j1];
        s[i1][j1] = e;
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if ((i==r and j==c) or (i==i1 and j==j1)) continue;
                s[i][j] = history->scacchiera[i][j];
            }
        }
        prepend(s);
        stampa(1);
        cout << endl;
    }

    void move_ped(int i1, int j1, int r, int c, int er, int ec){
        piece s[8][8];
        s[r][c] = history->scacchiera[i1][j1];
        s[i1][j1] = e;
        s[er][ec] = e;
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if ((i==r and j==c) or (i==i1 and j==j1) or (i==er and j==ec)) continue;
                s[i][j] = history->scacchiera[i][j];
            }
        }
        prepend(s);
        stampa(1);
        cout << endl;
    }

    void stampa (){
        list aux = history;
        int i=0;
        while (aux){
            cout << "history:  " << i << endl;
            for(int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    if (aux->scacchiera[i][j] == x) cout << "x";
                    if (aux->scacchiera[i][j] == o) cout << "o";
                    if (aux->scacchiera[i][j] == X) cout << "X";
                    if (aux->scacchiera[i][j] == O) cout << "O";
                    if (aux->scacchiera[i][j] == e) cout << " ";
                }
                cout << endl;
            }
            aux = aux->next;
            cout << endl;
            i++;
        }
    }

    void stampa (int i){
        list aux = history;
        for(int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (aux->scacchiera[i][j] == x) cout << "x";
                if (aux->scacchiera[i][j] == o) cout << "o";
                if (aux->scacchiera[i][j] == X) cout << "X";
                if (aux->scacchiera[i][j] == O) cout << "O";
                if (aux->scacchiera[i][j] == e) cout << " ";
            }
            cout << endl;
        }
    }
};

/* Costruttore: il costruttore accetta in input il tipo di giocatore (player1 oppure player2). 
Di default il giocatore è player1. L’intero player_nr serve a decidere quali pedine sono le proprie: 
- se player_nr = 1, il giocatore è player1 e quindi deve muovere le ‘x’ (vedi immagini precedenti). 
- Altrimenti, deve muovere le ‘o’.  
Se player_nr è diverso da 1 o 2, lanciare una player_exception con 
err_type uguale a index_out_of_bounds (e campo msg a scelta). 
Il costruttore inizializza una history vuota. */
/* COMPLETATO */
Player::Player(int player_nr){
    // errore out of bounds se il player non è nè 1 nè 2.
    if (player_nr!=1 and player_nr!=2) {
        player_exception pe;
        pe.t = player_exception::index_out_of_bounds;
        pe.msg = "Errore! Non è stato selezionato un giocatore valido (1 o 2)";
        throw pe;
    }
    else {
        // struct list che salva tutte le scacchiere, history punta alla testa
        pimpl=new Impl;
        pimpl->history = nullptr;
        pimpl->player_n = player_nr;
    }
}

/* Distruttore: attenzione a rilasciare correttamente le risorse allocate. 
Come avete capito, il vostro codice dovrà allocare dinamicamente della memoria quindi 
fate molta attenzione a questo aspetto (useremo valgrind per rilevare memory leaks).*/
/* COMPLETATO */
Player::~Player(){
    //deallocare tutte le scacchiere dinamiche
    pimpl->dealloc_history();
    //elimino infine tutto il pimpl
    delete pimpl;
}

/* Copy constructor: tutti i dati del Player in input vanno copiati nell’oggetto costruito. 
Attenzione ad allocare correttamente la memoria. */
/* COMPLETATO */
Player::Player(const Player& copied_player){
    //chiamo operatore di =
    *this = copied_player;
}

/* Copy assignment: tutti i dati del Player in input vanno copiati in this. 
Attenzione: non dimenticatevi di de-allocare la memoria di this prima di 
effettuare una nuova allocazione e copia. */
/* COMPLETATO (?) */
Player& Player::operator=(const Player& copied_player){
    // dealloco i dati di this
    pimpl->dealloc_history();
    //copio dati di copie_player in nuovo
    Impl::list aux = copied_player.pimpl->history;
    pimpl->player_n = copied_player.pimpl->player_n;
    while (aux){
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++) 
                pimpl->append(aux->scacchiera);        
        aux=aux->next;
    }
    return *this;
}


/* Operatore di accesso alla memoria del giocatore. 
Questo operatore restituisce la pedina contenuta in 
riga r e colonna c della “history_offset”-esima scacchiera più recente. 
Se la cella è vuota, restituire e (vedi enum piece). 
In altre parole, se history_offset=0 va restituita la pedina in coordinata (r,c) dell’ultima scacchiera vista; 
se history_offset=1 va restituita la pedina in coordinata (r,c) della penultima scacchiera vista ...
Lanciare una player_exception con campo err_type uguale a index_out_of_bounds (msg a scelta) 
se le coordinate (r,c,history_offset) non esistono in memoria. */
//COMPLETATO
Player::piece Player::operator()(int r, int c, int history_offset) const {
    if (r>7 or r<0 or c>7 or c<0){
        //exception in caso riga fuori posto
        if (r>7 or r<0){
            player_exception pe;
            pe.t = player_exception::index_out_of_bounds;
            pe.msg = "Errore! Valore di riga() fuori dai limiti";
            throw pe;
        }
        //exception in caso colonna fuori posto
        if (c>7 or c<0){
            player_exception pe;
            pe.t = player_exception::index_out_of_bounds;
            pe.msg = "Errore! Valore di colonna() fuori dai limiti";
            throw pe;
        }
    }
    //scorro fino a scacchiera giusta, finché esistono scacchiere
    Impl::list aux = pimpl->history;
    while (aux and history_offset>0) aux = aux->next;
    //exception se non esiste scacchiera con quell'offset
    if (history_offset>0 or !aux){
        player_exception pe;
        pe.t = player_exception::index_out_of_bounds;
        pe.msg = "Errore! Valore di offset() fuori dai limiti";
        throw pe;
    }
    switch (r)
    {
        case 0: r = 7;
            break;
        case 1: r = 6;
            break;
        case 2: r = 5;
            break;
        case 3: r = 4;
            break;
        case 4: r = 3;
            break;
        case 5: r = 2;
            break;
        case 6: r = 1;
            break;
        case 7: r = 0;
            break;
    }
    return aux->scacchiera[r][c];
}

/* NOTE MIE:
Il programma inizializza un file txt con init_board che contiene una scacchiera.txt con le posizioni iniziali, 
Chiama poi load_board per salvarla nell'ultima posizione di history
Il player dunque esegue la mossa, che viene salvata in una nuova scacchiera in ultima posizione di history aggiunta
Infine tale scacchiera (offset=0) viene salvata in un file txt tramite la store_board 
Per la presenza dell'offset, forse quindi conviene un'aggiunta in testa (prepend)*/

/* Caricamento da file (percorso “filename”) di una scacchiera. 
Si veda sezione 3.3 per il formato del file. 
La scacchiera caricata deve essere salvata nella posizione più recente della history del Player
(ossia, dopo il caricamento le sue pedine devono essere accessibili tramite operator()(r,c,0)). 
Se il file non esiste oppure se il formato del file è errato, oppure se la scacchiera caricata non è valida 
(esempio: troppe pedine, pedine su celle bianche, ecc …) lanciare una  
player_exception con err_type uguale a missing_file oppure invalid_board  
(a piacere. potete specificare meglio di che errore si tratta usando il campo msg che noi comunque non controlleremo). 
Attenzione: questa funzione non deve verificare la validità dell’ultima mossa! questa verifica è svolta da valid_move().*/
// almost 
void Player::load_board(const string& filename){
    ifstream board;
    board.open(filename, ios::in);

    if (filename.substr(filename.length()-4,4)!=".txt") {
        player_exception pe;
        pe.t = player_exception::invalid_board;
        pe.msg = "Errore! Formato file non valido";
        throw pe;
    }

    //MANCA ERRORE PER TROPPE PEDINE etc etc

    piece s[8][8];
    if (board.is_open()){
        string line;
        int i=0;
        while(getline(board, line)){
            int z=0;
            for (int j=0; j<8; j++){
                //NON MI RICORDO PIU' PERCHE' FUNZIONA, QUINDI RICONTROLLARE GLI INDICI DI Z
                if (z%2!=0) z++;
                if ((i+j)%2!=0 and line[z]!=' ') {
                    player_exception pe;
                    pe.t = player_exception::invalid_board;
                    pe.msg = "Errore! Ci sono pedine in celle bianche";
                    throw pe;
                }
                switch (line[z])
                {
                    case 'x': s[i][j] = x;
                        break;
                    case 'o': s[i][j] = o;
                        break;
                    case 'X': s[i][j] = X;
                        break;
                    case 'O': s[i][j] = O;
                        break;
                    case ' ': s[i][j] = e;
                        break;
                }
                z++;
            }
            ++i;
        }
        pimpl->prepend(s);
        board.close();
    }
}

/* Salvataggio di una scacchiera su file (al percorso “filename”). 
Se il file esiste già, sovrascriverlo. Deve venire salvata la “history-offset”-esima scacchiera più recente 
(ossia, se history-offset=0, la più recente; se history-offset=1 la penultima, e così via). 
Se history_offset è più lungo della history, lanciare una player_exception con err_type uguale a index_out_of_bounds. */
// COMPLETATO(?)
void Player::store_board(const string& filename, int history_offset)const {
    //scorro fino a scacchiera giusta, finché esistono scacchiere
    Impl::list aux = pimpl->history;
    while (aux and history_offset>0) aux = aux->next;
    //exception se non esiste scacchiera con quell'offset
    if (history_offset>0 or !aux){
        player_exception pe;
        pe.t = player_exception::index_out_of_bounds;
        pe.msg = "errore! valore di offset in store_board fuori dai limiti";
        throw pe;
    }

    fstream board;
    board.open(filename, ios::out);
    if (board.is_open()){
        for(int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (aux->scacchiera[i][j] == 0) board << "x";
                if (aux->scacchiera[i][j] == 1) board << "o";
                if (aux->scacchiera[i][j] == 2) board << "X";
                if (aux->scacchiera[i][j] == 3) board << "O";
                if (aux->scacchiera[i][j] == 4) board << " ";
                if (j<7) board << " ";
            }
            if (i<7) board << "\n";
        }
        board.close();
    }
}

/* Questa funzione deve: creare una nuova scacchiera (con i pezzi in posizione iniziale, vedi immagine in pagina 1) 
e infine salvare su file la nuova scacchiera. Nota: la funzione non deve salvare la scacchiera in history. 
Se il file esiste già sovrascriverlo (altrimenti, crearne uno nuovo). */
// COMPLETATO
void Player::init_board(const string& filename) const {
    ofstream board;
    board.open(filename, ios::out);
    piece s[8][8];
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

    if (board.is_open()){
        for(int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (s[i][j] == 0) board << "x";
                if (s[i][j] == 1) board << "o";
                if (s[i][j] == 2) board << "X";
                if (s[i][j] == 3) board << "O";
                if (s[i][j] == 4) board << " ";
                if (j<7) board << " ";
            }
            if (i<7) board << "\n";
        }
        board.close();
    }
}

/* Questa è la funzione che implementa la vostra strategia. La funzione deve eseguire una mossa sulle vostre pedine 
(per il turno: vedi costruttore) e aggiungere la scacchiera risultante nella posizione più recente della history del giocatore. 
Le scacchiere già presenti precedentemente nella history non vanno modificate! Chiaramente, 
se la mossa prevede l’eliminazione di una pedina dell’avversario, 
questa pedina non deve essere presente nella scacchiera risultante (va eliminata): 
sta a voi implementare correttamente il cambio di stato della scacchiera in seguito alla mossa! 
(ossia, aggiungere in history la scacchiera risultante dalla mossa). 
Attenzione: noi verificheremo che la vostra classe effettui mosse valide, 
quindi la nuova scacchiera in history deve essere ottenibile dalla precedente tramite una mossa. 
E’ possibile non effettuare alcuna mossa (ossia aggiungere una scacchiera identica alla precedente), 
ma questo porta a perdere la partita. Ricordate che, se un giocatore raggiunge la riga opposta con un pezzo di tipo “Pedina”, 
questo pezzo va obbligatoriamente promosso a “Dama” (la mancata promozione è considerata una mossa non valida). 
Se la history è vuota, lanciare una player_exception con err_type uguale a index_out_of_bounds.

Suggerimento: se siete incerti su quale mossa effettuare (o se non c’è una mossa che possa portare un evidente beneficio), 
usate la randomness (rand()), ossia scegliete un vostro pezzo a caso e muovetelo a caso (ovviamente in una cella valida). 
Questo ridurrà le possibilità che la partita entri in loop. Se siete bloccati (ossia non potete effettuare nessuna mossa), 
fate una mossa “vuota” e aggiungete in history una scacchiera identica alla precedente (questo fa perdere la partita, 
il che è corretto dato che l’avversario vi ha bloccati). */
void Player::move(){
    if (!pimpl->history){
        player_exception pe;
        pe.t=player_exception::index_out_of_bounds;
        pe.msg="history vuota";
        throw pe;
    }
    //prendi prima pedina a caso e vedi se può muoversi, se sì fai prima mossa disponibile
    if (pimpl->player_n == 1){
        pimpl->player_n = 2;
        cout << "turno di x" << endl;
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (pimpl->history->scacchiera[i][j] == x or pimpl->history->scacchiera[i][j] == X){
                    if (pimpl->check_above(i,j) == 's') {
                        pimpl->move_ped(i, j, i-1, j-1);
                        return;
                        }
                    if (pimpl->check_above(i,j) == 'S') {
                        pimpl->move_ped(i, j, i-2, j-2, i-1, j-1);
                        return;
                        }
                    if (pimpl->check_above(i,j) == 'd') {
                        pimpl->move_ped(i, j, i-1, j+1);
                        return;
                        }
                    if (pimpl->check_above(i,j) == 'D') {
                        pimpl->move_ped(i, j, i-2, j+2, i-1, j+1);
                        return;
                        }

                    if (pimpl->history->scacchiera[i][j] == X){
                        if (pimpl->check_below(i,j) == 's') {
                            pimpl->move_ped(i, j, i+1, j-1);
                            return;
                            }
                        if (pimpl->check_below(i,j) == 'S') {
                            pimpl->move_ped(i, j, i+2, j-2, i+1, j-1);
                            return;
                            }
                        if (pimpl->check_below(i,j) == 'd') {
                            pimpl->move_ped(i, j, i+1, j+1);
                            return;
                            }
                        if (pimpl->check_below(i,j) == 'D') {
                            pimpl->move_ped(i, j, i+2, j+2, i+1, j+1);
                            return;
                            }
                    }
                }
            }
        }
        pimpl->prepend(pimpl->history->scacchiera);
    }
    else {
        pimpl->player_n = 1;
        cout << "turno di o" << endl; 
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (pimpl->history->scacchiera[i][j] == o or pimpl->history->scacchiera[i][j] == O){
                    if (pimpl->check_below(i,j) == 's') {
                        pimpl->move_ped(i, j, i+1, j-1);
                        return;
                        }
                    if (pimpl->check_below(i,j) == 'S') {
                        pimpl->move_ped(i, j, i+2, j-2, i+1, j-1);
                        return;
                        }
                    if (pimpl->check_below(i,j) == 'd') {
                        pimpl->move_ped(i, j, i+1, j+1);
                        return;
                        }
                    if (pimpl->check_below(i,j) == 'D') {
                        pimpl->move_ped(i, j, i+2, j+2, i+1, j+1);
                        return;
                        }

                    if (pimpl->history->scacchiera[i][j] == X){
                        if (pimpl->check_above(i,j) == 's') {
                            pimpl->move_ped(i, j, i-1, j-1);
                            return;
                            }
                        if (pimpl->check_above(i,j) == 'S') {
                            pimpl->move_ped(i, j, i-2, j-2, i-1, j-1);
                            return;
                            }
                        if (pimpl->check_above(i,j) == 'd') {
                            pimpl->move_ped(i, j, i-1, j+1);
                            return;
                            }
                        if (pimpl->check_above(i,j) == 'D') {
                            pimpl->move_ped(i, j, i-2, j+2, i-1, j+1);
                            return;
                            }
                    }
                }
            }
        }
        pimpl->prepend(pimpl->history->scacchiera);
    }
    //manca promozione
}

/* Questa funzione compara le due scacchiere più recenti nella history (l’ultima e la penultima) e 
decide se la mossa corrispondente è valida, ossia se la penultima scacchiera può essere trasformata nell’ultima 
attraverso una mossa valida. Nota: la mossa potrebbe essere stata eseguita da uno qualsiasi dei due giocatori, 
non necessariamente da voi.

Alcuni casi particolari:  
- Se le ultime due scacchiere sono identiche la mossa è considerata non valida (serve a fare perdere un giocatore che 
non ha eseguito una mossa durante il proprio turno).  DONE
- Se la penultima scacchiera è quella iniziale (succede al secondo turno di una partita), 
  valid_move() dovrebbe controllare che l’ultima scacchiera corrisponda ad una mossa del player 1 (x). 
  Non verificheremo questa funzionalità all’esame.
- Se ci sono meno di due scacchiere in history, va lanciata una player_exception con err_type uguale a index_out_of_bounds. DONE

Vedi doc per ulteriori spiegazioni */
bool Player::valid_move() const {
    if (!pimpl->history or !pimpl->history->next){
        player_exception pe;
        pe.t=player_exception::index_out_of_bounds;
        pe.msg="valid_move chiamata su history minore di 2";
        throw pe;
    }

    //check che sia stata mossa x come prima mossa
    if (!pimpl->history->next->next){
        //check che sia mossa di x
    }

    Impl::list aux = pimpl->history;
    bool check = true;
    for(int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            if (aux->scacchiera[i][j] != pimpl->history->scacchiera[i][j]) check = false; //se le scacchiere sono diverse
    if (check) return false; //se le scacchiere sono uguali ritorna false

    //check movimento legale

    //check promozione
    
    return true;
}

/* La funzione rimuove dalla history la scacchiera più recente. Se la funzione viene chiamata su una history vuota, 
va lanciata una player_exception con err_type uguale a index_out_of_bounds. */
//COMPLETATO(?)
void Player::pop(){
    if (!pimpl->history){
        player_exception pe;
        pe.t=player_exception::index_out_of_bounds;
        pe.msg="pop chiamata su history vuota";
        throw pe;
    }
    Impl::list aux = pimpl->history;
    pimpl->history=pimpl->history->next;
    delete aux;
}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è vincente per il giocatore numero player_nr. 
Se player_nr è diverso da 1 o 2 oppure se la history è vuota, lanciare una player_exception con err_type uguale a index_out_of_bounds. 
In questa funzione (e nelle successive tre) basta controllare solo se un giocatore ha finito le pedine; 
non serve verificare la validità della mossa rispetto alla precedente (per questo abbiamo la funzione valid_move()), 
nè se uno dei due giocatori è bloccato (in questa situazione, alla prossima mossa il giocatore bloccato 
può solo aggiungere una scacchiera identica o non valida, e quindi perde automaticamente). */
//COMPLETATO(?)
bool Player::wins(int player_nr) const {
    if (player_nr!=1 and player_nr!=2) {
        player_exception pe;
        pe.t = player_exception::index_out_of_bounds;
        pe.msg = "errore! wins non ha selezionato un giocatore valido (1 o 2)";
        throw pe;
    }
    piece pl1, pl2;
    if (pimpl->player_n==2) {
        pl1 = (piece)0;
        pl2 = (piece)2;
    }
    else{
        pl1 = (piece)1;
        pl2 = (piece)3;
    }
    for(int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            if (pimpl->history->scacchiera[i][j] == pl1 or 
                pimpl->history->scacchiera[i][j] == pl2) return false;

    return true;
}
 
/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è vincente per il 
giocatore associato all’istanza corrente (this) di Player. Se la history è vuota, 
lanciare una player_exception con err_type uguale a index_out_of_bounds. */
//COMPLETATO(?)
bool Player::wins() const {
    if (!pimpl->history){
        player_exception pe;
        pe.t=player_exception::index_out_of_bounds;
        pe.msg="wins chiamata su history vuota";
        throw pe;
    }
    return wins(pimpl->player_n);
}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è perdente per il 
giocatore numero player_nr. Se player_nr è diverso da 1 o 2 oppure se la history è vuota, 
lanciare una player_exception con err_type uguale a index_out_of_bounds. */
//COMPLETATO(?)
bool Player::loses(int player_nr) const {
    if (player_nr!=1 and player_nr!=2) {
        player_exception pe;
        pe.t = player_exception::index_out_of_bounds;
        pe.msg = "errore! loses non ha selezionato un giocatore valido (1 o 2)";
        throw pe;
    }
    if (player_nr==1) return wins(2);
    else return wins (1);
}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è perdente per il 
giocatore associato all’istanza corrente (this) di Player. Se la history è vuota, 
lanciare una player_exception con err_type uguale a index_out_of_bounds. */
//COMPLETATO(?)
bool Player::loses() const {
    if (!pimpl->history){
        player_exception pe;
        pe.t=player_exception::index_out_of_bounds;
        pe.msg="loses chiamata su history vuota";
        throw pe;
    }
    return loses(pimpl->player_n);
}

/* Restituire quante volte la scacchiera più recente compare nella history. 
Per esempio, se la history contiene le scacchiere A, B, C, B, D, B, E, B 
(dove A,B,C,D,E sono scacchiere distinte e la più recente è quella più a destra), 
allora la funzione deve restituire 4 perchè la scacchiera più recente (B) compare 4 volte nella history.
Se la history è vuota, lanciare una player_exception con err_type uguale a index_out_of_bounds. */
// COMPLETATO (?)
int Player::recurrence() const {
    if (!pimpl->history){
        player_exception pe;
        pe.t=player_exception::index_out_of_bounds;
        pe.msg="recurrance chiamata su history vuota";
        throw pe;
    }
    int res=0;
    Impl::list aux = pimpl->history->next;
    int i = 0;
    while (aux){
        bool equal = true;
        while (i<8 and equal){
            for (int j=0; j<8; j++) {
                if (pimpl->history->scacchiera[i][j]!=aux->scacchiera[i][j]) 
                    equal = false;
            }
            ++i;
        }
        if (equal) ++res;
        aux = aux->next;
    }
    return res;
}

int main(){
    Player p(1);

    try{
        string board_name =  "board_1.txt";		
        p.init_board(board_name);
        p.load_board(board_name);
        while(!p.wins()) p.move();
    }
    catch (player_exception pe){
        cout << pe.msg << endl;
    }   

    return 0;
}