#ifndef _AVLNODE_
#define _AVLNODE_

class AVLNode{
    public:
        int key;
        AVLNode* left;
        AVLNode* right;
        int height;

        // Constructor
        AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1){}

        // Destructor
        ~AVLNode(){}
};

#endif