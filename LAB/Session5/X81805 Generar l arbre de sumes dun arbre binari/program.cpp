#include "arbreBin.hpp"
#include <iostream>
using namespace std;

//Pre: A és un arbre binari
//Post: retorna un arbre binari b on cada node de b es la suma dels descendents del seu node correpsonent a a.
// L’arbre de sumes d’un arbre a és un altre arbre b amb la mateixa estructura, tal que cada node de b és la suma dels descendents del seu node corresponent a a, incloent-lo a ell mateix.

// Com a entrada hi haurà la mida de l’arbre i els nodes de l’arbre binari en postordre. Per cada node s’indica el seu valor i el nombre de fills (2 fills, -1 indica un fill esquerre, 1 indica un fill dret o 0 fills). Podeu utilitzar l’operador >> definit dins la classe arbreBin per llegir l’arbre binari.
arbreBin<int> sumaArbre(const arbreBin<int> &A) {
    //base: si el árbol está vacío, retornar un árbol vacío
    if (A.es_buit()) return arbreBin<int>();

    //Llamadas recursivas para los subárboles izquierdo y derecho
    arbreBin<int> fe = sumaArbre(A.fe());
    arbreBin<int> fd = sumaArbre(A.fd());

    //Calculamos la suma para el nodo actual
    int suma_actual = A.arrel();

    //Si el subárbol izquierdo no es vacío, sumamos su raíz
    if (!fe.es_buit()) {
        suma_actual += fe.arrel();
    }

    //Si el subárbol derecho no es vacío, sumamos su raíz
    if (!fd.es_buit()) {
        suma_actual += fd.arrel();
    }

    //Retornamos un nuevo árbol con la suma en la raíz, y los subárboles izquierdo y derecho
    return arbreBin<int>(suma_actual, fe, fd);
}


int main() {
    arbreBin<int> A;
    cin >> A;


    cout << sumaArbre(A) << endl;

}