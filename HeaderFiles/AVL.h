#ifndef _AVL_
#define _AVL_

#include "AVLNode.h"
#include <iomanip>
#include <iostream>
using namespace std;

class AVL{
    
    public:
        AVL();
        ~AVL();

        void insert(int key);
        void deleteKey(int key);
        bool search(int key) const;
        void printInOrder() const;
        void printTree() const;

    private: 
        AVLNode* root;
        
        AVLNode* insert(AVLNode* node, int key);
        AVLNode* deleteNode(AVLNode* node, int key);
        AVLNode* minValueNode(AVLNode* node);
        AVLNode* rotateLeft(AVLNode* x);
        AVLNode* rotateRight(AVLNode* y);
        int getHeight(AVLNode* node) const;
        int getBalance(AVLNode* node) const;
        void updateHeight(AVLNode* node);
        void inOrderTraversal(AVLNode* node) const;
        void deleteTree(AVLNode* node);
        void printTree(AVLNode* node, int space) const;
    
};

#endif