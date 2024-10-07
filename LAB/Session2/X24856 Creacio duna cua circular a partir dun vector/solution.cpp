#include <sstream>
#include <iostream>
#include <vector>
#include "cua.hpp"
using namespace std;
typedef unsigned int nat;

// Donada la classe cua que permet guardar seqüències d’enters amb una cua simplement encadenada, sense fantasma i circular, cal implementar el mètode constructor

//  cua(const vector<int> &v)
// que crea una cua amb els elements del vector v amb el mateix ordre.

// Cal enviar a jutge.org només la implementació del mètode constructor. La classe cua té la següent especificació:

cua::cua(const vector<int> &v){

    _ult = nullptr;
    _long = 0;
    for (nat i = 0; i < v.size(); i++) {
        node *n = new node;
        n->info = v[i];
        if (_ult == nullptr) {
            n->seg = n;
            _ult = n;
        } else {
            n->seg = _ult->seg;
            _ult->seg = n;
            _ult = n;
        }
        _long++;
    }

}