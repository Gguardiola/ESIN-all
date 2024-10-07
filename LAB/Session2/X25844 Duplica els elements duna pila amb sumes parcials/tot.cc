
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned int nat;

// Donada la classe pila que permet apilar elements en una estructura simplement encadenada en memòria dinàmica, cal implementar el mètode

//      void duplica_amb_sumes();
// que, a partir d’una pila qualsevol, duplica els elements de la pila posant a sobre de cada element un nou element que conté la suma dels elements restants de la pila original (la suma dels elements fins arribar al fons de la pila original). Pots veure exemples en els jocs de prova públics.

// Cal enviar a jutge.org la següent especificació de la classe pila i la implementació del mètode dins del mateix fitxer. La resta de mètodes públics i privats ja estan implementats. Indica dins d’un comentari a la capçalera del mètode el seu cost en funció del nombre d’elements n de la pila.

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

    void duplica_amb_sumes();
    // Pre: true
    // Post: S’han duplicat els elements de la pila, a sobre de cada element hi ha un
    // nou element que conté la suma dels elements restants de la pila original

private:
    struct node {
    T info;
    node* seg;
    };
    node* _cim; // Apunta al cim de la pila
    nat _mida;  // Nombre d’elements de la pila

    // Aquí va l’especificació dels mètodes privats addicionals
};

// Aquí va la implementació del mètode duplica_amb_sumes i dels privats addicionals
template <typename T>
void pila<T>::duplica_amb_sumes() {
    if (_cim == nullptr) return;  // Caso de pila vacía

    // Fase 1: Calcular la suma total de los elementos
    T suma_total = 0;
    node* p = _cim;
    while (p != nullptr) {
        suma_total += p->info;
        p = p->seg;
    }

    // Fase 2: Duplicar la pila con las sumas
    p = _cim;  // Reiniciar el puntero a la cima de la pila
    node* nuevo_cim = nullptr;  // Nueva cima de la pila duplicada
    node* ultimo_nuevo = nullptr; // Para conectar los nuevos nodos

    while (p != nullptr) {
        // Crear el nuevo nodo que contendrá la suma de los elementos restantes
        node* n = new node;
        n->info = suma_total;  // Sumar el total hasta el momento
        n->seg = p;  // Conectar el nuevo nodo al nodo original

        // Actualizar la nueva cima de la pila
        if (nuevo_cim == nullptr) {
            nuevo_cim = n;  // Si es el primer nodo, establecerlo como cima
        } else {
            ultimo_nuevo->seg = n;  // Conectar el nodo nuevo al anterior
        }
        
        ultimo_nuevo = n;  // Mover el último nuevo nodo

        // Actualizar la suma total restando el valor del nodo actual
        suma_total -= p->info;

        // Mover al siguiente nodo en la pila original
        p = p->seg;
    }

    // Reasignar la cima de la pila y ajustar el tamaño
    _cim = nuevo_cim;
    _mida *= 2;  // Duplicar el tamaño de la pila
}
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

  pila<int> p(v1);
  cout << p.longitud() << " ";
  p.mostra();
  p.duplica_amb_sumes();
  cout << p.longitud() << " ";
  p.mostra();
  return 0;
}
