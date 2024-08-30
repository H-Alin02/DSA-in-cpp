#ifndef _PRIORITYQUEUE_
#define _PRIORITYQUEUE_
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template<typename T>
class Heap {
    private:
        vector<T> heap;
        function<bool(T, T)> comparator;

        int parent(int i) const { return (i - 1) / 2; }
        int leftChild(int i) const { return 2 * i + 1; }
        int rightChild(int i) const { return 2 * i + 2; }

        void heapifyUp(int i) {
            if (i && comparator(heap[i], heap[parent(i)])) {
                swap(heap[i], heap[parent(i)]);
                heapifyUp(parent(i));
            }
        }

        void heapifyDown(int i) {
            int left = leftChild(i);
            int right = rightChild(i);
            int largest = i;

            if (left < heap.size() && comparator(heap[left], heap[largest])) {
                largest = left;
            }

            if (right < heap.size() && comparator(heap[right], heap[largest])) {
                largest = right;
            }

            if (largest != i) {
                swap(heap[i], heap[largest]);
                heapifyDown(largest);
            }
        }

public:

    // Constructor: maxHeap = true for max-heap, false for min-heap (default)
    Heap(bool isMinHeap = true) {
        if(isMinHeap)
            comparator = less<T>();
        else comparator = greater<T>();
    }

    void push(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    T top() const {
        if (heap.empty()) {
            cerr << "Heap is empty" << endl;
        }
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    int size() const {
        return heap.size();
    }

    void print() const{
        for (int i = 0; i < heap.size(); ++i) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    void printTree() const{
        cout<<"\n\n-----------------------------\n\n";
        printTree(0, 0);
        cout<<"\n------------------------------\n\n";
    }

    void printTree(int i, int depth) const{
        if (i < heap.size()) {

        // Right subtree
        printTree(rightChild(i), depth + 1);

        // Print identation and the key
        for (int i = 0; i < depth; ++i) {
            cout << "\t";
        }
        cout << heap[i] << endl;

        // Left subtree
        printTree(leftChild(i), depth + 1);
        }
    }
};

#endif