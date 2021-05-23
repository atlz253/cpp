#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#define DEBUG 1  // Показ информационных сообщений в консоли
#define DBGPRINT(str) \
  if (DEBUG) cout << str;
#define CLEAR system("clear");
#define PAUSE cin.get();

using namespace std;

float input(const string &message) {
  float num;

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

class ComplexNum {
 private:
  float _real;
  float _imaginary;

 public:
  ComplexNum() {
    _real = 0;
    _imaginary = 0;
    DBGPRINT("ComplexNum (" << this << "): конструктор без параметров\n");
  }

  ComplexNum(const float real, const float imaginary) {
    _real = real;
    _imaginary = imaginary;
    DBGPRINT("ComplexNum (" << this << "): конструктор с параметрами\n");
  }

  ComplexNum(const ComplexNum &object) {
    _real = object._real;
    _imaginary = object._imaginary;
    DBGPRINT("ComplexNum (" << this << "): конструктор копирования\n");
  }

  float get_real(void) {
    DBGPRINT("get_real: получение a\n");
    return _real;
  }

  float get_imaginary(void) {
    DBGPRINT("get_imaginary: получение b\n");
    return _imaginary;
  }

  void set_real(const float real) {
    DBGPRINT("set_real: установка a\n");
    _real = real;
  }

  void set_imaginary(const float imaginary) {
    DBGPRINT("set_imaginary: установка b\n");
    _imaginary = imaginary;
  }

  void input_real(void) {
    DBGPRINT("imaginary_input: ввод a\n");
    _real = input("Введите a: ");
  }

  void input_imaginary(void) {
    DBGPRINT("imaginary_input: ввод b\n");
    _imaginary = input("Введите b: ");
  }

  ComplexNum *operator/(const ComplexNum &d) {
    DBGPRINT("operator/: деление комплексных чисел\n");
    return new ComplexNum(
        (_real * d._real + _imaginary * d._imaginary) /
            (d._real * d._real + d._imaginary * d._imaginary),
        (d._real * _imaginary - d._imaginary * _real) /
            (d._real * d._real + d._imaginary * d._imaginary));
  }

  bool operator>=(const ComplexNum &s) {
    DBGPRINT("operator>=: сравнение комплексных чисел\n");
    if (sqrt(_real * _real + _imaginary * _imaginary) >=
        sqrt(s._real * s._real + s._imaginary * s._imaginary))
      return true;
    else
      return false;
  }

  bool operator<=(const ComplexNum &s) {
    DBGPRINT("operator<=: сравнение комплексных чисел\n");
    if (sqrt(_real * _real + _imaginary * _imaginary) <=
        sqrt(s._real * s._real + s._imaginary * s._imaginary))
      return true;
    else
      return false;
  }

  ComplexNum *operator!() {
    DBGPRINT("operator!: получение сопряженного комплексного числа\n");
    return new ComplexNum(_real, -_imaginary);
  }

  friend ostream &operator<<(ostream &stream, ComplexNum *n) {
    DBGPRINT("[friend ostream &operator<<: дружественная функция вывода] ");
    cout.setf(ios::fixed);
    stream << setprecision(2) << n->_real;
    cout.setf(ios::showpos);
    stream << setprecision(2) << n->_imaginary << 'i';
    cout.unsetf(ios::showpos | ios::fixed);
    return stream;
  }

  friend istream &operator>>(istream &stream, ComplexNum *n) {
    DBGPRINT("[friend ostream &operator>>: дружественная функция ввода] ");
    n->input_real();
    n->input_imaginary();
    return stream;
  }

  ~ComplexNum() { DBGPRINT("~ComplexNum (" << this << "): объект удален\n"); }
};

class Menu {
 public:
  void init(void) {
    short int choice = 0;

    while (true) {
      CLEAR;
      cout << "1. создать объект без параметров" << endl;
      cout << "2. создать объект с параметрами" << endl;
      cout << "3. создать объект с помощью копирования" << endl;
      cout << "4. ввод комплексного числа" << endl;
      cout << "5. вывод комплексного числа" << endl;
      cout << "6. тестирование метода set" << endl;
      cout << "7. тестирование метода get" << endl;
      cout << "8. деление комплексных чисел" << endl;
      cout << "9. сравнение по модулю >=" << endl;
      cout << "10. сравнение по модулю <=" << endl;
      cout << "11. получение сопряженного комплексного числа" << endl;
      cout << "0. выход" << endl;
      cout << "\nВвод: ";
      cin >> choice;
      CLEAR;

      if (cin.fail()) {
        cout << "Ошибка ввода!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
        PAUSE;
      } else if (choice == 1) {
        delete new ComplexNum();
        PAUSE;
      } else if (choice == 2) {
        delete new ComplexNum(input("Введите a: "), input("Введите b: "));
        PAUSE;
      } else if (choice == 3) {
        ComplexNum *obj =
            new ComplexNum(input("Введите a: "), input("Введите b: "));
        delete new ComplexNum(*obj);
        delete obj;
        PAUSE;
      } else if (choice == 4) {
        ComplexNum *obj = new ComplexNum();
        cin >> obj;
        cout << obj << endl;
        delete obj;
        PAUSE;
      } else if (choice == 5) {
        ComplexNum *obj = new ComplexNum();
        cout << "Для тестирования функции вывода необходимо создать новый "
                "объект класса"
             << endl;
        cin >> obj;
        cout << "Вывод: " << obj << endl;
        delete obj;
        PAUSE;
      } else if (choice == 6) {
        ComplexNum *obj = new ComplexNum();
        obj->set_real(input("Введите a: "));
        obj->set_imaginary(input("Введите b: "));
        cout << obj << endl;
        delete obj;
        PAUSE;
      } else if (choice == 7) {
        ComplexNum *obj = new ComplexNum();
        cin >> obj;
        cout << obj->get_real() << endl << obj->get_imaginary() << endl;
        delete obj;
        PAUSE;
      } else if (choice == 8) {
        ComplexNum *obj_1 = new ComplexNum(), *obj_2 = new ComplexNum();
        cout << "Введите делимое" << endl;
        cin >> obj_1;
        cout << "Введите делитель: " << endl;
        cin >> obj_2;
        obj_1 = *obj_1 / *obj_2;
        cout << "Результат: " << obj_1 << endl;
        delete obj_1;
        delete obj_2;
        PAUSE;
      } else if (choice == 9) {
        ComplexNum *obj_1 = new ComplexNum(), *obj_2 = new ComplexNum();
        cout << "Введите левое число" << endl;
        cin >> obj_1;
        cout << "Введите правое число" << endl;
        cin >> obj_2;
        if (*obj_1 >= *obj_2)
          cout << "правда" << endl;
        else
          cout << "ложь" << endl;
        delete obj_1;
        delete obj_2;
        PAUSE;
      } else if (choice == 10) {
        ComplexNum *obj_1 = new ComplexNum(), *obj_2 = new ComplexNum();
        cout << "Введите левое число" << endl;
        cin >> obj_1;
        cout << "Введите правое число" << endl;
        cin >> obj_2;
        if (*obj_1 <= *obj_2)
          cout << "правда" << endl;
        else
          cout << "ложь" << endl;
        delete obj_1;
        delete obj_2;
        PAUSE;
      } else if (choice == 11) {
        ComplexNum *obj = new ComplexNum();
        cout << "Введите комплексное число" << endl;
        cin >> obj;
        cout << "Сопряженное число: " << !*obj << endl;
        delete obj;
        PAUSE;
      } else if (choice == 0) {
        break;
      } else {
        cout << "Ошибка ввода!" << endl;
        cin.ignore(32767, '\n');
      }
    }
  }
};

int main() {
  Menu *menu = new Menu();
  menu->init();
  delete menu;
  return 0;
}
