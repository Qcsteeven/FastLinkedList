#include <string>

#include "FastLinkedList.cpp"

int main() {
  std::cout << "Welcome to the user interface to test FLL\n";
  std::cout << "Enter the \"end\" if you want to end testing\n";
  FastLL fll;
  while (true) {
    std::cout
        << "Choose command(add, pop, size, find, print, get_max, get_min): ";
    std::string command;
    std::cin >> command;
    if (command == "add") {
      std::cout << "Enter the number: ";
      int value;
      std::cin >> value;
      fll.Add(value);
    } else if (command == "pop") {
      std::cout << "Enter the number: ";
      int value;
      std::cin >> value;
      fll.Pop(value);
    } else if (command == "find") {
      std::cout << "Enter the number: ";
      int value;
      std::cin >> value;
      if (fll.Find(value)) {
        std::cout << "Yes\n";
      } else {
        std::cout << "No\n";
      }
    } else if (command == "size") {
      std::cout << fll.Size() << '\n';
    } else if (command == "print") {
      fll.Print();
      std::cout << '\n';
    } else if (command == "get_max") {
      std::cout << fll.GetMax() << '\n';
    } else if (command == "get_min") {
      std::cout << fll.GetMin() << '\n';
    } else if (command == "end") {
      std::cout << "It's your result:\n";
      fll.Print();
      break;
    }
  }
}


