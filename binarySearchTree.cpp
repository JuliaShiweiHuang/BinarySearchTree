#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> /* printf */
#include <math.h>
#include <queue>

using namespace std;

class treeNode {
public:
	int value;
	treeNode(int integer){ value = integer; left = NULL; right = NULL; };
	friend class BinarySearchTree;
protected:
	treeNode *left, *right, *parent;
	//other stuff
};

class BinarySearchTree {
public:
	BinarySearchTree(){ root = NULL; };
	~BinarySearchTree(){
		destroy_tree(root);
	};
	void insert(int key) {
		if ( root == NULL ) {
			root = new treeNode(key);
		}
		else {
			insert_help(key, root);
		}
	}


	void remove (int v) {
		treeNode *z, *todelete, *x;
		z = search_help(v, root);
		if ( z == NULL ) {
			return;
		}

		if (( z -> left == NULL) || ( z -> right == NULL )) {
			todelete = z;
		}

		else {
			todelete = successor(z);
		}

		if ( todelete -> left == NULL ) {
			x = todelete -> right;
		}

		else {
			x = todelete -> left;
		}

		if ( x != NULL ) {
			x -> parent = todelete -> parent;
		}

		if ( todelete -> parent == NULL ) {
			root = x;
		}

		else {
			if ( todelete -> parent -> left == todelete ) {
				todelete -> parent -> left = x;
			}
			else {
				todelete -> parent -> right = x;
			}
		}

		if ( z != todelete ) {
			z -> value = todelete -> value;
		}

		delete todelete;
	}


	treeNode* search (int key) {
		return search_help(key, root);
	}


	void inOrderTraversal() {
		inOrder_help(root);
	}



private:
	treeNode *root;
	void destroy_tree(treeNode *leaf) {
		if ( leaf != NULL ) {
			destroy_tree(leaf -> left);
			destroy_tree(leaf -> right);
			delete leaf;
		}
	}

	void insert_help(int key, treeNode *leaf) {

		if (( key < leaf->value ) && ( leaf->left != NULL )) {
			insert_help(key, leaf->left);
		}

		if (( key < leaf->value) && ( leaf->left == NULL)) {
			leaf->left = new treeNode(key);
			leaf->left->parent = leaf;

		}

		if (( key > leaf->value ) && ( leaf->right != NULL )){
			insert_help(key, leaf->right);
		}

		if (( key > leaf->value ) && ( leaf->right == NULL)) {
			leaf->right = new treeNode(key);
			leaf->right ->parent = leaf;
			
		}

		if (key == leaf->value) {
			return;
		}
	}

	treeNode* successor(treeNode *c) {
		treeNode *z;
		z = c -> right;
		while ( z -> left != NULL ) {
			z = z -> left;
		}
		return z;
	}


	treeNode* search_help( int key, treeNode *leaf ) {
		if ( leaf == NULL ) {
			return NULL;
		}

		else if ( leaf -> value == key ) {
			return leaf;
		}

		else if ( key < leaf -> value ) {
			return search_help(key, leaf -> left);

		}

		else {
			return search_help(key, leaf->right);
		}
	}

	void inOrder_help (treeNode *leaf) {
		if (leaf == NULL) {
			return;
		}

		if ( leaf != NULL ) {
			inOrder_help(leaf->left);
			//Prints leaf-> value on screen
			cout << leaf -> value << endl;
			inOrder_help(leaf->right);
		}
	}

};




int main () {
// Part1: creates a tree
	BinarySearchTree myTree;
	cout << "Enter numbers. 0 or negative number to stop." << endl;
	int userNum;
	cin >> userNum;
	while ( userNum > 0 ) {
		myTree.insert(userNum);
		cin >> userNum;
	}

// Part2: search the tree
	cout << "Type in a positive integer to search in the tree." << endl;
	int searchNum;
	cin >> searchNum;
	while ( searchNum > 0 ) {
		if ( myTree.search(searchNum) != NULL ) {
			cout << "find " << searchNum << endl;
			cin >> searchNum;
		}
		else {
			cout << "not find " << searchNum << endl;
			cin >> searchNum;
		}
		
	}//while

// Part3: return inorder traversal
	cout << "printing out inorder traversal order from binary search tree:" << endl;
	myTree.inOrderTraversal();

}



