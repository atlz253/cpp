#include <iostream>
#include <stack>
#include <string>
#include <typeindex>

using namespace std;

#define CLEAR system("clear");
#define PAUSE cin.get();

template <class T>
stack<T> *st;

class Menu final {
 private:
  int _stackType = -1;

  template <typename T>
  T _input(const string &message) {
    T num;

    while (true) {
      char c;
      cout << message;
      cin >> num;
      c = getchar();

      if (cin.fail() || c != '\n') {
        cout << "Ошибка ввода!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
      } else {
        break;
      }
    }

    return num;
  }

  template <class T>
  void _test(void) {
    CLEAR;
    int input = 0;

    while (true) {
      cout << "1. добавить элемент" << endl
           << "2. удалить элемент" << endl
           << "3. отсортировать элементы" << endl
           << "4. печать содержимого стека" << endl
           << "5. возврат к предыдущему меню" << endl;

      input = _input<int>("Ввод: ");

      switch (input) {
        case 1:
          if (_stackType == 1) {
            st<T>->push(_input<float>("Введите число: "));
          } else if (_stackType == 2) {
            short int num;
            while (true) {
              num = _input<int>("Введите число: ");
              if (num < 0 || num > 127) {
                cout << "Ошибка ввода!" << endl;
              } else {
                st<T>->push((char)num);
                break;
              }
            }
          }
          break;
        case 2:
          st<T>->pop();
          break;
        case 3:
          _sort(st<T>);

          cout << "Результат: " << endl;
          _print(st<T>);
          cout << endl;
          PAUSE;
          break;
        case 4:
          cout << "Содержимое стека: " << endl;

          if (_stackType == 1)
            _print(st<float>);
          else if (_stackType == 2)
            _print(st<char>);

          PAUSE;
          break;
        case 5:
          delete st<T>;
          st<T> = nullptr;
          return;
        default:
          cout << "Ошибка ввода!" << endl;
      }
    }
  }

  template <class T>
  void _sort(stack<T> *st) {
    stack<T> t1, t2;
    do {
      t1.push(st->top());
      st->pop();
      while (!st->empty()) {
        if (st->top() > t1.top())
          t1.push(st->top());
        else
          t2.push(st->top());
        st->pop();
      }
      while (!t1.empty()) {
        st->push(t1.top());
        t1.pop();
      }
      if (t2.empty()) break;
      while (!t2.empty()) {
        st->push(t2.top());
        t2.pop();
      }

    } while (true);
  }

  template <class T>
  void _print(stack<T> *st) {
    if (!st->empty()) {
      T x = st->top();
      st->pop();

      _print(st);
      cout << (float)x << ' ';
      st->push(x);
    }
  }

 public:
  int run(void) {
    int input = 0;
    while (true) {
      CLEAR;
      cout << "Выберите пункт меню:" << endl
           << "1. стек с типом float" << endl
           << "2. стек с типом char" << endl
           << "0. выход." << endl;

      input = _input<int>("Ввод: ");

      _stackType = input;
      switch (input) {
        case 1:
        case 2:
          if (_stackType == 1)
            st<float> = new stack<float>();
          else if (_stackType == 2)
            st<char> = new stack<char>();
          else
            return -1;
          break;
        case 0:
          return 0;
        default:
          cout << "Ошибка ввода!" << endl;
      }

      if (_stackType == 1)
        _test<float>();
      else if (_stackType == 2)
        _test<char>();
    }
  }
};

int main() { return Menu().run(); }
