#ifndef LIST
#define LIST
#include "nodo.h"
template <class T>
class list
{
public:
  nodo<T>* head;
  nodo<T>* current;
  nodo<T>* tail;
  list():head(0),current(0),tail(0){}
  void insert(T dato1,T dato1);
  nodo<T>* find(T dato);
  bool find(nodo<T>*& node,T dato);
  nodo<T>* next();
  nodo<T>* begin();
  nodo<T>* end();
};

template <class T>
void list<T>::insert(T dato1,Tdato2)
{
  nodo<T>* nuevo = new nodo<T>(dato1,dato2);
  if(!head)
      {
          this->head=this->tail=nuevo;
          this->tail->siguiente = this->head;
          this->head->anterior = this->tail;
      }
  this->tail->siguiente = nuevo;
  nuevo->anterior = this->tail;
  this->tail = nuevo;
  this->tail->siguiente =this->head;
  this->head->anterior = this->tail;
}

template <class T>
bool list<T>::find(nodo<T>*& node,T dato)
{
  node = this->head;
  if(this->head->siguiente == this->head)
  {

      if(this->head->dato[0] == dato or this->head->dato[1]==dato)
          return true;
      return false;
  }
  while(node)
  {
      if(node == this->tail)
      {
          if(node->dato[0]==dato or node->dato[1]==dato)
              return true;
          return false;
      }
      if(node->dato[0] == dato or node->dato[1]==dato)
      {
          return true;
      }
      node = node->siguiente;
  }
  return false;
}

template <class T>
nodo<T>* list<T>::find(T dato)
{
  nodo<T>* node;
  if(find(node,dato))
    this->current = node;
    return node;
}

template <class T>
nodo<T>* list<T>::begin()
{
  this->current = this->head;
  return this->current;
}

template <class T>
nodo<T>* list<T>::next()
{
  return this->current->siguiente;
}

template <class T>
nodo<T>* list<T>::end()
{
  this->current = this->tail;
  return this->current;
}

#endif // LIST

