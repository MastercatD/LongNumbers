#include <iostream>
#include <stdio.h>
#include <string.h>
#include "LongNumber.h"
using namespace std;

int main()
{
	try
	{
		LongNumber A, B, C;//Числа для проверки 
		A.Set("25234636342347846");
		B = (LongNumber)"4125425734571313";
		C = B;//Присваиваем числам значения
		//Сравнение
		if (C == B)
		{
			cout << C.Get() << " = ";
			B.Print();
			cout << endl;
		}
		else
			cout << C.Get() << " != " << B.Get() << endl;
		if (C != A)
			cout << C.Get() << " != " << A.Get() << endl;
		else
			cout << C.Get() << " = " << A.Get() << endl;
		//Больше или меньше
		if (A > B)
			cout << A.Get() << " > " << B.Get() << endl;
		if (A < B)
			cout << A.Get() << " < " << B.Get() << endl;
		//Сложение
		C = A + B;
		cout << A.Get() << " + " << B.Get() << " = " << C.Get() << endl;
		//Вычитание
		C = A - B;
		cout << A.Get() << " - " << B.Get() << " = " << C.Get() << endl;
		C = B - A;
		cout << B.Get() << " - " << A.Get() << " = " << C.Get() << endl;
		//Умножение
		C = A * B;
		cout << A.Get() << " * " << B.Get() << " = " << C.Get() << endl;
		C = A * (LongNumber)"-1";
		cout << A.Get() << " * " << "(-1)" << " = " << C.Get() << endl;
		//Деление
		C = A / B;
		cout << A.Get() << " / " << B.Get() << " = " << C.Get() << endl;
		//Инкременты
		C = A;
		C++;
		cout << A.Get() << " -> " << C.Get() << endl;
		C = B;
		++C;
		cout << B.Get() << " -> " << C.Get() << endl;
		//Декременты
		C = A;
		C--;
		cout << A.Get() << " -> " << C.Get() << endl;
		C = B;
		--C;
		cout << B.Get() << " -> " << C.Get() << endl;
		//Сложение с присваиванием
		A = C;
		C += B;
		cout << A.Get() << " + " << B.Get() << " = " << C.Get() << endl;
		//Вычитание с присваиванием
		C = A;
		C -= B;
		cout << A.Get() << " - " << B.Get() << " = " << C.Get() << endl;
	}
catch (const MyException& ex)
{
	cout << ex.what();
	return 0;
}
}
