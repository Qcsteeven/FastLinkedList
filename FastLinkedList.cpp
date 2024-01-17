#include "FastLinkedList.h"

#include <iostream>

// Получить максимальный элемент
int FastLL::GetMax() { return tail_->value + tail_->height_up; }

// Получить минимальный элемент
int FastLL::GetMin() { return head_->value - head_->height_down; }

// Вывод размера струкутры
int FastLL::Size() { return size_; }

// Удаление элемента
void FastLL::Pop(int value) {
  // Бегунок по всем главным нодам
  MainNode* runner = head_;
  while (runner) {
    int min = runner->value - runner->height_down;
    int max = runner->value + runner->height_up;
    // Проверка в пределах текущей главной ноды
    if (min <= value && value <= max) {
      break;
    }
    if (runner->right) {
      runner = runner->right;
      continue;
    }
    return;
  }
  // Удаление, если значение в главной ноде
  if (runner->value == value) {
    if (runner->up && runner->down) {
      // Существуют ноды и сверху и снизу

      // Создание и инициализация value у двух новых главных нод
      MainNode* new_left = new MainNode{runner->down_tail->value};
      MainNode* new_right = new MainNode{runner->up->value};

      // Заполнение значений левой главной ноды
      if (runner->left) {
        new_left->left = runner->left;
      }
      Node* mini_runner = runner->down;
      while (mini_runner) {
        if (mini_runner->value == new_left->value - 1) {
          new_left->down_tail = mini_runner;
          mini_runner->next = nullptr;
        }
        if (mini_runner->next) {
          mini_runner = mini_runner->next;
        } else {
          break;
        }
      }
      if (runner->down->value != runner->down_tail->value) {
        new_left->down = runner->down;
      }
      new_left->height_down = runner->height_down - 1;
      new_left->right = new_right;

      // Заполнение значений правой главной ноды
      if (runner->right) {
        new_right->right = runner->right;
      }
      if (runner->up->next) {
        new_right->up = runner->up->next;
        new_right->up_tail = runner->up_tail;
      }
      new_right->height_up = runner->height_up - 1;
      new_right->left = new_left;

      // Обновление хвоста и головы при необходимости
      if (head_->value == runner->value) {
        head_ = new_left;
      }
      if (tail_->value == runner->value) {
        tail_ = new_right;
      }

      // Удаление главной ноды со значением value
      --size_;
      delete runner;
      return;
    } else if (runner->up && !runner->down) {
      // Существуют ноды только сверху
      MainNode* new_main = new MainNode{runner->up->value};
      if (runner->right) {
        new_main->right = runner->right;
        runner->right->left = new_main;
      }
      if (runner->left) {
        new_main->left = runner->left;
        runner->left->right = new_main;
      }
      if (runner->up->next) {
        new_main->up = runner->up->next;
        new_main->up_tail = runner->up_tail;
      }
      new_main->height_up = runner->height_up - 1;

      // Обновление хвоста и головы при необходимости
      if (head_->value == runner->value) {
        head_ = new_main;
      }
      if (tail_->value == runner->value) {
        tail_ = new_main;
      }

      // Удаление главной ноды со значением value
      --size_;
      delete runner;
      return;
    } else if ((!runner->up) && runner->down) {
      // Существуют ноды только снизу
      MainNode* new_main = new MainNode{runner->down_tail->value};
      if (runner->right) {
        new_main->right = runner->right;
        runner->right->left = new_main;
      }
      if (runner->left) {
        new_main->left = runner->left;
        runner->left->right = new_main;
      }

      Node* mini_runner = runner->down;
      while (mini_runner) {
        if (mini_runner->value == new_main->value - 1) {
          new_main->down_tail = mini_runner;
          mini_runner->next = nullptr;
        }
        if (mini_runner->next) {
          mini_runner = mini_runner->next;
        } else {
          break;
        }
      }
      if (runner->down->value != runner->down_tail->value) {
        new_main->down = runner->down;
      }
      new_main->height_down = runner->height_down - 1;

      // Обновление хвоста и головы при необходимости
      if (head_->value == runner->value) {
        head_ = new_main;
      }
      if (tail_->value == runner->value) {
        tail_ = new_main;
      }

      // Удаление главной ноды со значением value
      --size_;
      delete runner;
      return;
    } else {
      // Нет нод сверху и снизу
      if (runner->left && runner->right) {
        runner->left->right = runner->right;
      } else if (runner->left && !runner->right) {
        runner->left->right = nullptr;
        tail_ = runner->left;
      } else if ((!runner->left) && runner->right) {
        runner->right->left = nullptr;
        head_ = runner->right;
      } else {
        head_ = nullptr;
        tail_ = nullptr;
      }

      // Удаление главной ноды со значением value
      --size_;
      delete runner;
      return;
    }
  } else if (value > runner->value) {
    // Удаление побочной(маленькой) ноды если она сверху
    Node* mini_runner = runner->up;
    Node* less_runner = runner->up;

    // Удаление, если побочная нода сразу же нужная
    if (mini_runner->value == value) {
      if (mini_runner->next) {
        runner->up = nullptr;
        MainNode* new_main = new MainNode{mini_runner->next->value};
        if (runner->right) {
          MainNode* old_right = runner->right;
          new_main->right = old_right;
        } else {
          new_main->right = nullptr;
          tail_ = new_main;
        }
        runner->right = new_main;
        new_main->left = runner;
        if (mini_runner->next->next) {
          new_main->up = mini_runner->next->next;
          new_main->up_tail = runner->up_tail;
          new_main->height_up =
              (runner->height_up + runner->value) - new_main->value;
        }
        runner->height_up -= new_main->height_up + 2;
        --size_;
        delete mini_runner;
        return;
      } else {
        runner->up = nullptr;
        runner->up_tail = nullptr;
        --runner->height_up;
        --size_;
        delete mini_runner;
        return;
      }
    }

    // Иначе существует следующая нода
    mini_runner = mini_runner->next;

    // Поиск удаляемой ноды
    while (true) {
      if (mini_runner->value == value) {
        if (mini_runner->next) {
          // Если что-то после ноды есть
          runner->up = nullptr;
          MainNode* new_main = new MainNode{mini_runner->next->value};
          if (runner->right) {
            MainNode* old_right = runner->right;
            new_main->right = old_right;
          } else {
            new_main->right = nullptr;
            tail_ = new_main;
          }
          runner->right = new_main;
          new_main->left = runner;
          if (mini_runner->next->next) {
            new_main->up = mini_runner->next->next;
            new_main->up_tail = runner->up_tail;
            new_main->height_up =
                (runner->height_up + runner->value) - new_main->value;
          }
          runner->height_up -= new_main->height_up + 2;
          --size_;
          delete mini_runner;
          return;
        } else {
          // Если нода - хвост
          less_runner->next = nullptr;
          runner->up_tail = less_runner;
          --runner->height_up;
          --size_;
          delete mini_runner;
          return;
        }
      } else {
        if (mini_runner->next) {
          mini_runner = mini_runner->next;
          less_runner = less_runner->next;
        }
      }
    }

  } else {
    // Удаление побочной(маленькой) ноды, если она снизу
    Node* mini_runner = runner->down;
    Node* less_runner = runner->down;

    // Удаление, если побочная нода сразу же нужная
    if (mini_runner->value == value) {
      if (mini_runner->next) {
        runner->down = mini_runner->next;
        --runner->height_down;
        --size_;
        delete mini_runner;
        return;
      } else {
        runner->down = nullptr;
        runner->down_tail = nullptr;
        --runner->height_down;
        --size_;
        delete mini_runner;
        return;
      }
    }

    // Иначе существует следующая нода
    mini_runner = mini_runner->next;

    // Поиск удаляемой ноды
    while (true) {
      if (mini_runner->value == value) {
        if (mini_runner->next) {
          // Если что-то после ноды есть
          less_runner->next = mini_runner->next;
          --runner->height_down;
          --size_;
          delete mini_runner;
          return;
        } else {
          // Если нода в текущем хвосте последняя
          less_runner->next = nullptr;
          runner->down_tail = less_runner;
          --runner->height_down;
          --size_;
          delete mini_runner;
          return;
        }
      }
    }
  }
}

