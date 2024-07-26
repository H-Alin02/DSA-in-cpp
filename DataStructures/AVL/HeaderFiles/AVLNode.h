#ifndef _AVLNODE_
#define _AVLNODE_

class AVLNode{
    public:
        int key;
        AVLNode* left;
        AVLNode* right;
        int height;

        // Costruttore
        AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1){}

        // Distruttore
        ~AVLNode(){}
};

#endif
