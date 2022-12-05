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
    public:

        struct piece_list{
            piece scacchiera [8][8];
            piece_list* next;
        }; typedef piece_list list;

        list* history; 
        int player_n;
        
};

/* Costruttore: il costruttore accetta in input il tipo di giocatore (player1 oppure player2). 
Di default il giocatore è player1. L’intero player_nr serve a decidere quali pedine sono le proprie: 
- se player_nr = 1, il giocatore è player1 e quindi deve muovere le ‘x’ (vedi immagini precedenti). 
- Altrimenti, deve muovere le ‘o’.  
Se player_nr è diverso da 1 o 2, lanciare una player_exception con 
err_type uguale a index_out_of_bounds (e campo msg a scelta). 
Il costruttore inizializza una history vuota. */
/* COMPLETATO(?) */
Player::Player(int player_nr){
    
    // errore out of bounds se il player non è nè 1 nè 2.
    if (player_nr!=1 or player_nr!=2) {
        player_exception pe;
        pe.t = player_exception::index_out_of_bounds;
        pe.msg = "Errore! Non è stato selezionato un giocatore valido (1 o 2)";
        cout<<pe.msg;
    }
    else {
        // struct list che salva tutte le scacchiere, history punta alla testa
        pimpl->history = nullptr;
        pimpl->player_n = player_nr;
    }
}

