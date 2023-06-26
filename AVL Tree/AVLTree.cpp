#include <iostream>
#include "AVLTree.h"
#include <ostream>
#include <fstream>

using namespace std;

int AVLTree::height(Node *curr){
    if(curr == nullptr){ //edge case and base case for when empty
        return -1;
    }
    else{ 
        int leftHeight = height(curr->left);
        int rightHeight = height(curr->right);
        // after finding the max height of left and right, check which one is larger and return + 1
        if(leftHeight > rightHeight){ 
            return leftHeight + 1;
        }
        else{
            return rightHeight + 1;
        }
    }
}

void AVLTree::insert(const string &key){
    if(root == nullptr){ //edge case for emptry tree
        Node* newNode = new Node(key); 
        root = newNode;
    }
    else{
        insert(key, root); // call helper
    }
}

void AVLTree::insert(const string &key, Node* curr){
    if(curr == nullptr){ //base case
        return;
    }
    
    if(key < curr->data){ //case 1: when the key is less
        if(curr->left == nullptr){ 
            // if nothing in left child then just place it there
            Node *newNode = new Node(key);
            curr->left = newNode;
            newNode->parent = curr;
            //starting from the inserted node, go up to its parent and rotate each node
            while(curr){
                rotate(curr);
                curr = curr->parent;
            }
            
        }
        else{
            // else recursively traverse left
            insert(key, curr->left);
        }
    }
    else if(key > curr->data){ //case 2: when the key is greater 
        if(curr->right == nullptr){
            // if nothing in right child then just place it there
            Node *newNode = new Node(key);
            curr->right = newNode;
            newNode->parent = curr;
            //starting from the inserted node, go up to its parent and rotate each node
            while(curr){
                rotate(curr);
                curr = curr->parent;
            }
        }
        else{
            insert(key, curr->right);
        }
    }
    else{
        cout << "duplicate";
    }
    

}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout << "Error" << endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<< n->data << " -> " << n->left->data << ";" << endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<< n->data << " -> " << n->right->data<< ";" <<endl;    
        }
    }
}
void AVLTree::printBalanceFactors(){
    printBalanceFactors(root); //call private helper from root
}

void AVLTree::printBalanceFactors(Node *curr){
    if(curr != nullptr){
        //recrusively travel left then print and travel right so its in order
        printBalanceFactors(curr->left);
        cout << curr->data 
             << "(" << getBalance(curr) << ")"
             << ", ";
        printBalanceFactors(curr->right);
    }
    else{
        // throw runtime_error("printing empty root");
    }
}

void AVLTree::rotate(Node *curr){
    if(getBalance(curr) == 2){ // when tree is unbalanced left
        if(getBalance(curr->left) == -1){ //double rotate case
            rotateLeft(curr->left);
        }
        rotateRight(curr);
    }
    else if(getBalance(curr) == -2){ // when tree is unbalanced right
        if(getBalance(curr->right) == 1){ //double rotate case
            rotateRight(curr->right);
        }
        rotateLeft(curr);
    }
}

//private helper to set parameter's parent's left/right to its child to make code cleaner
void AVLTree::setChild(Node *parent, const string &location, Node* child){
    if(location != "left" && location != "right"){
        throw runtime_error("wrong location");
    }
    if(location == "left"){ 
        parent->left = child;
    }
    else{
        parent->right = child;
    }
    if(child != nullptr){
        child->parent = parent;
    }
}

//private helper to replace the child of a parent to make code cleaner
void AVLTree::replaceChild(Node* parent, Node* parentChild, Node* desiredChild){
    if(parent->left == parentChild){
        setChild(parent, "left", desiredChild);
    }
    else if(parent->right == parentChild){
        setChild(parent, "right", desiredChild);
    }
    else{
        cout << "neither";
    }
}
void AVLTree::rotateRight(Node *curr){
    Node *leftRightChild = curr->left->right;
    if(curr->parent != nullptr){ //if not currently the root, then replace swap curr and curr->left
        replaceChild(curr->parent, curr, curr->left);
    }
    else{ //edge case for root
        root = curr->left;
        root->parent = nullptr;
    }
    //fixes curr and curr's left
    setChild(curr->left, "right", curr);
    setChild(curr, "left", leftRightChild);
}

void AVLTree::rotateLeft(Node *curr){
    Node *rightLeftChild = curr->right->left;
    if(curr->parent != nullptr){ //if not currently root, then replace swap curr and curr->right
        replaceChild(curr->parent, curr, curr->right);
    }
    else{
        root = curr->right;
        root->parent = nullptr;
    }
    //fixes curr and curr's right
    setChild(curr->right, "left", curr);
    setChild(curr, "right", rightLeftChild);
}
