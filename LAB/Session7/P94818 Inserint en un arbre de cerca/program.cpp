#include <iostream>
#include <cstddef>
#include <vector>
#include <string>

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

        static node* insereix(node* p, const T &c);

        static void  print_aux(node* arrel, string pre);

        static void  inordre_especular(node* p, string esp, int n);

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

        void insereix(const T &c);

        void print();
        void print_XD();
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
void Abin<T>::inordre_especular(node* p, string esp, int n){

    if(p != NULL){
        inordre_especular(p->f_dret,esp, n+1);
        for(unsigned int i = 0; i < (n*10-(to_string(p->info)).length()); i++) cout << esp;
        cout << p->info << endl; 
        inordre_especular(p->f_esq,esp, n+1);
    }

}


template <typename T>
void Abin<T>::print_XD(){
    inordre_especular(_arrel," ",1);
}


template <typename T>
typename Abin<T>::node* Abin<T>::insereix(node* p, const T &c){

    if(p == NULL){
        node* q = new node;
        q->info = c;
        q->f_esq = NULL;
        q->f_dret = NULL;
        return q;
    }
    else if(c < p->info) p->f_esq = insereix(p->f_esq,c);
    else if(c > p->info) p->f_dret = insereix(p->f_dret,c);

    return p;
}

template <typename T>
void Abin<T>::insereix(const T &c){

    _arrel = insereix(_arrel,c);

} 

int main(){

    Abin<int> A;
    int n = 0;
    while(cin >> n) A.insereix(n);

    A.print_XD();

}