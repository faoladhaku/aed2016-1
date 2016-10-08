#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
template <class T>
class leaf
{
public:
    T valor[2];
    int grado;
    leaf<T> * padre;
    leaf<T> * hijo[2];
    leaf(T valor1,T valor2);
    bool operator< (const string& operado);
    int menor(leaf<T>*node,string dato1);
};
template <class T>
leaf<T>::leaf(T valor1,T valor2)
{
  this->grado = 1;
  this->valor[0] = valor1;
  this->valor[1] = valor2;
  this->padre = 0;
  this->hijo[0] = 0;
  this->hijo[1] = 0;
}

template <class T>
int leaf<T>::menor(leaf<T> *node, string dato1)
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
bool leaf<T>::operator< (const string& dato1)
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
class AVL
{
public:
    leaf<T> * root;
    leaf<T> * current;
    string ruta;
    AVL()
    {
        this->ruta = "grafico.dot";
        this->root=0;
        this->current=0;
    }
    AVL(T dato1,T dato2)
    {
      this->ruta = "grafico.dot";
      leaf<T>* nuevo = new leaf<T>(dato1,dato2);
      this->root=nuevo;
      this->current=0;
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
    leaf<T>* encontrar_2(T valor, leaf<T> * aux)
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
		add(valor1, valor2,root, root);
	}
	void add(T valor1, T valor2, leaf<T> *& m_leaf, leaf<T> * padre)
	{
		if(!m_leaf)
		{
			leaf<T> * nuevo = new leaf<T>(valor1,valor2);
			nuevo->padre= padre;
            m_leaf = nuevo;
            corregir(m_leaf);
		}
		else
		{
			if(valor1==m_leaf->valor[0]) return;
			if(m_leaf->operator <(valor1))
            {
                add(valor1,valor2,m_leaf->hijo[1],m_leaf);
            }
			else
            {
                add(valor1,valor2,m_leaf->hijo[0],m_leaf);
            }
		}
	}
	void corregir(leaf<T> * nodo)
	{

        if(!nodo) return;
	    if(nodo == root)
        {
            //nodo->color = NEGRO;
            return;
        }
        leaf<T> * bro = hno(nodo); ///bro es el hermano del nodo
        if(bro)
        {
                if(bro->grado==1 && nodo->grado == 1) return;
                else
                {
                    if(abs(nodo->grado-bro->grado)>=2)
                    {
                        equilibrar(nodo);
                        return;

                    }
                    else
                    {
                        nodo->padre->grado++;
                        corregir(nodo->padre);

                    }
                }
        }
        else
        {
            nodo->padre->grado++;
            if(nodo->grado==2)
            {

                equilibrar(nodo);
                return;

            }
            else
            {
                corregir(nodo->padre);
            }
        }

        //if(nodo->color==NEGRO) corregir(nodo->padre); /// tal vez no sea necesario

        return;
	}
	void equilibrar(leaf<T> * nodo)
	{

        if(nodo->padre->hijo[0]==nodo)
        {
                if(nodo->hijo[0] && nodo->hijo[1])
                {
                    if(nodo->hijo[0]->grado>nodo->hijo[1]->grado)
                    {
                        rotacionDerecha(nodo);
                        verificarGrado(nodo,4);
                    }
                    else
                    {
                        rid(nodo);
                        verificarGrado(nodo,3);
                    }
                }
                else
                {
                    if(!nodo->hijo[0])
                    {
                        rid(nodo);
                        verificarGrado(nodo,2);
                    }
                    else
                    {
                        rotacionDerecha(nodo);
                        verificarGrado(nodo,4);

                    }
                }
        }
        else
        {
                if(nodo->hijo[0] && nodo->hijo[1])
                {
                    if(nodo->hijo[0]->grado>nodo->hijo[1]->grado)
                    {
                            rdi(nodo);
                            verificarGrado(nodo,3);
                    }
                    else
                    {
                            rotacionIzquierda(nodo);
                            verificarGrado(nodo,1);
                    }
                }
                else
                {
                    if(!nodo->hijo[0])
                    {
                        rotacionIzquierda(nodo);
                        verificarGrado(nodo,1);
                    }
                    else
                    {

                        rdi(nodo);


                        verificarGrado(nodo,3);

                    }
                }
        }
	}
	/// rii 1 rid 2 rdi 3 rdd 4
	void verificarGrado(leaf<T> * nodo,int var)
	{


        //if(!nodo) return;
	    switch(var)
	    {
            case 1:

                nodo->hijo[0]->grado-=2;
            case 2:
                nodo->padre->grado++;
                nodo->padre->hijo[1]->grado-=2;
            case 3:

                nodo->padre->grado++;
                nodo->padre->hijo[0]->grado-=2;
                break;
            case 4:
                nodo->hijo[1]->grado-=2;
	    }


        //if(!nodo->padre) corregir(nodo);
        //corregir(nodo->padre);

	}
	///pos es la posicion del padre segun el abuelo
	/// 1 si esta a la derecha del abuelo
	/// 0 si esta a la izquiera del abuelo
	void rotacionDerecha(leaf<T> * nodo)
	{

        if(nodo->padre->padre)
        {
            if(nodo->padre->padre->hijo[0]==nodo->padre)    nodo->padre->padre->hijo[0]=nodo;
            else    nodo->padre->padre->hijo[1]=nodo;
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
	void rotacionIzquierda(leaf<T> * nodo)
	{
	    if(nodo->padre->padre)
        {
            if(nodo->padre->padre->hijo[0]==nodo->padre)    nodo->padre->padre->hijo[0]=nodo;
            else    nodo->padre->padre->hijo[1]=nodo;
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
	void rid(leaf<T> * nodo)
	{
	    leaf<T> * aux1 = nodo->padre;
        leaf<T> * aux2 = nodo->hijo[1];
        if(nodo->hijo[1]->hijo[0] && nodo->hijo[1]->hijo[1])
        {
            leaf<T> * aux3 = nodo->hijo[1]->hijo[1];
            leaf<T> * aux4 = nodo->hijo[1]->hijo[0];
            if(nodo->padre->padre)
            {
                leaf<T> * aux5 = nodo->padre->padre;
                aux2->padre=aux5;
                if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                else    aux5->hijo[1] = aux2;


            }
            else
            {
                aux2->padre=0;
            }

                aux2->hijo[1]=aux1;
                aux2->hijo[0]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
                aux1->hijo[0]=aux3;
                aux3->padre=aux1;
                nodo->hijo[1]=aux4;
                aux4->padre=nodo;


        }
        else
        {

            if(!nodo->hijo[1]->hijo[0])
            {
                leaf<T> * aux3 = nodo->hijo[1]->hijo[1];
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;


                }
                else
                {
                    aux2->padre=0;
                }

                    aux2->hijo[1]=aux1;
                    aux2->hijo[0]=nodo;
                    aux1->padre= aux2;
                    nodo->padre= aux2;
                    aux1->hijo[0]=aux3;
                    aux3->padre=aux1;
            }
            if(nodo->hijo[1]->hijo[0])
            {
                if(!nodo->hijo[1]->hijo[0])
                {
                    leaf<T> * aux4 = nodo->hijo[1]->hijo[0];
                    if(nodo->padre->padre)
                    {
                        leaf<T> * aux5 = nodo->padre->padre;
                        aux2->padre=aux5;
                        if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                        else    aux5->hijo[1] = aux2;


                    }
                    else
                    {
                        aux2->padre=0;
                    }

                        aux2->hijo[1]=aux1;
                        aux2->hijo[0]=nodo;
                        aux1->padre= aux2;
                        nodo->padre= aux2;
                        nodo->hijo[1]=aux4;
                        aux4->padre=nodo;

                }

            }
            else
            {
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                }
                else
                {
                    aux2->padre=0;
                }
                nodo->hijo[1]=0;
                aux1->hijo[0]=0;
                aux2->hijo[0]=aux1;
                aux2->hijo[1]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
            }



    }

	}
	void rdi(leaf<T> * nodo)
	{

	    leaf<T> * aux1 = nodo->padre;
        leaf<T> * aux2 = nodo->hijo[0];
        if(nodo->hijo[0]->hijo[0] && nodo->hijo[0]->hijo[1])
        {
            leaf<T> * aux3 = nodo->hijo[0]->hijo[0];
            leaf<T> * aux4 = nodo->hijo[0]->hijo[1];
            if(nodo->padre->padre)
            {
                leaf<T> * aux5 = nodo->padre->padre;
                aux2->padre=aux5;
                if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                else    aux5->hijo[1] = aux2;
            }
            else
            {
                root=aux2;
                aux2->padre=0;
            }


            aux2->hijo[0]=aux1;
            aux2->hijo[1]=nodo;
            aux1->padre= aux2;
            nodo->padre= aux2;

            aux1->hijo[1]=aux3;
            aux3->padre=aux1;
            nodo->hijo[0]=aux4;
            aux4->padre=nodo;

        }
        else
        {

            if(nodo->hijo[0]->hijo[1])
            {
                leaf<T> * aux4 = nodo->hijo[0]->hijo[1];
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                }
                else
                {
                    this->root= aux2;
                    aux2->padre=0;
                }


                aux2->hijo[0]=aux1;
                aux2->hijo[1]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
                nodo->hijo[0]=aux4;
                aux4->padre=nodo;
            }
            if(nodo->hijo[0]->hijo[0])
            {
                leaf<T> * aux3 = nodo->hijo[0]->hijo[0];
                if(nodo->padre->padre)
                {
                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                }
                else
                {
                    this->root=aux2;
                    aux2->padre=0;
                }


                aux2->hijo[0]=aux1;
                aux2->hijo[1]=nodo;
                aux1->padre= aux2;
                nodo->padre= aux2;
                aux1->hijo[1]=aux3;
                aux3->padre=aux1;
            }
            else
            {

                if(nodo->padre->padre)
                {

                    leaf<T> * aux5 = nodo->padre->padre;
                    aux2->padre=aux5;
                    if(nodo->padre->padre->hijo[0]==nodo->padre)   aux5->hijo[0] = aux2;
                    else    aux5->hijo[1] = aux2;
                    aux1->hijo[1]=0;
                    aux2->hijo[0]=aux1;
                    aux2->hijo[1]=nodo;
                    aux1->padre= aux2;
                    nodo->padre= aux2;
                    nodo->hijo[0]=0;
                    nodo->hijo[1]=0;
                }
                else
                {


                    aux2->hijo[0]=aux1;
                    aux2->hijo[1]=nodo;
                    aux1->padre= aux2;
                    aux1->hijo[1]=0;
                    nodo->padre= aux2;
                    nodo->hijo[0]=0;
                    nodo->hijo[1]=0;
                    aux2->padre=0;
                    root= aux2;

                }





            }


        }

	}
	leaf<T> * tio(leaf<T> * nodo)
	{
        if(nodo->padre->padre->hijo[0]== nodo->padre)
            return nodo->padre->padre->hijo[1];
        return nodo->padre->padre->hijo[0];
	}
	leaf<T> * hno(leaf<T> * nodo)
	{
        if(nodo->padre->hijo[0]== nodo)
            return nodo->padre->hijo[1];
        return nodo->padre->hijo[0];
	}
	void graficar()
	{
        ofstream * fichero = new ofstream (this->ruta);
        *fichero<<"digraph G {"<<endl;
        print(root,fichero);
        *fichero<<"}";
        fichero->close();

	}
	void print(leaf<T> * aux, ofstream * archivo)
	{

	    if(!aux)return;

	    if(aux->hijo[0]!=0)
        {

            *archivo<<aux->valor<<"->"<<aux->hijo[0]->valor<<endl;
            print(aux->hijo[0],archivo);
	    }
	    if(aux->hijo[1]!=0 )
	    {

	        *archivo<<aux->valor<<"->"<<aux->hijo[1]->valor<<endl;
	        print(aux->hijo[1],archivo);
	    }
	    //if(!aux->color) *archivo<<aux->valor<<" [color=black,style=filled,fontcolor=white];"<<endl;
        //else *archivo<<aux->valor<<" [color=red,style=filled,fontcolor=white];"<<endl;





	}
	leaf<T>* mybegin();
	leaf<T>* next();
	leaf<T>* myend();
	int levenshtein(const string &s1, const string &s2);

};

template <class T>
int AVL<T>::levenshtein(const string &s1, const string &s2)
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
leaf<T>* AVL<T>::mybegin()
{
  this->current = this->root;
  while(this->current->hijo[0])
    {
      this->current = this->current->hijo[0];
    }
  return this->current;
}

template <class T>
leaf<T>* AVL<T>::myend()
{
  this->current = this->root;
  while(this->current->hijo[1])
    {
      this->current = this->current->hijo[1];
    }
  return this->current;
}

template <class T>
leaf<T>* AVL<T>::next()
{
  leaf<T>* padre = this->current->padre;
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
