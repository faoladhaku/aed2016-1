#ifndef BT
#define BT
#include "nodot.h"
template <class T>
class bt
{
public:
  bt():root(0),current(0){}
  bt(T dato1,T dato2);
  nodot<T>* root;
  nodot<T>* current;
  void insert(T dato1,T dato2);
  void insert(T dato1,T dato2,nodot<T>*&node);
  nodot<T>* find(T dato1);
  bool find(T dato,nodot<T>*&node);
  nodot<T>* begin();
  nodot<T>* next();
  nodot<T>* end();
  nodot<T>* get_padre(nodot<T>* node);
};

template <class T>
bt<T>::bt(T dato1, T dato2)
{
  nodot<T>* nuevo = new nodot<T>(dato1,dato2);
  this->root = nuevo;
}

template <class T>
void bt<T>::insert(T dato1,T dato2)
{
  nodot<T>* nuevo = this->root;
  add_recursive(dato1,dato2,nuevo);
}

template <class T>
void bt<T>::insert(T dato1,T dato2, nodot<T> *&node)
{
  if(!node)
  {
      node = new nodot<T>(dato1,dato2);
      return;
  }
  if(node->dato[0]==dato1 or node->dato[1]==dato1 or node->dato[0]==dato2 or node->dato[1]==dato2)
  {
      return;
  }
  if(node<dato1)
  {
      add_recursive(dato1,dato2,node->der);
  }
  else
  {
      add_recursive(dato1,dato2,node->izq);
  }
}

template <class T>
nodot<T>* bt<T>::find(T dato1)
{
  nodot<T>* nuevo = this->root;
  find(dato1,nuevo);
  this->current = nuevo;
  return nuevo;
}

template <class T>
bool bt<T>::find(T dato1,nodot<T>*&node)
{
  if(!node)
  {
      return false;
  }
  if(node->dato[0] == dato1 or node->dato[1] == dato1)
  {
      return true;
  }
  if(node<dato1)
  {
      return find_recursive(dato1,node->der);
  }
  else
  {
      return find_recursive(dato1,node->izq);
  }
}

template <class T>
nodot<T>* bt<T>::begin()
{
  this->current = this->root;
  while(this->current->son[0])
    {
      this->current = this->current->son[0];
    }
  return this->current;
}

template <class T>
nodot<T>* bt<T>::next()
{
  nodot<T>* padre = get_padre(this->current);
  if(this->current == this->root)
    {
      if(this->current->son[1])
        {
          this->current = this->current->son[1];
          while(this->current->son[0])
            {
              this->current = this->current->son[0];
            }
          return this->current;
        }
    }
  if(padre->son[0] == this->current)
    {
      if(this->current->son[1])
        {
          this->current = this->current->son[1];
          while(this->current->son[0])
            {
              this->current = this->current->son[0];
            }
          return this->current;
        }
      this->current = padre;
      return this->current;
    }
  if(padre->son[1] == this->current)
    {
      if(this->current->son[1])
        {
          this->current = this->current->son[1];
          while(this->current->son[0])
            {
              this->current = this->current[0];
            }
          return this->current;
        }
      while(padre!=this->root)
        {
          padre = get_padre(padre);
          if(this->current<padre)
            {
              this->current = padre;
              return this->current;
            }
        }
    }
  return this->current;
}

template <class T>
nodot<T>* bt<T>::get_padre(nodot<T> *node)
{
  if(this->root!=node)
    {
      nodot<T>* padre = this->root;
      if(padre->son[0] == node)
        {
          return padre;
        }
      if(padre->son[1] == node)
        {
          return padre;
        }
      get_padre(padre->son[0]);
      get_padre(padre->son[1]);
    }
  return node;
}

template <class T>
nodot<T>* bt<T>::end()
{
  this->current = this->root;
  while(this->current->son[1])
    {
      this->current = this->current->son[1];
    }
  return this->current;
}

#endif // BT

