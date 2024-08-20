#ifndef _BSTNODE_
#define _BSTNODE_

template<typename T>
class BSTNode{

    public:
        T key;
        BSTNode<T>* left;
        BSTNode<T>* right;
        int height;

        // Constructor
        BSTNode(T k) : key(k), left(nullptr), right(nullptr), height(1){}

        // Destructor
        ~BSTNode(){}

};

#endif