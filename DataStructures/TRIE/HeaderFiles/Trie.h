#ifndef _TRIE_
#define _TRIE_

#include <iostream>
#include <string>
using namespace std;
#define MAX 26

struct TrieNode {
    struct TrieNode* children[MAX];
    int wordCount = 0;
    char value = '\0';

    TrieNode(char val) : value(val){
        for(int i = 0; i < MAX; i++){
            children[i] = nullptr;
        }
    }
};

class Trie {

    private:
        TrieNode* root;

        void insert_key(TrieNode* root, string& key){
            TrieNode* currentNode = root;

            for(auto c : key){
                if( currentNode->children[c - 'a'] == nullptr){
                    TrieNode* newNode = new TrieNode(c);
                    currentNode->children[c - 'a'] = newNode;
                }
                currentNode = currentNode->children[c - 'a'];
            }

            currentNode->wordCount++;
        }
        
        int search_key(TrieNode* root, string& key){
            TrieNode* currentNode = root;

            for( auto c : key){
                if(currentNode->children[c - 'a'] == nullptr)
                    return false;

                currentNode = currentNode->children[c - 'a'];
            }

            return (currentNode->wordCount > 0);
        }

        bool delete_key(TrieNode* root, string& key){
            TrieNode* currentNode = root;
            TrieNode* lastBranchNode = nullptr;
            char lastBranchChar = 'a';

            for(auto c : key){
                if(currentNode->children[c - 'a'] == nullptr){
                    return false;
                }else{
                    int count = 0;
                    for(int i = 0; i < MAX; i++){
                        if(currentNode->children[i] != nullptr)
                            count++;
                    }
                    if(count > 1){
                        lastBranchNode = currentNode;
                        lastBranchChar = c;
                    }
                    currentNode = currentNode->children[c - 'a'];
                }
            }
            
            int count = 0;
            for(int i = 0; i < MAX; i++){
                if(currentNode->children[i] != nullptr)
                    count++;
            }

            // Case 1: The deleted word is a prefix of other words in Trie
            if(count > 0){
                currentNode->wordCount--; 
                return true;
            }

            // Case 2: The deleted word shares a common prefix with other words in Trie
            if(lastBranchNode != nullptr){
                deleteTrie(lastBranchNode->children[lastBranchChar - 'a']);
                lastBranchNode->children[lastBranchChar - 'a'] = nullptr;
                return true;
            }

            // Case 3: The deleted word does not share any common prefix with other words in Trie
            else{
                deleteTrie(root->children[key[0] - 'a']);
                root->children[key[0] - 'a'] = nullptr;
                return true;
            }
        }

        void deleteTrie(TrieNode* root){
            if(root == nullptr) return;

            for(int i = 0; i < MAX; i++){
                deleteTrie(root->children[i]);
            }

            delete root;
        }

        void printTrie(TrieNode* node, int depth) const {
            if (node == nullptr) return;

            for(int i = MAX - 1; i >= 0; --i){
                if(node->children[i] != nullptr){
                    printTrie(node->children[i], depth + 1);
                }
            }
        
            if (node->value != '\0') { 
                for (int i = 0; i < depth; ++i) {
                    cout << "\t";
                }
                cout << node->value << endl;
            }
        }

    public:

        Trie(){ root = new TrieNode('\0'); }
        ~Trie(){ deleteTrie(root);}

        void insert(string& key){
            insert_key(root, key);
        }

        int search(string& key){
            return search_key(root, key);
        }

        bool delete_key(string& key){
            return delete_key(root, key);
        }

        void print(){
            cout << "\n\n-----------------------------\n\n";
            printTrie(root, 0);
            cout << "\n\n-----------------------------\n\n";
        }

};

#endif
