#include "conjunt_2enters.hpp"


cj_2enters::cj_2enters(){
    //implicit size = 0 on private header
}

cj_2enters::cj_2enters(const cj_2enters &cj){
    for(int i = 0; i < size; i++){
        this->A[i] = cj.A[i];
    }
    this->size = cj.size;
    this->totalCard = cj.totalCard;

}	
cj_2enters::~cj_2enters(){}


cj_2enters& cj_2enters::operator=(const cj_2enters &cj){
    for(int i = 0; i < size; i++){
        this->A[i] = cj.A[i];
    }
    this->size = cj.size;
    this->totalCard = cj.totalCard;

    return *this;
}

void cj_2enters::insereix(pair<int, int> pe){
    if (this->conte(pe))
    {
        return;
    }
    
    if(this->size + 2 <= MAXSIZE) {
        A[size] = pe.first;
        A[size+1] = pe.second;
        size += 2;
        totalCard++;
    }

    this->quicksortWrapper();
    
}


bool cj_2enters::conte(pair<int, int> pe) const{

    bool exists = false;
    int i = 0;
    while(i < this->size-1 && !exists) {
        if(A[i] == pe.first){   
            if (i+1 < this->size){    
                if (A[i+1] == pe.second){       
                    exists = true;
                }
            }
        }
        i++;
    }

    return exists;
    
}

pair<int, int> cj_2enters::max() const{

    pair<int, int> maxpe(A[0], A[1]);
    for (int i = 2; i < this->size; i+=2){
        if (maxpe.first == A[i]){
            if(maxpe.second <= A[i+1]){
                maxpe.first = A[i];
                maxpe.second = A[i+1];
            }
        } else if (maxpe.first < A[i]){
            maxpe.first = A[i];
            maxpe.second = A[i+1];
        }
    }
    
    return maxpe;
}
pair<int, int> cj_2enters::min() const{

    pair<int, int> minpe(A[0], A[1]);
    for (int i = 2; i < this->size; i+=2){
        if (minpe.first == A[i]){
            if(minpe.second >= A[i+1]){
                minpe.first = A[i];
                minpe.second = A[i+1];
            }
        } else if (minpe.first > A[i]){
            minpe.first = A[i];
            minpe.second = A[i+1];
        }
    }
    
    return minpe;    
}

int cj_2enters::card() const{

    return totalCard;
    
}

void cj_2enters::print(ostream& os) const{
    if (this->size == 0) {
        os << "[]";
        return;
    }
    
    os << "[";
    for(int i = 0; i < this->size ;i++) { 
        os << A[i];
        if(i % 2 == 0)              os <<",";
        else if(i+1 < this->size)   os <<" ";
    }
    os <<"]";

}



void cj_2enters::unir(const cj_2enters& B) {
    int aIterator = 0;   
    int bIterator = 0;   

    int temp[MAXSIZE];
    int tempSize = 0;

    while (aIterator < this->size || bIterator < B.getSize()) {
        pair<int, int> currentA;
        if (aIterator < this->size) {
            currentA = pair<int, int>(A[aIterator], A[aIterator + 1]);
        } else {
            currentA = pair<int, int>(INT_MAX, INT_MAX);
        }

        pair<int, int> currentB;
        if (bIterator < B.getSize()) {
            currentB = pair<int, int>(B.getConjunt()[bIterator], B.getConjunt()[bIterator + 1]);
        } else {
            currentB = pair<int, int>(INT_MAX, INT_MAX);
        }

        if (currentA < currentB) {
            temp[tempSize++] = currentA.first;
            temp[tempSize++] = currentA.second;
            aIterator += 2;
        }
        else if (currentB < currentA) {
            temp[tempSize++] = currentB.first;
            temp[tempSize++] = currentB.second;
            bIterator += 2;
        }
        else {
            temp[tempSize++] = currentA.first;
            temp[tempSize++] = currentA.second;
            aIterator += 2;
            bIterator += 2;
        }
    }

    for (int i = 0; i < tempSize; ++i) {
        A[i] = temp[i];
    }
    this->size = tempSize;
}


