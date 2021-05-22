#include <cmath>
#include <string>
#include <cstring>
#include <iostream>

#define PAUSE cin.get();
#define CLEAR system("clear");
#define SCLEAR                \
	while (getchar() != '\n') \
		;

using namespace std;

class String
{
private:
	static int copyCounter;

protected:
	char *_str;
	int _length;
	/*
		Тип строки:

		0 - пустая строка
		1 - строка
		2 - строка идентификатор
		3 - восьмеричная строка
	*/
	char _type;

public:
	String()
	{
		cout << "String: конструктор без параметров" << endl;
		_str = nullptr;
		_length = 0;
		_type = 1;
	}

	String(const char *str)
	{
		cout << "String: конструктор, принимающий в качестве параметра Си-строку" << endl;

		for (_length = 0; str[_length] != '\n'; _length++)

			_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = str[i];

		_type = 1;
	}

	String(char c)
	{
		cout << "String: конструктор, принимающий в качестве параметра символ (char)" << endl;

		_length = 1;
		_str = new char[_length];
		_str[0] = c;

		_type = 1;
	}

	String(const String &str)
	{
		copyCounter++;

		cout << "String: конструктор копирования (количество вызовов: " << copyCounter << ')' << endl;

		_length = str._length;
		_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = str._str[i];

		_type = 1;
	}

	int getLength()
	{
		cout << "String: получение длины строки" << endl;
		return _length;
	}

	void printLine()
	{
		for (int i = 0; i < _length; i++)
			cout << _str[i];
	}

	char getType()
	{
		return _type;
	}

	String &operator=(const String &str)
	{

		cout << "String: перегрузка оператора =" << endl;

		_type = str._type;
		_length = str._length;

		if (_str != nullptr)
			delete[] _str;

		_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = str._str[i];

		return *this;
	}

	String operator+(const String &str)
	{
		cout << "String: перегрузка оператора +" << endl;

		String newStr;
		int thisLength = strlen(_str);
		int strLength = strlen(str._str);

		newStr = new char[thisLength + strLength + 1];

		int i = 0;
		for (; i < thisLength; i++)
		{
			newStr._str[i] = _str[i];
		}
		for (int j = 0; j < strLength; j++, i++)
		{
			newStr._str[i] = str._str[j];
		}
		newStr._str[thisLength + strLength] = '\0';

		return newStr;
	}

	char &operator[](int i)
	{
		return _str[i];
	}

	~String()
	{
		cout << "String: деструктор" << endl;
		if (_str != nullptr)
			delete[] _str;
	}
};

class IdentifierString final : public String
{
private:
	static int copyCounter;

public:
	IdentifierString() : String()
	{
		cout << "IdentifierString: конструктор без параметров" << endl;
		_type = 2;
	}

	IdentifierString(const char *str)
	{
		cout << "IdentifierString: конструктор, принимающий в качестве параметра Си-строку" << endl;
		_length = strlen(str);
		_str = new char[_length];

		if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' || str[0] > 'Z') && (str[0] != '_'))
		{
			cout << "IdentifierString: встречен недопустимый символ. Создана пустая строка" << endl;
			_length = 0;
			_str = nullptr;
			_type = 0;
			return;
		}

		for (_length = 1; str[_length] != '\n'; _length++)
		{
			if ((str[_length] < '0' || str[_length] > '9') && (str[_length] < 'a' || str[_length] > 'z') &&
				(str[_length] < 'A' || str[_length] > 'Z') &&
				str[_length] != '_')
			{
				cout << "IdentifierString: встречен недопустимый символ. Создана пустая строка" << endl;
				_length = 0;
				str = nullptr;
				_type = 0;
				return;
			}
		}

		_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = str[i];

		_type = 2;
	}

	IdentifierString(char c)
	{
		cout << "IdentifierString: конструктор, принимающий в качестве параметра символ (char)" << endl;

		if ((c < '0' || c > '7') && c != '-' && c != '+')
		{
			cout << "IdentifierString: встречен недопустимый символ. Создана пустая строка" << endl;
			_length = 0;
			_str = nullptr;
			_type = 0;
			return;
		}

		_length = 1;
		_str = new char[_length];
		_str[0] = c;

		_type = 3;
	}

	IdentifierString(const IdentifierString &other)
	{
		copyCounter++;

		cout << "IdentifierString: конструктор копирования (количество вызовов: " << copyCounter << ')' << endl;

		_length = other._length;
		_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = other._str[i];

		_type = 2;
	}

