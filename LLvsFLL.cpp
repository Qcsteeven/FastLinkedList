#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "FastLinkedList.cpp"

int main() {
  std::ifstream inputll("add.txt");
  std::list<int> ll;

  auto start = std::chrono::high_resolution_clock::now();
  int size;
  inputll >> size;
  int value;
  for (int i = 0; i < size; ++i) {
    inputll >> value;
    ll.push_back(value);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> durationll = end - start;
  std::cout << "LinkedList(push_back) " << durationll.count() << " seconds"
            << std::endl;
  inputll.close();

  std::ifstream inputfll("add.txt");
  FastLL fll;
  start = std::chrono::high_resolution_clock::now();
  inputfll >> size;
  for (int i = 0; i < size; ++i) {
    inputfll >> value;
    fll.Add(value);
  };
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> durationfll = end - start;
  std::cout << "FastLinkedList(Add) " << durationfll.count() << " seconds"
            << std::endl;
  inputfll.close();

  std::ifstream inputllfind("add.txt");
  start = std::chrono::high_resolution_clock::now();
  inputllfind >> size;
  for (int i = 0; i < size; ++i) {
    inputllfind >> value;
    bool flag = false;
    for (int n : ll) {
      if (n == value) {
        flag = true;
        break;
      }
    }
  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> durationllfind = end - start;
  std::cout << "LinkedList(find) " << durationllfind.count() << " seconds"
            << std::endl;
  inputllfind.close();

  std::ifstream inputfllfind("add.txt");
  start = std::chrono::high_resolution_clock::now();
  inputfll >> size;
  for (int i = 0; i < size; ++i) {
    inputfllfind >> value;
    fll.Find(value);
  };
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> durationfllfind = end - start;
  std::cout << "FastLinkedList(Find) " << durationfllfind.count() << " seconds"
            << std::endl;
  inputfllfind.close();
}
