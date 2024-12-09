#include <iostream>
#include <cstddef>
#include <vector>

using namespace std;
typedef unsigned int nat;

template <typename T>
class Abin {

    private:

        struct node {
            node* f_esq;
            node* f_dret;
            T info;
        };
        node* _arrel;
        
        static node* copia_nodes(node* m);
        static void  esborra_nodes(node* m);

        static bool  existeix(node* p, const T &c);

    public:

        //constructors
        Abin(): _arrel(NULL) {};
        /* Pre: cert */
        /* Post: el resultat és un arbre sense cap element */
        Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
        /* Pre: cert */
        /* Post: el resultat és un arbre amb un element i dos subarbres */

        // Les tres grans
        Abin(const Abin<T> &a);
        ~Abin();
        Abin<T>& operator=(const Abin<T>& a);

        bool existeix(const T &c);

        void print_aux(node* arrel, string pre);
        void print();
};

template <typename T>
Abin<T>::~Abin() {
    esborra_nodes(_arrel);
};

template <typename T>
Abin<T>::Abin(const Abin<T> &a) {
    _arrel = copia_nodes(a._arrel);
};

template <typename T>
Abin<T>::Abin(Abin<T>& ae, const T& x, Abin<T>& ad) {
    _arrel = new node;
    try {
        _arrel->info = x;
    }
    catch (...) {
        delete _arrel;
        throw;
    }
    _arrel->f_esq = ae._arrel;
    ae._arrel = NULL;
    _arrel->f_dret = ad._arrel;
    ad._arrel = NULL;
}

template <typename T>
Abin<T>& Abin<T>::operator=(const Abin<T>& a) {
  if (this != &a) {
        node* aux;
        aux = copia_nodes(a._arrel);
        esborra_nodes(_arrel);
        _arrel = aux;
  }
  return (*this);
};


template <typename T>
void Abin<T>::print(){

    print_aux(_arrel,"");
    cout << endl;

}

template <typename T>
void Abin<T>::print_aux(node* arrel, string pre){

    if(arrel != NULL){

        cout << "[" << arrel->info << "]\n" << pre << " \\__";
        print_aux(arrel->f_dret,pre + " |  ");
        cout << "\n" << pre << " \\__";
        print_aux(arrel->f_esq,pre + "    ");

    }
    else cout << ".";

}

template <typename T>
typename Abin<T>::node* Abin<T>::copia_nodes(node* m){

    node* n;
    if (m == NULL) n = NULL;
    else {
        n = new node;
        try {
            n->info = m->info;
            n->f_esq = copia_nodes(m->f_esq);
            n->f_dret = copia_nodes(m->f_dret);
        } catch(...) {
            delete n;
            throw;
        }
    }
    return n;
};

template <typename T>
void Abin<T>::esborra_nodes(node* m) {
    if (m != NULL) {
        esborra_nodes(m->f_esq);
        esborra_nodes(m->f_dret);
        delete m;
    }
};

template <typename T>
bool Abin<T>::existeix(node* p, const T &c){

    bool trobat = false;

    if(p != NULL and not trobat){

        trobat = (c == p->info);
        if(not trobat){

            if(c > p->info) trobat = existeix(p->f_dret,c);
            else if(c < p->info) trobat = existeix(p->f_esq,c);
            
        }

    }

    return trobat;
}

template <typename T>
bool Abin<T>::existeix(const T &c){

    return existeix(_arrel,c);
}

Abin<int> llegir(){

    Abin<int> A, A1, A2;
    int n = 0; cin >> n;

    if(n != -1){
        A1 = llegir();
        A2 = llegir();
        A = Abin<int>(A1,n,A2);
    }

    return A;
}

int main(){

    int z = 0; cin >> z;

    Abin<int> A(llegir());
    // A.print();

    int c = 0;
    while(cin >> c) cout << c << (A.existeix(c) ? " 1\n" : " 0\n");

}