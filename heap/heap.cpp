#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class Heap {
  std::vector<T> list;
  int heapSize() {
    return list.size();
  };
  int left (int index) {
    if(index == 0) return 1;
    return 2 * index;
  }
  int right (int index) {
    if(index == 0) return 2;
    return (2 * index) + 1;
  }
  int parent(int index) {
    return floor((index / 2)) - 1;
  }
  void maxHeapify(int i) {
      int l = left(i);
      int r = right(i);
      
      int largest;
      if(l < heapSize() && list[l] > list[i]) {
        largest = l;
      } else {
        largest = i;
      }
      if(r < heapSize() && list[r] > list[largest]) {
        largest = r;
      }
      if(largest != i) {
        T temp = list[i];
        list[i] = list[largest];
        list[largest] = temp;
        maxHeapify(largest);
      }
    }
  void minHeapify(int i) {
      int l = left(i);
      int r = right(i);
      
      int smallest;
      if(l < heapSize() && list[l] < list[i]) {
        smallest = l;
      } else {
        smallest = i;
      }
      if(r < heapSize() && list[r] < list[smallest]) {
        smallest = r;
      }
      if(smallest != i) {
        T temp = list[i];
        list[i] = list[smallest];
        list[smallest] = temp;
        //std::cout << list[l] << " " << list[r] << " " << list[smallest];
        minHeapify(smallest);
      }
    }
  public:
    void buildMaxHeap(std::vector<T> l) {
      list = l;
      for(int i = floor(l.size() / 2) - 1; i >= 0; i--) {
        maxHeapify(i);
      }
    }
    void buildMinHeap(std::vector<T> l) {
      list = l;
      for(int i = floor(l.size() / 2) - 1; i >= 0; i--) {
        std::cout << i << '\n';
        minHeapify(i);
      }
    }
    void printHeap() {
      for(int i = 0; i < heapSize(); i++) {
        std::cout << list[i] << " ";
      }
    }
    ~Heap(){};
    
};


int main () {
  std::vector<int> list;
  list.push_back(16);
  list.push_back(4);
  list.push_back(10);
  list.push_back(14);
  list.push_back(7);
  list.push_back(9);
  list.push_back(3);
  list.push_back(2);
  list.push_back(8);
  list.push_back(1);
  std::cout << list.size();
  Heap<int> h;
  h.buildMaxHeap(list);
  h.printHeap();
  std::cout << '\n';
  h.buildMinHeap(list);
  h.printHeap();
  return 0;
}