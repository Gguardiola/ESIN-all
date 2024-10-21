 #include <cstdlib>
 #include <iostream>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename T>
 class Abin {
   public:
     Abin(): _arrel(NULL) {};
     // Pre: cert
     // Post: el resultat és un arbre sense cap element
     Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
     // Pre: cert
     // Post: el resultat és un arbre amb un element i dos subarbres
 
     // Les tres grans
     Abin(const Abin<T> &a);
     ~Abin();
     Abin<T>& operator=(const Abin<T>& a);
 
     // operador << d’escriptura
     template <class U> friend std::ostream& operator<<(std::ostream&, const Abin<U> &a);
 
     // operador >> de lectura
     template <class U> friend std::istream& operator>>(std::istream&, Abin<U> &a);
 
     // Modifica el contingut de l’arbre per tal de guardar a cada node la suma dels
     // nodes del seu subarbre.
     void arbre_sumes();
 
   private:
     struct node {
       node* f_esq;
       node* f_dret;
       T info;
     };
     node* _arrel;
     static node* copia_nodes(node* m);
     static void esborra_nodes(node* m);
     static void print_nodes(node* m, ostream &os, string d1);
 
     node* arbre_sumes_rec(node* n);
 };

//de forma recursiva, que modifica el contingut de l’arbre per tal de guardar a cada node la suma dels nodes del seu subarbre.
template <typename T>
void Abin<T>::arbre_sumes() {
    arbre_sumes_rec(_arrel);
}

template <typename T>
typename Abin<T>::node* Abin<T>::arbre_sumes_rec(node* n) {
    if (n == NULL) return NULL;

    node* left = arbre_sumes_rec(n->f_esq);
    node* right = arbre_sumes_rec(n->f_dret);

    if (left != NULL) n->info += left->info;
    if (right != NULL) n->info += right->info;

    return n;
}


