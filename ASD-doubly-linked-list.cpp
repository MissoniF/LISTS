// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// FILE DA MODIFICARE

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
    Elem info;
    node *prev;
    node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

void readFromStream(istream& str, List& l) {
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    // assumiamo che il segnale di fine input nel file sia  FINEINPUT
    while (e != FINEINPUT)  {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
    }
}

/* legge il contenuto di una lista da file */
void readFromFile(string nome_file, List& l) {
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}


/* legge il contenuto di una lista da standard input */
void readFromStdin(List& l) {
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}

/* stampa la lista */
void print(const List& l) {
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l) {   // avanza finche' non finisce la lista
      cout << q->info << "; ";
      q = q->next; 
    }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

/* crea la lista vuota */
void list::createEmpty(List& l) {
   l = new node;
   l->prev = l->next = l;
}

/* "smantella" la lista svuotandola */
void list::clear(const List& l) {
   List q = l->next;
   List aux;
   while(q != l){
      aux = q;
      q = q->next;
      delete aux;
   }
   l->prev = l->next = l;
}

/* restituisce l'elemento in posizione pos se presente; restituisce un elemento 
che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
Elem list::get(int pos, const List& l) {
   int size = list::size(l);
   if(pos<0 || pos>=size) return list::EMPTYELEM;
   if(pos==(size-1)) return (l->prev)->info;
   List aux = l->next;
   int counter = 0;
   while(counter != pos){
      counter++;
      aux = aux->next;
   }
   if(aux->next == l)
      return l->info;
   return aux->info;
}

/* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
void list::set(int pos, Elem e, const List& l) {
   int size = list::size(l);
   if(pos<0 || size<pos) cout << "-- POS FUORI RANGE!!\n";
   List q = l->next;
   int counter = 1;
   while(counter != pos){
      q = q->next;
      counter++;
   }
   q->info = e;
}

/* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void list::add(int pos, Elem e, const List& l) {                                               
   int size = list::size(l);
   if(pos<0 || (size-1)<pos) {cout << "-- POS FUORI RANGE!!\n"; return;}
   List aux = new node;
   aux->info = e;
   List q = l->next;
   int counter = 1;
   while(counter != pos){
      q = q->next;
      counter++;
   }
   aux->prev = q;
   aux->next = q->next;
   q->next = aux;
   aux->next->prev = aux;
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem e,  const List& l) {
   List aux = new node;
   aux->info = e;
   List q = l->next;
   while(q->next != l)
      q = q->next;
   q->next = aux;
   aux->next = l;
   l->prev = aux;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem e, const List& l) {
   List aux = new node;
   aux->info = e;
   if(isEmpty(l)){
      l->next = aux;
      l->prev = aux;
      aux->next = l;
   }
   
   else {
      List tmp = l->next;
      l->next = aux;
      aux->next = tmp;
   }
}

/* cancella l'elemento in posizione pos dalla lista */
void list::removePos(int pos, const List& l) {
   int size = list::size(l);
   if(pos<0 || pos>size) cout << "-- POS FUORI RANGE!!\n";
   List q = l->next;
   int counter = 1;
   while(counter != pos){
      q = q->next;
      counter++;
   }
   if(q != l){
   q->next->prev = q->prev;
   q->prev->next = q->next;
   delete q;
   }
}

 /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
void list::removeEl(Elem e, const List& l) {
   List q = l->next;
   while(q != l)
      if(q->info == e){
         q->next->prev = q->prev;
	 q->prev->next = q->next;
	 delete q;
      }
}

/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const List& l) {
   return (l->next == l);
}

 /* restituisce la dimensione della lista */
int list::size(const List& l) {
   int counter = 0;
   List aux = l->next;
   while(aux != l){
      counter++;
       aux = aux->next;
      }
   return counter;
}
