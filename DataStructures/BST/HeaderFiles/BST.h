#ifndef _BST_
#define _BST_

#include "BSTNode.h"
#include <iomanip>
#include <iostream>
using namespace std;

class BST{
    
    public:
        BST();
        ~BST();

        virtual void insert(int key);
        virtual void deleteKey(int key);
        bool search(int key) const;
        void printInOrder() const;
        void printTree() const;

    protected: 
        BSTNode* root;
        
        virtual BSTNode* insert(BSTNode* node, int key);
        virtual BSTNode* deleteNode(BSTNode* node, int key);
        BSTNode* minValueNode(BSTNode* node);
        void inOrderTraversal(BSTNode* node) const;
        void deleteTree(BSTNode* node);
        void printTree(BSTNode* node, int space) const;
    
};

#endif