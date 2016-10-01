#ifndef NODOT
#define NODOT
#include <string.h>
using namespace std;
template <class T>
class nodot
{
public:
  nodot();
  nodot(T dato1,T dato2);
  T dato[2];
  nodot<T>* son[2];
  bool operator< (const string& dato1);
  bool operator!= (const nodot<T>*& node);
  bool operator== (const nodot<T>*& node);
  int menor(nodot<T>*node,string dato1);
};

template <class T>
nodot<T>::nodot()
{
  this->dato[0]=this->dato[1]=0;
  this->son[0]=this->son[1]=0;
}

template <class T>
nodot<T>::nodot(T dato1,T dato2)
{
  this->dato[0]=dato1;
  this->dato[1]=dato2;
  this->son[0]=this->son[1]=0;
}

template <class T>
int nodot<T>::menor(nodot<T> *node, string dato1)
{
  string a = node->dato[0];
  int i = a.size();
  int y = dato1.size();
  //cout<<i;
  if(i<y)
    {
      return i;
    }
  else if(y<i)
    {
      return y;
    }
}

template <class T>
bool nodot<T>::operator< (const string& dato1)
{
  int size = menor(this,dato1);
  for(int i=0;i<size-1;i++)
    {
      if(this->dato[0][i]<dato1[i])
        return true;
    }
  return false;
}

template <class T>
bool nodot<T>::operator !=(const nodot<T>*& node)
{
  if(this->dato[0] != node->dato[0])
    return true;
  return false;
}

template <class T>
bool nodot<T>::operator ==(const nodot<T>*& node)
{
  if(this->dato[0] == node->dato[0] or this->dato[0] == node->dato[1])
    return true;
  return false;
}

#endif // NODOT

