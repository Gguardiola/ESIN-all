#include <iostream>
#include <sstream>
#include <string>
using namespace std;

typedef unsigned int nat;

template <typename Clau>
class dicc {

    public:
        // Constructora per defecte. Crea un diccionari buit.
        dicc(): _arrel(NULL) {};

        // Les tres grans: Constructora per còpia, destructora, operador d’assignació
        dicc(const dicc &d);
        ~dicc();
        dicc<Clau>& operator=(const dicc<Clau> &d);

        // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
        void insereix(const Clau &k);

        // Elimina la clau k del diccionari. Si no hi era, no fa res.
        void elimina(const Clau &k);

        // Consulta si la clau k està en el diccionari.
        bool consulta(const Clau &k) const;

        // Retorna quants elements (claus) té el diccionari.
        nat quants() const;

        // Impressió per cout de claus del diccionari en ordre ascendent, separades per
        // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
        // Imprimeix totes les claus
        void print() const;

        // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
        void print_interval(const Clau &k1, const Clau &k2) const;

        // Retorna la clau més petita i la més gran respectivament.
        // Pre: El diccionari no està buit
        Clau min() const;
        Clau max() const;

        // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
        // Pre: El diccionari no està buit. 1 <= i <= quants()
        Clau iessim(nat i) const;

    private:

        struct node{
            node* f_esq;
            node* f_dret;
            Clau info;
            nat total;
        };
        node* _arrel;

        node* insereix(node* p, const Clau &k, bool &add);
        node* elimina(node* p, const Clau &k, bool &elim);
        
        static void  interval(node* p, const Clau &k1, const Clau &k2, string &s);

        static node* elimina_aux(node* p, node* q);
        
        static void  elimina_nodes(node* p);
        static node* copia_nodes(node* p);

        static void  inordre(node* p, string &s);

        // void print_aux(node* arrel, string pre) const;

        // void print2() const;

};

// Destructora
template <typename Clau>
dicc<Clau>::~dicc(){ // O(n)
    elimina_nodes(_arrel);
}

// Constructor per còpia
template <typename Clau> // O(n)
dicc<Clau>::dicc(const dicc<Clau> &c){
    _arrel = copia_nodes(c._arrel);
    _arrel->total = c._arrel->total;
}

template <typename Clau> // O(n) = n
typename dicc<Clau>::node* dicc<Clau>::copia_nodes(node* p){

    node* n = new node;
    if(p != NULL){
        try{
            n->info = p->info;
            n->f_esq = copia_nodes(p->f_esq);
            n->f_dret = copia_nodes(p->f_dret);
        }
        catch(...){
            delete n;
            throw;
        }
    }
    else n = NULL;
    
    return n;
}

// Operador d'assignació
template <typename Clau> // O(n) = n
dicc<Clau>& dicc<Clau>::operator=(const dicc<Clau> &d){

    if(this != &d){
        node* aux = copia_nodes(d._arrel);
        elimina_nodes(_arrel);
        _arrel = aux;
    }

    return *this;
}

template <typename Clau> // O(n) = n
void dicc<Clau>::elimina_nodes(node* p){

    if(p != NULL){
        elimina_nodes(p->f_esq);
        elimina_nodes(p->f_dret);
        delete p;
    }

}

// Insereix la clau k en el diccionari. Si ja hi era, no fa res.
template <typename Clau> // O(n) = log(n) ≈ h
void dicc<Clau>::insereix(const Clau &k){
    bool add = false;
    _arrel = insereix(_arrel,k,add);
}

template <typename Clau> // O(n) = log(n) ≈ h
typename dicc<Clau>::node* dicc<Clau>::insereix(node* p, const Clau &k, bool &add){

    if(p == NULL){
        node* q = new node;
        q->info = k;
        q->f_esq = NULL;
        q->f_dret = NULL;
        q->total = 1;
        add = true;
        return q;
    }
    else{
        if(k < p->info) p->f_esq = insereix(p->f_esq,k,add);
        else if(k > p->info) p->f_dret = insereix(p->f_dret,k,add);
        if(add) p->total++;
    }

    return p;
}

// Elimina la clau k del diccionari. Si no hi era, no fa res.
template <typename Clau>
void dicc<Clau>::elimina(const Clau &k){
    bool elim = false;
    _arrel = elimina(_arrel,k,elim);
    // cout << endl;
    // print2();
}

template <typename Clau> //
typename dicc<Clau>::node* dicc<Clau>::elimina(node* p, const Clau &k, bool &elim){

    if(p != NULL){

        if(k > p->info) {
            p->f_dret = elimina(p->f_dret,k,elim);
            if(elim and p != NULL) p->total--;
        }
        else if (k < p->info) {
            p->f_esq = elimina(p->f_esq,k,elim);
            if(elim and p != NULL) p->total--;
        }
        else{
            elim = true;
            if(p->f_esq == NULL and p->f_dret == NULL){
                delete p;
                p = NULL;
            }
            else if(p->f_esq != NULL and p->f_dret == NULL){
                node* del = p;
                p = p->f_esq;
                delete del;
            }
            else if(p->f_esq == NULL and p->f_dret != NULL){
                node* del = p;
                p = p->f_dret;
                delete del;
            }
            else if(p->f_esq != NULL and p->f_dret != NULL){
                p = elimina_aux(p,NULL);
                if(elim and p != NULL) p->total--;
            }
        }

    }

    return p;
}

