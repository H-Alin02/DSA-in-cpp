#ifndef _AVLNODE_
#define _AVLNODE_

template <typename T>
class AVLNode{
    public:
        T key;
        AVLNode<T>* left;
        AVLNode<T>* right;
        int height;

        // Constructor
        AVLNode(T k) : key(k), left(nullptr), right(nullptr), height(1){}

        // Destructor
        ~AVLNode(){}
};

#endif