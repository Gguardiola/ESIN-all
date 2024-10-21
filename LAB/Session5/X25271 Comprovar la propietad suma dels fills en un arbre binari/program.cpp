#include "arbreBin.hpp"
#include <iostream>
using namespace std;

bool suma_fills(const arbreBin<int> &A) {
    bool compleix;

    if(A.es_buit()) compleix = true;
    else {
        if(A.fe().es_buit() && A.fd().es_buit()) compleix = true;
        else if(A.fe().es_buit() && !A.fd().es_buit()) {
            if(A.fd().arrel() != A.arrel()) compleix = false;
            else compleix = suma_fills(A.fd());
        }
        else if(A.fd().es_buit() && !A.fe().es_buit()) {
            if(A.fe().arrel() != A.arrel()) compleix = false;
            else compleix = suma_fills(A.fe());
        }
        else {
            if(A.arrel() != (A.fe().arrel() + A.fd().arrel())) compleix = false;
            else compleix = suma_fills(A.fe());
            if(compleix) compleix = suma_fills(A.fd());
        }
    }

    return compleix;
}


int main() {
    arbreBin<int> A;

    cin >> A;

    cout << A << endl;

    if(suma_fills(A)) cout<< "L'arbre compleix la propietat 'Suma dels fills'." << endl;
    else cout << "L'arbre no compleix la propietat 'Suma dels fills'." << endl;

}

// #include "arbreBin.hpp"

// using namespace std;

// bool sumaFills(const arbreBin<int> &A){

//     bool res ;

//     if(A.es_buit()) res = true;
//     else{

//         if(A.fe().es_buit() and A.fd().es_buit()) res = true;

//         else if(A.fe().es_buit() and not A.fd().es_buit()){
//             if(A.fd().arrel() != A.arrel()) res = false;
//             else res = sumaFills(A.fd());
//         }
//         else if(A.fd().es_buit() and not A.fe().es_buit()){
//             if(A.fe().arrel() != A.arrel()) res = false;
//             else res = sumaFills(A.fe());
//         }
//         else{
//             if(A.arrel() != (A.fe().arrel() + A.fd().arrel())) res = false;
//             else res = sumaFills(A.fe());
//             if(res) res = sumaFills(A.fd());
//         }

//     }

//     return res;
// }


// int main(){

//     arbreBin<int> A;

//     cin >> A;

//     cout << A << endl;

//     if(sumaFills(A)) cout << "L'arbre compleix la propietat 'Suma dels fills'." << endl;
//     else cout << "L'arbre no compleix la propietat 'Suma dels fills'." << endl;

// }



