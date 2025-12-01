/*
Autor: Rodrigo Alejandro Hurtado Cortes - A01713854
Fecha: Septiembre 8, 2025
*/

#include <iostream>
#include <vector>

#ifndef SORTS_H_
#define SORTS_H_

using namespace std;

template <class T>
class Sorts
{

private:
    void swap(std::vector<T>&, int, int);
    void split(std::vector<T>&, std::vector<T>&, int, int);
    void order(std::vector<T>&, std::vector<T>&, int, int, int);
    void copyy(std::vector<T>&, std::vector<T>&, int, int);

public:
    Sorts(){};
    
    Sorts(vector<T>&){};

    void ordenaSeleccion(std::vector<T>&);
    void ordenaBurbuja(std::vector<T>&);
    void ordenaMerge(std::vector<T>&);
    int busqSecuencial(const std::vector<T>&, T);
    int busqBinaria(const std::vector<T>&, T);
};


/*Funcion Auxiliar Swap
Ayuda al intercambio de los elementos en dos indexes diferentes del vector source.
*/
template <class T>
void Sorts<T>::swap(std::vector<T> &source, int one, int two){
    T temp = source[one];
    source[one] = source[two];
    source[two] = temp;
}


//-----------------------------------------------------------------------
//Funciones
/*Selection Sort
Busqueda del minimo y avanze en el limite del ordenamiento despues del 
minimo.
*/

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &source){
    
    for(int i = 0; i<source.size(); i++){
        int min = source[i];
        int min_key = i;

        for (int j = source.size()-1; j > i; j--){
            if(source[j] < min){
                min = source[j];
                min_key = j;
            }
        }
        
        if(min_key != i){
            swap(source, min_key, i);
        }
    }
};

//-----------------------------------------------------------------------

/*Bubble Sort
Ordenamiento en orden desde el extremo derecho al izquierdo, de modo que
los minimos son los primeros en estar en orden.
*/

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &source){

    for(int i = 0; i<source.size(); i++){
        for(int j = source.size()-1; j>i; j--){
            if(source[j]<source[j-1])
                swap(source, j, j-1);
        }
    }

};


//-----------------------------------------------------------------------

/*Merge Sort
Algoritmo de ordenamiento recursivo que hace uso de tres funciones
auxiliares, una que divide, una que ordena los conjuntos y una funcion
que copia los resultados.
*/

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &source){
vector<T> copy(source.size());

split(source, copy, 0, source.size()-1);
};

/***************************************************************/
/*Funcion auxiliar Split
Divide el vector en secciones a la mitad hasta llegar a los elementos 
unitarios del mismo.
*/

template<class T>
void Sorts<T>::split(std::vector<T> &source, std::vector<T> &copy, int start, int end){
    if((end-start)< 1){
        return;
    }
    else{
      int mid = (start+end)/2;
      split(source, copy, start, mid);
      split(source, copy, mid+1, end);

      order(source, copy, start, mid, end);
      copyy(source, copy, start, end);  
    }
};

/***************************************************************/
/*Funcion auxiliar Order
En base a los conjuntos obtenidos de las divisiones ordenadas, 
la funcion parte y ordena ambos conjuntos en una sola cadena.
*/

template<class T>
void Sorts<T>::order(std::vector<T> &source, std::vector<T> &copy, int start,int mid, int end){
    int start1 = start;
    int start2 = mid+1;
    int finalOrder = start;


    while(start1 <= mid && start2 <= end){
        if(source[start1] < source[start2]){
            copy[finalOrder] = source[start1];
            start1++;
        }
        else{
            copy[finalOrder] = source[start2];
            start2++;
        }
        finalOrder++;
    }

    if(start2 > end){
        for(; start1 <= mid; start1++){
            copy[finalOrder++] = source[start1];
        }
    }
    else{
        for(; start2 <= end; start2++){
            copy[finalOrder++] = source[start2];
        }
    }


};

/***************************************************************/
/*Funcion auxiliar Copy
Copia el vector copy en el vector original source entre los limites
establecidos start, end.
*/
template<class T>
void Sorts<T>::copyy(std::vector<T> &source, std::vector<T> &copy, int start, int end){
    for(int i = start; i<= end; i++){
        source[i] = copy[i];
    }
};


//-----------------------------------------------------------------------


/*Sequantial Search
Busqueda de un elemento dentro de un vector utilizando un ciclo for que
va de inicio a fin.
*/
template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &source, T valor){
    
    for(int i=0; i<source.size(); i++){
        if(source[i] == valor){
            return i;
        }
    }
    return -1;
};


//-----------------------------------------------------------------------
/*Sequantial Search
Busqueda de un elemento dentro de un vector a traves de la busqueda
binaria donde se llega hasta n elementos.
*/
template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &source, T valor){
    
    int start = 0;
    int end = source.size()-1;
    

    while((end-start) > 1){
        int mid = (start+end)/2;
        if(source[mid] == valor)
            return mid;
        else if(source[mid]<valor){
            start = mid+1;
        }
        else{
            end = mid-1;
        }
    }  
    
    return -1;
};

#endif
