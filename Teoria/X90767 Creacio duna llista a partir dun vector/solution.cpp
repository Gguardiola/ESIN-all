#include "llista.hpp"

//PRE:True
//Post El p.i conte els elements de v amb el mateix order.

Llista::Llista(const vector<int> &v){
    _prim(nullptr);
    _long(v.size());
    node * pant(nullptr);
    for(int i = 0; i < v.size(); i++) {
        node *pnew = new node;
        pnew->info = v[i];
        pnew->seg = nullptr;
        if(pant == nullptr) {
            _prim = pnew;
        } else {
            pant->seg = pnew;
            pant = pnew;
        }
        pant = pnew;
    }
}

//con fantsama

// Llista::Llista(const vector<int> &v){
//     _prim = new node;
//     _long(v.size());
//     node * pant(_prim);
//     for(int i = 0; i < v.size(); i++) {
//         node *pnew = new node;
//         pnew->info = v[i];
//         pnew->seg = nullptr;
//         pant->seg = pnew;
//         pant = pnew;
//     }
// }

//circular con fantasma

// Llista::Llista(const vector<int> &v){
//     _prim = new node;
//     _prim->seg = _prim;
//     _prim->ant = _prim;
//     _long(v.size());
//     node * pant(_prim);
//     for(int i = 0; i < v.size(); i++) {
//         node *pnew = new node;
//         pnew->info = v[i];
//         pnew->seg = _prim;
//         pnew->ant = pant;
//         pant->seg = pnew;
//         _prim->ant = pnou;
//         pant = pnew;
//     }
// }