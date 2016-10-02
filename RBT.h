#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define ROJO 1
#define NEGRO 0
template <class T>
class leaf
{
public:
    T valor;
    bool color;
    leaf<T> * padre;
    leaf<T> * hijo[2];
    leaf(T valor)
    {
        this->color = ROJO;
        this->valor = valor;
        this->padre = 0;
        this->hijo[0] = 0;
        this->hijo[1] = 0;
    }
};
template <class T>
class RBT
{
public:
    leaf<T> * root;
    leaf<T> * NIL;
    string ruta;
    RBT()
    {
        ruta = "grafico.dot";
        this->root=0;
        NIL = new leaf<T>(0);
        NIL->color=NEGRO;
        NIL->valor=-65;
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

    void add(T valor)
	{
		add(valor, root, root);
	}
	void add(T valor, leaf<T> *& m_leaf, leaf<T> * padre)
	{
		if(!m_leaf || m_leaf==NIL)
		{
			leaf<T> * nuevo = new leaf<T>(valor);
			nuevo->hijo[0]=NIL;
			nuevo->hijo[1]=NIL;
			nuevo->padre= padre;
            m_leaf = nuevo;
            corregir(m_leaf);
		}
		else
		{
			if(valor==m_leaf->valor) return;
			if(valor<m_leaf->valor)
            {
                add(valor,m_leaf->hijo[0],m_leaf);
            }
			else
            {
                add(valor,m_leaf->hijo[1],m_leaf);
            }
		}
	}
	void corregir(leaf<T> *& nodo)
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
	void verificarColor(leaf<T> *& nodo)
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
	void rotacionDerecha(leaf<T> *& nodo, bool pos)
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
	void rotacionIzquierda(leaf<T> * nodo, bool pos)
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
	leaf<T> * tio(leaf<T> *& nodo)
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
	void print(leaf<T> * aux, ofstream * archivo)
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

};
