#include "../HeaderFiles/PatternMatching.h"
#include <iostream>
int main(){

    vector<char> alphabet = {'a', 'b', 'c'};
    string pattern = "aba";

    PatternMatching* obj = new KMP_PatternMatching(alphabet);

    cout << "Simple search : \n" << obj->simpleSearch("abbababa", pattern) << "\n\n";

    vector<int> result = obj->multiIndexSearch("abbababa", pattern);
    cout << "Text: " << "abbababa" << "\nPattern: " << pattern << "\n";
    cout << "Pattern found at indexes: ";
    for (auto i : result) cout << i << " ";
    cout << "\n\n";

    pattern = "bb";
    result = obj->multiIndexSearch("bbbbbbb", pattern);
    cout << "Text: " << "bbbbbbb" << "\nPattern: " << pattern << "\n";
    cout << "Pattern found at indexes: ";
    for (auto i : result) cout << i << " ";
    cout << "\n\n";


    delete obj;
    return 0;
}