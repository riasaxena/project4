//We used the zybooks avl tree implementation to guide ours

#ifndef __PROJ_FOUR_AVL_HPP
#define __PROJ_FOUR_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.

	size_t numKeys;
	
	
	struct Node{
		Key key;
		Value value;
		int height;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* root;

	void rebalance(Node* curr);
	void updateHeight(Node* curr);
	int getBalance(Node* curr);
	void rotateLeft(Node* curr);
	void rotateRight(Node* curr);
	void setChild(Node* parent, std::string whichChild, Node* child);
	void replaceChild(Node* parent, Node* currentChild, Node* child);
	void inOrderTraversal(Node* curr, std::vector<Key> & inOrder) const;
	void preOrderTraversal(Node* curr, std::vector<Key> & inOrder) const;
	void postOrderTraversal(Node* curr, std::vector<Key> & inOrder) const;
	void destructor(Node* curr);
	



public:
	//Node* root;
	
	MyAVLTree();
	void print2DUtil(Node *root, int space);

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree()
	{
		destructor(root);
		
	}

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;

};


template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
  :numKeys{0}, root{nullptr} 
{

}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return numKeys; // stub
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return (numKeys == 0); // stub
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{

	Node* curr = root;
  	while(curr != nullptr){
    	if(curr->key == k){
      		return true;
    	} else {
      		if(k < curr->key){
        		curr = curr->left;
      		} else {
        		curr = curr->right;
      		}
		}
    }
    	
  
	return false; // stub
}

template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	Node* curr = root;
  	while(curr != nullptr){
    	if(curr->key == k){
      		return curr->value;
    	} else {
      		if(k < curr->key){
        		curr = curr->left;
      		} else {
        		curr = curr->right;
      		}
		}
    }
	throw ElementNotFoundException("Element not found");

}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	Node* curr = root;
  	while(curr != nullptr){
    	if(curr->key == k){
      		return curr->value;
    	} else {
      		if(k < curr->key){
        		curr = curr->left;
      		} else {
        		curr = curr->right;
      		}
		}
    }
	throw ElementNotFoundException("Element not found");
}
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::print2DUtil(Node *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += 10;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current node after space  
    // count  
    std::cout<<std::endl;  
    for (int i = 10; i < space; i++)  
        std::cout<<" ";  
    std::cout<<root->key<<"\n";  
  
    // Process left child  
    print2DUtil(root->left, space);  
} 
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	if(root == nullptr){
		Node* n = new Node;
		n->key = k;
		n->value = v;
		n->right = nullptr;
		n->left = nullptr;
		n->height = 0;
		n->parent = nullptr;
		root = n;

	} else {
		Node* curr = root;
		while(curr != nullptr){
			if(k < curr->key){
				if(curr->left == nullptr){
					Node* n = new Node;
					n->key = k;
					n->value = v;
					n->right = nullptr;
					n->left = nullptr;
					n->height = 0;
					n->parent = curr;
					curr->left = n;
					break;
				} else {
					curr = curr->left;
				}
			} else {
				if(curr->right == nullptr){
					Node* n = new Node;
					n->key = k;
					n->value = v;
					n->right = nullptr;
					n->left = nullptr;
					n->height = 0;
					n->parent = curr;
					curr->right = n;
					break;
				} else {
					curr = curr->right;
				}

			}
		}
		
		while(curr != nullptr){
			rebalance(curr);
			curr = curr->parent;
		}

		
	}
	numKeys++;
	
    
}


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::updateHeight(Node* curr)
{
	int leftHeight = -1;
	if(curr->left != nullptr){
		leftHeight = curr->left->height;
	}
	int rightHeight = -1;
	if(curr->right != nullptr){
		rightHeight = curr->right->height;
	}
	curr->height = std::max(leftHeight, rightHeight) + 1;
	
}

template<typename Key, typename Value>
int MyAVLTree<Key, Value>::getBalance(Node* curr) 
{
	int leftHeight = -1;
	if(curr->left != nullptr){
		leftHeight = curr->left->height;
	}
	int rightHeight = -1;
	if(curr->right != nullptr){
		rightHeight = curr->right->height;
	}
	return leftHeight - rightHeight;
		
	
	
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::rotateRight(Node* curr) 
{
	Node* leftRightChild = curr->left->right;
	if(curr->parent != nullptr){
		replaceChild(curr->parent, curr, curr->left);
	} else {
		root = curr->left;
		root->parent = nullptr;
	}
	setChild(curr->left, "right", curr);
	setChild(curr, "left", leftRightChild);
		
	
	
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::rotateLeft(Node* curr) 
{
	Node* rightLeftChild = curr->right->left;
	if(curr->parent != nullptr){
		replaceChild(curr->parent, curr, curr->right);
	} else {
		root = curr->right;
		root->parent = nullptr;
	}
	setChild(curr->right, "left", curr);
	setChild(curr, "right", rightLeftChild);
		
	
	
}
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::setChild(Node* parent, std::string whichChild, Node* child){
	if(whichChild == "left"){
		parent->left = child;
	} else {
		parent->right = child;
	}
	if(child != nullptr){
		child->parent = parent;
	}
	updateHeight(parent);
    
}
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::replaceChild(Node* parent, Node* currentChild, Node* child){
	if(parent->left == currentChild){
		setChild(parent, "left", child);
	} else {
		if(parent->right == currentChild){
			setChild(parent, "right", child);
		}
	}
    
}
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::rebalance(Node* curr) 
{
	updateHeight(curr);
	if(getBalance(curr) == -2){
		if(getBalance(curr->right) == 1){
			rotateRight(curr->right);
		}
		rotateLeft(curr);
		

	} else if(getBalance(curr) == 2){
		if(getBalance(curr->left) == -1){
			rotateLeft(curr->left);
		}
		rotateRight(curr);
	}
	
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrderTraversal(Node* curr, std::vector<Key> & inOrder) const
{
	if(curr == nullptr){
		return;
	} else {
		inOrderTraversal(curr->left, inOrder);
		inOrder.push_back(curr->key);
		inOrderTraversal(curr->right, inOrder);
	}

	
}



template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> inOrder;
	Node* curr = root;
	inOrderTraversal(curr, inOrder);
	return inOrder;
}


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrderTraversal(Node* curr, std::vector<Key> & inOrder) const
{
	if(curr == nullptr){
		return;
	} else {
		inOrder.push_back(curr->key);
		preOrderTraversal(curr->left, inOrder);
		preOrderTraversal(curr->right, inOrder);
	}

	
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> inOrder;
	Node* curr = root;
	preOrderTraversal(curr, inOrder);
	return inOrder;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrderTraversal(Node* curr, std::vector<Key> & inOrder) const
{
	if (curr == nullptr){
		return;
	}
	postOrderTraversal(curr -> left, inOrder);
	postOrderTraversal(curr -> right, inOrder);
	inOrder.push_back(curr->key);

}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> inOrder;
	Node* curr = root; 
	postOrderTraversal(curr, inOrder);
	return inOrder; 

}

template<typename Key, typename Value>
void MyAVLTree<Key,Value>::destructor(Node* curr)
{
    if (curr != nullptr)
    {
        destructor(curr->left);
        destructor(curr->right);
        delete curr;
    }
}
 







#endif 