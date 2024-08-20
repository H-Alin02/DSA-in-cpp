#include "../HeaderFiles/BST.h"
#include <iostream>
#define dataType char

int main() {
    BST<dataType> bstTree;
    int choice;
    dataType value;

    do {
        cout << "Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Print Tree\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bstTree.insert(value);
                bstTree.printTree();
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                bstTree.deleteKey(value);
                bstTree.printTree();
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (bstTree.search(value)) {
                    cout << "Value " << value << " found in the tree.\n";
                } else {
                    cout << "Value " << value << " not found in the tree.\n";
                }
                break;
            case 4:
                cout << " Print the AVL tree: ";
                bstTree.printTree();
                cout << endl;
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
