#ifndef _BSTNODE_
#define _BSTNODE_

class BSTNode{

    public:
        int key;
        BSTNode* left;
        BSTNode* right;
        int height;

        // Costruttore
        BSTNode(int k) : key(k), left(nullptr), right(nullptr), height(1){}

        // Distruttore
        ~BSTNode(){}

};

#endif