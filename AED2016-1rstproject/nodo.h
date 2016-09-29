#ifndef NODO
#define NODO
using namespace std;
template <class T>
class nodo
{
public:
  T dato[2];
  nodo<T>* siguiente;
  nodo<T>* anterior;
  nodo();
  nodo(T dato1,T dato2);
};

template <class T>
nodo<T>::nodo()
{
  this->anterior=0;
  this->siguiente=0;
  this->dato[0] = 0;
  this->dato[1] = 1;
}

template <class T>
nodo<T>::nodo(T dato1,T dato2)
{
  this->anterior=0;
  this->siguiente=0;
  this->dato[0] = dato1;
  this->dato[1] = dato2;
}

#endif // NODO

