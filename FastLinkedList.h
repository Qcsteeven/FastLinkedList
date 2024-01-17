#ifndef FLL
#define FLL

class FastLL {
 private:
  struct Node {
    int value;
    Node* next = nullptr;
  };
  struct MainNode {
    int value = 0;
    int height_up = 0;
    int height_down = 0;
    MainNode* right = nullptr;
    MainNode* left = nullptr;
    Node* up = nullptr;
    Node* down = nullptr;
    Node* up_tail = nullptr;
    Node* down_tail = nullptr;
  };

 public:
  ~FastLL();
  int Size();
  int GetMax();
  int GetMin();
  bool Find(int value);
  void Add(int value);
  void Pop(int value);
  void Print();

 private:
  int size_ = 0;
  MainNode* head_ = nullptr;
  MainNode* tail_ = nullptr;
};

#endif  // FLL