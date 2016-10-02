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
  void insert(string dato1,T dato2);
  void insert(string dato1,T dato2,nodot<T>*&node);
  nodot<T>* find(T dato1);
  bool find(T dato,nodot<T>*&node);
  nodot<T>* mybegin();
  nodot<T>* next();
  nodot<T>* myend();
  nodot<T>* get_padre(nodot<T>* node);
  bool terminate();
  int levenshtein(const string &s1, const string &s2);
  vector<nodot<T>*> comparation(int ratio, T word);
};

template <class T>
bt<T>::bt(T dato1, T dato2)
{
  nodot<T>* nuevo = new nodot<T>(dato1,dato2);
  this->root = nuevo;
}

template <class T>
void bt<T>::insert(string dato1,T dato2)
{
  nodot<T>* nuevo = this->root;
  insert(dato1,dato2,nuevo);
}

template <class T>
void bt<T>::insert(string dato1,T dato2, nodot<T> *&node)
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
  if(node->operator <( dato1))
  {
      insert(dato1,dato2,node->son[1]);
  }
  else
  {
      insert(dato1,dato2,node->son[0]);
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
  if(node->operator <(dato1))
  {
      return find(dato1,node->son[1]);
  }
  else
  {
      return find(dato1,node->son[0]);
  }
}

template <class T>
nodot<T>* bt<T>::mybegin()
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
              this->current = this->current->son[0];
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
  this->current=nullptr;
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
nodot<T>* bt<T>::myend()
{
  this->current = this->root;
  while(this->current->son[1])
    {
      this->current = this->current->son[1];
    }
  return this->current;
}

template <class T>
bool bt<T>::terminate()
{
  if(this->current == NULL)
    {
      return false;
    }
  return true;
}
<<<<<<< HEAD
=======

template <class T>
int bt<T>::levenshtein(const string &s1, const string &s2)
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
vector<nodot<T>*> bt<T>::comparation(int ratio, T word)
{
  vector<nodot<T>*> resultados;
  //find(word);
  mybegin();
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

#endif // BT
>>>>>>> d604a7cc13a2425700e397add6b027e968a30168

template <class T>
int bt<T>::levenshtein(const string &s1, const string &s2)
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
vector<nodot<T>*> bt<T>::comparation(int ratio, T word)
{
  vector<nodot<T>*> resultados;
  //find(word);
  mybegin();
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

#endif // BT