	void changeCase()
	{
		cout << "IdentifierString: перевод символов в верхний регистр" << endl;

		for (int i = 0; i < _length; i++)
		{
			if (_str[i] > 96 && _str[i] < 123)
				_str[i] = _str[i] - 32;
		}
	}

	IdentifierString operator+(const IdentifierString &other)
	{
		cout << "IdentifierString: перегрузка оператора +" << endl;

		int i;
		IdentifierString newStr;
		newStr._length = _length + other._length;
		newStr._str = new char[newStr._length];

		for (i = 0; i < _length; i++)
			newStr._str[i] = _str[i];

		for (i = 0; i < other._length; i++)
			newStr._str[i + _length] = other._str[i];

		return newStr;
	}

	char &operator[](int i)
	{
		return _str[i];
	}
};

class OctalString final : public String
{
private:
	static int copyCounter;

	int _add(int x, int y)
	{
		while (y != 0)
		{
			int tmp = x & y;
			x = x ^ y;
			y = tmp << 1;
		}
		return x;
	}

	int _octalSum(int a, int b)
	{
		int sum = 0, tmp = 0, d = 0, m = 1;
		while (a || b || tmp)
		{
			d = 0;
			d = _add(_add(tmp, (a % 10)), (b % 10));
			a /= 10;
			b /= 10;
			if (d > 7)
			{
				tmp = 1;
				d = d % 8;
			}
			else
			{
				tmp = 0;
			}
			sum = _add(sum, d * m);
			m *= 10;
		}
		return sum;
	}

	int _low(int n, int s)
	{
		int res = 1;
		for (size_t i = 0; i != s; i++)
			res *= n;
		return res;
	}

	int _toOctal(int n)
	{
		int result = 0;
		for (size_t i = 0; n >= _low(10, i); i++)
			result += n % _low(10, i + 1) / _low(10, i) * _low(8, i);

		return result;
	}

	int _toDecimal(int n)
	{
		int b, k, result;
		k = 1;
		result = 0;
		while (n > 0)
		{
			b = n % 8;
			n /= 8;
			result += b * pow(10, k - 1);
			b = 0;
			k++;
		}
		return result;
	}

public:
	OctalString() : String()
	{
		cout << "OctalString: конструктор без параметров" << endl;
		_type = 3;
	}

	OctalString(const char *str)
	{
		cout << "OctalString: конструктор, принимающий в качестве параметра Си-строку" << endl;
		_length = strlen(str);
		_str = new char[_length];

		if ((str[0] < '0' || str[0] > '7') && (str[0] != '-') && (str[0] != '+'))
		{
			cout << "OctalString: встречен недопустимый символ. Создана пустая строка" << endl;
			_length = 0;
			_str = nullptr;
			_type = 0;
			return;
		}

		for (_length = 1; str[_length] != '\n'; _length++)
		{
			if ((str[_length] < '0' || str[_length] > '7'))
			{
				cout << "OctalString: встречен недопустимый символ. Создана пустая строка" << endl;
				_length = 0;
				_str = nullptr;
				_type = 0;
				return;
			}
		}

		_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = str[i];

		_type = 3;
	}

	OctalString(char c)
	{
		cout << "OctalString: конструктор, принимающий в качестве параметра символ (char)" << endl;

		if ((c < '0' || c > '7') && (c != '-') && (c != '+'))
		{
			cout << "OctalString: встречен недопустимый символ. Создана пустая строка" << endl;
			_length = 0;
			_str = nullptr;
			_type = 0;
			return;
		}

		_length = 1;
		_str = new char[_length];
		_str[0] = c;
		_type = 3;
	}

	OctalString(const OctalString &str)
	{
		copyCounter++;

		cout << "OctalString: конструктор копирования (количество вызовов: " << copyCounter << ')' << endl;

		_length = str._length;
		_str = new char[_length];

		for (int i = 0; i < _length; i++)
			_str[i] = str._str[i];

		_type = 3;
	}

	OctalString &operator=(const OctalString &other)
	{
		cout << "OctalString: перегрузка оператора =" << endl;

		if (_str != nullptr)
			delete[] _str;

		int length = strlen(other._str);
		_str = new char[length];

		for (int i = 0; i < length; i++)
			_str[i] = other._str[i];

		return *this;
	}

