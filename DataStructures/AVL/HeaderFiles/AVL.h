#ifndef _AVL_
#define _AVL_

#include "AVLNode.h"
#include <iomanip>
#include <iostream>
#include "../../BST/HeaderFiles/BST.h"
using namespace std;

template<typename T>
class AVL : public BST<T>{
    
    public:
        AVL(): BST<T>(){}
        ~AVL() {}

    void insert(T key) override {
        this->root = insert(static_cast<AVLNode<T>*>(this->root), key);
    }

    void deleteKey(T key) override {
        this->root = deleteNode(static_cast<AVLNode<T>*>(this->root), key);
    }

private:
    AVLNode<T>* insert(AVLNode<T>* node, T key) {
        // Inserimento come BST
        if (!node) return new AVLNode<T>(key);

        if (key < node->key)
            node->left = insert(static_cast<AVLNode<T>*>(node->left), key);
        else if (key > node->key)
            node->right = insert(static_cast<AVLNode<T>*>(node->right), key);
        else
            return node;

        // Aggiorna altezza e bilancia
        updateHeight(node);
        return balance(node);
    }

    AVLNode<T>* deleteNode(AVLNode<T>* node, T key) {
        if (!node) return node;

        if (key < node->key)
            node->left = deleteNode(static_cast<AVLNode<T>*>(node->left), key);
        else if (key > node->key)
            node->right = deleteNode(static_cast<AVLNode<T>*>(node->right), key);
        else {
            // Nodo trovato
            if (!node->left || !node->right) {
                AVLNode<T>* temp = node->left ? static_cast<AVLNode<T>*>(node->left) : static_cast<AVLNode<T>*>(node->right);
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode<T>* temp = static_cast<AVLNode<T>*>(this->minValueNode(static_cast<AVLNode<T>*>(node->right)));
                node->key = temp->key;
                node->right = deleteNode(static_cast<AVLNode<T>*>(node->right), temp->key);
            }
        }

        if (!node) return node;

        updateHeight(node);
        return balance(node);
    }

    AVLNode<T>* balance(AVLNode<T>* node) {
        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(static_cast<AVLNode<T>*>(node->left)) < 0)
                node->left = rotateLeft(static_cast<AVLNode<T>*>(node->left));
            return rotateRight(node);
        }

        if (balance < -1) {
            if (getBalance(static_cast<AVLNode<T>*>(node->right)) > 0)
                node->right = rotateRight(static_cast<AVLNode<T>*>(node->right));
            return rotateLeft(node);
        }

        return node;
    }

    int getHeight(AVLNode<T>* node) const {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode<T>* node) const {
        return node ? getHeight(static_cast<AVLNode<T>*>(node->left)) - getHeight(static_cast<AVLNode<T>*>(node->right)) : 0;
    }

    void updateHeight(AVLNode<T>* node) {
        node->height = 1 + max(getHeight(static_cast<AVLNode<T>*>(node->left)), getHeight(static_cast<AVLNode<T>*>(node->right)));
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = static_cast<AVLNode<T>*>(x->right);
        AVLNode<T>* T2 = static_cast<AVLNode<T>*>(y->left);

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = static_cast<AVLNode<T>*>(y->left);
        AVLNode<T>* T2 = static_cast<AVLNode<T>*>(x->right);

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }
};

#endif