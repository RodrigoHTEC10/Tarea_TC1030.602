/*
Title: Homework No. 9 - Hashes
Date: November 27th, 2025
Author: Rodrigo Alejandro Hurtado Cortes - A01713854

Description: 
Homework that shows the implementation of hashes with a quadratic
collition handling technique.
*/

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
==============================================================
Class Quadratic
==============================================================
Description:
Class that shows the implementation of a hash data structure
with a quadratic collition handling technique; which has a 
determined size, a concrete parameterized hash function and 
an elements count.

This data structure allows to access information faster based 
on a defined key that interpreted with a hasg function turns 
the key into the index of the element itself.

The current file was mainly created taking as a base the hash
class exercise modifying the collition handling technique and
eliminating unused methods.
*/

template <class Key, class Value>
class Quadratic {
private:
    //Private Instance Variables
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

    //Private methods
	long indexOf(const Key) const;
public:
    //Constructor
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	
    //Public methods
    bool full() const;
	void put(Key, Value);
	Value get(const Key) ;
	std::string toString() const;
};


/*Declaration of Public Methods*/
/*--------- Constructor ---------*/
/*
Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))

Constructor that defines the size of the hash data structure [sze], 
the initial value of the keys [init] and the Hash Function defined
outsdide the class [f].
*/
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	size = sze;
	initialValue = init;
	count = 0;
	func = f;

	keys = new Key[size];
	std::fill_n(keys, size, init);

	values = new Value[size];
	std::fill_n(values, size, 0);
};


/*--------- Private Methods ---------*/
/*
long indexOf(const Key k) const

Method responsible for returning the index if there is any where the key
[k] is found within the array keys based on the collition handling
technique.

If the key is not found until the check returns to the starting index,
returns -1.
*/
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	int check, start, i;
	i = 1;
	start = func(k) % size;
	check = start;
	do{
		if(keys[check] == k)
			return check;
		check = int(check + pow(i,2)) %size;
        i++;
	}while(start != check);
	return -1;
};

/*--------- Public Methods ---------*/
/*
bool full() const

Method responsible for returning a bool in case the count of elements
is greater than the defined size of the data structure.
*/
template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
};


//---------------------------------------------------------
/*
bool put(Key k, Value v)

Method responsible for adding the value [v] at the position
defined based on the hash function func() applied to the key
[k].
If the structure is full, its not able to add it.

In case the key is already in the data structure, the value
is overwritten at the same index as found.

In case the key is not on the data structure, the initial hash
or the quadratic collition handling technique will define the
index for both the key [k] and the value [v].
*/
template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v) {
	int pos, start, i, check;

    //If full, the function is ended inmediately.
    if(full()){
        return ;
    }

    //Check if key is already in keys.
	pos = indexOf(k);
	if(pos != -1){
		values[pos] = v;
		count++;
        return ;
	}

    //Adding k to keys
    i = 1;
	start = func(k)%size;
	check = start;
	do{
		if(keys[check]==initialValue){
			keys[check] = k;
			values[check] = v;
			count++;
			return;
		}
		check =int(check+pow(i,2))%size;
        i++;
	}while(start != check);

	return;
};


//---------------------------------------------------------
/*
Value get(const Key k)

Method responsible for retuning the value saved under the key
[k] inside the hash data structure.

If the key is not inside the structure, it returns -1.
*/
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	Value v;
	unsigned int i, start;

	i = indexOf(k);
	if(i != -1){
		return values[i];
	}
    return -1;
};


//---------------------------------------------------------
/*
string toString() const

Method responsible for returning a string with the index, key
and values stored inside the has data structure whose keys are
different to the initial value defined [initialValue].

Method provided by the professor Benjamín Valdés Aguirre. 
*/
template <class Key, class Value>
string Quadratic<Key, Value>::toString() const {
    stringstream aux;
    for (int i = 0; i < size; i++){
        if (keys[i] != initialValue){
            aux << "(" << i << " ";
            aux << keys[i] << " : " << values[i] << ") ";
        }
    }
    return aux.str();
};

#endif
