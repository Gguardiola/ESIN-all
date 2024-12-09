#include <iostream>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename Clau>
 class dicc {
 
   public:
     // Constructora per defecte. Crea un diccionari buit.
     dicc();
 
     // Destructora
     ~dicc();
 
     // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
     void insereix(const Clau &k);
 
     // Retorna quants elements (claus) té el diccionari.
     nat quants() const;
 
     // Retorna la segona clau.
     // Pre: El diccionari té com a mínim 2 claus.
     Clau segona() const;
 
   private:
     struct node {
       Clau _k;      // Clau
       node* _esq;   // fill esquerre
       node* _dret;  // fill dret
       nat _n;       // Nombre de nodes del subarbre
       node(const Clau &k, node* esq = NULL, node* dret = NULL);
     };
     node *_arrel;
 
     static void esborra_nodes(node* m);
     static node* insereix_bst(node *n, const Clau &k, bool &ins);
     static const Clau& trobar_segona(const node* n);

     static const node* trobar_minim(const node* n);
     // Aquí va l’especificació dels mètodes privats addicionals
 };
 
 // Aquí va la implementació dels mètodes públics i privats

template <typename Clau>
const typename dicc<Clau>::node* dicc<Clau>::trobar_minim(const node* n) {
    while (n->_esq != NULL) {
        n = n->_esq;
    }
    return n;
}

template <typename Clau>
const Clau& dicc<Clau>::trobar_segona(const node* n) {
    const node* actual = n;
    const node* pare = NULL;

    // Recorremos hasta encontrar el nodo mínimo
    while (actual->_esq != NULL) {
        pare = actual;
        actual = actual->_esq;
    }

    // Si el nodo mínimo tiene hijo derecho, la segunda clave está en ese subárbol
    if (actual->_dret != NULL) {
        return trobar_minim(actual->_dret)->_k;
    }

    // Si no, la segunda clave es el valor del padre del nodo mínimo
    return pare->_k;
}

template <typename Clau>
Clau dicc<Clau>::segona() const {
    return trobar_segona(_arrel);
}


