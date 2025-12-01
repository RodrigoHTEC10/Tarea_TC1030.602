/*
Author: Rodrigo Alejandro Hurtado Cortes
Title: DList
Date: September 29th
Homework No. 4
*/

#ifndef DLIST_H_
#define DLIST_H_

#include <iostream>
#include <string>

using namespace std;

template <class T> class DList;

/*
======================================================================
CLASS DLINK
Description: Class that represents the object contained within the
double linked list.
======================================================================
*/
template <class T>
class DLink {
private:
    //Constructors
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);

    //Private Instance Variables
	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	//Frind Class to access DLink PIV and functions.
	friend class DList<T>;
};

/*
Declaration of Constructors
*/


/*
DLink(T val)

Constructor which value is obtained from the val parameter while the 
pointers point to null.
*/
template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}


/*
DLink(T val, DLink *prev, DLink* nxt)

Constructor which value is obtained from the val parameter and its
pointers point to prev and nxt respectively.
*/
template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

/*
======================================================================
CLASS LIST
Description: Class that holds the functions and structure of a double 
linked list.
======================================================================
*/

template <class T>
class DList {
private:
    //Private Instance Variables
    DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

public:
    //Constructor
	DList();

    //Functions
    void insertion(T);
    int search(T);
    void update(int, T);
    T deleteAt(int);
	string toStringForward() const;
	string toStringBackward() const;

};

//---------------------------------------------------------------

/*
DList()

Default constructor that declares the head and tail pointers to null
and size equals 0.
*/
template <class T>
DList<T>::DList(): head(0), tail(0), size(0) {};

//---------------------------------------------------------------

/*
void insertion(T value)

Void function that creates a DLink object with value [value] added 
to the end of the list, connecting the next pointer of the previous
element and tail to itself, its pointer next to null and previous to 
the previous element.

In case the value is the first element of the list, the head and tail 
pointer points to itself.
*/
template <class T>
void DList<T>::insertion(T value){
	DLink<T>* ptr;
	ptr = head;
	//Insertion in case its the first element
	if(size == 0){
		DLink<T>* link = new DLink(value);
		head = link;
		tail = link;
		size++;
		return ;
	}
	
	else{
		//Insertion at the last position
		while(ptr != 0){
			if(ptr->next == 0){
				DLink<T>* link = new DLink(value);
				ptr->next = link;
				link->previous = ptr;
				tail = link;
				size++;
				return;
			}
			else{
				ptr = ptr->next;
			}
		}
	}

	
};

//---------------------------------------------------------------

/*
int search(T value)

Function that retuns the index where the DLink object with value [value]
is located in the list. In case the object is not found, the function
returns -1.
*/
template <class T>
int DList<T>::search(T value){
	if(size  > 0){
		DLink<T>* ptr;
		ptr = head;
		int counter = 0;

		while(ptr != 0){
			if(ptr->value == value){
				return counter;
			}
			else{
				ptr = ptr->next;
				counter++;
			}
		}
	}
	return -1;
};

//---------------------------------------------------------------
/*
void update(int index, T newValue)

Void function that at position index changes the value of the 
respective object to newValue.
*/
template <class T>
void DList<T>::update(int index, T newValue){
	if(size > 0){
		DLink<T>* ptr;
		ptr = head;
		int counter = 0;

		while(ptr != 0){
			if(counter == index){
				ptr->value = newValue;
				return;
			}
			else{
				ptr = ptr->next;
				counter++;
			}
		}
	}
	return;
};

//---------------------------------------------------------------
/*
void deleteAt(int index)

Void function that deletes the object at the index [index] of 
the list.
*/
template <class T>
T DList<T>::deleteAt(int index){
	if(size > 0){
		DLink<T>* ptr;
		DLink<T>* borrar;
		T valor;
		ptr = head;
		int counter = 0;

		if(index >= 0 && index<size){
			//Delete in case it is the first object
			if(index == 0){
				borrar = head;
				valor = borrar->value;

				//In case there is only one object in the list
				if(size == 1){
					head = 0;
					tail = 0;
				}
				//In case there are more objects
				else{
					head = ptr->next;
					ptr->next->previous = 0;
				}

				borrar->next = 0;
				borrar->previous = 0;	
				delete borrar;
				size --;
				return valor;
			}

			else{
				while(ptr != 0){
					//Delete in case the index is other object within the list.
					if(counter+1 == index){
						borrar = ptr->next;					
						valor = borrar->value;

						//In case the object to erase is the last one
						if(ptr->next->next == 0){
							tail = ptr;
							ptr->next = 0;						
						}
						//In case the object is neither the first or last.
						else{
							ptr->next = borrar->next;
							borrar->next->previous = ptr;
						}

						borrar->next = 0;
						borrar->previous = 0;	
						delete borrar;
						size --;
						return valor;

					}
					else{
						ptr = ptr->next;
						counter++;
					}
				}
			}
		}
	}
	return T(0);
};


//---------------------------------------------------------------
/*
string toStringForward()

Function that returns the string of the list printed in format
[x,x,x] from head to tail.
*/
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}
//---------------------------------------------------------------
/*
string toStringBackward()

Function that returns the string of the list printed in format
[x,x,x] from tail to head.
*/
template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}



#endif