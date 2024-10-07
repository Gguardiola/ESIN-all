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

template <typename T>
void pila<T>::fusiona(const pila<T> &p2) {
  node *p = _cim;
  node *pant = nullptr;
  node *paux = p2._cim;

  // Si la pila implícita está vacía, simplemente copiar los elementos de p2
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
  
  // Si p2 está vacía, no hacemos nada
  else if (p2._mida == 0) {
    return;
  }

  // Si ambas pilas tienen elementos, hacer la fusión
  else {
    while (paux != nullptr) {
      if (p == nullptr || paux->info <= p->info) {
        // Insertar el nodo de p2 en la pila implícita
        node *pnew = new node;
        pnew->info = paux->info;

        if (pant == nullptr) { // Caso especial para insertar al principio
          pnew->seg = _cim;
          _cim = pnew;
        } else {
          pant->seg = pnew;
          pnew->seg = p;
        }

        // Avanzar paux (pila p2)
        paux = paux->seg;
        pant = pnew;
      } else {
        // Avanzar en la pila implícita
        pant = p;
        p = p->seg;
      }
    }
  }

  // Actualizar la longitud de la pila
  _mida = _mida + p2._mida;
}


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

#include <sstream>

template <typename T>
pila<T>::pila() : _cim(NULL), _mida(0) {}

template <typename T>
pila<T>::~pila() {
  while (_cim != NULL) {
    node* aux = _cim;  
    _cim = _cim->seg;
    delete aux;
  }
}

template <typename T>
pila<T>::pila(const vector<int> &v) : _cim(NULL), _mida(v.size()) {
  node *p, *pant = NULL;
  for (nat i=0; i<v.size(); i++) {
    p = new node;
    try {
      p->info = v[i];
    } catch (const char* message) {
      cerr << message << endl;
      delete p;
      throw;
    }
    p->seg = NULL;
    if (pant == NULL)
      _cim = p;
    else
      pant->seg = p;
    pant = p;
  }
}

template <typename T>
nat pila<T>::longitud() const {
  return _mida;
}

template <typename T>
void pila<T>::mostra() const {
  node *p = _cim;
  cout << "[";
  if (p != NULL) {
    cout << p->info;
    p = p->seg;
    while (p != NULL) {
      cout << " " << p->info;
      p = p->seg;
    }
  }
  cout << "]" << endl;
}

int main() {
  int n;
  string linea;

  // Obtenim v1
  vector<int> v1;
  getline(cin, linea);
  istringstream ss1(linea);
  while (ss1 >> n) {
    v1.push_back(n);
  }

  // Obtenim v2
  vector<int> v2;
  getline(cin, linea);
  istringstream ss2(linea);
  while (ss2 >> n) {
    v2.push_back(n);
  }

  pila<int> p1(v1);
  pila<int> p2(v2);
  p1.fusiona(p2);
  cout << p1.longitud() << " ";
  p1.mostra();
  cout << p2.longitud() << " ";
  p2.mostra();
  return 0;
}
