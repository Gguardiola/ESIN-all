
#include <iostream>
 #include <vector>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename Clau>
 class dicc {
   public:
     dicc() : _arrel(NULL) {};
     // Pre: Cert
     // Post: El resultat és un dicc sense cap element
 
     ~dicc();
     // Pre: Cert
     // Post: El dicc ha estat destruït
 
     pair<Clau, char> insereix(const Clau &k);
     // Pre: Cert
     // Post: La clau k s’ha inserit en el diccionari si no hi era. Retorna la clau dels nodes
     // visitats a on hi ha el desequilibri més proper a les fulles i un caràcter amb el seu
     // tipus de desequilibri: ’E’: Esquerre, ’D’: Dret, ’ ’: No s’ha trobat cap desequilibri
 
   private:
     struct node {
       Clau _k;      // Clau
       node* _esq;   // fill esquerre
       node* _dret;  // fill dret
       nat _h;       // Altura del subarbre
     };
     node *_arrel;
 
     static void esborra_nodes(node* m);
     pair<Clau, char> insereix(node*& n, const Clau& k, bool& desequilibri_trobat);
     static nat altura(node* n);
     // Aquí va l’especificació dels mètodes privats addicionals
 };
 
 // Aquí va la implementació dels mètodes públics i privats

template <typename Clau>
nat dicc<Clau>::altura(node* n) {
    return n == NULL ? 0 : n->_h;
}

template <typename Clau>
pair<Clau, char> dicc<Clau>::insereix(const Clau &k) {
    bool desequilibri_trobat = false;
    return insereix(_arrel, k, desequilibri_trobat);
}

template <typename Clau>
pair<Clau, char> dicc<Clau>::insereix(node*& n, const Clau& k, bool& desequilibri_trobat) {
    if (n == NULL) {
        n = new node{k, NULL, NULL, 1};
        return {k, ' '};
    }

    pair<Clau, char> desequilibri;
    if (k < n->_k) {
        desequilibri = insereix(n->_esq, k, desequilibri_trobat);
    } else if (k > n->_k) {
        desequilibri = insereix(n->_dret, k, desequilibri_trobat);
    } else {
        return {k, ' '}; // La clau ja existeix
    }

    // Actualitza l'altura del node actual
    n->_h = 1 + max(altura(n->_esq), altura(n->_dret));

    // Comprova desequilibris si encara no s'ha trobat cap
    if (!desequilibri_trobat) {
        int balance = altura(n->_esq) - altura(n->_dret);
        if (abs(balance) > 1) {
            desequilibri_trobat = true;
            return {n->_k, balance > 1 ? 'E' : 'D'};
        }
    }

    return desequilibri;
}




template <typename Clau>
void dicc<Clau>::esborra_nodes(node* m) {
  if (m != NULL) {
    esborra_nodes(m->_esq);
    esborra_nodes(m->_dret);
    delete m;
  }
}

template <typename Clau>
dicc<Clau>::~dicc() {
  esborra_nodes(_arrel);
}


int main() {
  int n;
  dicc<int> d;
  while (cin >> n) {
    vector<int> v;
    pair<int, char> desq = d.insereix(n);
    cout << "insereix " << n << ':';
    if (desq.second != ' ') {
      cout << ' ' << desq.first << ' ' << desq.second;
    }
    cout << endl;
  }
  return 0;
}
