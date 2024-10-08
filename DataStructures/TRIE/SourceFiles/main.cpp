#include <iostream>
#include <vector>
#include "../HeaderFiles/Trie.h"
using namespace std;

int main(){
    Trie trie;
    int choice;
    string word;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Print Trie\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter word to insert: ";
                getline(cin,word);
                trie.insert(word);
                trie.print();
                break;
            case 2:
                cout << "Enter word to delete: ";
                getline(cin,word);
                cout << "Query String: " << word << "\n";
                if (trie.delete_key(word)) {
                    trie.print();
                    cout << "\nThe query string is successfully deleted\n";
                }
                else {
                    cout << "\nThe query string is not present in the Trie\n";
                }
                break;
            case 3:
                cout << "Enter value to search: ";
                getline(cin,word);
                cout << "Query String: " << word << "\n";
                if (trie.search(word)) {
                    cout << "\nThe query string is present in the Trie\n";
                }
                else {
                    cout << "\nThe query string is not present in the Trie\n";
                }
                break;
            case 4:
                trie.print();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 5.\n";
                break;
        }
    } while (choice != 5);


    return 0;
}