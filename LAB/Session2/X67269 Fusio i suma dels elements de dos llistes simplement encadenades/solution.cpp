
#include "llista.hpp"
#include <iostream>

// Donada la classe Llista que permet guardar seqüències d’enters amb una llista simplement encadenada, sense fantasma i no circular, cal implementar el mètode

//  void fusiona_suma(Llista &l2, nat n);
// que fusiona els elements del paràmetre implícit i de l2 agafant n elements del paràmetre implícit i n elements de l2 alternativament (o els que quedin si n’hi ha menys de n). Al principi del paràmetre implícit s’afegeix un nou element que conté la suma de tots els elements del paràmetre implícit i l2. La llista l2 queda buida.

// Per exemple, si inicialment tenim aquestes dues llistes:

//   p.i. [2 5 3 8 4]
//   l2   [1 6 9]    
// desprès de cridar fusiona_suma amb n=2, les dues llistes quedaran així:

//   p.i. [38 2 5 1 6 3 8 9 4]
//   l2   []
// Pots veure més exemples en els jocs de prova públics. Cal enviar a jutge.org només la implementació del mètode fusiona_suma. Indica dins d’un comentari a la capçalera del mètode el seu cost en funció del nombre d’elements n1 de la llista del p.i. i nombre d’elements n2 de la llista l2.

// Per testejar la solució, jutge.org ja té implementats la resta de mètodes de la classe Llista i un programa principal que processa línies d’enters amb els que crea dues llistes i desprès crida vàries vegades el mètode fusiona_suma amb diferents valors de n.

// Entrada

// L’entrada conté dues línies formades per seqüències d’enters, són els elements que tindran les dues llistes inicials. A continuació segueix una seqüència d’enters que representen diferents valors de n.

// Sortida

// Per a cada valor n d’entrada es fusionen i es sumen els elements de les dues llistes inicials agafant alternativament n elements de cadascuna i s’escriu tres línies: El valor n, el contingut de la primera llista i el contingut de la segona llista. Per cada llista s’escriu el nombre d’elements de la llista seguit d’un espai i dels elements de la llista entre claudàtors i separats per espais.
void Llista::fusiona_suma(Llista &l2, nat n) {
    // Fase 1: Calcular la suma total de los elementos de ambas listas
    int suma_total = 0;
    node* p1 = _prim;
    node* p2 = l2._prim;

    // Sumar elementos de la primera lista
    while (p1 != nullptr) {
        suma_total += p1->info;
        p1 = p1->seg;
    }

    // Sumar elementos de la segunda lista
    while (p2 != nullptr) {
        suma_total += p2->info;
        p2 = p2->seg;
    }

    // Fase 2: Insertar la suma total al principio de la primera lista
    node* new_node = new node;
    new_node->info = suma_total;
    new_node->seg = _prim;
    _prim = new_node;

    // Aumentamos la longitud de la lista original por el nodo añadido
    _long++; 

    // Fase 3: Fusionar elementos de ambas listas
    p1 = _prim->seg;  // Saltamos el nodo de la suma total
    p2 = l2._prim;
    node* prev = _prim; // Puntero al último nodo fusionado en la lista principal
    int count = 0;      // Contador para rastrear cuántos elementos se han fusionado

    while (p1 != nullptr || p2 != nullptr) {
        // Tomar 'n' elementos de la primera lista
        for (nat i = 0; i < n && p1 != nullptr; ++i) {
            prev->seg = p1;   // Conectar al nodo actual de la primera lista
            prev = p1;        // Avanzar el puntero de fusión
            p1 = p1->seg;     // Avanzar en la lista original
            count++;
        }
        
        // Tomar 'n' elementos de la segunda lista
        for (nat i = 0; i < n && p2 != nullptr; ++i) {
            prev->seg = p2;   // Conectar al nodo actual de la segunda lista
            prev = p2;        // Avanzar el puntero de fusión
            p2 = p2->seg;     // Avanzar en la lista l2
            count++;
        }
    }

    // Terminar la lista correctamente
    prev->seg = nullptr;

    // Actualizamos la longitud de la lista original sumando la cantidad de elementos fusionados
    _long += count; 

    // Vaciar la lista l2
    l2._prim = nullptr;
    l2._long = 0;
}
