#include "bst-tree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <type_traits>
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
  if(size == 9 || size == 10 ) {
    return 11;
  }
  size = (size * 10) / 13;
  if(size < 1) {
    size = 1;
  }
  return size;
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

int partition2(std::vector<int>& t, int l, int r) {
  #if 1
    std::swap(t[l + 1], t[(l + r) / 2]);
    if(t[l + 1] > t[r]) std::swap(t[l+1], t[r]);
    if(t[l] > t[r]) std::swap(t[l], t[r]);
    if(t[l + 1] > t[l]) std::swap(t[l + 1], t[l]);
  #endif

  int x = t[l];
  int i = l, j = r + 1;
  while ( true ) {
    do {
      i++;
    } while (i <= r && t[i] < x);
    do{
      j--;
    } while(t[j] > x);
    if(i > j)
      break;
    std::swap(t[i], t[j]);
  }
  std::swap(t[j], t[l]);
  return j;
}
 
void quickSort(std::vector<int>& arr, int l, int r) {
  if(l >= r) return;
  int p = partition2(arr, l, r);
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
  if(r - l > 20) {
    int p = partition(arr, l, r);
    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
  } else {
    bubbleSort(arr, l, r + 1);
  }
}


std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<int> gen(0, 100);

template<class Container, typename T = typename Container::value_type>
void printVec(const Container& a) {
  for(const auto& element : a) {
    if constexpr(std::numeric_limits<T>::is_integer) {
      std::printf("%d ", element);
    } else if constexpr(std::is_floating_point<T>::value) {
      std::printf("%.3f ", element);
    } else {
      std::printf("Tego nie!");
    }
  }
  std::puts("");
}

void test(int n = 10) {
  std::vector<int> a(n);
  std::vector<int> b;

  for(auto& element : a) {
    element = gen(mt);
  }

  Timer t;

  b = {a};
  t.restart();
  std::sort(b.begin(), b.end());
  std::printf("std::sort() %.3lfs\n", t.restart());

  b = {a};
  t.restart();
  combSort(b, b.size());
  std::printf("Comb %.3lfs\n", t.restart());

  b = {a};
  t.restart();
  quickSort(b, 0, b.size() - 1);
  std::printf("QuickSort %.3lfs\n", t.restart());

  b = {a};
  t.restart();
  hybridQuickSort(b, 0, b.size() - 1);
  std::printf("Hybrid %.3lfs\n", t.restart());

  b = {a};
  t.restart();
  bubbleSort(b, 0, b.size());
  std::printf("Bubble sort %.3lfs\n", t.restart());

  if(n < 100) {
    printVec(a);
    printVec(b);
  }
}

std::vector<double> testTimes(int n = 1) {
  std::vector<double> result;

  std::vector<int> a(n);
  std::vector<int> b(n);

  for(auto& element : a) {
    element = gen(mt);
  }

  Timer t;

  b = {a};
  t.restart();
  std::sort(b.begin(), b.end());
  result.push_back(t.restart());

  b = {a};
  t.restart();
  hybridQuickSort(b, 0, b.size() - 1);
  result.push_back(t.restart());

  b = {a};
  t.restart();
  quickSort(b, 0, b.size() - 1);
  result.push_back(t.restart());

  b = {a};
  t.restart();
  combSort(b, b.size());
  result.push_back(t.restart());

  b = {a};
  t.restart();
  bubbleSort(b, 0, b.size());
  result.push_back(t.restart());

  return result;
}


int main(int argc, char** argv) {
  std::puts("std::sort() hybridQuickSort(), quickSort(), combSort(), bubbleSort()");
  for(int i = 1; i < 30000; i += 30) {
    auto times = testTimes(i);
    std::printf("%d ", i);
    printVec(times);
  }
}