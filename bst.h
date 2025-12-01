/*
Author: Rodrigo Alejandro Hurtado Cortes
Title: DList
Date: October 8th
Homework No. 4
*/

#ifndef BST_H_
#define BST_H_

using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template <class T> class BST;

/*
======================================================================
CLASS TreeNode
Description: Class that represents the nodes contained within a binary
search tree structure.
======================================================================
*/

template <class T>
class TreeNode {
private:
	//Private Instance Variables
	T value;
	TreeNode *left, *right;

public:
	//Constructors
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	
	//Public Functions
	void add(T);
	int findLevel(T, int);
    bool find(T);
    string findAncestor(T, string);
	int checkLevel(int);
	void inorder(stringstream&) const;
	void preorder(stringstream&) const;
    void postorder(stringstream&) const;
	void collectValues(vector<T>&);

	friend class BST<T>;
};

/*
Declaration of Functions
*/


/*
TreeNode(T val)

Constructor that assigns the value of the node as the parameter val
and assigns both pointers left and right to null.
*/
template <class T>
TreeNode<T>::TreeNode(T val): value(val), left(0), right(0) {}

//---------------------------------------------------------------
/*
TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri)

Constructor that assigns the value of the node as the parameter val
and assigns pointers left and right to le and ri respectively.
*/
template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri): value(val), left(le), right(ri) {}

//---------------------------------------------------------------
/*
void add(T val)

Function responsible for adding the value val depending on the value 
comparison of the parameter val compared to the value of the node.

Depending on the presence or absence of pointers left and right, either 
a new node is created on those pointers or the value is passed to be
added on the next node.
*/
template <class T>
void TreeNode<T>::add(T val) {
	if(val > value){
		if(right == 0){
			right = new TreeNode<T>(val);
		}else{
			right->add(val);
		}
	}
	else{
		if(left == 0){
			left = new TreeNode<T>(val);
		}else{
			left->add(val);
		}
	}
	return;
}

//---------------------------------------------------------------
/*
int find(T val, int counter)

Recursive function that per each level down into the tree trying to find
the value [val] increases the counter for 1, returining the final counter
once the value has been found.

As a precondition for this function is that the value val must be a valid
number within the BST, there is no need to add an alternative return.
*/
template <class T>
int TreeNode<T>::findLevel(T val, int counter) {
	if(value == val){
		return counter;
	}
	else if(val > value) {
        if(right != 0){
            return (right->findLevel(val,  counter+1));
        }
	}
	else{
		if(left != 0){
            return (left->findLevel(val,  counter+1));
        }
	}
    return 0;
}

//---------------------------------------------------------------
/*
bool find(T val)

Recursive function that returns a bool in case the value [val] forms part
of the nodes of the tree.
*/
template <class T>
bool TreeNode<T>::find(T val) {
	if(value == val){
		return true;
	}
	else if(val > value) {
		return (right != 0 && right->find(val));
	}
	else{
		return (left != 0 && left->find(val));
	}
}


//---------------------------------------------------------------
/*
string findAncestor(T val, string ances)

Recursive function that while looking for a number, adds each the passed
numbers to the string [ances] until the value [val] is found within the 
tree, then returns the list of numbers obtained as a string.
*/
template <class T>
string TreeNode<T>::findAncestor(T val, string ances) {
	if(value == val){
		return ances; 
	}
	else if(val > value) {
        ances = ances +to_string(value)+" ";
        if(right != 0){
            return (right->findAncestor(val, ances));
        }
        else{
            return "[]";
        }
	}
	else{
        ances = ances+" "+ to_string(value)+" ";
		if(left != 0){
            return (left->findAncestor(val, ances));
        }
        else{
            return "[]";
        }
	}
}

//---------------------------------------------------------------
/*
int checkLevel(int level)

Function responsible for returning the maximum number of levels
of a tree based on a recursive strategy that returns the level
only if a leaf has been reached; otherwise, a comparison between
the right and left levels will be executed always returning the
greatest level.
*/
template <class T>
int TreeNode<T>::checkLevel(int level){
	
	if(right==0 && left==0){
		return level;
		cout<<to_string(level)<<endl;
	}

	else{
		int rightLevel = 0;
		int leftLevel = 0;

		if(right!=0){
			rightLevel = right->checkLevel(level+1);
		}
		if(left!=0){
			leftLevel = left->checkLevel(level+1);
		}
		if(rightLevel>leftLevel)
			return rightLevel;
		return leftLevel;
	}
};



