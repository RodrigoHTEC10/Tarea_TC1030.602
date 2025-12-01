/*
Author: Rodrigo Alejandro Hurtado Cortes
Title: List
Homework No. 3
*/

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
using namespace std;

template <class T> class List;

/*
======================================================================
CLASS LINK
Description: Class that represents the object contained within the
linked list.
======================================================================
*/
template <class T>
class Link{
	private:

	//Private Instance Variables
	T value;
	Link<T>* next;

	//Constructors
	Link(T);
	Link(T, Link<T>*);

	/*
	Declaration of Friend class to access the private constructors
	of the Link class.
	*/
	friend class List<T>;
};

/*
Declaration of Constructors
*/

/*
Link(T val)

Constructor which value is obtained from the val parameter while the 
next pointer points to null.
*/
template <class T>
Link<T>::Link(T val): value(val), next(0) {};

//-------------------------------------------------------------------

/*
Link(T val, Link<T>* ptr)

Constructor which value is obtained from the val parameter and its
next pointer points to ptr.
*/
template <class T>
Link<T>::Link(T val, Link<T>* ptr): value(val), next(ptr) {};



/*
======================================================================
CLASS LIST
Description: Class that holds the functions and structure of a linked
list.
======================================================================
*/
template <class T>
class List{        
	private:
		//Private Instance Variables
		Link<T>* head;
		int size;

    public:
		//Constructor
		List();

		//Functions
        void insertion(T);
        int search(T);
        void update(int, T);
		T deleteAt(int);
		string toString() const;        
};

//---------------------------------------------------------------

/*
List()

Default constructor that declares the head to null and size equals 0.
*/
template <class T>
List<T>::List(): head(0), size(0) {};

//---------------------------------------------------------------

/*
void insertion(T value)

Void function that creates a Link object with value [value] added 
to the end of the list, connecting the next pointer of the previous
element
to itself and its pointer points to null.
In case the value is the first element of the list, the head pointer 
points to itself.
*/
template <class T>
void List<T>::insertion(T value){
	Link<T>* ptr;
	ptr = head;
	//Insertion in case its the first element
	if(size == 0){
		Link<T>* link = new Link(value);
		head = link;
		size++;
		return ;
	}
	
	else{
		//Insertion at the last position
		while(ptr != 0){
			if(ptr->next == 0){
				Link<T>* link = new Link(value);
				ptr->next = link;
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

Function that retuns the index where the Link object with value [value]
is located in the list. In case the object is not found, the function
returns -1.
*/
template <class T>
int List<T>::search(T value){
	if(size  > 0){
		Link<T>* ptr;
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
void List<T>::update(int index, T newValue){
	if(size > 0){
		Link<T>* ptr;
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
T List<T>::deleteAt(int index){
	if(size > 0){
		Link<T>* ptr;
		Link<T>* borrar;
		T valor;
		ptr = head;
		int counter = 0;

		//Delete in case it is the first object
		if(index == 0){
			borrar = head;
			valor = borrar->value;
			head = ptr->next;
			borrar->next = 0;	
			delete borrar;
			size --;
		}

		while(ptr != 0){
			//Delete in case the index is other object within the list.
			if(counter+1 == index){
				borrar = ptr->next;
				valor = borrar->value;
				ptr->next = borrar->next;
				borrar->next = 0;
				delete borrar;
				size--;
				return valor;
			}
			else{
				ptr = ptr->next;
				counter++;
			}
		}
		return valor;
	}
	return T(0);
};

//---------------------------------------------------------------
/*
string toString()

Function that returns the string of the list printed in format
[x,x,x].
*/
template <class T>
string List<T>::toString() const {
	stringstream aux;
	Link<T> *p;

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

#endif
