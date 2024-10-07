
#include "llista.hpp"
#include <iostream>

// Donada la classe Llista que permet guardar seqüències d’enters amb una llista simplement encadenada, amb fantasma i no circular, cal implementar el mètode constructor

//  Llista(const vector<int> &v)
// que crea una llista amb els elements del vector v amb el mateix ordre.

// Per testejar la solució, jutge.org ja té implementats la resta de mètodes de la classe Llista i un programa principal que processa línies d’enters amb els que crear vectors i posteriorment llistes.

// Entrada

// L’entrada conté vàries línies formades per seqüències d’enters. Cadascuna d’elles són els elements que tindrà el vector amb el que es construirà cada llista.

// Sortida

// Per a cada línia d’entrada, escriu una línia amb el resultat: El nombre d’elements de la llista seguit d’un espai i dels elements de la llista entre claudàtors i separats per espais.

Llista::Llista(const vector<int> &v) {
    _prim = new node;  // Nodo fantasma
    _prim->seg = nullptr;
    _prim->info = 0;   // El nodo fantasma tiene info irrelevante
    _long = 0;

    node *actual = _prim;  // Apuntamos al nodo fantasma

    for (nat i = 0; i < v.size(); i++) {
        node *n = new node;  // Crear un nuevo nodo
        n->info = v[i];      // Asignar valor del vector
        n->seg = nullptr;
        actual->seg = n;     // Conectar el nodo nuevo a la lista
        actual = n;          // Mover el puntero al último nodo
        _long++;             // Incrementar longitud
    }
}