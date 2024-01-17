#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <chrono>

#include "FastLinkedList.cpp"

int main() {
  std::ifstream input("add.txt");
  int value;
  FastLL fll;
  auto start = std::chrono::high_resolution_clock::now();
  int size;
  input >> size;
  for (int i = 0; i < size; ++i) {
    input >> value;
    if (value == 208) {
        fll.Add(value);
    } else {
        fll.Add(value);

    }
    
    
    if (i % 100 == 0) {
        std::cout << i << '\n';
    }
    
  };
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = end - start;
  std::cout << duration.count();

  input.close();
}
