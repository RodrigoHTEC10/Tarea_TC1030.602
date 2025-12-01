/*
Author: Rodrigo Alejandro Hurtado Cortes
Title: Heap
Date: October 20th
Homework No. 5
*/

#ifndef HEAP_H_
#define HEAP_H_

using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/*
======================================================================
CLASS Heap
Description: Class that contains the PIV and methods of a Min Heap 
Tree that prioritizes having the smaller numbers in the higher levels
of the data structure. 
======================================================================
*/
template <class T>
class Heap{
    private:
        //Private Instance Variables
        T* data;
        unsigned int siz;
        unsigned int count;

        //Private Functions
        void heapify(int);
        int left(int);
        int right(int);
        void swap(int, int);

    public:
        //Public Functions
        Heap(unsigned int);
        void push(T);
        void pop();
        T top();
        bool empty();
        int size();
        string toString() const;
};

/*
//-------------------------------------------------------------------/
Declaration of Private Functions
//-------------------------------------------------------------------/

int left(int pos)

Function that returns the left son of the element whose index is the 
[pos] parameter.
*/

template <class T>
int Heap<T>::left(int pos){
	return (pos*2)+1;
}

//-------------------------------------------------------------------/
/*
int right(int pos)

Function that returns the right son of the element whose index is the 
[pos] parameter.
*/
template <class T>
int Heap<T>::right(int pos){
	return (pos*2)+2;
}

//-------------------------------------------------------------------/
/*
void swap(int i, int j)

Function responsible for swapping the elements located on the indexes
[i] and [j].
*/ 
template <class T>
void Heap<T>::swap(int i, int j){
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
	return ;
}

//-------------------------------------------------------------------/
/*
void heapify(int pos)

Recursive function that starting from [pos] in the Head data structure
checks in order if the left and right son of element have a greater
priority that itself. In case it is true, a swap is performed and 
a revision is performed in the sons, making the recursive call with 
their position.
*/
template <class T>
void Heap<T>::heapify(int pos) {
	if(pos >= 0 && pos <= count){
        int left_p, right_p;
        left_p = left(pos);
        right_p = right(pos);

        /*Check if the left is an avaliable index based on the number
        of elements*/
        if(left_p <= count){
			if(data[left_p] > 0){
				if(data[pos] > data[left_p]){
					swap(pos, left_p);
				}
			}
            //Recursive call
            heapify(left_p);
		}

        /*Check if the right is an avaliable index based on the number
        of elements*/
		if(right_p <= count){
			if(data[right_p] > 0){
				if(data[pos] > data[right_p]){
					swap(pos, right_p);
				}
			}
            //Recursive call
            heapify(right_p);
		}
		return ;
	}
	return ;
}

/*
//-------------------------------------------------------------------/
Declaration of Public Functions
//-------------------------------------------------------------------/

Heap(unsigned int sze)

Default constructor of a Heap data structure that creates an internal 
array of [sze] elements, saving its size on the siz variable and the
number of elements contained within it inside the variable count, 
setting it to 0.
*/
template<class T>
Heap<T>::Heap(unsigned int sze){
    siz = sze;
    data = new T[siz];
    count = 0;
};

//-------------------------------------------------------------------/
/*
void push(T val)

Function responsible for adding an element to the Head data structure,
increase count and use the function heapify() to secure the right order
of the elements.
*/
template<class T>
void Heap<T>::push(T val){
	data[count++] = val;
	heapify(0);	
};

//-------------------------------------------------------------------/
/*
void pop()

Function responsible for eliminating the first element of the Head data
structure, decrease count and use the function heapify() to secure the
right order of the elements.
*/
template<class T>
void Heap<T>::pop(){
    data[0] = data[count-1];
    data[count-1] = 0;
    count--;
    heapify(0);
};

//-------------------------------------------------------------------/
/*
T top()

Function responsible for returining the first element of the Heap data
structure which is the smallest, as this is the highest priority.
*/
template<class T>
T Heap<T>::top(){
    return data[0];
};

//-------------------------------------------------------------------/
/*
bool empty()

Function responsible for returning a boolean that indicates if the Heap
data structure is empty.
*/

template<class T>
bool Heap<T>::empty(){
    return (siz == count);
};

//-------------------------------------------------------------------/
/*
int size()

Function responsible for returning the number of elements contained in 
the Heap data structure.
*/
template<class T>
int Heap<T>::size(){
    return count;
};

//-------------------------------------------------------------------/
/*
string toString()

Function responsible for returning the elements of the Heap data 
structure as a string in order from left to right lowering levels.
*/
template <class T>
string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}


#endif