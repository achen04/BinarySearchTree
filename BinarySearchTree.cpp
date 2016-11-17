/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

/* 
 *  Parameters: none
 *  Returns: None
 *  Note: this is the constructor
 */
BinarySearchTree::BinarySearchTree()
{
        root = NULL;
}

/* 
 *  Parameters: none
 *  Returns: none
 *  Note: this is the destructor; it calls another function to do a 
 *  post order delete
 */
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
}

/* 
 *  Parameters: a node
 *  Returns: none
 *  Note: this uses a post order traversal to remove all nodes
 */
void BinarySearchTree::post_order_delete(Node *node)
{
	if (node != NULL) {
		post_order_delete(node->left);
		post_order_delete(node->right);
		delete node;
		node = NULL;
	}
	return;
}

/* 
 *  Parameters: the binary search tree
 *  Returns: none
 *  Note: this is the copy constructor
 */
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

/* 
 *  Parameters: the binary search tree
 *  Returns: a pointer to the binary search tree
 *  Note: this is the assignment overload function. it first checks for self
 *  assignment, then deletes the current tree if it exists, and then uses a
 *  pre-order traversal to copy the tree
 */
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
	if (this != &source) { //check for self assignment
		//clean up the old list first
		Node *node = root;
		if (node != NULL) 
			post_order_delete(node);
		root = pre_order_copy(source.root);
	}	
		
	return *this;
}

/* 
 *  Parameters: a node
 *  Returns: a node of the new binary tree
 *  Note: this uses a pre-order traversal to copy details from the node
 *  to a new node
 */
Node *BinarySearchTree::pre_order_copy(Node *node) const
{	
        if (node == NULL)
                return NULL;
	
        Node *new_node = new Node();
	
	new_node->data = node->data;
	new_node->count = node->count;
	new_node->left = pre_order_copy(node->left);
	new_node->right = pre_order_copy(node->right);

	return new_node;
}


/* 
 *  Parameters: none
 *  Returns: the minimum value in the tree
 *  Note: this is a public function that calls the private function
 *  to do the actual work
 */
int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

/* 
 *  Parameters: the root node first, and when called recursively, it is
 *  the parent node that is the parameter until function reaches the leaf
 *  Returns: the left child, or when the node is NULL, meaning that it is 
 *  a leaf, it returns the left-est node in the tree (which is the min.)
 *  Note: this is a private function that helps the public find_min function
 */
Node *BinarySearchTree::find_min(Node *node) const
{	
	
        if (node -> left == NULL)
		return node;
	else
		return find_min(node -> left);
}

/* 
 *  Parameters: none
 *  Returns: the maximum value in the tree. if the tree is empty, then
 *  this function will return INT_MAX. 
 *  Note: this is a public function that calls a helper function to
 *  actually find the min
 */
int BinarySearchTree::find_max() const
{
	if (root == NULL) 
		return INT_MAX;
	return find_max(root) -> data;
        
}

/* 
 *  Parameters: the root node first, and when called recursively, it is
 *  the parent node that is the parameter until function reaches the leaf
 *  Returns: the right child, or when the node is NULL, meaning that it is 
 *  a leaf, it returns the right-est node in the tree
 *  Note: this is a private function that helps the public find_min function
 */
Node *BinarySearchTree::find_max(Node *node) const
{
	if (node -> right == NULL)
		return node;
	else
		return find_max(node -> right); 
}

/* 
 *  Parameters: the value that we are looking for
 *  Returns: true if the value is in the tree, false if it is not
 *  Note: this is a public function that calls the private contains
 *  function that does the actual work
 */

bool BinarySearchTree::contains(int value) const
{
	return contains(root, value);
	
}

/* 
 *  Parameters: a node and the value that is being searched for
 *  Returns: true if the value is in the tree, false if it is not
 *  Note: this is the private function
 */
bool BinarySearchTree::contains(Node *node, int value) const
{
        if (node == NULL) 
		return false;
	else if (node->data == value) 
		return true;
	// if value is greater than current node data, go right
	else if (node->data < value)
		return contains(node->right, value);
	// if value is less than current node data, go left
	else
		return contains(node->left, value);
}

/* 
 *  Parameters: the value to be inserted
 *  Returns: nothing
 *  Note: this is the public function that calls the private insert function
 */
void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

