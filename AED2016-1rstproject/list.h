#ifndef LIST
#define LIST
#include "nodo.h"
template <class T>
class mylist
{
public:
  nodo<T>* head;
  nodo<T>* current;
  nodo<T>* tail;
  mylist():head(0),current(0),tail(0){}
  void insert(T dato1,T dato2);
  nodo<T>* find(T dato);
  bool find(nodo<T>*& node,T dato);
  nodo<T>* next();
  nodo<T>* begin();
  nodo<T>* end();
  bool terminate();
  vector<nodo<T>*> comparation(int ratio, T word);
  int levenshtein(const string &s1, const string &s2);
};

template <class T>
void mylist<T>::insert(T dato1,T dato2)
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
bool mylist<T>::find(nodo<T>*& node,T dato)
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
nodo<T>* mylist<T>::find(T dato)
{
  nodo<T>* node;
  if(find(node,dato))
    this->current = node;
    return node;
}

template <class T>
nodo<T>* mylist<T>::begin()
{
  this->current = this->head;
  return this->current;
}

template <class T>
nodo<T>* mylist<T>::next()
{
  this->current = this->current->siguiente;
  return this->current->siguiente;
}

template <class T>
nodo<T>* mylist<T>::end()
{
  this->current = this->tail;
  return this->current;
}

template <class T>
bool mylist<T>::terminate()
{
  int i=0;
  if(this->current== this->tail)
    {
       i=1;
    }
  if(i ==1)
    {
      i=0;
      return false;
    }
  return true;
}
template <class T>
int mylist<T>::levenshtein(const string &s1, const string &s2)
{
   int N1 = s1.size();
   int N2 = s2.size();
   int i, j;
   vector<int> S(N2+1);

   for ( i = 0; i <= N2; i++ )
      S[i] = i;

   for ( i = 0; i < N1; i++ )
   {
      S[0] = i+1;
      int corner = i;
      for ( j = 0; j < N2; j++ )
      {
         int upper = S[j+1];
         if ( s1[i] == s2[j] )
            S[j+1] = corner;
         else
            S[j+1] = min(S[j], min(upper, corner)) + 1;
         corner = upper;
      }
   }
   return S[N2];
}

template <class T>
vector<nodo<T>*> mylist<T>::comparation(int ratio, T word)
{
  vector<nodo<T>*> resultados;
  //find(word);
  begin();
  /*for(this->current;terminate();next())
    {
      if(levenshtein(word,this->current->dato[0]) <= ratio)
      {
         resultados.push_back(this->current);
      }
    }
  return resultados;
  */
  while(terminate())
    {
      if(levenshtein(word,this->current->dato[0]) <= ratio)
      {
         resultados.push_back(this->current);
      }
      next();
    }
  return resultados;
}

#endif // LIST

