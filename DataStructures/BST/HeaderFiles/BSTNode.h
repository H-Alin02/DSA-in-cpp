#ifndef _BSTNODE_
#define _BSTNODE_

class BSTNode{

    public:
        int key;
        BSTNode* left;
        BSTNode* right;
        int height;

        // Constructor
        BSTNode(int k) : key(k), left(nullptr), right(nullptr), height(1){}

        // Destructor
        ~BSTNode(){}

};

#endif