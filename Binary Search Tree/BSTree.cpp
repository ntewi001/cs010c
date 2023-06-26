#include <iostream>
#include "Node.h"
#include "BSTree.h"

using namespace std;

BSTree::~BSTree(){
    Destructor(root)
}

void BSTree::Destructor(Node *node){
    Destructor(curr->left);
    Destructor(curr->right);
    delete curr;
}
// This function inserts a new string into the tree
void BSTree::insert(const string &newString){
    Node *newNode = new Node(newString);
    if(root == nullptr){ // edge case for empty tree
        root = newNode;
    }
    else{
        insert(newNode, root); // recursive helper function to insert the new node
    }
}

void BSTree::insert(Node* newNode, Node* parent){
    //if greater than parent
    if(newNode->data > parent->data){
        // if parent's right child is empty, insert.
        if(parent->right == nullptr){
            parent->right = newNode;
        }
        // else check parent's right child
        else{
            insert(newNode, parent->right);
        }
    }
    // if less than parent
    else if(newNode->data < parent->data){
        // if parent's left child is empty, insert.
        if(parent->left == nullptr){
            parent->left = newNode;
        }
        //else check parent's left child
        else{
            insert(newNode, parent->left);
        }
    }
    // if newNode is a duplicate string, increment by 1
    else{
        parent->count += 1;
    }
}

void BSTree::remove(const string &newString){
    root = remove(root, newString); //call recursive helper
}
Node* BSTree::remove(Node* curr, const string &key){
    if(curr == nullptr){ // base case
        return nullptr; 
    }

    if(key > curr->data){   // recursively remove the node from the right subtree
        curr->right = remove(curr->right, key);
        return curr;
    }
    else if(key < curr->data){ // recursively remove the node from the left subtree
        curr->left = remove(curr->left, key);
        return curr;
        
    }
    else{
        if(curr->count > 1){ // if there is more than one instance of the string, decrement the count by 1
            curr->count -= 1;
            return curr;
        }
        else{ 
            if(curr->left == nullptr && curr->right == nullptr){ // if the node has no children, delete the node
                delete curr;   
                return nullptr;
            }
            else if(curr->left == nullptr){ // // if the node only has a right child, replace the node with the right child
                if(curr->data == "alpha"){ 
                    Node* victim = curr->right;
                    while(victim->left != nullptr){ // find the smallest node in the right subtree to replace the root node
                        victim = victim->left;
                        }
                        curr->data = victim->data;
                        curr->count = victim->count;
                        curr->right = remove(curr->right, curr->data); // recursively call to delete if children
                        return curr;
                }
                Node *rightChild = curr->right;
                delete curr;
                return rightChild;
            }
            else{ // two children
                // find the largest 
                Node* victim = curr->left;
                while(victim->right != nullptr){ // find the smallest node in the right subtree to replace the root node
                    victim = victim->right;
                }
                curr->data = victim->data;
                curr->count = victim->count;
                curr->left = remove(curr->left, curr->data); // recursively call to delete if children
                return curr;
            }
        }
    }
    
}



// Traverses the tree in pre-order and prints each node's data and count
void BSTree::preOrder() const{
    preOrder(root);
}

void BSTree::preOrder(const Node *curr) const{
    if (curr != nullptr) {
        cout << curr->data << "(" << curr->count << "), "; // print the current node
        preOrder(curr->left); // traverse left subtree
        preOrder(curr->right); // traverse right subtree
    }
}

// Traverses the tree in post-order and prints each node's data and count
void BSTree::postOrder() const{
    postOrder(root);
}

void BSTree::postOrder(const Node* curr) const{
    if(curr != nullptr){
        postOrder(curr->left); // traverse left subtree
        postOrder(curr->right); // traverse right subtree
        cout << curr->data << "(" << curr->count << "), "; // output data
    }
}

// Traverses the tree in in-order and prints each node's data and count
void BSTree::inOrder() const{
    if(root == nullptr){
        return;
    }
    else{
        inOrder(root);
    }
}

void BSTree::inOrder(const Node* curr) const{
    if(curr == nullptr){ //base case if end of tree or empty
        return;
    }
    else{
        //traverse left
        inOrder(curr->left);
        //output data
        cout << curr->data << "(" << curr->count << "), ";
        //traverse right
        inOrder(curr->right);
        
    }
}

//find largest value
string BSTree::largest() const{
    if(root == nullptr){ // If the root is null, the tree is empty, so return an empty string.
        return "";
    }
    else{ // If the right child is not null, the largest value in the subtree must be in the right subtree, so recursively search it.
        return largest(root);
    }
}

string BSTree::largest(const Node* curr) const{
    if(curr->right == nullptr){ //if at the right child of curr node
        return curr->data;
    }
    else{ // if tree not empty recursively keep going
        return largest(curr->right);
    }
}
string BSTree::smallest() const{
    if(root == nullptr){
        return "";
    }
    else{
        return smallest(root);
    }
}
string BSTree::smallest(const Node* curr) const{
    if(curr->left == nullptr){//if at the right child of curr node
        return curr->data;
    }
    else{ // if tree not empty recursively keep going
        return smallest(curr->left);
    }
}

bool BSTree::search(const string &key) const{
    if(root == nullptr){ //base case
        return false;
    }
    else{ //recursively starting from the root
        return search(root, key);
    }
}

bool BSTree::search(const Node* curr, const string &key) const{
    if(curr == nullptr){ // base case or end of children
        return false;
    }
    if(curr->data == key){ // return true if key is current node
        return true;
    }
    else if(key > curr->data){ //recursively traverse right
        return search(curr->right, key);
    }
    else{ //recursively traverse left
        return search(curr->left, key);
    }
}


// This function takes a key and returns the height of the node with that key in the BST.
int BSTree::height(const string &key) const{
    if(search(key)){ // If the key is found, calculate its height.
        const Node* target = searchNode(key,root); // Find the node with the given key.
        return height(target) - 1; // Return the height of the node minus one, since the height of a leaf node is zero.
    }
    else{ // If the key is not found, return -1.
        return -1;
    }
}
// This function takes a key and a pointer to the root node of a BST, and returns a pointer to the node with the given key.
const Node* BSTree::searchNode(const string &key,const Node* root) const{
    if(key == root->data){ // If the key matches the data of the current node, return the pointer to that node.
        return root;
    }
    else if(key > root->data){ // If the key is greater than the data of the current node, search the right subtree.
        return searchNode(key, root->right);
    }
    else{ // If the key is less than the data of the current node, search the left subtree.
        return searchNode(key, root->left);
    }
}

// This function takes a pointer to a node in a BST and returns the height of that node.
int BSTree::height(const Node* root) const{
    if(root == nullptr){ // If the node is null, its height is zero.
        return 0;
    }
    else{ // If the node is not null, recursively calculate the height of its left and right subtrees.
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if(leftHeight > rightHeight){ // Return the height of the taller subtree plus one.
            return (leftHeight + 1);
        }
        else{
            return (rightHeight + 1);
        }
    }
}
