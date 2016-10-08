#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define ROJO 1
#define NEGRO 0
template <class T>
class leaf1
{
public:
    T valor[2];
    bool color;
    leaf1<T> * padre;
    leaf1<T> * hijo[2];
    leaf1(T valor1, T valor2);
    int menor(leaf1<T>*node,string dato1);
    bool operator< (const string& dato1);
};

template <class T>
leaf1<T>::leaf1(T valor1,T valor2)
{

  this->color = ROJO;
  this->valor[0] = valor1;
  this->valor[1] = valor2;
  this->padre = 0;
  this->hijo[0] = 0;
  this->hijo[1] = 0;
}

template <class T>
int leaf1<T>::menor(leaf1<T> *node, string dato1)
{
  string a = node->valor[0];
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
bool leaf1<T>::operator< (const string& dato1)
{
  int size = menor(this,dato1);
  for(int i=0;i<size-1;i++)
    {
      if(this->valor[0][i]<dato1[i])
        return true;
    }
  return false;
}

template <class T>
class RBT
{
public:
    leaf1<T> * root;
    leaf1<T> * current;
    leaf1<T> * NIL;
    string ruta;

    RBT()
    {
        ruta = "grafico.dot";
        this->root=0;
        NIL = new leaf1<T>(0,0);
        NIL->color=NEGRO;
        NIL->valor[0]=-65;
    }
    RBT(T dato1, T dato2)
    {
        ruta = "grafico.dot";
        this->root=new leaf1<T>(dato1,dato2);
        NIL = new leaf1<T>(0,0);
        NIL->color=NEGRO;
        NIL->valor[0]=-65;
    }

    bool encontrar(T valor)
    {
        return encontrar(valor,root);
    }
    bool encontrar(T valor, leaf<T> * aux)
    {
            if(!aux) return 0;
            if(valor==aux->valor) return 1;
            else
            {
                if(valor<aux->valor) return encontrar(valor,aux->hijo[0]);
                return encontrar(valor,aux->hijo[1]);
            }
    }
    leaf<T>* encontrar_2(T valor)
    {
        return encontrar_2(valor,root);
    }
    leaf<T>* encontrar_2(T valor, leaf1<T> * aux)
    {
            if(!aux) return 0;
            if(valor==aux->valor) return aux;
            else
            {
                if(valor<aux->valor) return encontrar_2(valor,aux->hijo[0]);
                return encontrar_2(valor,aux->hijo[1]);
            }
    }

    void add(T valor1, T valor2)
	{
		add(valor1,valor2, root, root);
	}
	void add(T valor1,T valor2, leaf1<T> *& m_leaf, leaf1<T> * padre)
	{
		if(!m_leaf || m_leaf==NIL)
		{
			leaf1<T> * nuevo = new leaf1<T>(valor1,valor2);
			nuevo->hijo[0]=NIL;
			nuevo->hijo[1]=NIL;
			nuevo->padre= padre;
            m_leaf = nuevo;
            corregir(m_leaf);
		}
		else
		{
			if(valor1==m_leaf->valor[0]) return;
			if(m_leaf->operator <(valor2))
            {
                add(valor1,valor2,m_leaf->hijo[1],m_leaf);
            }
			else
            {
                add(valor1,valor2,m_leaf->hijo[0],m_leaf);
            }
		}
	}
	void corregir(leaf1<T> *& nodo)
	{
        if(!nodo) return;
	    if(nodo == root)
        {
            nodo->color = NEGRO;
            return;
        }
        if(nodo->color==NEGRO) corregir(nodo->padre); /// tal vez no sea necesario
	    if(nodo->padre->color==ROJO)
        {
            if(tio(nodo)->color==ROJO)
            {
                tio(nodo)->color=NEGRO;
                nodo->padre->color=NEGRO;
                if(nodo->padre->padre->valor != this->root->valor)
                {
                    nodo->padre->padre->color=ROJO;
                    corregir(nodo->padre->padre);
                }


                return;
            }
                if(nodo->padre->hijo[0]==nodo)
                {
                    if(nodo->padre->padre->hijo[0]==nodo->padre)
                    {
                        rotacionDerecha(nodo->padre,0);
                        verificarColor(nodo->padre);
                    }
                    else
                    {
                        rotacionDerecha(nodo,1);
                        rotacionIzquierda(nodo,1);
                        verificarColor(nodo);

                    }
                }
                else
                {
                    if(nodo->padre->padre->hijo[1]==nodo->padre)
                    {

                        rotacionIzquierda(nodo->padre,1);

                        verificarColor(nodo->padre);
                    }
                    else
                    {
                        rotacionIzquierda(nodo,0);
                        rotacionDerecha(nodo,0);
                        verificarColor(nodo);

                    }
                }

        }
        return;
	}
	void verificarColor(leaf1<T> *& nodo)
	{
	    if(!nodo) return;
	    nodo->color=NEGRO;
        nodo->hijo[0]->color=ROJO;
        nodo->hijo[1]->color=ROJO; /// tal vez no sea necesario
        if(!nodo->padre) corregir(nodo);
        corregir(nodo->padre);

	}
	///pos es la posicion del padre segun el abuelo
	/// 1 si esta a la derecha del abuelo
	/// 0 si esta a la izquiera del abuelo
	void rotacionDerecha(leaf1<T> *& nodo, bool pos)
	{

        if(nodo->padre->padre)
        {
            nodo->padre->padre->hijo[pos]=nodo;
            nodo->padre->hijo[0]= nodo->hijo[1];
            nodo->hijo[1]=nodo->padre;
            nodo->padre=nodo->padre->padre;
            nodo->hijo[1]->padre=nodo;
        }

        else
        {

            root = nodo;
            nodo->padre->hijo[0]= nodo->hijo[1];
            nodo->hijo[1]=nodo->padre;
            nodo->padre=0;
            nodo->hijo[1]->padre=nodo;
        }


	}
	void rotacionIzquierda(leaf1<T> * nodo, bool pos)
	{
	    if(nodo->padre->padre)
        {
            nodo->padre->padre->hijo[pos]=nodo;
            nodo->padre->hijo[1]= nodo->hijo[0];
            nodo->hijo[0]=nodo->padre;
            nodo->padre=nodo->padre->padre;
            nodo->hijo[0]->padre=nodo;

        }
        else
        {
            root = nodo;
            nodo->padre->hijo[1]= nodo->hijo[0];
            nodo->hijo[0]=nodo->padre;
            nodo->padre=0;
            nodo->hijo[0]->padre=nodo;
        }

	}
	leaf1<T> * tio(leaf1<T> *& nodo)
	{
        if(nodo->padre->padre->hijo[0]== nodo->padre)
            return nodo->padre->padre->hijo[1];
        return nodo->padre->padre->hijo[0];
	}
	void graficar()
	{
        ofstream * fichero = new ofstream (this->ruta);
        *fichero<<"digraph G {"<<endl;
        print(root,fichero);
        *fichero<<"}";
        fichero->close();

	}
	void print(leaf1<T> * aux, ofstream * archivo)
	{
	    if(!aux)return;

	    if(aux->hijo[0] && aux->hijo[0]!= NIL)
        {
            *archivo<<aux->valor<<"->"<<aux->hijo[0]->valor<<endl;
            print(aux->hijo[0],archivo);
	    }
	    if(aux->hijo[1] && aux->hijo[1]!= NIL)
	    {
	        *archivo<<aux->valor<<"->"<<aux->hijo[1]->valor<<endl;
	        print(aux->hijo[1],archivo);
	    }
	    if(!aux->color) *archivo<<aux->valor<<" [color=black];"<<endl;
        else *archivo<<aux->valor<<" [color=red];"<<endl;





	}
	leaf1<T>* mybegin();
	leaf1<T>* next();
	leaf1<T>* myend();
	int levenshtein(const string &s1, const string &s2);
};

template <class T>
leaf1<T>* RBT<T>::mybegin()
{
  this->current = this->root;
  while(this->current->hijo[0])
    {
      this->current = this->current->hijo[0];
    }
  return this->current;
}

template <class T>
leaf1<T>* RBT<T>::myend()
{
  this->current = this->root;
  while(this->current->hijo[1])
    {
      this->current = this->current->hijo[1];
    }
  return this->current;
}
template <class T>
leaf1<T>* RBT<T>::next()
{
  leaf1<T>* padre = this->current->padre;
  if(this->current == this->root)
    {
      if(this->current->hijo[1])
        {
          this->current = this->current->hijo[1];
          while(this->current->hijo[0])
            {
              this->current = this->current->hijo[0];
            }
          return this->current;
        }
    }
  if(padre->hijo[0] == this->current)
    {
      if(this->current->hijo[1])
        {
          this->current = this->current->hijo[1];
          while(this->current->hijo[0])
            {
              this->current = this->current->hijo[0];
            }
          return this->current;
        }
      this->current = padre;
      return this->current;
    }
  if(padre->hijo[1] == this->current)
    {
      if(this->current->hijo[1])
        {
          this->current = this->current->hijo[1];
          while(this->current->hijo[0])
            {
              this->current = this->current->hijo[0];
            }
          return this->current;
        }
      while(padre!=this->root)
        {
          padre = padre->padre;
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
int RBT<T>::levenshtein(const string &s1, const string &s2)
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