// Добавление элемента
void FastLL::Add(int value) {
  // Если нет элементов то инициализируется начало списка
  if (!head_) {
    head_ = new MainNode{value};
    tail_ = head_;
    ++size_;
    return;
  }

  // Создание новой головы при необходимости
  if (value < (head_->value - head_->height_down - 1)) {
    MainNode* oldhead = head_;
    head_ = new MainNode{value};
    head_->right = oldhead;
    oldhead->left = head_;
    if (!oldhead->right) {
      tail_ = oldhead;
    }
    ++size_;
    return;
  }

  // Создаётся главная нода, которая находит циклом, куда добавить элемент
  MainNode* runner = head_;
  while (runner) {
    // Инициализация нижней и верхней границы в пределах текущей главной ноды
    int min = runner->value - runner->height_down;
    int max = runner->value + runner->height_up;

    // Если элемент уже есть, то происходит выход из функции
    if (min <= value && value <= max) {
      return;
    }

    // Проверка: идти вверх или вниз
    if (value > runner->value) {
      // Вверх
      // Если можно добавить элемент больший, то увеличивается высота вверх
      if (max + 1 == value) {
        break;
      } else {
        // Если нет следующего эл-та, то добавляется новый
        if (!runner->right) {
          runner->right = new MainNode{value};
          runner->right->left = runner;
          tail_ = runner->right;
          ++size_;
          return;
        }
        // Иначе переход к следующей MainNode
        runner = runner->right;
      }
    } else {
      // Вниз

      // Если можно добавить меньший элемент, то переход к побочным нодам
      if (min - 1 == value) {
        break;
      } else {
        // Новая MainNode между прошлой и текущей
        MainNode* oldnode = runner->left;
        runner->left = new MainNode{value};
        runner->left->left = oldnode;
        runner->left->right = runner;
        oldnode->right = runner->left;
        ++size_;
        return;
      }
    }
  }

  // Добавление в нижнюю или верхнюю часть
  if (runner->value > value) {
    // Вниз

    // Если ноды нет, то создаётся
    if (!runner->down) {
      runner->down = new Node{value};
      runner->down_tail = runner->down;
      ++runner->height_down;
      ++size_;
      return;
    }
    // Иначе хвост уходит дальше как и новая нода
    Node* old_node = runner->down;
    runner->down = new Node{value, old_node};

    ++runner->height_down;
    ++size_;
  } else {
    // Вверх

    // Если ноды нет, то создаётся
    if (!runner->up) {
      runner->up = new Node{value};
      runner->up_tail = runner->up;
      ++runner->height_up;
      ++size_;
      // Корректировка структуры
      if (runner->right) {
        // Текущая правая главная нода
        MainNode* r_run = runner->right;

        // Проверка, нужна ли коректировка
        if (r_run->value - r_run->height_down - 1 == runner->up->value) {
          // Сохранение значений перед превращением главной ноды в побочную
          int r_val = runner->right->value;
          MainNode* next_main = nullptr;
          if (r_run->right) {
            next_main = r_run->right;
          }

          // Проверка, есть ли у правой главной ноды, что-то выше или ниже
          if (r_run->up && r_run->down) {
            // И выше и ниже есть побочные ноды
            Node* cur_node = new Node{r_val, r_run->up};
            r_run->down_tail->next = cur_node;
            runner->up_tail->next = r_run->down;
            runner->up_tail = r_run->up_tail;
          } else if (r_run->up && !r_run->down) {
            // Только выше есть побочные ноды
            Node* cur_node = new Node{r_val, r_run->up};
            runner->up_tail->next = cur_node;
            runner->up_tail = r_run->up_tail;
          } else if ((!r_run->up) && r_run->down) {
            // Только ниже есть побочные ноды
            Node* cur_node = new Node{r_val};
            r_run->down_tail->next = cur_node;
            runner->up_tail->next = r_run->down;
            runner->up_tail = cur_node;
          } else {
            // Ни выше, ни ниже нет побочных нод
            Node* cur_node = new Node{r_val};
            runner->up_tail->next = cur_node;
            runner->up_tail = cur_node;
          }

          // Проверка, есть ли дальше главная нода
          if (next_main) {
            runner->right = next_main;
          } else {
            runner->right = nullptr;
            tail_ = runner;
          }

          // Корректировка высоты
          runner->height_up += r_run->height_down + 1 + r_run->height_up;

          // Удаление главной ноды, которая превратилась в побочную
          delete r_run;
        }
      }
      return;
    }

    // Присоединяем новую ноду к хвосту
    runner->up_tail->next = new Node{value};
    runner->up_tail = runner->up_tail->next;
    ++runner->height_up;

    // Корректировка структуры
    if (runner->right) {
      // Текущая правая главная нода
      MainNode* r_run = runner->right;

      // Проверка, нужна ли коректировка
      if (r_run->value - r_run->height_down - 1 ==
          runner->value + runner->height_up) {
        // Сохранение значений перед превращением главной ноды в побочную
        int r_val = runner->right->value;
        MainNode* next_main = nullptr;
        if (r_run->right) {
          next_main = r_run->right;
        }

        // Проверка, есть ли у правой главной ноды, что-то выше или ниже
        if (r_run->up && r_run->down) {
          // И выше и ниже есть побочные ноды
          Node* cur_node = new Node{r_val, r_run->up};
          r_run->down_tail->next = cur_node;
          runner->up_tail->next = r_run->down;
          runner->up_tail = r_run->up_tail;
        } else if (r_run->up && !r_run->down) {
          // Только выше есть побочные ноды
          Node* cur_node = new Node{r_val, r_run->up};
          runner->up_tail->next = cur_node;
          runner->up_tail = r_run->up_tail;
        } else if ((!r_run->up) && r_run->down) {
          // Только ниже есть побочные ноды
          Node* cur_node = new Node{r_val};
          r_run->down_tail->next = cur_node;
          runner->up_tail->next = r_run->down;
          runner->up_tail = cur_node;
        } else {
          // Ни выше, ни ниже нет побочных нод
          Node* cur_node = new Node{r_val};
          runner->up_tail->next = cur_node;
          runner->up_tail = cur_node;
        }

        // Проверка, есть ли дальше главная нода
        if (next_main) {
          runner->right = next_main;
        } else {
          runner->right = nullptr;
          tail_ = runner;
        }

        // Корректировка высоты
        runner->height_up += r_run->height_down + 1 + r_run->height_up;

        // Удаление главной ноды, которая превратилась в побочную
        delete r_run;
      }
    }

    ++size_;
  }
}

