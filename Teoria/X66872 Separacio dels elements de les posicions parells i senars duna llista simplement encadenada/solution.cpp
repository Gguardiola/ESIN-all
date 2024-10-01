#include "llista.hpp"

void Llista:separa(Llista &l2) {
    node *pant(_prim), *p(_prim->nullptr), *p2(nullptr);

    if(p != nullptr) p = p->seg;

    while(p != nullptr) {
        pant->seg = p->seg;
        if(p2 == nullptr) {
            l2._prim = p;
        } else {
            p2->seg = p;
        }
        p2 = p;
        pant = p->seg;
        if(pant != nullptr) {
            p = pant->seg
        }
        else{
            _long++;
            l2._long++;
        }
    }
    if (p2 != nullptr) {
        p2->seg = nullptr;
    }
}