#ifndef BINOMIALHEAP
#define BINOMIALHEAP

template <class T>
class nodoBinomial
{
public:
  int grado;
  T dato;
  nodoBinomial<T>* padre;
  list<nodoBinomial<T>*> sons;
  nodoBinomial(T dato);
};

template <class T>
nodoBinomial<T>::nodoBinomial(T dato)
{
  this->dato = dato;
  this->grado = 0;
}

template <class T>
class binomialheap
{
  typedef nodoBinomial<T>* nodo;
  typedef list<nodo> lista;
  typedef typename lista::iterator iterador;
public:
  list<nodoBinomial<T>*> heads;
  void insert(T dato);
  T minimo();
  void merge();
  void decrease_key(nodo decrese,T dato);
  void extract_min();
  void mydelete(nodo deleted);
};

template <class T>
void binomialheap<T>::insert(T dato)
{
  heads.push_back(new nodoBinomial<T>(dato));
  merge();
}

template <class T>
T binomialheap<T>::minimo()
{
  iterador it = heads.begin();
  T min =  (*it)->dato;
  for(; it !=heads.end() ; ++it)
        if(min > (*it)->dato)
           min = (*it)->dato;
  return min;
}

template <class T>
void binomialheap<T>::merge()
{
  iterador x = heads.begin();
  iterador next_x = next(x,1);
  iterador siblings_nextx;
  for(;next_x!=heads.end();++next_x)
  {
      siblings_nextx = next(next_x,1);
      if( siblings_nextx!=heads.end() or siblings_nextx==heads.end())
      {
          if( (*siblings_nextx)->grado != (*next_x)->grado and (*x)->grado == (*next_x)->grado)
          {
              nodoBinomial<T>* nuevo;
              if( (*x)->dato < (*next_x)->dato)
              {
                  nuevo = (*next_x);
                  heads.erase(next_x);
                  (*x)->sons.push_back(nuevo);
                  (*x)->grado +=1;
              }
              else if( (*x)->dato > (*next_x)->dato)
              {
                  nuevo = (*x);
                  heads.erase(x);
                  (*next_x)->sons.push_back(nuevo);
                  (*next_x)->grado +=1;
              }
          }
      }
      else if( (*x)->grado == (*next_x)->grado)
      {
          nodoBinomial<T>* nuevo;
              if( (*x)->dato < (*next_x)->dato)
              {
                  nuevo = (*next_x);
                  heads.erase(next_x);
                  (*x)->sons.push_back(nuevo);
                  (*x)->grado +=1;
              }
              else if( (*x)->dato > (*next_x)->dato)
              {
                  nuevo = (*x);
                  heads.erase(x);
                  (*next_x)->sons.push_back(nuevo);
                  (*next_x)->grado +=1;
              }
      }
      x = next(x,1);
  }
}

template <class T>
void binomialheap<T>::decrease_key(nodo decrese, T dato)
{
  decrese->dato = dato;
  while(decrese->padre)
  {
         if (decrese->dato < decrese->padre->dato)
                swap(decrese->dato,decrese->padre->dato);
         else return;
  }
}

template <class T>
void binomialheap<T>::extract_min()
{
  iterador it = heads.begin();
  nodo min =  *it;
  for(; it !=heads.end() ; ++it)
       if(min->dato > (*it)->dato)
          min = *it;

   iterador it_son = min->sons.begin();
   for(; it_son !=min->sons.end() ; ++it_son)
        heads.push_back(*it_son);
   heads.remove(min);
   merge();
}

template <class T>
void binomialheap<T>::mydelete(nodo deleted)
{
  decrease_key(deleted,-10000);
  extract_min();
}

#endif // BINOMIALHEAP

