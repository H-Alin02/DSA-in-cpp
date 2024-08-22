#include "../HeaderFiles/PatternMatching.h"
#include <iostream>
int main(){

    vector<char> alphabet = {'a', 'b', 'c'};
    string pattern = "aba";

    PatternMatching* obj = new KMP_PatternMatching(alphabet);

    cout << obj->simpleSearch("abbabaaba", pattern) << endl;

    vector result = obj->multiIndexSearch("abbabaaba", pattern);
    for (auto i : result) cout << i << " ";
    cout << endl;

    /*obj->search("ababacababac","aaaaaa");
    obj->search("ababacababac","aacaaab");
    obj->search("ababacababac","abaabaaabaaab");
    obj->search("ababacababac","abaabcabaabcb");
    */

    delete obj;
    return 0;
}