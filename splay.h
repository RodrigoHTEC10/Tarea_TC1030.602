/*
Title: Homework No. 7 - Splay Tree
Date: November 4th, 2025
Author: Rodrigo Alejandro Hurtado Cortes - A01713854

Description: Homework that shows the implementation of a splay tree 
with the desired functions that satisfy the main file requirements
based on the given instructions.
*/

#ifndef SPLAY_H_
#define SPLAY_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class SplayTree;


/*
====================================================================
CLASS NODE
Description: Class that contains the PIV and methods of the Node of
a Splay Tree which has the characteristic of storing its parents and
mainly perform the splay operation which moves the desired note to
the root of the tree.
====================================================================
*/
template <class T>
class Node {
private:
	//Private Instance Variables
	T value;
	Node *left, *right, *parent;

	//Private Methods
	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	//Constructors
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);

	//Public Functions
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	Node<T>* splay(Node<T>*, Node<T>*);
	void inorder(stringstream&) const;
	void print_tree(stringstream&) const;
	void preorder(stringstream&) const;
	
	//Friend Class Declaration
	friend class SplayTree<T>;
};

/*
--------------------------------------------------------------------
Constructors Declaration
--------------------------------------------------------------------
Node(T val)

Default constructor that sets the pointers of the Node to 0 and sets
its value as the parameter val.
*/

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

/*
--------------------------------------------------------------------
Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)

Constructor with parameters that sets the pointers and value of the node
as the declared within the parameters [val, le, ri and p].
*/

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}


/*
--------------------------------------------------------------------
Private Methods Declaration
--------------------------------------------------------------------
Node<T>* add(T val)

Recursive method responsible for adding a node of value [val] on the
splay tree depending on its value and the tree data structure ordering 
them with a binary search tree structure and return its pointer.
*/

template <class T>
Node<T>* Node<T>::add(T val) {
	if(val > value){
		if(right){
			return right->add(val);
		}
		else{
			right = new Node<T>(val, 0, 0, this);
			return right;
		}
	}
	else{
		if(left){
			return left->add(val);
		}
		else{
			left = new Node<T>(val, 0, 0, this);
			return left;
		}
	}
	return 0;
}

/*
--------------------------------------------------------------------
Node<T>* find(T val)

Recursive method responsible for looking for a concrete value [val] 
within the nodes of the splay tree following the order of a binary
search tree. 
If the element is found, the function returns its pointer; otherwise,
returns the pointer of the node where the node of value [val] should be
located.
*/

template <class T>
Node<T>* Node<T>::find(T val) {
	if(value == val){
		return this;
	}
	else{
		//Val is greater than actual value.
		if(val > value){
			if(right){
				return right->find(val);
			}
			else{
				return this;
			}
		}
		//Val is less than actual value.
		else{
			if(left){
				return left->find(val);
			}
			else{
				return this;
			}
		}
	}
	return 0;
}

/*
--------------------------------------------------------------------
Node<T>* remove(val)

Recursive method that looks for the node of value [val], obtains a 
succesor for such value using the function Node<T>::successor(), places
this successor in the place of the node to eliminate, and finally
deletes the chosen node leaving the successor at its place.
*/

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *succ, *old;
	
	if(val<value){
		//In case val is less than value
		if(left != 0){
			//In case val is equal to the value of the left children.
			if(left->value == val){
				old = left;
				succ = left->succesor();

				//Only if the succesor is different to null.
				if(succ != 0){

					/*Substitution of the old pointers to the successor
					pointers.*/
					succ->left = old->left;
					succ->right = old->right;
					succ->parent = old->parent;

					/*In case the succesor has children, assings the parent
					pointer to itself.*/
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
				}
				//Elimination of old.
				delete old;
				left = succ;
				return left->parent;
			}
			/*Recursive call in case the value is not equal to the value
			of the left children*/
			else{
				return left->remove(val);
			}
		}
	}
	else{
		//In case val is greater than value
		if(right != 0){
			//In case val is equal to the value of the right children.
			if(right->value == val){
				old = right;
				succ = right->succesor();
				//Only if the succesor is different to null.
				if(succ != 0){

					/*Substitution of the old pointers to the successor
					pointers.*/
					succ->right = old->left;
					succ->right = old->right;
					succ->parent = old->parent;

					/*In case the succesor has children, assings the parent
					pointer to itself.*/
					if(succ->right)
						succ->right->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
				}
				//Elimination of old.
				delete old;
				right = succ;
				return right->parent;
			}
			/*Recursive call in case the value is not equal to the value
			of the left children*/
			else{
				return left->remove(val);
			}
		}
	}
	return this;
}

