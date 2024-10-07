 
 #include <iostream>
 #include <vector>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename T>
 class cua { // Cua no circular en memòria dinàmica
   public:
     cua();
     // Construeix una cua buida.
 
     ~cua();
     // Destrueix el p.i.
 
     cua(const vector<int> &v);
     // Crea cua amb els elements de v amb el mateix ordre.
 
     nat longitud() const;
     // Retorna el nombre d’elements del p.i.
 
     void mostra() const;
     // Mostra el p.i. pel canal estàndard de sortida.
 
     void fusiona(const cua<T> &c2);
     // Pre: Les cues del p.i. i c2 estan ordenades de menor a major
     // Post: Al p.i. se li han afegit els elements de c2 ordenadament. c2 no es modifica
 
   private:
     struct node {
       T info;
       node* seg;
     };
     node* _pri; // Apunta al primer element de la cua
     node* _ult; // Apunta al darrer element de la cua
     nat _mida;
 
     // Aquí va l’especificació dels mètodes privats addicionals
 };
 
 // Aquí va la implementació del mètode públic fusiona i privats addicionals
template <typename T>
void cua<T>::fusiona(const cua<T> &c2) {
    node *p = _pri;         // Puntero a la primera cola (this)
    node *paux = c2._pri;   // Puntero a la segunda cola (c2)
    node *pant = nullptr;   // Puntero al nodo anterior

    // Si la primera cola está vacía, simplemente copiar todos los elementos de la segunda cola
    if (_mida == 0) {
        for (nat i = 0; i < c2._mida; i++) {
            node *pnew = new node;
            if (pant == nullptr) {
                _pri = pnew;  // Establecer el nuevo nodo como primer nodo si no hay anterior
            } else {
                pant->seg = pnew;  // Conectar el nodo anterior al nuevo nodo
            }
            pnew->info = paux->info;  // Copiar el valor del nodo
            pant = pnew;  // Actualizar el nodo anterior

            // Avanzar al siguiente nodo de la segunda cola
            if (paux->seg != nullptr) paux = paux->seg;
            else                      _ult = pnew;  // Actualizar el último nodo
        }
    }
    // Si la segunda cola está vacía, no hay nada que hacer
    else if (c2._mida == 0) {
        return;
    }
    // Si ambas colas tienen elementos, fusionarlas
    else {
        while (paux != nullptr) {
            // Si hemos alcanzado el final de la primera cola o el valor del nodo de c2 es menor o igual
            if (p == nullptr || paux->info <= p->info) {
                node *pnew = new node;
                pnew->info = paux->info;

                if (pant == nullptr) {
                    // Insertar al principio si no hay nodo anterior
                    pnew->seg = _pri;
                    _pri = pnew;
                } else {
                    // Insertar en el medio o al final
                    pant->seg = pnew;
                    pnew->seg = p;
                }

                paux = paux->seg;  // Avanzar en la segunda cola
                pant = pnew;

                // Si la primera cola está vacía, actualizar el último nodo
                if (p == nullptr) {
                    _ult = pnew;
                }
            } 
            // Si el nodo de la primera cola es menor, simplemente avanzamos
            else {
                pant = p;
                p = p->seg;
            }
        }

        // Si aún quedan elementos en la segunda cola (paux no es nullptr)
        if (p == nullptr && paux != nullptr) {
            // Conectar el último nodo de la primera cola con el primer nodo restante de la segunda cola
            pant->seg = paux;
            _ult = c2._ult;  // Actualizar el último nodo
        }
    }

    // Actualizar el tamaño de la cola fusionada
    _mida = _mida + c2._mida;
}
#include <sstream>

template <typename T>
cua<T>::cua() : _pri(NULL), _ult(NULL), _mida(0) {}

template <typename T>
cua<T>::~cua() {
  while (_pri != NULL) {
    node* aux = _pri;  
    _pri = _pri->seg;
    delete aux;
  }
}

template <typename T>
cua<T>::cua(const vector<int> &v) : _pri(NULL), _ult(NULL), _mida(v.size()) {
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
    if (pant == NULL)
      _pri = p;
    else
      pant->seg = p;
    pant = p;
  }
  if (v.size() > 0) { // Arreglem darrer element
    p->seg = NULL;
    _ult = p;
  }
}

template <typename T>
nat cua<T>::longitud() const {
  return _mida;
}

template <typename T>
void cua<T>::mostra() const {
  node *p = _pri;
  cout << "[";
  if (p != NULL) {
    while (p != _ult) {
      cout << p->info << " ";
      p = p->seg;
    }
    cout << p->info;
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

  cua<int> c1(v1);
  cua<int> c2(v2);
  c1.fusiona(c2);
  cout << c1.longitud() << " ";
  c1.mostra();
  cout << c2.longitud() << " ";
  c2.mostra();
  return 0;
}
