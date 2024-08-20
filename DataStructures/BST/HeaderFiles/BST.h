#ifndef _BST_
#define _BST_

#include "BSTNode.h"
#include <iomanip>
#include <iostream>
using namespace std;

// Binary Search Tree
template<typename T>
class BST{
    
    public:
        BST() : root(nullptr) {}
        ~BST() { deleteTree(root);}

        virtual void insert(T key){
            root = insert(root,key);
        }

        virtual void deleteKey(T key){
            root = deleteNode(root,key);
        }

        bool search(T key) const{
            BSTNode<T>* current = root;
            while(current){
                if(key == current->key)
                    return true;
                else if(key < current->key)
                    current = current->left;
                current = current->right;
            }
            return false;
        }

        void printInOrder() const{
            inOrderTraversal(root);
            cout << "\n\n";
        }
        
        void printTree() const{
            cout<<"\n\n-----------------------------\n\n";
            printTree(root, 0);
            cout<<"\n-------------------------------\n\n";
        }

    protected: 
        BSTNode<T>* root;
        
        virtual BSTNode<T>* insert(BSTNode<T>* node, T key){
            // empty tree
            if (!node) return new BSTNode<T>(key);

            // Finding the right place to insert
            if (key < node->key) {
                node->left = insert(node->left, key);
            } else if (key > node->key) {
                node->right = insert(node->right, key);
            } else {
                return node;
            }

            return node;
        }

        virtual BSTNode<T>* deleteNode(BSTNode<T>* node, T key){
            // empty tree
            if(!node) return node;

            // Find node to delete
            if(key < node->key)
                node->left = deleteNode(node->left,key);
            else if(key > node->key)
                node->right = deleteNode(node->right,key);
            else { // key found
                if(!node->left || !node->right){
                    BSTNode<T>* tmp = node->left ? node->left : node->right;
                    if(!tmp){ 
                        // Leaf
                        tmp = node;
                        node = nullptr;
                    }else{
                        // Single child
                        *node = *tmp;
                    }

                    delete tmp;
                }else{
                    // Two children
                    BSTNode<T>* tmp = minValueNode(node->right);
                    node->key = tmp->key;
                    node->right = deleteNode(node->right, tmp->key);
                }
            }

            // if the current node is deleted
            if(!node) return node;

            return node;
        }

        BSTNode<T>* minValueNode(BSTNode<T>* node){
            BSTNode<T>* current = node;
            while(current && current->left){
                current = current->left;
            }
            return current;
        }

        void inOrderTraversal(BSTNode<T>* node) const{
            if(node){
            inOrderTraversal(node->left);
            cout << node->key << " -> ";
            inOrderTraversal(node->right);
            }
        }

        void deleteTree(BSTNode<T>* node){
            if(!node) return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }

        void printTree(BSTNode<T>* node, int depth) const{
            if (node == nullptr) return;

            // Right subtree
            printTree(node->right, depth + 1);

            // Print identation and the key
            for (int i = 0; i < depth; ++i) {
                cout << "\t";
            }
            cout << node->key << endl;

            // Left subtree
            printTree(node->left, depth + 1);
        }
    
};

#endif