/*
--------------------------------------------------------------------
Private methods declaration
--------------------------------------------------------------------
Node<T>* succesor()

Recursive method responsible for returning the pointer of the smallest
of the greatest children of a chosen pointer. If the chosen pointer does
not have any greater child, then it returns the pointer of the greatest 
of the smaller children and setting its left and right children for its
parent to keep its elements.
*/

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	//In case the pointer does not have a right child.
	if(right == 0){
		if(left != 0){
			//In case the left children has a left children.
			if(left->left != 0){
				this->left = left->left;
			}
			else{
				this->left=0;
			}

			//In case the left children has a right children.
			if(le->right != 0){
				this->right = le->right;
			}
			else{
				this->right=0;
			}
		}
		return le;
	}

	/*In case the right children of the pointer does not have a left 
	children*/
	else if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}
	
	/*In case the right children of the pointer does have a left 
	children*/
	else{
		Node<T> *parent, *child;
		parent = right;
		child = right->left;
		while (child->left != 0) {
			parent = child;
			child = child->left;
		}
		parent->left = child->right;
		child->right = 0;
		return child;
	}
	
	return 0;
}

/*
--------------------------------------------------------------------
Node<T>* rot_right(Node<T>* x)

Function that performs a right rotation with the pointer x and returns
its new location.
*/

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;

	if(y->right)
		y->right->parent = x;
	y->right = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}


/*
--------------------------------------------------------------------
Node<T>* rot_left(Node<T>* x)

Function that performs a left rotation with the pointer x and returns
its new location.
*/
template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;

	if(y->left)
		y->left->parent = x;
	y->left = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

/*
--------------------------------------------------------------------
Node<T>* splay(Node<T>* root, Node<T>* x)

Iterative method responsible for moving the node x to the root position
through double and simple left and right rotations, returning x at the
end of the procedure.

This complementary function together with add(val), remove(val) and 
find(val) leads to the behavior of the splay tree by moving these
pointers to the root of the tree.
*/
template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		//In case the pointer is already at the root location.
		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		//Actions to take in case x is in a different position.
		}else{
			Node<T>*p = x->parent;
			Node<T>*g = p->parent; 
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

/*
--------------------------------------------------------------------
Complementary functions
--------------------------------------------------------------------
Functions provided by the README.md file.

void print_tree(stringstream &aux)

Recursive method responsible for printing the tree structure showing each
node's parent and children.
*/

template <class T>
void Node<T>::print_tree(stringstream &aux) const {
    if (parent != 0){
        aux << "\n node " << value;
        aux << " parent " << parent->value;
    }else
        aux << "\n root " << value;
    if (left != 0)
        aux << " left " << left->value;
    if (right != 0)
        aux << " right " << right->value;
    aux << "\n";

    if (left != 0) {
        left->print_tree(aux);
    }
    if (right != 0) {
        right->print_tree(aux);
    }
}

/*
--------------------------------------------------------------------
void inorder(stringstream &aux)

Recursive method responsible for printing the values of the splay tree
in ascending order.
*/

template <class T>
void Node<T>::inorder(stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        right->inorder(aux);
    }
}

/*
--------------------------------------------------------------------
void preorder(stringstream &aux)

Recursive method responsible for printing the values of the splay tree
starting from the root, going to the left and right branches after.
*/

template <class T>
void Node<T>::preorder(stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}


/*
====================================================================
SPLAY TREE NODE
Description: Class that contains the splay tree data structure by 
holding its root, constructor and methods that add, find, remove and
print its stored values.
====================================================================
*/

template <class T>
class SplayTree {
private:
	//Private Instance Variables
	Node<T> *root;

public:
	//Public Methods
	SplayTree();
	void add(T);
	bool find(T);
	void remove(T);
	string inorder() const;
	string print_tree() const;
	string preorder() const;
};

/*
--------------------------------------------------------------------
Constructor
--------------------------------------------------------------------
SplayTree()

Default constructor that sets the new tree root to null.
*/

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

/*
--------------------------------------------------------------------
Public Methods Declaration
--------------------------------------------------------------------
void add(T val)

Method responsible for adding the parameter [val] to the splay tree data
structure, and moving it afterwards to the root of the tree.
*/

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

/*
--------------------------------------------------------------------
void find(T val)

Method responsible for finding the parameter [val] on the splay tree 
data structure, and move it to the root of the tree afterwards
It additionally returns a bool in case the val was part of the splay tree.
*/

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

/*
--------------------------------------------------------------------
void remove(T val)

Method responsible for removing the parameter [val] from the splay tree 
data structure, and move its parent to the root of the tree afterwards.
*/

template <class T>
void SplayTree<T>::remove(T val) {
	if(root != 0){
		if(val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}


/*
--------------------------------------------------------------------
Complementary Functions
--------------------------------------------------------------------
string inorder()

Method responsible for returning a string with all the values stored in
the splay tree in order.
*/

template <class T>
string SplayTree<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (root != 0) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

/*
--------------------------------------------------------------------
string print_tree()

Method responsible for returning a string with all the values stored in
the splay tree showing its parents and children in order from root to
bottom.
*/

template <class T>
string SplayTree<T>::print_tree() const {
	stringstream aux;

	if (root != 0) {
		root->print_tree(aux);
	}
	return aux.str();
}


/*
--------------------------------------------------------------------
string preorder()

Method responsible for returning a string with all the values stored in
the splay tree in preorder.
*/
template <class T>
string SplayTree<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (root != 0) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif
