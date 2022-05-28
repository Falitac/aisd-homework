#include "bst-tree.hpp"
#include <iostream>
#include <vector>
#include <random>
#include "Timer.hpp"

void bstTreeTest(int num) {
  Node* root = nullptr;
  int val;
  while(std::cin >> val) {
    Node* t = insertBST(root, val);
  }

  print2BST(root); std::printf("\n");

  //int num = -20;
  std::printf("Deleting %d\n", num);
  removeBST(root, findValueBST(root, num));
  print2BST(root);

  clearBST(root);
  std::puts("All done");
}

int getGap(int size) {
  int result = (size * 10) / 13;
  if(result < 1) {
    result = 1;
  }
  return result;
}

void combSort(std::vector<int>& arr, int size) {
  int gap = size;
  for(;;) {
    gap = getGap(gap);
    bool swapped = false;
    for(int i = 0; i < size - gap; i++) {
      int next = i + gap;
      if(arr[i] > arr[next]) {
        std::swap(arr[i], arr[next]);
        swapped = true;
      }
    }
    if(!swapped && gap == 1) {
      break;
    }
  }
}

int partition(std::vector<int>& arr, int l, int r) {
  std::swap(arr[l + 1], arr[(l + r) / 2]);
  if(arr[l + 1] > arr[r]) std::swap(arr[l+1], arr[r]);
  if(arr[l] > arr[r]) std::swap(arr[l], arr[r]);
  if(arr[l + 1] > arr[l]) std::swap(arr[l + 1], arr[l]);

  int x = arr[r];
  int i = l - 1;
  for (int j = l; j < r; j++) {
    if(arr[j] < x) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i+1], arr[r]) ;
  return i + 1;
}
 
void quickSort(std::vector<int>& arr, int l, int r) {
  if(l >= r) return;
  int p = partition(arr, l, r);
  quickSort(arr, l, p - 1);
  quickSort(arr, p + 1, r);
}

void bubbleSort(std::vector<int>& arr, int l, int r) {
  for(int i = 0; i < r - l; i++) {
    bool swapped = false;
    for(int j = l + 1; j < r; j++) {
      if(arr[j - 1] > arr[j]) {
        std::swap(arr[j - 1], arr[j]);
        swapped = true;
      }
    }
    if(!swapped)
      break;
  }
}

void hybridQuickSort(std::vector<int>& arr, int l, int r) {
  if(r - l > 10) {
    int p = partition(arr, l, r);
    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
  } else {
    bubbleSort(arr, l, r);
  }
}


std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<int> gen(0, 100);

void printVec(std::vector<int>& a) {
  for(auto& element : a) {
    std::printf("%d ", element);
  }
  std::puts("");
}

void test(int n = 10) {
  std::vector<int> a(n);

  for(auto& element : a) {
    element = gen(mt);
  }
  std::vector<int> b(a);
  std::vector<int> c(a);
  /*
  for(int i = 0; i < a.size(); i++) {
    a[i] = a.size() - i;
  }
  */


  Timer t;
  t.restart();

  quickSort(a, 0, a.size() - 1);
  std::printf("QuickSort %.3lfs\n", t.restart());

  combSort(b, b.size());
  std::printf("Comb %.3lfs\n", t.restart());

  hybridQuickSort(c, 0, c.size() - 1);
  std::printf("Hybrid %.3lfs\n", t.restart());
  if(n < 100) {
    printVec(a);
    printVec(b);
    printVec(c);
  }
}

int main(int argc, char** argv) {
  test(1000000);
}