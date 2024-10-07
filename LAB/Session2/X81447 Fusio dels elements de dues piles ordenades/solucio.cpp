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


// // Aquí va la implementació del mètode públic fusiona i privats addicionals

template <typename T>
void pila<T>::fusiona(const pila<T> &p2) {
  node *p = _cim;
  node *pant = nullptr;
  node *paux = p2._cim;

  if (_mida == 0) {
    for (nat i = 0; i < p2._mida; i++) {
      node *pnew = new node;
      if (pant == nullptr) {
        _cim = pnew;
      } else {
        pant->seg = pnew;
      }
      pnew->info = paux->info;
      pant = pnew;
      if (paux->seg != nullptr) paux = paux->seg;
    }
  }
  
  else if (p2._mida == 0) {
    return;
  }

  else {
    while (paux != nullptr) {
      if (p == nullptr || paux->info <= p->info) {
        node *pnew = new node;
        pnew->info = paux->info;

        if (pant == nullptr) { 
          pnew->seg = _cim;
          _cim = pnew;
        } else {
          pant->seg = pnew;
          pnew->seg = p;
        }

        paux = paux->seg;
        pant = pnew;
      } else {
        pant = p;
        p = p->seg;
      }
    }
  }

  _mida = _mida + p2._mida;
}


// template <typename T>
// void pila<T>::fusiona(const pila<T> &p2) {


  
//   node *p = _cim;
//   node *pant = nullptr;
//   node *paux = p2._cim;

//   if (_mida == 0){
//     for (nat i = 0; i < p2._mida; i++) {
//       node *pnew = new node;
//       if(pant == nullptr) {
//         _cim = pnew;
//       } else {
//         pant->seg = pnew;
//       }
//       pnew->info = paux->info;
//       pant = pnew;
//       if(paux->seg != nullptr) paux = paux->seg;
//     }
//   }

//   else if(p2._mida == 0) {
//     return;
//   }

//   else {
//     nat i = 0;
//     while(paux != nullptr && p != nullptr) {
//       // cout<<"-"<<endl;
//       if(paux->info > p->info) {
//         // cout<<"++"<<endl;
//         pant = p;
//         p = p->seg;
//         if (p == nullptr) {
//           node *pnew = new node;
//           pnew->info = paux->info;
//           pant->seg = pnew;
//           pnew->seg = nullptr;
//         }
//         // mostra();
        
//       } else if(paux->info <= p->info) {
//         // cout<<"+"<<endl;
//         node *pnew = new node;
//         if(pant == nullptr) _cim = pnew;
//         else                pant->seg = pnew;
//         pnew->seg = p;
//         pnew->info = paux->info;
//         if(paux->seg != nullptr) paux = paux->seg;
//         else                     paux = nullptr;
//         pant = p;
//         i++;
//         // mostra();
//       }

//     }

//     if(p == nullptr){
//       for (nat j = i; j < p2._mida; j++) {
//         node *pnew = new node;
//         pant->seg = pnew;
//         pnew->info = paux->info;
//         pant = pnew;
//         if(paux->seg != nullptr) paux = paux->seg;
//       }
//     }
    
//   }

//   _mida = _mida + p2._mida;

// }

// cj_2enters::cj_2enters(const cj_2enters &cj) {
//   _size = cj._size;
//   _first = nullptr;
//   node *pc2 = cj_first, *pc1=nullptr;
//   while(pc2 !=nullptr) {
//     node *pn = new node;
//     pn->info = pc2->info;
//     pn->next = nullptr;
//     if(pc1 == nullptr) _first = pn;
//     else                pc1->next = pn;

//     pc1 = pn;
//     pc2 = pc2->next;
//   }

//   _last = pc1;
// }
