#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

template <typename T>
class Heap {
  std::vector<T> list;
  int heapSize;
  int left (int index) {
    if(index == 0) return 1;
    return 2 * index + 1;
  }
  int right (int index) {
    if(index == 0) return 2;
    return (2 * index) + 2;
  }
  int parent(int index) {
    if(index == 2 || index == 1 || index == 0) return 0;
    return floor(((index - 1) / 2));
  }
  void maxHeapify(int i) {
      int l = left(i);
      int r = right(i);
      //std::cout << "index is " << i << '\n';
      //std::cout << "left is " << l << "parent is " << parent(l) << '\n';
      //std::cout << "right is " << r << "parent is " << parent(r) << '\n';
      int largest;
      if(l < heapSize && list[l] > list[i]) {
        largest = l;
      } else {
        largest = i;
      }
      if(r < heapSize && list[r] > list[largest]) {
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
      if(l < heapSize && list[l] < list[i]) {
        smallest = l;
      } else {
        smallest = i;
      }
      if(r < heapSize && list[r] < list[smallest]) {
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
    void swapKeysUp(int index) {
      int p = parent(index);
      while(list[p] <= list[index] && index > 0) {
        T temp = list[p];
        list[p] = list[index];
        list[index] = temp;
        index = p;
        p = parent(index);
      }
    }
    void swapKeysDown(int index) {
      int p = parent(index);
      while(list[p] >= list[index] && index > 0) {
        T temp = list[p];
        list[p] = list[index];
        list[index] = temp;
        index = p;
        p = parent(index);
      }
    }

  public:
    void buildMaxHeap(std::vector<T> l) {
      list = l;
      heapSize = list.size();
      for(int i = floor(list.size() / 2) - 1; i >= 0; i--) {
        maxHeapify(i);
      }
    }

    void MaxHeapInsert(T value) {
      list.push_back(value);
      heapSize++;
      swapKeysUp(heapSize - 1);
    }

    T heapExtractMax() {
      if(heapSize > 0) {
        T temp = list[0];
        list[0] = list[heapSize - 1];
        heapSize = heapSize - 1;
        list.pop_back();
        maxHeapify(0);
        return temp;
      }
      throw std::range_error("out of range");
    }

    void buildMinHeap(std::vector<T> l) {
      list = l;
      heapSize = list.size();
      for(int i = floor(list.size() / 2) - 1; i >= 0; i--) {
        minHeapify(i);
      }
    }
    void MinHeapInsert(T value) {
      list.push_back(value);
      heapSize++;
      swapKeysDown(heapSize - 1);
    }
    T heapExtractMin() {
      if(heapSize > 0) {
        T temp = list[0];
        list[0] = list[heapSize - 1];
        heapSize = heapSize - 1;
        list.pop_back();
        minHeapify(0);
        return temp;
      }
      throw std::range_error("out of range");
    }
    void printHeap() {
      for(int i = 0; i < heapSize; i++) {
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
  //std::cout << list.size();
  Heap<int> h;
  h.MaxHeapInsert(2);
  h.MaxHeapInsert(4);
  h.MaxHeapInsert(6);
  h.MaxHeapInsert(9);
  h.MaxHeapInsert(10);
  h.MaxHeapInsert(19);
  h.MaxHeapInsert(25);
  h.MaxHeapInsert(35);
  h.MaxHeapInsert(20);
  h.heapExtractMax();
  h.printHeap();

  //h.MinHeapInsert(1);
  //h.printHeap();
  /*
  int extractedMin;
  extractedMin = h.heapExtractMin();
  extractedMin = h.heapExtractMin();
  extractedMin = h.heapExtractMin();
  extractedMin = h.heapExtractMin();
  std::cout  << '\n';
  std::cout << "extracted min is " << extractedMin << '\n';
  */

  return 0;
}