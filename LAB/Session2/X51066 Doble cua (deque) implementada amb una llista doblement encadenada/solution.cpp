#include <cstddef>
using namespace std;
typedef unsigned int nat;

// Pots veure exemples de cada mètode en els jocs de prova públics. Cal enviar a jutge.org la següent especificació de la classe deque i la implementació dels quatre mètodes anteriors dins del mateix fitxer (la resta de mètodes públics ja estan implementats en el fitxer main.cc). Indica dins d’un comentari a la capçalera de cada mètode el seu cost en funció del nombre d’elements n de la deque.
template <typename T>
class deque {
public:
    deque();
    // Pre: True
    // Post: El p.i. és una deque buida.

    deque(const deque &dq);
    // Pre: True
    // Post: El p.i. conté una còpia de dq.

    ~deque();
    // Post: Destrueix els elements del p.i.

    nat size() const;
    // Pre: True
    // Post: Retorna el nombre d’elements de la deque.

    bool empty() const;
    // Pre: True
    // Post: Retorna true si la deque és buida; false en cas contrari.

    T front() const;
    // Pre: La deque no és buida.
    // Post: Retorna el primer element de la deque.

    T rear() const;
    // Pre: La deque no és buida.
    // Post: Retorna l’últim element de la deque.

    void push(T e);
    // Pre: True
    // Post: Insereix un element al davant de la deque.

    void inject(T e);
    // Pre: True
    // Post: Insereix un element al darrera de la deque.

    void pop();
    // Pre: La deque no és buida.
    // Post: Elimina el primer element de la deque.

    void eject();
    // Pre: La deque no és buida.
    // Post: Elimina l’últim element de la deque.

private:
/* Double-ended queue implementada amb una llista doblement encadenada,
    sense fantasma i no circular. */
    struct node {
    T info;    // Informació del node
    node *seg; // Punter al següent element
    node *ant; // Punter a l’anterior element
    };
    node *_prim; // Punter al primer element
    node *_ult;  // Punter a l’últim element
    nat _long;   // Nombre d’elements

    // Aquí va l’especificació dels mètodes privats addicionals
};

template <typename T>
void deque<T>::push(T e) {
    node *n = new node;
    n->info = e;
    n->seg = _prim;
    n->ant = nullptr;

    if (_prim != nullptr) {
        _prim->ant = n;
    } else {
        // Si la cola estaba vacía, también actualizamos _ult
        _ult = n;
    }

    _prim = n;
    _long++;
}

template <typename T>
void deque<T>::inject(T e) {
    node *n = new node;
    n->info = e;
    n->seg = nullptr;
    n->ant = _ult;

    if (_ult != nullptr) {
        _ult->seg = n;
    } else {
        // Si la cola estaba vacía, también actualizamos _prim
        _prim = n;
    }

    _ult = n;
    _long++;
}

template <typename T>
void deque<T>::pop() {
    if (_long == 0) return;  // Evitamos eliminar si la cola está vacía

    node *n = _prim;
    _prim = _prim->seg;

    if (_prim != nullptr) {
        _prim->ant = nullptr;
    } else {
        // Si hemos eliminado el último nodo, también actualizamos _ult
        _ult = nullptr;
    }

    delete n;
    _long--;
}

template <typename T>
void deque<T>::eject() {
    if (_long == 0) return;  // Evitamos eliminar si la cola está vacía

    node *n = _ult;
    _ult = _ult->ant;

    if (_ult != nullptr) {
        _ult->seg = nullptr;
    } else {
        // Si hemos eliminado el último nodo, también actualizamos _prim
        _prim = nullptr;
    }

    delete n;
    _long--;
}

