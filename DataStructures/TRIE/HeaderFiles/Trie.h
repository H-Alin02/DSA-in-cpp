#ifndef _TRIE_
#define _TRIE_

#include <iostream>
#include <string>
using namespace std;
#define MAX 26

struct TrieNode {
    struct TrieNode* children[MAX];
    int wordCount = 0;

    TrieNode(){
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
                    currentNode->children[c - 'a'] = new TrieNode();
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
            TrieNode* lastBranchNode = NULL;
            char lastBranchChar = 'a';

            for(auto c : key){
                if(currentNode->children[c - 'a'] == NULL){
                    return false;
                }else{
                    int count = 0;
                    for(int i = 0; i < 26; i++){
                        if(currentNode->children[i] != NULL)
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
            for(int i = 0; i < 26; i++){
                if(currentNode->children[i] != NULL)
                    count++;
            }

            // Case 1: The deleted word is a prefix of other words in Trie
            if(count > 0){
                currentNode->wordCount--;
                return true;
            }

            // Case 2: The deleted word shares a common prefix with other words in Trie
            if(lastBranchNode != NULL){
                lastBranchNode->children[lastBranchChar - 'a'] = NULL;
                return true;
            }

            // Case 3: The deleted word does not share any common prefix with other words in Trie
            else{
                root->children[key[0] - 'a'] = NULL;
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

    public:

        Trie(){ root = new TrieNode(); }
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

};

#endif
