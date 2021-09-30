#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;

    Node* left;
    Node* right;
    Node* parent;
};

Node* search(Node* x, int key) {
    if(x == NULL) 
        return NULL;
    if(key == x->data) 
        return x;
    if(key < x->data) 
        return search(x->left, key);
    else
        return search(x->right, key); 

}

Node* treeMin(Node* x) {
    while (x-> left != NULL) {
        x = x-> left;
    }
    return x;
}

void treeInsert(Node* root, int k) {
    //Creates a new node to insert
    Node* key = new Node();
    key->data = k;
    
    Node* y = NULL;
    Node* x = root;

    //Traverses the tree, comparing the value of key to each node, until it gets to the end
    if(x->data != NULL) { //If the root is not empty
        while(x != NULL) {
            y = x;
            if(key->data < x->data) 
                x = x->left;
            else
                x = x->right;
        }
    }
    //Initializes the parent of key, which at this point is y
    key->parent = y;

    //Places key in the correct position
    if(y == NULL) { //There is no root, so make key the root
        //root->data = key->data;
        root->data = key->data;
    }
    else if(key->data < y->data) {
        y->left = key;
        y->left->left = NULL;
        y->left->right = NULL;
    }
    else {
        y->right = key;
        y->right->right = NULL;
        y->right->left = NULL;
    }
}

void transplant(Node* root, Node* u, Node* v) {
    if(u->parent == NULL) //u is the root
        root = v;
    else if(u == u->parent->left) //u is the left child of its parent
        u->parent->left = v;
    else //u is the right child of its parent
        u->parent->right = v;
   
    if(v != NULL) //Updates the parent of v
        v->parent = u->parent;
}

void treeDelete(Node* root, int key) {
    Node* z;
    //Finds the node we need to delete
    z = search(root, key);

    if(z == NULL)
        return;

    if(z->left == NULL) { //z has one right child, or no children
        transplant(root, z, z->right);
    }
    else if(z->right == NULL) { //z has one left child
        transplant(root, z, z->left); //Replaces z with its left child
    }
    else {
        Node* y = treeMin(z->right);
        if(y->parent != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        z->data = y->data;
        treeDelete(root, y->data);
    }
}

/*void deleteRoot(Node* root) {
    if(root->left == NULL && root->right == NULL) {
        root->data = NULL;
    }
    else if(root->left != NULL && root->right == NULL) { //the root has one left child    
        root = root->left;
    }
    else if(root->right != NULL && root->left == NULL) { //the root has one right child
        root = root->right;
    }
    else {
        Node* succ = treeMin(root->right);
        root->data = succ->data;
        treeDelete(root, succ->data);
    }
    //return root;
}*/

/*void treeDelete(Node* root, int value) {
     Node* z;
     //Finds the node we need to delete
     if(root->data == value)
        z = root;
     else
        z = search(root, value);

     if(z->right == NULL && z->left == NULL){
        //Deleting a leaf
        if(z->parent->data <= z->data) {
            z->parent->right = NULL;
        }
        else
            z->parent->left = NULL;
        delete z;
    }
    else if(z->left != NULL && z->right == NULL) {
        //We are deleting a node with only a left child
        Node* child = z->left;
        
        if(z->parent-> data < z->data) {
            z->parent->right = child;
        }
        else
            z->parent->left = child;
        delete z;
    }
    else if(z->right != NULL && z->left == NULL) {
        //Deleting a node with only a right child
        Node* child = z->right;
        if(z->parent->data <= z->data) {
            z->parent->right = child;
        }
        else
            z->parent->left = child;
        delete z;
    }
    else if(z == root) {
        Node* succ = treeMin(root->right);
        root->data = succ->data;
        treeDelete(root, succ->data);
    }
    else {
        //We are deleting a node with two children
        Node* succ = treeMin(z->right);
        z->data = succ->data;
        treeDelete(root, succ->data);
    }
}*/


void inorderTreeWalk(Node* x) {
    if(x == NULL) {
        return;
    }
    inorderTreeWalk(x->left);
    cout << x->data << endl;
    inorderTreeWalk(x->right);
}

void postorderTreeWalk(Node* x) {
    if(x != NULL) {
        postorderTreeWalk(x->left);
        postorderTreeWalk(x-> right);
        cout << x->data << endl;
    }
}

void preorderTreeWalk(Node* x) {
    if(x != NULL) {
        cout<< x->data << endl;
        preorderTreeWalk(x->left);
        preorderTreeWalk(x->right);
        
    }
}

int main() {
    string userInput;
    cin >> userInput;

    //Initializes the tree, which at first is empty
    Node* tree = new Node();
    int key;
    //tree->left = NULL;
    //tree->right = NULL;
    //tree->data = NULL;
    //Node* z;
    
    while(userInput[0] != 'e') {    
        if(userInput[0] == 'i') { 
            if(userInput.length() <= 2)//For one-digit inputs
                key = userInput[1] - 48;
            else //For two-digit inputs
                key = (userInput[1] - 48) * 10 + (userInput[2] - 48);

            treeInsert(tree, key);
        }
        else if(userInput[0] == 'd') {
            if(userInput.size() <= 2)
                key = userInput[1] - 48;
            else
                key = (userInput[1] - 48) * 10 + (userInput[2] - 48);

            if(key == tree->data) { //If the node being deleted is the root
                if(tree->left == NULL && tree->right == NULL) { //The root has no children
                    tree = NULL; //Basically delete the tree
                }
                else if(tree->left != NULL && tree->right == NULL) { //the root has one left child    
                    tree = tree->left; //Make the root equal to its left child
                }
                else if(tree->right != NULL && tree->left == NULL) { //the root has one right child
                    tree = tree->right; //Make the root equal to its right child
                }
                else { //The root has two children
                    Node* succ = treeMin(tree->right); //Find the successor, the smallest child on the right
                    tree->data = succ->data; //Make the root's data the successor's data
                    transplant(tree, succ, succ->right); //Delete the successor                                 
                }
            }
            else {
                treeDelete(tree, key);
            }
        }
        else if(userInput == "opre") {
            preorderTreeWalk(tree);
        }
        else if(userInput == "opost") {
            postorderTreeWalk(tree);
        }
        else { //userInput == oin
            inorderTreeWalk(tree);
        }

        //Gets more input
        cin >> userInput;
    } 
}



