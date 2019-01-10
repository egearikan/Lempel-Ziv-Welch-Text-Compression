#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

static int Number=256;

template<class T> 
class BinarySearchTree
{
private:
	struct tree_node
	{
		tree_node* left;
		tree_node* right;
		T data;
		int code;
	};
	tree_node* root;

public:
	BinarySearchTree();
	~BinarySearchTree();
	bool isEmpty() const { return root==NULL; }
	void insert(T,int);

	int GetNumber(T);
	bool find(T);
	void mEmpty();
	void makeEmpty(tree_node*) ;
};

template<class T>
BinarySearchTree<T>::BinarySearchTree(){
	root=NULL;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree(){
	mEmpty();
}

template <class T>
void BinarySearchTree<T>::mEmpty(){
	makeEmpty(root);
}

template<class T>
void BinarySearchTree<T>::makeEmpty(tree_node *root){
	tree_node* temp=root;
	if (temp != NULL) {
		makeEmpty(temp->left);
		makeEmpty(temp->right);
		delete temp;
	}
	root = NULL;
}

template <class T>
void BinarySearchTree<T>::insert(T d,int c){

	tree_node* t = new tree_node;
	tree_node* parent;
	t->data = d;
	t->code=c;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;
	// is this a new tree?
	if(isEmpty()) root = t;
	else{

		if(!find(d)){//if the item exist in tree then we wont add it

			//Note: ALL insertions are as leaf nodes
			tree_node* curr;
			curr = root;
			// Find the Node's parent
			while(curr){
				parent = curr;
				if(t->data > curr->data) curr = curr->right;
				else curr = curr->left;
			}

			if(t->data < parent->data)
				parent->left = t;
			else
				parent->right = t;
		}
	}
}

template <class T>
bool BinarySearchTree<T>::find(T d){
	//Locate the element
	bool found = false;
	if(isEmpty())
		return false;

	tree_node* curr;
	tree_node* parent;
	curr = root;
	parent = (tree_node*)NULL;
	while(curr != NULL){
		if(curr->data == d){
			found = true;
			break;
		}
		else{
			parent = curr;
			if(d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if(!found)
		return false;
	else
		return true;
}

template <class T>
int BinarySearchTree<T>::GetNumber(T d){//it will search the string of interest and return the number of the string

	tree_node* curr;
	tree_node* parent;
	curr = root;

	parent = (tree_node*)NULL;
	while(curr != NULL){
		if(curr->data == d){
			return curr->code;
			break;
		}
		else{
			parent = curr;
			if(d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
}

int main(){

	BinarySearchTree<string> bst;
	string line1,c="";
	string uncompressed="";
	ifstream input1;
	ofstream encode;

	input1.open("compin.txt");
	encode.open("compout.txt");

	char asd;
	while(input1.get(asd)){//read an save all the char of txt file into a string
		uncompressed=uncompressed+asd;
	}


	string cp ;
	for(string::const_iterator it = uncompressed.begin(); it != uncompressed.end(); ++it){//encoding

		char p = *it;//it will be iterated to every char in the string
		cp = c + p;

		if(bst.find(cp))
			c=cp;

		else if (cp.size()>1){

			if(c.size()==1){//print out the code of ascii number of c since it contains a only char 
				char temp=c[0];
				encode<< (int) temp<< " ";
			}
			else 
				encode<<bst.GetNumber(c)<< " ";//or it will directly find the new encoded string's number in dict

			if(Number<4096){//in case if number reaches 4096 it wont add this to dict however it will store the string
				bst.insert(cp,Number);
				Number++;
			}

			c = string(1, p);//iterating the c
		}

		else if (cp.size()==1){
			c = string(1, p);//to hold the prev char
		}
	}

	if(!c.empty()){//to print out the last string s
		if(c.size()==1){
			char temp=c[0];
			encode<< (int) temp<< " ";
		}
		else
			encode<<bst.GetNumber(c)<< " ";
	}

	encode.close();////end of encoding
	bst.~BinarySearchTree();
	return 0;
}