//---------------------------------------------------------------
/*
void inorder(stringstream &aux) const

Function responsible for printing nodes of the tree structure in
order.
*/
template <class T>
void TreeNode<T>::inorder(stringstream &aux) const {
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

//---------------------------------------------------------------
/*
void preorder(stringstream &aux) const

Function responsible for printing nodes of the tree structure in
preorder.
*/
template <class T>
void TreeNode<T>::preorder(stringstream &aux) const {
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

//---------------------------------------------------------------
/*
void postorder(stringstream &aux) const

Function responsible for printing nodes of the tree structure in
postorder.
*/
template <class T>
void TreeNode<T>::postorder(stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
		aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
		aux << " ";
	}
	aux << value;
	
}

//---------------------------------------------------------------
/*
void collectValues(vector<T>& vect)

Function responsible for adding all the elements contained in the
nodes following the TreeNode from which it was called in a vector
to return it.
*/
template <class T>
void TreeNode<T>::collectValues(vector<T>& vect){
	vect.push_back(value);
	if (left != 0) {
		left->collectValues(vect);
	}
	if (right != 0) {
		right->collectValues(vect);
	}
}

/*
======================================================================
CLASS BST
Description: Class that represents the binary search tree structure.
======================================================================
*/
template <class T>
class BST {
private:
	//Private Instance Variable
	TreeNode<T> *root;
	int size;
    
public:
	//Constructor
	BST();

	//Public Functions
	bool empty();
	void add(T);
	bool find(T);
    int height();
    int whatlevelamI(T);
    string ancestors(T);
    string visit();
	string inorder();
	string preorder();
    string postorder();
    string byLevel();
};

/*
Declaration of Functions
*/

/*
BST()

Default constructor that established the root of the tree pointer to
null.
*/

template <class T>
BST<T>::BST() : root(0), size(0) {}

//---------------------------------------------------------------
/*
bool empty()

Function that returns a bool as true if the root pointer is null,
therefore there are no nodes in the tree.
*/
template <class T>
bool BST<T>::empty(){
	return (root == 0);
}

//---------------------------------------------------------------
/*
void add(T val)

Function responsible for adding a new TreeNode to the data structure
depending on the value of the parameter val.
If the root pointer is null, it directly adds a new TreeNode; otherwise,
the function TreeNode<T>::add(T val) is called from the pointer only if 
the value does not form part already of the tree data structure.
*/
template<class T>
void BST<T>::add(T val) {
	if(root == 0){
		root = new TreeNode<T>(val);
		size++;
	}
	else{
		if(!root->find(val)){
			root->add(val);
			size++;
		}
	}
	
}

//---------------------------------------------------------------
/*
bool find(T val)

Function responsible for returning a bool value depending on the
presence or absence of the value [val] on the tree data structure.

If the root pointer is null, it returns false inmediately; otherwise,
the result of the function TreeNode<T>::find(T val) is returned.
*/
template <class T>
bool BST<T>::find(T val) {
	if(root != 0){
		return root->find(val);
	}
	else{
		return false;
	}
}

//---------------------------------------------------------------
/*
int BST<T>::height()

Function responsible for retuning the maximum level of the tree
data structure.
*/

template <class T>
int BST<T>::height(){
    if(empty())
	{
		return 0;
	}
	else{
		return root->checkLevel(1);
	}
	
};

//---------------------------------------------------------------
/*
string inorder(){

Function responsible for returning the elements of the tree in 
order structure as a string.
*/
template <class T>
string BST<T>::inorder(){
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

//---------------------------------------------------------------
/*
string preorder()

Function responsible for returning the elements of the tree in
pre order structure as a string.
*/
template <class T>
string BST<T>::preorder(){
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

//---------------------------------------------------------------
/*
string postorder()

Function responsible for returning the elements of the tree in
post order structure as a string.
*/
template <class T>
string BST<T>::postorder(){
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

//---------------------------------------------------------------
/*
string byLevel()

Function responsible returning the elements of the tree by level 
structure as a string. 
*/
template <class T>
string BST<T>::byLevel(){
	string text = "[";
	if (!empty()) {
        vector<int> values;
		//Getting the values contained within the tree structure.
		root->collectValues(values);

		int valueLevel;
		//Loop through the maximum number of levels.		
		for(int level = 1 ; level<=height(); level++){
			/*
			Loop through the elements of the vector values to identify
			which belongs to the current level of the outer loop in
			order to add it to the string text.
			*/
			for(int i = 0; i<values.size(); i++){
				//Use of the findLevel() function previously described.
				valueLevel = root->findLevel(values[i], 1);
				if(valueLevel == level){
					text += to_string(values[i])+" ";
				}
			}
		}
		text.pop_back();
	}
	text += "]";
	return text;
	
}

//---------------------------------------------------------------
/*
string visit(){

Returns a string that compiles the four ways to print the nodes of a tree
in the following order.
1. Preorder
2. In Order
3. Postorder
4. By Level
*/
template <class T>
string BST<T>::visit(){
    return preorder() +"\n"+ inorder() +"\n"+ postorder() +"\n"+ byLevel();
}

//---------------------------------------------------------------
/*
int whatlevelamI(T val)

Function responsible for returning the level at which an element has been
found in the tree data structure.
*/
template <class T>
int BST<T>::whatlevelamI(T val){
    if(root != 0){
		return root->findLevel(val, 1);
	}
    return 0;
};

//---------------------------------------------------------------
/*
string ancestors(T val)

Function responsible for returning a string that collects all the 
elements previous to the value [val] in straight line from the root.
*/
template <class T>
string BST<T>::ancestors(T val){
    if(root != 0){
        string ancestors = root->findAncestor(val, "[");
        ancestors = ancestors.substr(0, ancestors.length()-1)+"]";
        return ancestors;
	}
    return "[]";
};



#endif