// Поиск (проверка(Да/Нет), есть ли элемент в структуре)
bool FastLL::Find(int value) {
  // Бегунок по всем MainNode
  MainNode* runner = head_;
  while (runner) {
    int min = runner->value - runner->height_down;
    int max = runner->value + runner->height_up;
    // Проверка в пределах текущей MainNode
    if (min <= value && value <= max) {
      return true;
    }
    if (runner->right) {
      runner = runner->right;
      continue;
    }
    return false;
  }
  return false;
}

// Вывод всех элементов структуры
void FastLL::Print() {
  // Бегунок по всем главным нодам
  MainNode* runner = head_;
  while (runner) {
    // Бегунок по нодам (побочным)
    Node* mini_runner;

    // Вывод всех побочных меньше главной ноды
    if (runner->down) {
      Node* mini_runner = runner->down;
      while (mini_runner) {
        std::cout << mini_runner->value << " ";
        if (mini_runner->next) {
          mini_runner = mini_runner->next;
        } else {
          break;
        }
      }
    }

    // Вывод главной ноды
    std::cout << runner->value << " ";

    // Вывод всех побочных больше главной ноды
    if (runner->up) {
      Node* mini_runner = runner->up;
      while (mini_runner) {
        std::cout << mini_runner->value << " ";
        if (mini_runner->next) {
          mini_runner = mini_runner->next;
        } else {
          break;
        }
      }
    }

    // Если следущей главной ноды нет, то всё выведено
    if (runner->right) {
      runner = runner->right;
    } else {
      break;
    }
  }
}

// Удаление элементов
FastLL::~FastLL() {
  // Бегунок по всем главным нодам
  MainNode* runner = head_;
  while (runner) {
    // Бегунок по нодам (побочным)
    Node* mini_runner;

    // Удаление всех побочных меньше главной ноды
    if (runner->down) {
      Node* mini_runner = runner->down;
      while (mini_runner) {
        Node* next;
        if (mini_runner->next) {
          next = mini_runner->next;
          delete mini_runner;
        } else {
          delete mini_runner;
          break;
        }
        mini_runner = mini_runner->next;
      }
    }

    // Удаление всех побочных больше главной ноды
    if (runner->up) {
      Node* mini_runner = runner->up;
      while (mini_runner) {
        Node* next;
        if (mini_runner->next) {
          next = mini_runner->next;
          delete mini_runner;
        } else {
          delete mini_runner;
          break;
        }
        mini_runner = mini_runner->next;
      }
    }

    // Если следущей главной ноды нет, то всё
    if (runner->right) {
      MainNode* old_node = runner;
      runner = runner->right;
      delete old_node;
    } else {
      break;
    }
  }
}