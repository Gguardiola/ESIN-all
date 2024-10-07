
#include "llista.hpp"
#include <iostream>

// Separació dels elements de les posicions parells i senars d'una llista simplement encadenada

// Donada la classe Llista que permet guardar seqüències d’enters amb una llista simplement encadenada, sense fantasma i no circular, cal implementar el mètode

//  void separa(Llista &l2)
// que a partir d’una llista l2 buida, separa els elements del paràmetre implícit quedant al paràmetre implícit els elements de les posicions senars i a l2 els de les posicions parells.

// Cal enviar a jutge.org només la implementació del mètode separa. La classe Llista té la següent especificació:

// Per testejar la solució, jutge.org ja té implementats la resta de mètodes de la classe Llista i un programa principal que processa línies d’enters amb els que crea llistes i desprès crida el mètode separa.

// Entrada

// L’entrada conté vàries línies formades per seqüències d’enters. Cadascuna d’elles són els elements que tindrà cada llista.

// Sortida

// Per a cada línia d’entrada, escriu una línia amb el resultat desprès d’haver separat els elements de les posicions senars i parells de la llista: Per cada llista mostra el nombre d’elements de la llista seguit d’un espai i dels elements de la llista entre claudàtors i separats per espais.

void Llista::separa(Llista &l2) {
    node *p = _prim;       // Puntero a la lista original
    node *pant = nullptr;  // Puntero anterior a la lista original
    node *p2 = nullptr;    // Puntero a la nueva lista (l2)
    nat i = 1;             // Contador de posición

    while (p != nullptr) {
        if (i % 2 == 0) { // Si es una posición par
            if (p2 == nullptr) { // Si l2 está vacía
                l2._prim = p; // Asignar el primer nodo de l2
            } else {
                p2->seg = p; // Conectar el nodo a l2
            }
            p2 = p; // Avanzar en l2
            if (pant != nullptr) {
                pant->seg = p->seg; // Conectar el anterior al siguiente
            } else {
                _prim = p->seg; // Actualizar el inicio de la lista original
            }
            p = p->seg; // Avanzar en la lista original
            p2->seg = nullptr; // Terminar la lista l2
        } else { // Si es una posición impar
            pant = p; // Actualizar el puntero anterior
            p = p->seg; // Avanzar en la lista original
        }
        i++;
    }

    // Actualizar el tamaño de las listas
    _long = (i + 1) / 2; // Actualizamos el tamaño de la l
}



