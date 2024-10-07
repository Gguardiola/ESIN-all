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
    // Si la lista está vacía o tiene un solo elemento, ya está ordenada
    if (_prim == nullptr || _prim->seg == nullptr) return;

    // Divide la lista en dos mitades usando el método de dos punteros
    node* lento = _prim;
    node* rapido = _prim->seg;

    // Encontrar el punto medio de la lista
    while (rapido != nullptr && rapido->seg != nullptr) {
        lento = lento->seg;
        rapido = rapido->seg->seg;
    }

    // `lento` ahora es el punto medio de la lista
    node* mitad = lento->seg; // Segunda mitad de la lista
    if (mitad != nullptr) {
        mitad->ant = nullptr;  // Desconectar la primera mitad de la segunda
    }
    lento->seg = nullptr;     // Desconectar la primera mitad

    // Crear dos listas para las mitades
    Llista primeraMitad;
    primeraMitad._prim = _prim; // Primera mitad
    primeraMitad._ult = lento;
    primeraMitad._long = _long / 2;

    Llista segundaMitad;
    segundaMitad._prim = mitad; // Segunda mitad
    segundaMitad._ult = _ult;
    segundaMitad._long = _long - primeraMitad._long;

    // Ordenar cada mitad recursivamente
    primeraMitad.ordena();
    segundaMitad.ordena();

    // Fusionar ambas mitades ordenadas
    _prim = merge(primeraMitad._prim, segundaMitad._prim);

    // Actualizar _ult y _long
    _ult = _prim;
    while (_ult && _ult->seg != nullptr) {
        _ult = _ult->seg;
    }
    _long = primeraMitad._long + segundaMitad._long;
}

Llista::node* Llista::merge(node* l1, node* l2) {
    // Nodo temporal para crear la lista fusionada
    node dummy;
    node* tail = &dummy; // Usar un nodo dummy como cabeza de la lista fusionada
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

    // Si quedan elementos en alguna de las listas, los adjuntamos al final
    if (l1 != nullptr) {
        tail->seg = l1;
        l1->ant = tail;
    } else if (l2 != nullptr) {
        tail->seg = l2;
        l2->ant = tail;
    }

    return dummy.seg; // Retornamos la lista fusionada
}

