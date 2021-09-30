#include<iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    int letter;
    Node* right;
    Node* left;
    Node* parent;
};

void huffman(vector<int> f) {
    vector<Node*> trees;
    vector<Node*> trees2; //Make a copy of the trees vector: will be used for printing
    //Make a leaf node for each letter
    for(int i = 0; i < 6; i++) {
        Node* z = new Node;
        z->value = f[i];
        z->letter = i;
        //z->left = NULL;
        //z->right = NULL;
        trees2.push_back(z); //This makes it so I don't have to sort trees2 by letter later (for printing)

        //Put the leaf nodes in a list organized by frequency
        bool inserted = false;
        if(trees.empty())
            trees.push_back(z);
        else {
            int k = 0;
            for(auto it = trees.begin(); it != trees.end(); it++) {
                if(f[i] <= trees[k]->value) {
                    //cout << "Inserting " << z->value << " into " << k << endl;
                    trees.insert(trees.begin()+k, z);
                    inserted = true;
                    break;
                }
                k++;
            }
            if(!inserted) {
                trees.push_back(z);
                //cout << "Inserting " << z->value << " into " << k << endl;
            }
        }
    }
    Node* newTree;
    Node* root;
    while(true) {
        //Remove the 2 leaves with the smallest values
        Node* s1 = trees[0];
        Node* s2 = trees[1];
        trees.erase(trees.begin());
        trees.erase(trees.begin());
        //Make them into their own tree with the value being the two frequencies added together
        newTree = new Node;
        newTree->left = s1;
        newTree->right = s2;
        newTree->value = s1->value + s2->value;
        //Update the parent attributes
        s1->parent = newTree;
        s2->parent = newTree;

        //Put this tree into the list
        if(trees.empty()) { //If trees is empty it means all the nodes are connected, so exit the loop
            root = newTree; //The root will be the node that was just created
            break;
        }
        else if(trees.size() == 1) {
            if(newTree->value < trees[0]->value) 
                trees.insert(trees.begin(), newTree);
            else
                trees.push_back(newTree);
        }
        else {
            int k = 0;
            bool inserted = false;
            for(auto it = trees.begin(); it != trees.end(); it++) {
                if(newTree->value <= trees[k]->value) {
                    trees.insert(trees.begin() + k, newTree);  
                    inserted = true; 
                    break;
                }   
                k++;
            }
            if(!inserted) {
                trees.push_back(newTree);
            }
        }      
    }

    //Now the tree is done so print out the codes
    //I'm gonna try this really sketch thing where I start at the leaf nodes and go upwards until I get to the root
    Node* temp;
    vector<int> nums;
    char c;
    for(int i = 0; i < trees2.size(); i++) {
        temp = trees2[i];
        c = trees2[i]->letter + 65;
        cout << c << ":";
        //Move upwards from the leaf until you get to the root and output 0 or 1 depending on whether the current node is the left or right child
        while(temp != root) {
            if(temp == temp->parent->right) {
                nums.insert(nums.begin(), 1);
                temp = temp->parent;
            }
            else{
                nums.insert(nums.begin(), 0);
                temp = temp->parent;
            }
        }

        for(int j = 0; j < nums.size(); j++) {
            cout<< nums[j];
        }
        cout << endl;
        nums.clear();
    }
        
}


int main() {
    vector<int> f;
    int input;
    for(int i = 0; i < 6; i++) {
        cin >> input;
        f.push_back(input);
    } 
    huffman(f);
}
