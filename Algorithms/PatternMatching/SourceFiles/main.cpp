#include "../HeaderFiles/PatternMatching.h"
#include <iostream>
int main(){

    vector<char> alphabet = {'a', 'b', 'c'};
    string pattern = "aba";

    // SIMPLE SEARCH NAIVE vs KMP
    PatternMatching* obj1 = new NaivePatternMatching(alphabet);
    cout << "Simple search NAIVE: \n" << obj1->simpleSearch("abbababa", pattern) << "\n\n";
    
    PatternMatching* obj2 = new KMP_PatternMatching(alphabet);
    cout << "Simple search KMP: \n" << obj2->simpleSearch("abbababa", pattern) << "\n\n";
    
    // MULTI INDEX SEARCH NAIVE vs KMP
    cout << "NAIVE: \n";
    vector<int> result = obj1->multiIndexSearch("abbababa", pattern);
    cout << "Text: " << "abbababa" << "\nPattern: " << pattern << "\n";
    cout << "Pattern found at indexes: ";
    for (auto i : result) cout << i << " ";
    cout << "\n\n";

    cout << "KMP: \n";
    result = obj2->multiIndexSearch("abbababa", pattern);
    cout << "Text: " << "abbababa" << "\nPattern: " << pattern << "\n";
    cout << "Pattern found at indexes: ";
    for (auto i : result) cout << i << " ";
    cout << "\n\n";

    cout << "NAIVE: \n";
    pattern = "bb";
    result = obj1->multiIndexSearch("bbbbbbb", pattern);
    cout << "Text: " << "bbbbbbb" << "\nPattern: " << pattern << "\n";
    cout << "Pattern found at indexes: ";
    for (auto i : result) cout << i << " ";
    cout << "\n\n";

    cout << "KMP: \n";
    pattern = "bb";
    result = obj2->multiIndexSearch("bbbbbbb", pattern);
    cout << "Text: " << "bbbbbbb" << "\nPattern: " << pattern << "\n";
    cout << "Pattern found at indexes: ";
    for (auto i : result) cout << i << " ";
    cout << "\n\n";
    

   delete obj1;
   delete obj2;

    return 0;
}