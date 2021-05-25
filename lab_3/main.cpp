#include <iostream>
#include <string>
#include <typeindex>

using namespace std;

#define CLEAR system("clear");
#define PAUSE cin.get();

template <class T>
class IStack
{
 public:
  bool virtual isEmpty() = 0;
  virtual float top() = 0;
  virtual float pop() = 0;
  virtual int push(T) = 0;
  virtual ~IStack(){};
};

template <class T>
class StackVector final : public IStack<T>
{
 private:
  int _top = 0;
  T *_data = nullptr;
  int _maxlength = 0;

 public:
  StackVector(int n)
  {
    _maxlength = n;
    _data = new T[_maxlength];
    _top = -1;
  }

  virtual bool isEmpty() override
  {
    if (_top < 0)
      return true;
    else
      return false;
  }

  virtual float top() override { return _data[_top]; }

  virtual float pop() override { return _data[_top--]; }

  virtual int push(T data) override
  {
    if (_top == _maxlength - 1) return 0;
    _data[++_top] = data;
    return 1;
  }

  virtual ~StackVector() override { delete[] _data; }
};

template <class T>
class StackList final : public IStack<T>
{
 private:
  typedef struct node
  {
    T data;
    node *next;
  } * pnode;

  pnode pstack = nullptr;

 public:
  StackList() { pstack = NULL; }

  virtual bool isEmpty() override
  {
    if (pstack == nullptr)
      return true;
    else
      return false;
  }

  virtual float top() override { return pstack->data; }

  virtual float pop() override
  {
    pnode del = pstack;
    T temp = pstack->data;
    pstack = pstack->next;
    delete del;

    return temp;
  }

  virtual int push(T data) override
  {
    pnode ins = new struct node;

    ins->data = data;
    ins->next = pstack;
    pstack = ins;

    return 1;
  }

  virtual ~StackList() override
  {
    pnode temp;

    while (pstack)
    {
      temp = pstack;
      pstack = pstack->next;
      delete temp;
    }
  }
};

template <class T>
IStack<T> *stack = nullptr;

class Menu final
{
 private:
  int _stackType = -1;

  template <typename T>
  T _input(const string &message)
  {
    T num;

    while (true)
    {
      char c;
      cout << message;
      cin >> num;
      c = getchar();

      if (cin.fail() || c != '\n')
      {
        cout << "Ошибка ввода!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
      }
      else
      {
        break;
      }
    }

    return num;
  }

  template <class T>
  void _test(void)
  {
    CLEAR;
    int input = 0;

    while (true)
    {
      cout << "1. добавить элемент" << endl
           << "2. удалить элемент" << endl
           << "3. отсортировать элементы" << endl
           << "4. печать содержимого стека" << endl
           << "5. возврат к предыдущему меню" << endl;

      input = _input<int>("Ввод: ");

      switch (input)
      {
        case 1:
        {
          if (_stackType == 1)
          {
            stack<T>->push(_input<float>("Введите число: "));
          }
          else if (_stackType == 2)
          {
            short int num;
            while (true)
            {
              num = _input<int>("Введите число: ");
              if (num < 0 || num > 127)
              {
                cout << "Ошибка ввода!" << endl;
              }
              else
              {
                stack<T>->push((char)num);
                break;
              }
            }
          }
          break;
        }
        case 2:
        {
          stack<T>->pop();
          break;
        }
        case 3:
        {
          _sort(stack<T>);

          cout << "Результат: " << endl;
          _print(stack<T>);
          cout << endl;
          PAUSE;
          break;
        }
        case 4:
        {
          cout << "Содержимое стека: " << endl;

          if (_stackType == 1)
            _print(stack<float>);
          else if (_stackType == 2)
            _print(stack<char>);

          PAUSE;
          break;
        }
        case 5:
        {
          delete stack<T>;
          stack<T> = nullptr;
          return;
        }
        default:
          cout << "Ошибка ввода!" << endl;
      }
    }
  }

  template <class T>
  void _sort(IStack<T> *stack)
  {
    StackList<T> t1, t2;
    do
    {
      t1.push(stack->top());
      stack->pop();
      while (!stack->isEmpty())
      {
        if (stack->top() > t1.top())
          t1.push(stack->top());
        else
          t2.push(stack->top());
        stack->pop();
      }
      while (!t1.isEmpty())
      {
        stack->push(t1.top());
        t1.pop();
      }
      if (t2.isEmpty()) break;
      while (!t2.isEmpty())
      {
        stack->push(t2.top());
        t2.pop();
      }

    } while (true);
  }

  template <class T>
  void _print(IStack<T> *stack)
  {
    if (!stack->isEmpty())
    {
      T x = stack->top();
      stack->pop();

      _print(stack);
      cout << (float)x << ' ';
      stack->push(x);
    }
  }

 public:
  int run(void)
  {
    int input = 0;
    while (true)
    {
      CLEAR;
      cout << "Выберите пункт меню:" << endl
           << "1. стек с типом float" << endl
           << "2. стек с типом char" << endl
           << "0. выход." << endl;

      input = _input<int>("Ввод: ");

      _stackType = input;
      switch (input)
      {
        case 1:
        case 2:
          while (true)
          {
            CLEAR;
            cout << "Выберите пункт меню:" << endl
                 << "1. Стек с помощью связной структуры хранения." << endl
                 << "2. Стек с помощью векторной структуры хранения." << endl;

            input = _input<int>("Ввод: ");

            switch (input)
            {
              case 1:
                if (_stackType == 1)
                  stack<float> = new StackList<float>();
                else if (_stackType == 2)
                  stack<char> = new StackList<char>();
                else
                  return -1;

                break;
              case 2:
                if (_stackType == 1)
                  stack<float> = new StackVector<float>(_input<int>("Введите количество элементов дека: "));
                else if (_stackType == 2)
                  stack<char> = new StackVector<char>(_input<int>("Введите количество элементов дека: "));
                else
                  return -1;

                break;

              default:
                cout << "Ошибка ввода!" << endl;
                PAUSE;
                continue;
            }
            break;
          }
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
