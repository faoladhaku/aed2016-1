#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
template<class T>
class lista;
template<class T>
class heap
{
public:
    T valor;
    int grado;
    bool marcado;
    heap * padre;
    heap * next;
    heap * before;
    lista<T> * hijos;
    heap(T valor)
    {
        this->marcado =0;
        this->padre = 0;
        this->grado=0;
        this->valor=valor;
        this->next = 0;
        this->before= 0;
        this->hijos=0;
    }


};
template <class T>
class lista
{
public:
    heap<T> * cabeza;
    lista()
    {
        this->cabeza=0;


    }
    void add(T valor)
    {
        heap<T> * nuevo = new heap<T>(valor);
        if(!cabeza) cabeza = nuevo;
        else nuevo->next=cabeza;
        cabeza=nuevo;


    }
    void add(heap<T> *& nuevo)
    {

        if(this->cabeza == 0)
        {

            this->cabeza = nuevo;

        }
        else nuevo->next=cabeza;
        cabeza=nuevo;



    }
    void print()
    {
        heap<T> * aux = cabeza;
        while(aux)
        {

            aux= aux->next;
        }
    }

};
template <class T>
class FibonacciHeap
{
public:
    heap<T> * minimo;
    heap<T> * first;
    heap<T> * toTest;
    int tam;
    string ruta;
    FibonacciHeap()
    {
            this->tam = 0;
            ruta = "grafico.dot";
            this->minimo = 0;
            this->first = 0;

    }
    void Sacar(heap<T> * aux)
    {

        if(!aux) return;
       if(aux->before || aux->next)
        {
            if(aux->before && aux->next)
            {
                aux->before->next= aux->next;
                aux->next->before=aux->before;

            }
            else
            {
                if(aux->before) aux->before->next=0;
                if(aux->next)
                {
                    aux->next->before=0;
                    first= aux->next;
                }
            }

        }
        else
        {
            first = 0;
        }
        aux->next=0;
        aux->before=0;
    }
    void cambiar(heap<T> * aux1, heap<T> * aux2)
    {
        T aux3 = aux1->valor;
        aux1->valor = aux2->valor;
        aux2->valor = aux3;
    }
    void unir(heap<T> * nodo, heap<T> ** headHeap,int tamArray)
    {

        if(!first)
        {
            cout<<"no existe primero y se agregara todo"<<endl;
            bool p=0;
            for(int i = 0;i<tamArray;i++)
            {
                if(headHeap[i])
                {
                    if(!p)
                        {
                            first=headHeap[i];
                            p=1;
                        }
                    headHeap[i]->next=0;
                    headHeap[i]->before=0;

                    insertarN(headHeap[i]);


                }

            }

            return;

        }
        if(!nodo) return;
        //if(!nodo->next) return;
        if(headHeap[nodo->grado]==0)
        {
            cout<<"en array no existe grado igual "<<nodo->valor<<endl;
            heap<T> * toSend =nodo->next;

            Sacar(nodo);
            headHeap[nodo->grado]=nodo;

            if(!toSend) first = 0;
            unir(toSend,headHeap,tamArray);
        }
        else
        {
            cout<<"si esxiste en arrar, voy a combinar "<<nodo->valor<<endl;
            Sacar(nodo);

            if(nodo->valor<headHeap[nodo->grado]->valor)
            {
                cout<<"voy a combinar estos "<<nodo->valor<<"------"<<headHeap[nodo->grado]->valor<<endl;
                if(!nodo->hijos) nodo->hijos=new lista<T>();
                nodo->hijos->add(headHeap[nodo->grado]);
                headHeap[nodo->grado]=0;
                nodo->grado++;

                insertarN(nodo);
                unir(nodo,headHeap,tamArray);
            }
            else
            {

                heap<T> * toSend = headHeap[nodo->grado];
                toSend->grado++;
                if(!headHeap[nodo->grado]->hijos) headHeap[nodo->grado]->hijos=new lista<T>();
                headHeap[nodo->grado]->hijos->add(nodo);
                insertarN(headHeap[nodo->grado]);
                headHeap[nodo->grado]=0;
                unir(toSend,headHeap,tamArray);
            }










        }


    }
    void insertarN(heap<T> * nuevo)
    {
        cout<<"insertando elemento: "<<nuevo->valor<<" con grado: "<<nuevo->grado<<endl;
        if(!nuevo) return;
        nuevo->before=0;
        nuevo->next=0;
        if(!first)
        {
            first = nuevo;
            return;
        }
        if(first==nuevo) return;
        first->before = nuevo;
        nuevo->next=first;
        if(minimo)
            if(minimo->valor>nuevo->valor)
            {
                minimo = nuevo;
            }
        first=nuevo;
    }
    void insertar(T valor)
    {
        tam++;
        heap<T> * nuevo = new heap<T>(valor);
        if(!first)
        {
            first = nuevo;
            minimo=nuevo;
            return;
        }

        first->before = nuevo;
        nuevo->next=first;
        if(minimo->valor>nuevo->valor)
        {
            minimo = nuevo;
        }
        first=nuevo;
    }
    void insertar(heap<T> * nuevo)
    {
        if(!nuevo) return;

        if(!minimo)
        {
            minimo = nuevo;
            first = nuevo;
            nuevo->before = 0;
            nuevo->next = 0;
        }

        else
        {
            if(minimo->before)
            {
                minimo->before->next=nuevo;
                nuevo->before=minimo->before;
                minimo->before = nuevo;
                nuevo->next = minimo;
            }
            else
            {
                first = nuevo;
                if(nuevo!=minimo)nuevo->next=minimo;
                minimo->before = nuevo;
                nuevo->before=0;
            }
            if(minimo->valor>nuevo->valor)
            {
                minimo = nuevo;
            }
        }
    }
    heap<T> * extractMin()
    {
        tam--;
        cout<<"extrayendo minimo"<<minimo->valor<<endl;
        if(minimo->hijos)cout<<minimo->valor<<"-- "<<minimo->hijos->cabeza->valor<<endl;
        heap<T> *toReturn = minimo;
        if(minimo->before || minimo->next)
        {
            cout<<"el minimo tiene algun hermano"<<endl;
            if(minimo->before && minimo->next)
            {
                minimo->before->next= minimo->next;
                minimo->next->before=minimo->before;
                minimo->before=0;
                minimo->next=0;

            }
            else
            {
                if(minimo->before)
                {
                    cout<<"tiene hermana atras;"<<endl;
                    minimo->before->next=0;
                    minimo->before = 0;
                    minimo->next = 0;

                    cout<<minimo<<endl;
                    cout<<"x"<<endl;

                }
                if(minimo->next)
                {
                    cout<<"dfsd"<<endl;
                    minimo->next->before=0;
                    first= minimo->next;
                    minimo->before = 0;
                    minimo->next = 0;

                }
                cout<<"dfsd"<<endl;
            }

        }
        else
        {
            cout<<"el minimo esta solo"<<endl;

            minimo->before=0;
            minimo->next=0;
            first->before=0;
            first->next=0;
            first=0;
            minimo=0;

        }

        if(toReturn->hijos)
        {
            //cout<<"dad"<<toReturn->hijos->cabeza->next->next->next<<endl;
            heap<T> * aux = toReturn->hijos->cabeza;
            toReturn->hijos=0;
            while(aux)
            {

                cout<<"hijo del minimo que inserto: "<<aux->valor<<endl;

                heap<T> * aux2 = aux;
                aux=aux->next;
                insertarN(aux2);

            }

        }

        cout<<"se extrajo correctamente"<<endl;
        int tamArray = (int)ceil(log(tam));
        tamArray++;
        heap<T> ** toUnit = new heap<T>*[tamArray];
        for(int i = 0; i<tamArray; i++) toUnit[i]=0;

        unir(first,toUnit,tamArray);
        minimo=first;
        cout<<"luego de union el  first es: "<<first->valor<<endl;
        detectarMinimo(first,first->valor,minimo);
        cout<<"ya detecto el minimo "<<minimo->valor<<endl;
        return toReturn;
    }
    void detectarMinimo(heap<T> * aux,T valor, heap<T> *& mini)
    {
        if(!aux) return;
        //if(!aux->next) return;
        if(aux->valor<valor)
        {
            mini=aux;
            detectarMinimo(aux->next,aux->valor,mini);

        }
        else
        {
            detectarMinimo(aux->next,valor,mini);
        }

    }
    void graficar()
	{

        ofstream * fichero = new ofstream (this->ruta);
        *fichero<<"digraph G {"<<endl;
        heap<T> * aux = first;

        while(aux->next)
        {

            *fichero<<aux->valor<<"->"<<aux->next->valor<<endl;
            if(aux->hijos)print(aux,aux->hijos->cabeza,fichero);
            aux = aux->next;
        }

        if(aux)
            if(aux->hijos)  print(aux,aux->hijos->cabeza,fichero);
        *fichero<<"}";
        fichero->close();

	}
	void print(heap<T> * dad, heap<T> * aux, ofstream * archivo)
	{

	    if(!aux)return;
        while(aux)
        {
            *archivo<<dad->valor<<"->"<<aux->valor<<endl;
            if(aux->hijos) print(aux,aux->hijos->cabeza,archivo);
            aux = aux->next;
        }
	}

};