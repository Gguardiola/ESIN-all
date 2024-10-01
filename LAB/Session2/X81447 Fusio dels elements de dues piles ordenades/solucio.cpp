#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned int nat;
 
template <typename T>
class pila { // pila en memòria dinàmica
  public:
    pila();
    // Crea pila buida

    ~pila();
    // Destrueix el p.i.

    pila(const vector<int> &v);
    // Crea pila amb els elements de v amb el mateix ordre.

    nat longitud() const;
    // Retorna el nombre d’elements del p.i.

    void mostra() const;
    // Mostra el p.i. pel canal estàndard de sortida.

    void fusiona(const pila<T> &p2);
    // Pre: Les piles del p.i. i p2 estan ordenades de menor a major
    // Post: Al p.i. se li han afegit els elements de p2 ordenadament. p2 no es modifica

  private:
    struct node {
      T info;
      node* seg;
    };
    node* _cim; // Apunta al cim de la pila
    nat _mida;  // Nombre d’elements de la pila

    // Aquí va l’especificació dels mètodes privats addicionals
};

// Aquí va la implementació del mètode públic fusiona i privats addicionals
template <typename T>
void pila<T>::fusiona(const pila<T> &p2) {
  vector<int> temp1 = {1,2,3,4,5,6};
  pila<int> newPila(temp1);
  newPila._cim = p2._cim;
}