# ReadMe for COMP 15 HW4
## Binary Search Tree

===============================PURPOSE=========================================
1. The purpose of this program is to create a binary search tree
implementation. This means this program follows the invariant of a binary
search tree, which is that all nodes to the left are smaller in value, and
all nodes to the right are larger in value.


===============================FILES=========================================
2. 
	- Main.cpp: This calls the functions to 

	- BinarySearchTree.h: This file defines the struct of the Node as well
	as the functions that are used in the binary search tree, which 
	includes functions like find min, find max, insert, contains, remove,
	a copy constructor, and an assignment overload function.

	- BinarySearchTree.cpp: This contains the functions of the 


=============================TO COMPILE =======================================
3. To compile, please use included Makefile


===========================DATA STRUCTURE======================================
4. The main data structure used in this program is a binary search tree?


===========================ALGORITHM==========================================
5. A particular function that is important to this program is the remove 
function. It shows the many number of cases that need to be considered when 
dealing with binary trees. When removing a node, these are the cases that need
to be considered:
	- The to be removed node has a count of more than one. This can be 
	dealt with by decrementing the count by one.
	- The node has one child. A bypass method can be used to remove this
	node, which means that the parent of the node connects to the child
	of the node. Cases in which the right parent is the connection or 
	the left parent is, need to be considered. Whether it is a left or
	right child needs to be considered as well. (Different pointers
	would be used).
	- The node has two children. To deal with this case, the minimum node
	of the right child subtree needs to be identified. Then, replace the
	node's data & count with the minimum's data & count. Then, resursively
	delete the right's minimum to fully remove the node. Note that there 
	is also the case in which the minimum has a count of more than one, 
	which means that if the remove function is called recursively, there
	would be duplicates. The minimum's data would be copied over, while
	it still exists at it's original position because it's count is simply
	decremented rather than removing the node. Thus, 



===========================HELP======================================
6. A TA had helped me with this assignment. 
