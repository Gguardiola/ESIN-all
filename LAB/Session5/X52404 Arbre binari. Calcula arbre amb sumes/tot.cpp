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




#include <iostream>

template <typename T>
typename Abin<T>::node* Abin<T>::copia_nodes(node* m) {
/* Pre: cert */
/* Post: si m és NULL, el resultat és NULL; sinó,
   el resultat apunta al primer node d'un arbre binari
   de nodes que són còpia de l'arbre apuntat per m */
  node* n;
  if (m == NULL) n = NULL;
  else {
    n = new node;
    try {
      n->info = m->info;
      n->f_esq = copia_nodes(m->f_esq);
      n->f_dret = copia_nodes(m->f_dret);
    } catch(...) {
      delete n;
      throw;
    }
  }
  return n;
};

template <typename T>
void Abin<T>::esborra_nodes(node* m) {
/* Pre: cert */
/* Post: no fa res si m és NULL, sinó allibera
   espai dels nodes de l'arbre binari apuntat per m */
  if (m != NULL) {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

template <typename T>
Abin<T>::Abin(Abin<T>& ae, const T& x, Abin<T>& ad) {
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try {
    _arrel->info = x;
  }
  catch (...) {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = NULL;
  _arrel->f_dret = ad._arrel;
  ad._arrel = NULL;
}

template <typename T>
Abin<T>::Abin(const Abin<T> &a) {
  _arrel = copia_nodes(a._arrel);
};

template <typename T>
Abin<T>::~Abin() {
  esborra_nodes(_arrel);
};

template <typename T>
Abin<T>& Abin<T>::operator=(const Abin<T>& a) {
  if (this != &a) {
    node* aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
};

template <typename T>
void Abin<T>::print_nodes(node* p, ostream &os, string prefix) {
  if (p == NULL) 
    os << ".";
  else {
    string prefix2;
    os << "["<<p->info << "]\n" << prefix << " \\__";
    prefix2 = prefix + " |  ";
    print_nodes(p->f_dret, os, prefix2);
    os << "\n" << prefix << " \\__";
    prefix2 = prefix + "    ";
    print_nodes(p->f_esq, os, prefix2);
  }
}

// operador << d'escriptura
template <class U>
ostream& operator<<(ostream &os, const Abin<U> &a) {
  a.print_nodes(a._arrel, os, "");
  os << "\n";
  return os;
}

// operador >> de lectura
template <class U>
istream& operator>>(istream &is, Abin<U> &a) {  
  int valor;
  cin >> valor;
  if (valor != -1) {
    Abin<U> ae;
    is >> ae;
    Abin<U> ad;
    is >> ad;
    a = Abin<U>(ae, valor, ad);
  }
  return is;
}

int main() {
  Abin<int> a;
  cin >> a;
  cout << a << endl;
  a.arbre_sumes();
  cout << a;
  return 0;
}