	int operator-(const OctalString &other)
	{
		cout << "OctalString: перегрузка оператора -" << endl;

		int numb1_8 = stoi(_str);
		int numb2_8 = stoi(other._str);

		int numb1_10 = _toOctal(numb1_8);
		int numb2_10 = _toOctal(numb2_8);
		int result_10, result;

		if (numb1_10 > numb2_10)
			result_10 = numb1_10 - numb2_10;
		else
			result_10 = numb2_10 - numb1_10;

		result = _toDecimal(result_10);

		return result;
	}

	int operator+(const OctalString &other)
	{
		cout << "OctalString: перегрузка оператора +" << endl;
		return _octalSum(stoi(_str), stoi(other._str));
	}

	char &operator[](int i)
	{
		return _str[i];
	}
};

int String::copyCounter = 0;
int IdentifierString::copyCounter = 0;
int OctalString::copyCounter = 0;

class Menu
{
private:
	int _stringNumber = 0;
	String **_strArr = nullptr;

	int _input(const string &message)
	{
		int num;

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

	void _initStrings(void)
	{
		int choice, j;
		char *str = new char[200];

		while (true)
		{
			CLEAR;
			_stringNumber = _input("Введите количество строк, которые нужно создать: ");
			if (_stringNumber < 1)
			{
				cout << "Ошибка ввода!" << endl;
				PAUSE;
				continue;
			}

			_strArr = new String *[_stringNumber];
			if (!_strArr)
			{
				cout << "Ошибка выделения памяти!" << endl;
				_stringNumber = 0;
				PAUSE;
				continue;
			}

			for (size_t i = 0; i < _stringNumber; i++)
			{
				cout << endl
					 << "Ввод строки " << i << ": ";
				for (j = 0; j < 200; j++)
				{
					str[j] = getchar();
					if (str[j] == '\n')
						break;
				}

				if (str[j] != '\n')
					SCLEAR;

				if (j == 0)
				{
					cout << "Вы ввели пустую строку!" << endl;
					PAUSE;
					continue;
				}

				cout << "Выберите тип строки:" << endl
					 << "1. Cтрока" << endl
					 << "2. Строка-идентификатор" << endl
					 << "3. Восьмеричная строка" << endl;

				while (true)
				{
					choice = _input("Введите тип строки: ");
					if (choice < 1 || choice > 3)
						cout << "Неверный ввод!" << endl;
					else
						break;
				}

				switch (choice)
				{
				case 1:
					_strArr[i] = new String(str);
				case 2:
					_strArr[i] = new IdentifierString(str);
					break;
				case 3:
					_strArr[i] = new OctalString(str);
					break;
				}

				if (_strArr[i]->getLength() == 0)
					continue;
			}

			break;
		}

		delete[] str;
	}

public:
	int run(void)
	{
		int option, entered_lines = 0;
		bool test_readiness = true;

		while (true)
		{
			_initStrings();

			String *operand_1 = nullptr;
			String *operand_2 = nullptr;

			while (test_readiness)
			{
				CLEAR;

				cout << "1. Операции для строки" << endl
					 << "2. Операции для строки-идентификатора" << endl
					 << "3. Операции для восьмеричной строка" << endl
					 << "4. Выбрать операнды" << endl
					 << "5. Вернуться в меню инициализации" << endl
					 << "6. Завершить выполнение программы" << endl;

				option = _input("Ввод: ");

				switch (option)
				{
				case 1:
				{
					if (operand_1 == nullptr)
					{
						cout << "Ошибка: операнд не задан" << endl;
						break;
					}
					cout << endl
						 << "1. Получение длины строки" << endl
						 << "2. Получение типа заданной строки" << endl;

					option = _input("Ввод: ");
					switch (option)
					{
					case 1:
						cout << "Длина строки равна " << operand_1->getLength() << endl;
						break;
					case 2:
						switch (operand_1->getType())
						{
						case 0:
							cout << "Пустая строка" << endl;
							break;
						case 1:
							cout << "Строка" << endl;
							break;
						case 2:
							cout << "Строка-идентификатор" << endl;
							break;
						case 3:
							cout << "Восьмиричная строка" << endl;
							break;
						}
					default:
						cout << "Ошибка ввода!" << endl;
						break;
					}
					break;
				}

				case 2:
				{
					if (operand_1 == nullptr)
					{
						cout << "Ошибка: операнд не задан" << endl;
						break;
					}
					else if (operand_1->getType() != 2)
					{
						cout << "Ошибка: заданный операнд не является строкой-идентификатором" << endl;
						break;
					}

					cout << endl
						 << "1. Перевести все символы первого операнда в верхний регистр" << endl;
					cout << "2. Сложить первый операнд со вторым" << endl;

					while (true)
					{
						option = _input("Ввод: ");
						if (option < 1 || option > 2)
							cout << "Неверный ввод!" << endl;
						else
							break;
					}

					if (option == 1)
					{
						((IdentifierString *)operand_1)->changeCase();
						cout << "Результат: ";
						operand_1->printLine();
						cout << endl;
					}
					else
					{
						if (operand_2->getType() != 2)
						{
							cout << "Ошибка: второй операнд не является строкой-идентификатором" << endl;
							break;
						}
						else
						{
							IdentifierString result;
							result = *((IdentifierString *)operand_1) + *((IdentifierString *)operand_2);
							cout << endl
								 << "Результат: ";
							result.printLine();
							cout << endl
								 << endl;
						}
					}
					break;
				}

				case 3:
				{
					if (operand_1 == nullptr)
					{
						cout << "Ошибка: операнд не задан" << endl;
						break;
					}
					else if (operand_1->getType() != 3)
					{
						cout << "Ошибка: заданный операнд не является восьмиричной строкой" << endl;
						break;
					}

					cout << endl
						 << "1. Сложить первый операнд со вторым" << endl;
					cout << "2. Вычесть из большего операнда меньший" << endl;

					while (true)
					{
						option = _input("Ввод: ");
						if (option < 1 || option > 3)
							cout << "Неверный ввод!" << endl;
						else
							break;
					}

					if (option == 1)
					{
						if (operand_2->getType() != 3)
						{
							cout << "Ошибка: второй операнд не является восьмиричной строкой" << endl;
							break;
						}
						else
						{
							int result;
							result = *((OctalString *)operand_1) + *((OctalString *)operand_2);
							cout << endl
								 << "Результат: ";
							cout << result << endl;
							cout << endl
								 << endl;
						}
					}
					else if (option == 2)
					{
						if (operand_2->getType() != 3)
						{
							cout << "Ошибка: второй операнд не является восьмиричной строкой" << endl;
							break;
						}
						int result;
						if (operand_1 > operand_2)
						{
							result = *((OctalString *)operand_1) - *((OctalString *)operand_2);
							cout << endl
								 << "Результат: ";
							cout << result << endl;
							cout << endl
								 << endl;
						}
						else
						{
							result = *((OctalString *)operand_2) - *((OctalString *)operand_1);
							cout << endl
								 << "Результат: ";
							cout << result << endl;
							cout << endl
								 << endl;
						}
					}
					break;
				}

				case 4:
				{
					cout << endl;
					for (int i = 0; i < _stringNumber; i++)
					{
						cout << i + 1 << ") ";
						if (_strArr[i]->getType() == 1)
							cout << "Строка: ";
						else if (_strArr[i]->getType() == 2)
							cout << "Строка-идентификатор: ";
						else
							cout << "Восьмеричная строка: ";
						_strArr[i]->printLine();
						cout << endl;
					}
					cout << endl;
					cout << "Выберите номер строки, которую вы хотите сделать первым операндом" << endl;

					while (true)
					{
						option = _input("Ввудите номер строки: ");
						if (option < 1 || option > _stringNumber)
							cout << "Неверный ввод!" << endl;
						else
							break;
					}

					operand_1 = _strArr[option - 1];
					cout << "Первый операнд равен строке '";
					operand_1->printLine();
					cout << "'" << endl
						 << endl;
					cout << "Выберите номер строки, которую вы хотите сделать вторым операндом" << endl;

					while (true)
					{
						option = _input("Введите номер строки: ");
						if (option < 1 || option > _stringNumber)
							cout << "Неверный ввод!" << endl;
						else
							break;
					}

					operand_2 = _strArr[option - 1];
					cout << "Второй операнд равен строке '";
					operand_2->printLine();
					cout << "'" << endl;

					break;
				}

				case 5:
				{
					test_readiness = false;
					break;
				}

				case 6:
				{
					for (int i = 0; i < _stringNumber; i++)
					{
						if (_strArr[i] != nullptr)
							delete _strArr[i];
					}
					delete[] _strArr;
					return 0;
				}

				default:
					cout << "Ошибка: выбран несуществующий пункт меню" << endl;
					break;
				}

				SCLEAR;
			}
		}
	}
};

int main()
{
	return Menu().run();
}