void cj_2enters::intersectar(const cj_2enters& B){
    int aIterator = 0;   
    int bIterator = 0;   

    int temp[MAXSIZE];
    int tempSize = 0;

    while (aIterator < this->size || bIterator < B.getSize()) {
        pair<int, int> currentA;
        if (aIterator < this->size) {
            currentA = pair<int, int>(A[aIterator], A[aIterator + 1]);
        } else {
            currentA = pair<int, int>(INT_MAX, INT_MAX);
        }

        pair<int, int> currentB;
        if (bIterator < B.getSize()) {
            currentB = pair<int, int>(B.getConjunt()[bIterator], B.getConjunt()[bIterator + 1]);
        } else {
            currentB = pair<int, int>(INT_MAX, INT_MAX);
        }

        if (currentA < currentB) {
            aIterator += 2;
        }
        else if (currentB == currentA) {
            temp[tempSize++] = currentB.first;
            temp[tempSize++] = currentB.second;
            aIterator += 2;
            bIterator += 2;
        } else {
            bIterator += 2;
        }
    }

    for (int i = 0; i < tempSize; ++i) {
        A[i] = temp[i];
    }
    this->size = tempSize;
}
void cj_2enters::restar(const cj_2enters& B){
    int aIterator = 0;   
    int bIterator = 0;   

    int temp[MAXSIZE];
    int tempSize = 0;

    while (aIterator < this->size || bIterator < B.getSize()) {
        pair<int, int> currentA;
        if (aIterator < this->size) {
            currentA = pair<int, int>(A[aIterator], A[aIterator + 1]);
        } else {
            break;
        }

        pair<int, int> currentB;
        if (bIterator < B.getSize()) {
            currentB = pair<int, int>(B.getConjunt()[bIterator], B.getConjunt()[bIterator + 1]);
        } else {
            currentB = pair<int, int>(INT_MAX, INT_MAX);
        }

        if (currentA < currentB) {
            temp[tempSize++] = currentA.first;
            temp[tempSize++] = currentA.second;
            aIterator += 2;
        }
        else if (currentA == currentB) {
            aIterator += 2;
            bIterator += 2;
        }
        else {
            bIterator += 2;
        }
    }

    for (int i = 0; i < tempSize; ++i) {
        A[i] = temp[i];
    }
    this->size = tempSize;
}

cj_2enters cj_2enters::operator+(const cj_2enters& B) const{
    int aIterator = 0;   
    int bIterator = 0;   

    int temp[MAXSIZE];
    int tempSize = 0;

    while (aIterator < this->size || bIterator < B.getSize()) {
        pair<int, int> currentA;
        if (aIterator < this->size) {
            currentA = pair<int, int>(A[aIterator], A[aIterator + 1]);
        } else {
            currentA = pair<int, int>(INT_MAX, INT_MAX);
        }

        pair<int, int> currentB;
        if (bIterator < B.getSize()) {
            currentB = pair<int, int>(B.getConjunt()[bIterator], B.getConjunt()[bIterator + 1]);
        } else {
            currentB = pair<int, int>(INT_MAX, INT_MAX);
        }

        if (currentA < currentB) {
            temp[tempSize++] = currentA.first;
            temp[tempSize++] = currentA.second;
            aIterator += 2;
        }
        else if (currentB < currentA) {
            temp[tempSize++] = currentB.first;
            temp[tempSize++] = currentB.second;
            bIterator += 2;
        }
        else {
            temp[tempSize++] = currentA.first;
            temp[tempSize++] = currentA.second;
            aIterator += 2;
            bIterator += 2;
        }
    }

    cj_2enters newConjunt;
    newConjunt.setConjunt(temp, tempSize);        
    return newConjunt;
}

