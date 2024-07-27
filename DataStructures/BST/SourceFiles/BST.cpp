#include "../HeaderFiles/BST.h"
#include <iostream>
using namespace std;

BST::BST() : root(nullptr) {}

BST::~BST(){ deleteTree(root);}

void BST::insert(int key){
    root = insert(root,key);
}

BSTNode* BST::insert(BSTNode* node, int key){
    // Caso base: albero vuoto
    if(!node) return new BSTNode(key);

    // Ricerca del sottoalbero adeguato
    if(key < node->key)
        node->left = insert(node->left,key);
    else if(key > node->key)
        node->right = insert(node->right,key);
    else {
        return node; 
    }

    return node;
}

void BST::deleteKey(int key){
    root = deleteNode(root,key);
}

BSTNode* BST::deleteNode(BSTNode* node, int key){
    // Caso base: albero vuoto
    if(!node) return node;

    // Ricerca del nodo da cancellare
    if(key < node->key)
        node->left = deleteNode(node->left,key);
    else if(key > node->key)
        node->right = deleteNode(node->right,key);
    else { //Chiave trovata
        if(!node->left || !node->right){
            BSTNode* tmp = node->left ? node->left : node->right;
            if(!tmp){ 
                //Caso foglia
                tmp = node;
                node = nullptr;
            }else{
                // Singolo figlio
                *node = *tmp;
            }

            delete tmp;
        }else{
            //Caso nodo con due figli
            BSTNode* tmp = minValueNode(node->right);
            node->key = tmp->key;
            node->right = deleteNode(node->right, tmp->key);
        }
    }

    if(!node) return node; // caso in cui il nodo corrente sia stato eliminato

    return node;
}

BSTNode* BST::minValueNode(BSTNode* node){
    BSTNode* current = node;
    while(current && current->left){
        current = current->left;
    }
    return current;
}

bool BST::search(int key) const{
    BSTNode* current = root;
    while(current){
        if(key == current->key)
            return true;
        else if(key < current->key)
            current = current->left;
        current = current->right;
    }
    return false;
}

void BST::printInOrder() const{
    inOrderTraversal(root);
    cout << "\n\n";
}

void BST::inOrderTraversal(BSTNode* node) const{
    if(node){
        inOrderTraversal(node->left);
        cout << node->key << " -> ";
        inOrderTraversal(node->right);
    }
}

void BST::deleteTree(BSTNode* node){
    if(!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::printTree() const {
    cout<<"\n\n-----------------------------\n\n";
    printTree(root, 0);
    cout<<"\n-------------------------------\n\n";

}

void BST::printTree(BSTNode* node, int depth) const {
   if (node == nullptr) return;

    // Sottoalbero destro
    printTree(node->right, depth + 1);

    // stampa depth volte un TAB
    for (int i = 0; i < depth; ++i) {
        cout << "\t"; // Indentazione
    }
    cout << node->key << endl;

    // Sottoalbero sinistro
    printTree(node->left, depth + 1);
}