template <typename Clau>
typename dicc<Clau>::node* dicc<Clau>::elimina_aux(node* p, node* q){

    node* n = p;
    n = n->f_dret;

    while(n->f_esq != NULL){
        q = n;
        n = n->f_esq;
    }

    p->info = n->info;

    if(n->f_dret != NULL and q == NULL) p->f_dret = n->f_dret;
    else if(n->f_dret != NULL and q != NULL)  q->f_esq = n->f_dret;
    else if(n->f_dret == NULL and q == NULL){
        p->total--;
        p->f_dret = NULL;
    }
    else if(n->f_dret == NULL and q != NULL){
        q->total--;
        q->f_esq = NULL;
    }

    delete n;
    return p;
}   

// Consulta si la clau k està en el diccionari.
template <typename Clau> // O(n) = log(n) ≈ h
bool dicc<Clau>::consulta(const Clau &k) const{

    bool trobat = false;
    node* p = _arrel;

    while(p != NULL and not trobat){
        if(p->info > k) p = p->f_esq;
        else if(p->info < k) p = p->f_dret;
        else trobat = true;
    }

    return trobat;
}

// Retorna quants elements (claus) té el diccionari.
template <typename Clau> // O(n) = 1
nat dicc<Clau>::quants() const{
    if(_arrel != NULL) return _arrel->total;
    else return 0;
}

// Impressió per cout de claus del diccionari en ordre ascendent, separades per
// un espai, començant per ’[’ i acabant per ’]’, en dues versions:
// Imprimeix totes les claus
template <typename Clau> // O(n) = n
void dicc<Clau>::print() const{
    
    string s = "";
    inordre(_arrel,s);
    if(s.size() > 0) s.pop_back(); // O(1)
    
    if(s.size() > 0) cout << "[" + s + "]";
    else cout << "[]";

    // cout << endl;
    // print2();
}

template <typename Clau> // O(n) = n
void dicc<Clau>::inordre(node* p, string &s){

    if(p != NULL){
        inordre(p->f_esq,s);
        s += (to_string(p->info)+" ");
        inordre(p->f_dret,s);
    }

}

// Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2) const{

    string s = "";
    interval(_arrel,k1,k2,s);
    if(s.size() > 0) s.pop_back();

    if(s.size() > 0) cout << "[" + s + "]";
    else cout << "[]";

}

template <typename Clau>
void dicc<Clau>::interval(node* p, const Clau &k1, const Clau &k2, string &s){

    if(p != NULL){

        if(k1 < p->info) interval(p->f_esq,k1,k2,s);
        if((p->info >= k1) and (p->info <= k2)) s += (to_string(p->info)+" ");
        if(k2 > p->info) interval(p->f_dret,k1,k2,s);

    }

}

// Retorna la clau més petita i la més gran respectivament.
// Pre: El diccionari no està buit
template <typename Clau> // O(n) = log(n) ≈ h
Clau dicc<Clau>::min() const{

    node* p = _arrel;
    while(p->f_esq != NULL) p = p->f_esq;
    return p->info;

}

template <typename Clau> // O(n) = log(n) ≈ h
Clau dicc<Clau>::max() const{

    node* p = _arrel;
    while(p->f_dret != NULL) p = p->f_dret;
    return p->info;

}

// Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
// Pre: El diccionari no està buit. 1 <= i <= quants()
template <typename Clau> // O(n) = log(n)
Clau dicc<Clau>::iessim(nat i) const{

    Clau C;

    nat c = 0;
    node* p = _arrel;
    bool stop = false;

    if(p->f_dret != NULL) c = p->total - p->f_dret->total;
    else c = p->total;

    while(p != NULL and not stop){

        if(c > i){
            p = p->f_esq;
            if(p != NULL){
                if(p->f_dret != NULL) c = c - p->f_dret->total - 1;
                else c--;
            } 
        }
        else if (c < i){
            p = p->f_dret;
            if(p != NULL){
                if(p->f_esq != NULL) c = c + p->f_esq->total + 1;
                else c++;
            }
        }
        else if(c == i){
            stop = true;
            C = p->info;
        }

    }

    return C;
}

// template <typename Clau>
// void dicc<Clau>::print2() const{

//     print_aux(_arrel,"");

// }

// template <typename Clau>
// void dicc<Clau>::print_aux(node* arrel, string pre) const{

//     if(arrel != NULL){

//         cout << "[" << arrel->info << "|" << arrel->total << "]\n" << pre << " \\__";
//         print_aux(arrel->f_dret,pre + " |  ");
//         cout << "\n" << pre << " \\__";
//         print_aux(arrel->f_esq,pre + "    ");

//     }
//     else cout << ".";

// }

int main(){
    string linea, comanda;;
    int n, n1, n2;
    while (getline(cin, linea)) {
        
        dicc<int> d;

        // Obtenim elements 1er diccionari
        istringstream ss1(linea);
        while (ss1 >> n) d.insereix(n);
        
        d.print(); cout << endl;

        // Processem comandes
        while (getline(cin, linea) and linea != "----------") {
            
            cout << linea << ": ";
            istringstream ss2(linea);
            ss2 >> comanda;

            if (comanda == "insereix") {
                ss2 >> n;
                d.insereix(n);
                cout << d.quants();
            } 
            else if (comanda == "elimina") {
                ss2 >> n;
                d.elimina(n);
                cout << d.quants();
            } 
            else if (comanda == "consulta") {
                ss2 >> n;
                cout << d.consulta(n);
            } 
            else if (comanda == "quants") cout << d.quants();

            else if (comanda == "print") d.print();
    
            else if (comanda == "print_interval") {
                ss2 >> n1 >> n2;
                d.print_interval(n1, n2);
            } 
            else if (comanda == "min") cout << d.min();

            else if (comanda == "max") cout << d.max();
            
            else if (comanda == "iessim") {
                ss2 >> n;
                cout << d.iessim(n);
            }
            cout<<endl;
            
        }
        if (linea == "----------")
        cout << linea << endl;
    }
}