cj_2enters cj_2enters::operator*(const cj_2enters& B) const{
    int aIterator = 0;   
    int bIterator = 0;   

    int temp[MAXSIZE];
    int tempSize = 0;

    while (aIterator < this->size || bIterator < B.getSize()) {
        pair<int, int> currentA;
        if (aIterator < this->size) {
            currentA = pair<int, int>(A[aIterator], A[aIterator + 1]);
        } else {
            currentA = pair<int, int>(INT_MAX, INT_MAX);
        }

        pair<int, int> currentB;
        if (bIterator < B.getSize()) {
            currentB = pair<int, int>(B.getConjunt()[bIterator], B.getConjunt()[bIterator + 1]);
        } else {
            currentB = pair<int, int>(INT_MAX, INT_MAX);
        }

        if (currentA < currentB) {
            aIterator += 2;
        }
        else if (currentB == currentA) {
            temp[tempSize++] = currentB.first;
            temp[tempSize++] = currentB.second;
            aIterator += 2;
            bIterator += 2;
        } else {
            bIterator += 2;
        }
    }

    cj_2enters newConjunt;
    newConjunt.setConjunt(temp, tempSize);        
    return newConjunt;

}
cj_2enters cj_2enters::operator-(const cj_2enters& B) const {
    int aIterator = 0;   
    int bIterator = 0;   

    int temp[MAXSIZE];
    int tempSize = 0;

    while (aIterator < this->size || bIterator < B.getSize()) {
        pair<int, int> currentA;
        if (aIterator < this->size) {
            currentA = pair<int, int>(A[aIterator], A[aIterator + 1]);
        } else {
            break;
        }

        pair<int, int> currentB;
        if (bIterator < B.getSize()) {
            currentB = pair<int, int>(B.getConjunt()[bIterator], B.getConjunt()[bIterator + 1]);
        } else {
            currentB = pair<int, int>(INT_MAX, INT_MAX);
        }

        if (currentA < currentB) {
            temp[tempSize++] = currentA.first;
            temp[tempSize++] = currentA.second;
            aIterator += 2;
        }
        else if (currentA == currentB) {
            aIterator += 2;
            bIterator += 2;
        }
        else {
            bIterator += 2;
        }
    }
    cj_2enters newConjunt;
    newConjunt.setConjunt(temp, tempSize);        
    return newConjunt;
}



bool cj_2enters::operator==(const cj_2enters& B) const{

    if (this->getSize() != B.getSize()) {
        return false;
    }    

    for (int i = 0; i < this->getSize() -1; i++) {
        if (this->A[i] != B.getConjunt()[i]) return false;
    }

    return true;

}
bool cj_2enters::operator!=(const cj_2enters& B) const{
        if (this->getSize() != B.getSize()) {
        return true;
    }    

    for (int i = 0; i < this->getSize() -1; i++) {
        if (this->A[i] != B.getConjunt()[i]) return true;
    }

    return false;
    
}

int cj_2enters::getSize() const {
    return this->size;
}

int* cj_2enters::getConjunt() const {
    return this->A;

}

void cj_2enters::setConjunt(const int B[], int newSize) {
    for(int i = 0; i < newSize; i++){
        this->A[i] = B[i];
    }
    this->size = newSize;
    this->totalCard = newSize / 2;
}

void cj_2enters::quicksortWrapper() {
    this->quicksort(this->A, 0, this->size-2);
}

void cj_2enters::quicksort(int A[], int low, int high){
    if(low < high) {
        int pivot = partition(A, low, high);
        quicksort(A, low, pivot -2);
        quicksort(A, pivot + 2, high);
    }
}

int cj_2enters::partition(int A[], int low, int high){
    int pivot = A[high];
    int i = low;
    int aux;
    for (int j = low; j <= high -2; j+=2){
        if (A[j] < pivot || (A[j] == pivot && A[j + 1] <= A[high+1])){
        
            aux = A[i];
            A[i] = A[j];
            A[j] = aux;

            aux = A[i+1];
            A[i+1] = A[j+1];
            A[j+1] = aux;

            i+=2;
        }
    }

    aux = A[i];
    A[i] = A[high];
    A[high] = aux;

    aux = A[i+1];
    A[i+1] = A[high+1];
    A[high+1] = aux;

    return i;
    
}

// quicksort estandar sin conjuntos - apuntes

// void cj_2enters::quicksortWrapper() {
//     this->quicksort(this->A, 0, this->size);
// }

// void cj_2enters::quicksort(int A[], int low, int high){
//     if(low < high) {
//         int pivot = partition(A, low, high);
//         quicksort(A, low, pivot -1);
//         quicksort(A, pivot + 1, high);
//     }
// }
// int cj_2enters::partition(int A[], int low, int high){
//     int pivot = A[high];
//     int i = low-1;
//     int aux;
//     for (int j = low; j <= high -1; j++){
//         if(A[j] <= pivot){
//             i++;
//             aux = A[i];
//             A[i] = A[j];
//             A[j] = aux;
//         }
//     }

//     aux = A[i+1];
//     A[i+1] = A[high];
//     A[high] = aux;

//     return i+1;
    
// }
