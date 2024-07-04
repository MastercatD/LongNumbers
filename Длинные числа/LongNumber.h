#ifndef ADD_H
#define ADD_H
#include <exception>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class MyException : public exception//Класс обработки
{
public:
	MyException(const char* msg) :exception(msg) {}
};
class LongNumber//Класс длинных чисел
{
	char number[255];
	int Comparing(const char* num1, const char* num2, bool abs = false);//Метод сравнения чисел в строковой форме
	char* Adding(const char* num1, const char* num2, const bool minus);//Метод сложения двух чисел
	char* Subtracting(char* num1, char* num2, const bool minus1, const bool minus2);//Метод разности двух чисел
	char* Multiplication(const char* num1, const char* num2, const bool minus1, const bool minus2);//Метод умножения двух чисел
	LongNumber DivisionRecursion(LongNumber num1, LongNumber num2, LongNumber result, int digit);//Деление числа нацело
public:
	//Конструктор копирования взят по умолчанию
	//Деструктор класса взят по умолчанию
	void Print();//Вывод числа
	LongNumber(const char* valueNumber = "0");//Конструктор класса
	char* Get();//Получить значение числа
	void Set(const char* valueNumber);//Задать число
	LongNumber& operator = (const LongNumber& numberObject);//Оператор присваивания
	bool operator == (const LongNumber& numberObject);//Оператор сравнения — равенство
	bool operator != (const LongNumber& numberObject);//Оператор сравнения — неравенство
	bool operator > (const LongNumber& numberObject);//Оператор сравнения — больше
	bool operator < (const LongNumber& numberObject);//Оператор сравнения — меньше
	bool operator >= (const LongNumber& numberObject);//Оператор сравнения — больше или равно
	bool operator <= (const LongNumber& numberObject);//Оператор сравнения — меньше или равно
	LongNumber operator + (const LongNumber& numberObject);//Оператор сложения
	LongNumber operator - (const LongNumber& numberObject);//Оператор вычитания
	LongNumber operator * (const LongNumber& numberObject);//Оператор умножения
	LongNumber operator / (const LongNumber& numberObject);//Оператор деления
	LongNumber& operator ++ ();//Инкремент в префиксной форме
	LongNumber& operator ++ (int dummy);//Инкремент в постфиксной форме
	LongNumber& operator -- ();//Декремент в префиксной форме
	LongNumber& operator -- (int dummy);//Декремент в постфиксной форме
	LongNumber& operator +=(const LongNumber& numberObject);//Сложение присваивание
	LongNumber& operator -=(const LongNumber& numberObject);//Вычитание присваивание
};
#endif