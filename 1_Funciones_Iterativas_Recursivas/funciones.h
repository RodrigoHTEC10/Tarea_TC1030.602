/*
Autor: Rodrigo Alejandro Hurtado Cortes - A01713854
Fecha:  19 de Agosto del 2025
*/


#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones{

    public:
        Funciones(){}

        /*
        Funcion sumaIterativa(int n) realiza la suma de todos los 
        numeros desde 0 hasta n a traves de una iteracion y regresa
        suma como un numero entero.
        
        Big O Notation: O(n)  lineal ya que depende del parametro n.
        */


        int sumaIterativa(int n){
            int suma = 0;
            for(int i = 0; i<=n; i++){
                suma += i;
            }
            return suma;
        }

        /*------------------------------------------------------------*/

        /*
        Funcion sumaRecursiva(int n) realiza la suma de todos los 
        numeros desde 0 hasta n a traves de recursión y regresa
        suma como un numero entero.

        Logica: Comenzando desde el numero hasta que el parametro sea 
        igual a 0 y devuelva 0 (caso base), todos los numeros se van
        sumando con el obtenido de la suma del anterior. 
        Se aplico recursion izquierda / cabeza.

        Big O Notation: O(2n) ya que es necesario recorrer dos veces
        el tamaño de n para recolectar los numeros y posteriormente
        realizar las operaciones pendientes (sumas).
        */

        int sumaRecursiva(int n){
            if(n==0)
                return 0;
            else
                return sumaRecursiva(n-1)+n;
        }

        /*------------------------------------------------------------*/

        /*
        Funcion sumaDirecta(int n) realiza la suma de todos los 
        numeros desde 0 hasta n a traves de una sola operacion
        matematica y regresa dicha suma como un numero entero.

        Logica: Para obtener la sumatorio del 1 al 5.
        Si colocamos los numeros del 1 al 5, y debajo de este en el
        orden contrario colocamos los mismos numeros y los sumamos
        obtendremos 5 numeros 6, es decir 30, pero dado que tenemos
        dos series de numeros, lo dividimos entre 2, dandonos 15.
        El resultado de la sumatoria.
        
        Aplicando este principio sabemos que tendremos el numero n de
        numeros n+1 y tenemos que dividirlo entre 2. Dandonos la formula
        empleada: (n*(n+1))/2. 

        Big O Notation: O(1) ya que la operacion siempre seria la misma.
        */

        int sumaDirecta(int n){
            return (n*(n+1)/2);
        }

};

#endif 
