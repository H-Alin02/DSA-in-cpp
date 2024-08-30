#include <iostream>
#include "../HeaderFiles/Heap.h"
using namespace std;

int main(){

    // Example of a Min-Heap
    Heap<int> minHeap(true);
    for(int i = 10; i > 0; i--){
        minHeap.push(i);
        minHeap.print();
        minHeap.printTree();
    }
    
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
        minHeap.print();
        minHeap.printTree();
    }
    cout << endl;

    return 0;
}