/* 
 *  Parameters: a node, the parent of the node, and the value being looked for
 *  (when this function is first being called, the node starts with the root)
 *  Returns: nothing
 *  Note: this is the private function. if the value is already in the tree.
 *  then the node's count is incremented by 1. 
 */
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{	
	if (node == NULL) {
		node = new Node();
		node->data = value;
		node->count = 1;
		node->left = NULL;
		node->right = NULL;
		//case of completely empty tree
		if (parent == NULL) 
			root = node;
		//case of one node in tree
		else if (parent->data > value)
			parent->left = node;
		else //parent < value
			parent->right = node;
	}
	
	else if (node->data > value) {
		insert(node->left, node, value);
	}
	
	else if (node->data < value){
		insert(node->right, node, value);
	}

	//only option left is for the node data to be equal to the value
	else 
		node->count++;
	
}

/* 
 *  Parameters: the value of the node to be removed
 *  Returns: true if the node with the value has been successfully removed.
 *  and false if the node has not been found and thus cannot be removed
 */
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}
	

/* 
 *  Parameters: a node, the parent of the node, and the value of the node
 *  to be removed; when this function is first called by the public remove
 *  function, the node is the root and the parent is NULL
 *  Returns: true if the node with the value has been successfully removed.
 *  and false if the node has not been found and thus cannot be removed
 */
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
	if (node == NULL)
		return false; //value not found, cannot be removed
	// (when there is one node)
	if (root->left == NULL and root->right == NULL) {
		delete node;
		root = NULL;
		return true;
	}
	if (value < node->data)
		return remove(node->left, node, value);
	else if (value > node->data)
		return remove(node->right, node, value);
	else {		//value has to be equal now
		return remove_helper(node, parent);
	}

}

/* 
 *  Parameters: a node, and the parent of the node
 *  Returns: true if the node with the value has been successfully removed.
 *  and false if the node has not been found and thus cannot be removed
 *  Note: there are several cases that needs to be dealt with. these include
 *  the case when the node's count is greater than one (count needs to
 *  be decremented without removing the node) // the case when the node
 *  has no children and is a leaf (remove this node) // the case when
 *  the node has one child (bypass the node to the child from the parent) //
 *  the case when the node has two children (find the minimum node of the 
 *  right child, replace the node's data with the value and count of the
 *  right's minimum, and then recursively delete right's minimum
 */
bool BinarySearchTree::remove_helper(Node *node, Node *parent)
{
	if (node->count > 1) {
		node->count--;
		return true;
	}
	
	//two children
	if (node->left != NULL && node->right != NULL) {
		node->data = find_min(node->right)->data;
		node->count = find_min(node->right)->count;
		//checking the case if the min has count > 1; trying
		//to avoid duplicates
		find_min(node->right)->count = 1;
		//recursively delete right's minimum
		return remove(node->right, node, find_min(node->right)->data);
	}		
	
	//one child, use bypass method
	else if (node->left == NULL or node->right == NULL) {
		Node *temp;
		if (node->left == NULL) { //right child
			temp = node->right;
			if (parent->right == node) {
				delete node;
				parent->right = temp;
			}
			else { //parent->left == node 
				delete node;
				parent->left = temp;
			}
		}
		else { //left child
			temp = node->left;
			if (parent->right == node) {
				delete node;
				parent->right = temp;
			}
			else { //parent->left == node
				delete node;
				parent->left = temp;
			}
		}
		return true;
	}	
	
	//no children; a leaf
	delete node;
	return true;
}


/* 
 *  Parameters: nothing
 *  Returns: the height of the tree
 */
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

/* 
 *  Parameters: a node (when this is first called, it starts with the root)
 *  Returns: the height of the tree
 *  Note: if the tree only has a root, then the height is 0. if the tree
 * is completely empty, then it has a height of -1
 */
int BinarySearchTree::tree_height(Node *node) const
{	
	if (node == NULL)
		return -1;
	
	int left_tree = tree_height(node->left);
	int right_tree = tree_height(node->right);
	
	if (left_tree > right_tree)
		return 1 + left_tree;
	else
		return 1 + right_tree;

}

/* 
 *  Parameters: None
 *  Returns: the total number of nodes, not including duplicates
 */
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

/* 
 *  Parameters: a node. when this is called from the public node_count
 *  function, the node that is given is the root
 *  Returns: the total number of nodes, not including duplicates
 */
int BinarySearchTree::node_count(Node *node) const
{
	//no node in this tree
	if (node == NULL) {
		return 0;
	}
	
	else 
		return node_count(node->left) + node_count(node->right) +  1;
}

/* 
 *  Parameters: None
 *  Returns: the sum of all the node values (including duplicates)
 */
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

/* 
 *  Parameters: a node. when this is called from the count_total
 *  function, the node that is given is the root
 *  Returns: return the sum of all the node values (including duplicates)
 */
int BinarySearchTree::count_total(Node *node) const
{
        if (node == NULL) {
		return 0;
	}
	
	else 
		return count_total(node->left) + count_total(node->right) 
		+ (node->count * node->data);
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left==child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}
