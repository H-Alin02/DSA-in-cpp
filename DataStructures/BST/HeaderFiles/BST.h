#ifndef _BST_
#define _BST_

#include "BSTNode.h"
#include <iomanip>
#include <iostream>
using namespace std;

// Binary Search Tree
class BST{
    
    public:
        BST() : root(nullptr) {}
        ~BST() { deleteTree(root);}

        virtual void insert(int key){
            root = insert(root,key);
        }

        virtual void deleteKey(int key){
            root = deleteNode(root,key);
        }

        bool search(int key) const{
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
        BSTNode* root;
        
        virtual BSTNode* insert(BSTNode* node, int key){
            // empty tree
            if(!node) return new BSTNode(key);

            // Finding the right place to insert
            if(key < node->key)
                node->left = insert(node->left,key);
            else if(key > node->key)
                node->right = insert(node->right,key);
            else {
                return node; 
            }

            return node;
        }

        virtual BSTNode* deleteNode(BSTNode* node, int key){
            // empty tree
            if(!node) return node;

            // Find node to delete
            if(key < node->key)
                node->left = deleteNode(node->left,key);
            else if(key > node->key)
                node->right = deleteNode(node->right,key);
            else { // key found
                if(!node->left || !node->right){
                    BSTNode* tmp = node->left ? node->left : node->right;
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
                    BSTNode* tmp = minValueNode(node->right);
                    node->key = tmp->key;
                    node->right = deleteNode(node->right, tmp->key);
                }
            }

            // if the current node is deleted
            if(!node) return node;

            return node;
        }

        BSTNode* minValueNode(BSTNode* node){
            BSTNode* current = node;
            while(current && current->left){
                current = current->left;
            }
            return current;
        }

        void inOrderTraversal(BSTNode* node) const{
            if(node){
            inOrderTraversal(node->left);
            cout << node->key << " -> ";
            inOrderTraversal(node->right);
            }
        }

        void deleteTree(BSTNode* node){
            if(!node) return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }

        void printTree(BSTNode* node, int depth) const{
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