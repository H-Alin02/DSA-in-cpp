#ifndef _AVLNODE_
#define _AVLNODE_
#include "../../BST/HeaderFiles/BSTNode.h"

template <typename T>
class AVLNode : public BSTNode<T>{
    public:
        int height;

        // Constructor
        AVLNode(T k) : BSTNode<T>(k), height(1) {}

        // Destructor
        ~AVLNode(){}
};

#endif