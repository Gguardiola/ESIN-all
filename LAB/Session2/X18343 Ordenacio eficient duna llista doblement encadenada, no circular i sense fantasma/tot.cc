#include <cstddef>
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned int nat;

class Llista {
public:
    Llista();
    Llista(const vector<int> &v);
    ~Llista();
    nat longitud() const;
    void mostra() const;
    void mostra_invertida() const;
    void ordena();

private:
    struct node {
        int info;  // Información del nodo
        node *seg; // Puntero al siguiente elemento
        node *ant; // Puntero al anterior elemento
    };
    node *_prim; // Puntero al primer elemento
    node *_ult;  // Puntero al último elemento
    nat _long;   // Número de elementos

    // Método privado para fusionar dos listas ordenadas
    node* merge(node* l1, node* l2);
};

void Llista::ordena() {
    // Coste temporal: O(n log n)
    // Raonament: El Merge Sort divideix la llista en dues meitats, ordena cadascuna recursivament
    // i les fusiona. Cada divisió és O(log n) i la fusió és O(n), resultant en O(n log n) en total.

    if (_prim == nullptr || _prim->seg == nullptr) return; // Si la lista está vacía o tiene un solo elemento

    // Divide la lista en dos mitades
    node* meio = _prim;
    node* final = _prim;

    // Utilizamos el método de dos punteros para encontrar el medio
    while (final != nullptr && final->seg != nullptr) {
        meio = meio->seg;
        final = final->seg->seg;
    }

    // `meio` es el punto medio de la lista
    node* mitad = meio->seg; // Guardamos la segunda mitad
    meio->seg = nullptr; // Romper la lista en dos mitades

    // Crear dos listas para las mitades
    Llista primeraMitad;
    primeraMitad._prim = _prim; // Primera mitad
    primeraMitad._ult = meio;
    primeraMitad._long = longitud() / 2;

    Llista segundaMitad;
    segundaMitad._prim = mitad; // Segunda mitad
    if (mitad) {
        mitad->ant = nullptr; // Asegurarse de que el puntero anterior de la segunda mitad sea nulo
    }
    segundaMitad._ult = _ult;
    segundaMitad._long = _long - primeraMitad._long;

    // Ordenar cada mitad recursivamente
    primeraMitad.ordena();
    segundaMitad.ordena();

    // Fusionar ambas mitades
    _prim = merge(primeraMitad._prim, segundaMitad._prim);
    
    // Actualizar _ult y _long
    _ult = _prim; 
    while (_ult && _ult->seg != nullptr) _ult = _ult->seg; // Manejar caso donde _ult sea nulo
    _long = primeraMitad._long + segundaMitad._long;
}

Llista::node* Llista::merge(node* l1, node* l2) {
    // Función auxiliar para fusionar dos listas ordenadas
    node dummy; // Nodo temporal
    node* tail = &dummy; // Usar el nodo dummy como cabeza
    dummy.seg = nullptr; // Inicializamos el puntero siguiente de dummy

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->info > l2->info) {
            tail->seg = l1;
            l1->ant = tail; // Actualiza el puntero anterior
            l1 = l1->seg;
        } else {
            tail->seg = l2;
            l2->ant = tail; // Actualiza el puntero anterior
            l2 = l2->seg;
        }
        tail = tail->seg;
    }

    // Adjuntar el resto
    tail->seg = (l1 != nullptr) ? l1 : l2; 
    if (tail->seg) { // Actualizar el puntero anterior del resto
        tail->seg->ant = tail;
    }

    return dummy.seg; // Retornar la lista fusionada
}


#include <iostream>
#include <sstream>

Llista::Llista() : _long(0) {
  _ult = _prim = nullptr;
}

Llista::Llista(const vector<int> &v) : _long(v.size()) {
  _prim = nullptr;
  node *p(nullptr), *pant(nullptr);
  for (nat i=0; i<v.size(); i++) {
    p = new node;
    p->info = v[i];
    p->seg = nullptr;
    p->ant = pant;
    if (pant != nullptr)
      pant->seg = p;
    else
      _prim = p;
    pant = p;
  }
  _ult = p;
}

Llista::~Llista() {
  node *p(_prim), *pelim;
  while (p != nullptr) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
}

nat Llista::longitud() const {
  return _long;
}

void Llista::mostra() const {
  node *p = _prim;
  cout << "[";
  if (p != nullptr) {
    cout << p->info;
    p = p->seg;
  }
  while (p != nullptr) {
    cout << " " << p->info;
    p = p->seg;
  }
  cout << "]";
}

void Llista::mostra_invertida() const {
  node *p = _ult;
  cout << "[";
  if (p != nullptr) {
    cout << p->info;
    p = p->ant;
  }
  while (p != nullptr) {
    cout << " " << p->info;
    p = p->ant;
  }
  cout << "]";
}

int main() {
  string linea;
  while (getline(cin, linea)) {
    vector<int> v;
    istringstream ss(linea);
    int n;
    while (ss >> n) {
      v.push_back(n);
    }
    Llista l(v);
    l.ordena();
    cout << l.longitud() << " ";
    l.mostra();
    cout << " ";
    l.mostra_invertida();
    cout << endl;
  }
  return 0;
}
