#include "LongNumber.h"
using namespace std;


int LongNumber::Comparing(const char* num1, const char* num2, bool abs)
{
	bool minus1 = false, minus2 = false;//Знаки чисел
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
		minus2 = true;
	if (abs == false)//Сравниваем значения чисел, а не их модули
	{
		if (minus1 > minus2)//Определение большего числа сравнением знаков
			return 1;
		if (minus1 < minus2)
			return -1;
	}
	int size1 = strlen(num1);//Размеры 1 числа 
	int size2 = strlen(num2);//Размеры 2 числа 
	if (size1 - minus1 > size2 - minus2)//Определение большего числа сравнением их длины
		return 1;
	if (size1 - minus1 < size2 - minus2)
		return -1;
	for (int i = minus1, j = minus2; num1[i] != '\0'; i++, j++)//Сравнение разрядов чисел
	{
		if (num1[i] > num2[j])
			return 1;
		if (num1[i] < num2[j])
			return -1;
	}
	return 0;//Числа равны
}
char* LongNumber::Adding(const char* num1, const char* num2, const bool minus)
{
	int remains = 0;//Остаток
	int digit = 0, digit1, digit2;//Отслеживание разряда цифры, разряды первого и второго числа
	char result[255];//Результат сложения
	digit1 = strlen(num1);//Разрядов 1 числа
	digit2 = strlen(num2);//Разрядов 2 числа
	digit1--; digit2--;
	int beg = 0;//Начало числа
	if (minus == true)
		beg = 1;//При наличии минуса начало числа смещается и минус не учитывается
	while (digit1 >= beg && digit2 >= beg)
	{
		//Складывание чисел происходит по правилам сложения в столбик
		remains += (num1[digit1] - '0') + (num2[digit2] - '0');
		result[digit] = (remains % 10 + '0');
		remains /= 10;
		digit1--; digit2--; digit++;
	}
	if (digit1 < beg)
	{
		while (remains != 0 && digit2 >= beg)//Если остаток всё ещё присутствует, учитываем его
		{
			remains += (num2[digit2] - '0');
			result[digit] = (remains % 10 + '0');
			remains /= 10;
			digit++; digit2--;
		}
		while (digit2 >= beg)//Когда остатка нет, просто заполняем старшие разряды числа
		{
			result[digit] = num2[digit2];
			digit++; digit2--;
		}
	}
	if (digit2 < beg)
	{
		while (remains != 0 && digit1 >= beg)//Если остаток всё ещё присутствует, учитываем его
		{
			remains += (num1[digit1] - '0');
			result[digit] = (remains % 10 + '0');
			remains /= 10;
			digit++; digit1--;
		}
		while (digit1 >= beg)//Когда остатка нет, просто заполняем старшие разряды числа
		{
			result[digit] = num1[digit1];
			digit++; digit1--;
		}
	}
	if (remains != 0)
	{
		result[digit] = remains + '0';//При наличии остатка заполняем им самый старший разряд
		if (minus)
		{
			digit++;
			result[digit] = '-';//Ставим минус при сложении двух отрицательных чисел
		}
		result[digit + 1] = '\0';//Зануляем строку
	}
	else//Иначе просто ставим минус и зануляем строку
	{
		if (minus)
		{
			result[digit] = '-';//Ставим минус при сложении двух отрицательных чисел
			digit++;
		}
		result[digit] = '\0';
		digit--;
	}
	for (int inversdig = 0; inversdig < digit; digit--, inversdig++)//Инвертируем ответ, так как цифры в нём находятся в обратном порядке
	{
		char container = result[inversdig];//Временное хранилище
		result[inversdig] = result[digit];
		result[digit] = container;
	}
	return result;
}
char* LongNumber::Subtracting(char* num1, char* num2, const bool minus1, const bool minus2)
{
	int remains = 0;//Результат вычитания двух цифр
	int digit, digit1, digit2;//Отслеживание разряда цифры, разряды первого и второго числа
	char result[255];//Результат вычитания
	bool minus;//Знак результата
	if (Comparing(num1, num2, true) == 0)
	{//Если числа одинаковы то результатом их вычитания будет ноль
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	if (Comparing(num1, num2, true) == -1)
	{
		char container[255];//Временное хранилище
		strcpy(container, num2);
		strcpy(num2, num1);
		strcpy(num1, container);
		minus = minus2;
	}//num1 большее число, num2 меньшее число
	else minus = minus1;//Результат будет со знаком большего числа
	digit1 = strlen(num1);//Разрядов 1 числа
	digit2 = strlen(num2);//Разрядов 2 числа
	digit1--; digit2--;
	int beg1 = 0, beg2 = 0;//Начало первого и второго числа в строке
	if (minus == true)
		beg1 = 1;
	else beg2 = 1;
	digit = beg1;//Смещённое начало в зависимости от наличия минуса
	while (digit2 >= beg2)
	{
		//Разность чисел считается вычитанием в столбик
		remains += (num1[digit1] - '0') - (num2[digit2] - '0');
		if (remains < 0)
		{
			num1[digit1 - 1] = ((num1[digit1 - 1] - '0') - 1) + '0';//Вычитаем единицу на разряд выше
			remains += 10;
		}
		result[digit] = remains + '0';
		remains = 0;
		digit1--; digit2--; digit++;
	}
	while (digit1 >= beg1)//Оставшиеся разряды заполняем большим числом num1
	{
		result[digit] = num1[digit1];
		digit++; digit1--;
	}
	int diff = 0;//Отслеживаем, на сколько разрядов уменьшилось наибольшее число
	for (int digitcopy = digit - 1; result[digitcopy] == '0'; digitcopy--, diff++);
	result[digit - diff] = '\0';//Зануляем конец строки
	digit--;
	for (int inversdig = beg1; inversdig < digit - diff; digit--, inversdig++)//Инвертируем ответ, так как цифры в нём находятся в обратном порядке
	{
		char container = result[inversdig];//Временное хранилище
		result[inversdig] = result[digit - diff];
		result[digit - diff] = container;
	}
	if (minus)
		result[0] = '-';//Ставим минус если результат вычислений отрицательный

	return result;
}
char* LongNumber::Multiplication(const char* num1, const char* num2, const bool minus1, const bool minus2)
{
	int remains = 0;//Остаток от умножения двух цифр
	int digit = 0, digit1, digit2;//Отслеживание разряда цифры, разряды первого и второго числа
	char result[255];//Результат умножения
	result[0] = '0';
	result[1] = '\0';
	bool minus = false;//Знак результата
	digit1 = strlen(num1);//Разрядов 1 числа
	digit2 = strlen(num2);//Разрядов 2 числа
	digit1--; digit2--;
	if (minus1 != minus2)//Знак результата зависит от знаков множителей
		minus = true;//При наличии минуса начало смещено
	for (int digadd = 0; digit2 >= (int)minus2; digadd++, digit2--)//Считываем число до знака
	{
		char addresult[255];//Результат умножения на один из разрядов
		//Умножение в столбик 
		digit = 0;
		while (digit < digadd)
		{
			addresult[digit] = '0';
			digit++;//Учитываем разряд текущего числа
		}

		for (int digit1copy = digit1; digit1copy >= (int)minus1; digit1copy--, digit++)
		{
			remains += (num2[digit2] - '0') * (num1[digit1copy] - '0');
			addresult[digit] = remains % 10 + '0';
			remains /= 10;
		}
		while (remains != 0)//Избавляемся от остатка
		{
			addresult[digit] = remains % 10 + '0';
			remains /= 10;
			digit++;
		}
		addresult[digit] = '\0';//Зануляем строку
		digit--;
		for (int inversdig = 0; inversdig < digit; digit--, inversdig++)//Инвертируем число, так как цифры в нём находятся в обратном порядке
		{
			char container = addresult[inversdig];//Временное хранилище
			addresult[inversdig] = addresult[digit];
			addresult[digit] = container;
		}
		strcpy(result, Adding(result, addresult, false));//Прибавляем к имеющимся результатам
	}
	if (minus)//Добавляем минус к числу
	{
		for (int i = strlen(result) + 1; i > 0; i--)
		{
			result[i] = result[i - 1];
		}
		result[0] = '-';
	}
	return result;
}
LongNumber LongNumber::DivisionRecursion(LongNumber num1, LongNumber num2, LongNumber result, int digit)
{
	LongNumber curdigit = "1";//Текущий разряд
	for (int i = 1; i < digit; i++)
		curdigit = curdigit * (LongNumber)"10";
	while (num1 < result * num2)
	{
		result = result - curdigit;
	}
	digit--;//Уменьшаем разряд
	if (digit > 0)
	{
		result = result + curdigit;
		result = DivisionRecursion(num1, num2, result, digit);//Если можем продолжать уточнить делить делим
	}
	return result;
}
void LongNumber::Print()
{
	cout << number;
}
LongNumber::LongNumber(const char* valueNumber)
{
	strcpy(number, valueNumber);//Начальное значение числа при инициализации
		//По умолчанию начальное значение равно нулю
	int digit = strlen(number);
	for (int i = 1; i < digit; i++)
		if (number[i] > 57 || number[i] < 48)
			throw MyException("Элемент неправильно заполнен");
	if ((number[0] > 57 || number[0] < 48) && number[0] != '-')
		throw MyException("Элемент неправильно заполнен");
}
char* LongNumber::Get()
{
	return number;
}
void LongNumber::Set(const char* valueNumber)
{
	strcpy(number, valueNumber);
}
LongNumber& LongNumber::operator=(const LongNumber& numberObject)
{
	int digit = strlen(numberObject.number);
	for (int i = 1; i < digit; i++)
		if (numberObject.number[i] > 57 || numberObject.number[i] < 48)
			throw MyException("Присваиваемый элемент неправильно заполнен");
	if ((numberObject.number[0] > 57 || numberObject.number[0] < 48) && number[0] == '-')
		throw MyException("Присваиваемый элемент неправильно заполнен");
	strcpy(this->number, numberObject.number);
	return *this;//Возвращается ссылка на указатель объекта, к которому выполнили присваивание
}
bool LongNumber::operator==(const LongNumber& numberObject)
{
	if (Comparing(this->number, numberObject.number) == 0)
		return true;
	else return false;
}
bool LongNumber::operator!=(const LongNumber& numberObject)
{
	if (Comparing(this->number, numberObject.number) != 0)
		return true;
	else return false;
}
bool LongNumber::operator>(const LongNumber& numberObject)
{
	if (Comparing(this->number, numberObject.number) == 1)
		return true;
	else return false;
}
bool LongNumber::operator<(const LongNumber& numberObject)
{
	if (Comparing(this->number, numberObject.number) == -1)
		return true;
	else return false;
}
bool LongNumber::operator>=(const LongNumber& numberObject)
{
	if (Comparing(this->number, numberObject.number) >= 0)
		return true;
	else return false;
}
bool LongNumber::operator<=(const LongNumber& numberObject)
{
	if (Comparing(this->number, numberObject.number) <= 0)
		return true;
	else return false;
}
LongNumber LongNumber::operator+(const LongNumber& numberObject)
{
	char num1[255], num2[255];//Числа между которыми происходит сложение
	strcpy(num1, this->number);
	strcpy(num2, numberObject.number);
	char result[255];//Результат сложения
	bool minus1 = false, minus2 = false;//Знаки чисел
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
		minus2 = true;
	if (minus1 == minus2)//Если у чисел одинаковые знаки, мы их складываем
		strcpy(result, Adding(num1, num2, minus1));//Результат сложения будет со знаком чисел
	else//Если знаки разные проводим вычитание
		strcpy(result, Subtracting(num1, num2, minus1, minus2));//Результат вычитания будет со знаком большего числа
	LongNumber Number = result;//Результат сложения
	return Number;//Возвращаем полученное значение в нашем типе данных
}
LongNumber LongNumber::operator-(const LongNumber& numberObject)
{
	char num1[255], num2[255];//Числа между которыми происходит вычитание
	strcpy(num1, this->number);
	strcpy(num2, numberObject.number);
	char result[255];//Результат разности
	bool minus1 = false, minus2 = true;//Знаки чисел
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
	{
		minus2 = false;//Минус на минус даёт плюс, поэтому меняем знак числа
		for (int i = 0; num2[i] != '\0'; i++)
			num2[i] = num2[i + 1];
	}
	else//Иначе этот минус надо добавить к числу
	{
		for (int i = strlen(num2) + 1; i > 0; i--)
		{
			num2[i] = num2[i - 1];
		}
		num2[0] = '-';
	}
	if (minus1 == minus2)//Если у чисел одинаковые знаки, мы их складываем
		strcpy(result, Adding(num1, num2, minus1));//Результат сложения будет со знаком чисел
	else//Если знаки разные проводим вычитание
		strcpy(result, Subtracting(num1, num2, minus1, minus2));//Результат вычитания будет со знаком большего числа
	LongNumber Number = result;//Результат разности
	return Number;//Числа равны и результат вычитания равен нулю
}
LongNumber LongNumber::operator*(const LongNumber& numberObject)
{
	char num1[255], num2[255];//Числа между которыми происходит умножение
	strcpy(num1, this->number);
	strcpy(num2, numberObject.number);
	if (num1[0] == '0' || num2[0] == '0')
	{
		LongNumber Number = "0";
		return Number;//Результатом умножения на 0 будет 0
	}
	char result[255];//Результат умножения
	bool minus1 = false, minus2 = false;//Знаки чисел
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
		minus2 = true;
	LongNumber Number = Multiplication(num1, num2, minus1, minus2);
	return Number;//Возвращаем результат умножение в нашем типе данных
}
LongNumber LongNumber::operator/(const LongNumber& numberObject)
{
	LongNumber num1, num2;//Делимое и делитель
	num1.Set(this->number);
	num2.Set(numberObject.number);
	if (num2 == (LongNumber)"0")
		throw MyException("Делитель равне нулю");
	//Деление основывается на предыдущих методах и операциях между длинными числами
	bool minus1 = false, minus2 = false;//Знаки чисел
	if (num1.number[0] == '-')
	{
		minus1 = true;
		num1 = num1 * (LongNumber)"-1";//Избавляемся от минуса
	}
	if (num2.number[0] == '-')
	{
		minus2 = true;
		num2 = num2 * (LongNumber)"-1";//Избавляемся от минуса
	}
	if (num1 < num2)
	{
		LongNumber Number = "0";
		return Number;//Если делитель больше делимого, то целая часть результата деленя будет равна нулю
	}
	int digit1 = strlen(num1.Get());//Разрядов в первом числе
	int digit2 = strlen(num2.Get());//Разрядов во втором числе
	int difdigit = digit1 - digit2;//Разница в разрядах между числами
	LongNumber result = "1";//Результат деления
	for (int i = 0; i < difdigit; i++)
		result = result * (LongNumber)"10";//Всего разрядов в результате
	result = DivisionRecursion(num1, num2, result, difdigit);
	if (minus1 != minus2)
		result = result * (LongNumber)"-1";//Если знаки делимого и делителя различны, то результат будет отрицательным
	return result;
}
LongNumber& LongNumber::operator++()
{
	strcpy(this->number, ((LongNumber)number + (LongNumber)"1").number);
	return *this;
}
LongNumber& LongNumber::operator++(int dummy)
{
	LongNumber container = *this;
	strcpy(this->number, ((LongNumber)number + (LongNumber)"1").number);
	return container;
}
LongNumber& LongNumber::operator--()
{
	strcpy(this->number, ((LongNumber)number - (LongNumber)"1").number);
	return *this;
}
LongNumber& LongNumber::operator--(int dummy)
{
	LongNumber container = *this;
	strcpy(this->number, ((LongNumber)number - (LongNumber)"1").number);
	return container;
}
LongNumber& LongNumber::operator+=(const LongNumber& numberObject)
{
	strcpy(this->number, ((LongNumber)number + numberObject).number);
	return *this;
}
LongNumber& LongNumber::operator-=(const LongNumber& numberObject)
{
	strcpy(this->number, ((LongNumber)number - numberObject).number);
	return *this;
}