/* Distruttore: attenzione a rilasciare correttamente le risorse allocate. 
Come avete capito, il vostro codice dovrà allocare dinamicamente della memoria quindi 
fate molta attenzione a questo aspetto (useremo valgrind per rilevare memory leaks).*/
/* COMPLETATO(?) */
Player::~Player(){
    //deallocare tutte le scacchiere dinamiche
    while (pimpl->history!=nullptr) {
		Player::Impl::list* pc = pimpl->history;
        pimpl->history = pimpl->history->next;
        delete pc;
	}
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
    while (pimpl->history!=nullptr) {
		Player::Impl::list* pc = pimpl->history;
        pimpl->history = pimpl->history->next;
        delete pc;
	}
    //copio dati di copie_player in nuovo
    pimpl->player_n = copied_player.pimpl->player_n;
    while (copied_player.pimpl->history){
        //creo nuovo e copio dati
        Player::Impl::list* nuovo = new Player::Impl::list;
        for (int i=0; i<8; i++)
            for (int j=0; j<8; j++) nuovo->scacchiera[i][j] = copied_player.pimpl->history->scacchiera[i][j];
        nuovo->next = nullptr;
        //assegno dati di nuovo a history, controllando che sia vuoto o meno
        if (!pimpl->history) pimpl->history=nuovo;
        else {
            while (pimpl->history) pimpl->history=pimpl->history->next;
            pimpl->history=nuovo;
        }
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
Player::piece Player::operator()(int r, int c, int history_offset) const {
    if (r>7 or r<0 or c>7 or c<0){
        //exception in caso riga fuori posto
        if (r>7 or r<0){
            player_exception pe;
            pe.t = player_exception::index_out_of_bounds;
            pe.msg = "Errore! Valore di riga fuori dai limiti";
            cout<<pe.msg;
        }
        //exception in caso colonna fuori posto
        if (c>7 or c<0){
            player_exception pe;
            pe.t = player_exception::index_out_of_bounds;
            pe.msg = "Errore! Valore di colonna fuori dai limiti";
            cout<<pe.msg;
        }
    }
    else {
        //scorro fino a scacchiera giusta, finché esistono scacchiere
        while (pimpl->history and history_offset>0) pimpl->history = pimpl->history->next;
        //exception se non esiste scacchiera con quel offset
        if (history_offset>0){
            player_exception pe;
            pe.t = player_exception::index_out_of_bounds;
            pe.msg = "Errore! Valore di offset fuori dai limiti";
            cout<<pe.msg;
        }
        else return pimpl->history->scacchiera[r][c];
    }
    return e;
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
void Player::load_board(const string& filename){
    

}

/* Salvataggio di una scacchiera su file (al percorso “filename”). 
Se il file esiste già, sovrascriverlo. Deve venire salvata la “history-offset”-esima scacchiera più recente 
(ossia, se history-offset=0, la più recente; se history-offset=1 la penultima, e così via). 
Se history_offset è più lungo della history, lanciare una player_exception con err_type uguale a index_out_of_bounds. */
void Player::store_board(const string& filename, int history_offset)const {

}

/* Questa funzione deve: creare una nuova scacchiera (con i pezzi in posizione iniziale, vedi immagine in pagina 1) 
e infine salvare su file la nuova scacchiera. Nota: la funzione non deve salvare la scacchiera in history. 
Se il file esiste già sovrascriverlo (altrimenti, crearne uno nuovo). */
void Player::init_board(const string& filename) const {
    fstream board;
    board.open(filename, ios::out); //da controllare se va bene usare ios
    if (board.is_open()){
        // da sostituire con i tipi piece
        board << "o   o   o   o  \n";
        board << "  o   o   o   o\n";
        board << "o   o   o   o  \n";
        board << "               \n";
        board << "               \n";
        board << "  x   x   x   x\n";
        board << "x   x   x   x  \n";
        board << "  x   x   x   x";
        board.close();
    }
    piece scacchiera[8][8];
    for(int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (i+j%2==0){
                if (i>=0 and i<=2) scacchiera[i][j] = o;
                else if (i>=5 and i<=7) scacchiera[i][j] = x;
                else scacchiera[i][j] = e;
            }
            else scacchiera[i][j] = e;
        }
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

}

/* Questa funzione compara le due scacchiere più recenti nella history (l’ultima e la penultima) e 
decide se la mossa corrispondente è valida, ossia se la penultima scacchiera può essere trasformata nell’ultima 
attraverso una mossa valida. Nota: la mossa potrebbe essere stata eseguita da uno qualsiasi dei due giocatori, 
non necessariamente da voi.

Alcuni casi particolari:  
Se le ultime due scacchiere sono identiche la mossa è considerata non valida (serve a fare perdere un giocatore che 
non ha eseguito una mossa durante il proprio turno).  
- Se la penultima scacchiera è quella iniziale (succede al secondo turno di una partita), 
  valid_move() dovrebbe controllare che l’ultima scacchiera corrisponda ad una mossa del player 1 (x). 
  Non verificheremo questa funzionalità all’esame.
- Se ci sono meno di due scacchiere in history, va lanciata una player_exception con err_type uguale a index_out_of_bounds.

Vedi doc per ulteriori spiegazioni */
bool Player::valid_move() const {
    // giocatore esegue mossa -> salva nella nuova scacchiera -> se non valida, giocatore squalificato

    return true;
}

/* La funzione rimuove dalla history la scacchiera più recente. Se la funzione viene chiamata su una history vuota, 
va lanciata una player_exception con err_type uguale a index_out_of_bounds. */
void Player::pop(){

}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è vincente per il giocatore numero player_nr. 
Se player_nr è diverso da 1 o 2 oppure se la history è vuota, lanciare una player_exception con err_type uguale a index_out_of_bounds. 
In questa funzione (e nelle successive tre) basta controllare solo  se un giocatore ha finito le pedine; 
non serve verificare la validità della mossa rispetto alla precedente (per questo abbiamo la funzione valid_move()), 
nè se uno dei due giocatori è bloccato (in questa situazione, alla prossima mossa il giocatore bloccato 
può solo aggiungere una scacchiera identica o non valida, e quindi perde automaticamente). */
bool Player::wins(int player_nr) const {

    return false;
}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è vincente per il 
giocatore associato all’istanza corrente (this) di Player. Se la history è vuota, 
lanciare una player_exception con err_type uguale a index_out_of_bounds. */
bool Player::wins() const {

    return false;
}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è perdente per il 
giocatore numero player_nr. Se player_nr è diverso da 1 o 2 oppure se la history è vuota, 
lanciare una player_exception con err_type uguale a index_out_of_bounds. */
bool Player::loses(int player_nr) const {

    return false;
}

/* Restituisce true se e solo se l’ultima scacchiera (la più recente) in history è perdente per il 
giocatore associato all’istanza corrente (this) di Player. Se la history è vuota, 
lanciare una player_exception con err_type uguale a index_out_of_bounds. */
bool Player::loses() const {

    return false;
}

/* Restituire quante volte la scacchiera più recente compare nella history. 
Per esempio, se la history contiene le scacchiere A, B, C, B, D, B, E, B 
(dove A,B,C,D,E sono scacchiere distinte e la più recente è quella più a destra), 
allora la funzione deve restituire 4 perchè la scacchiera più recente (B) compare 4 volte nella history.
Se la history è vuota, lanciare una player_exception con err_type uguale a index_out_of_bounds. */
int Player::recurrence() const {
    int res=0;

    return res;
}