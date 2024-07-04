#ifndef ADD_H
#define ADD_H
#include <exception>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class MyException : public exception//����� ���������
{
public:
	MyException(const char* msg) :exception(msg) {}
};
class LongNumber//����� ������� �����
{
	char number[255];
	int Comparing(const char* num1, const char* num2, bool abs = false);//����� ��������� ����� � ��������� �����
	char* Adding(const char* num1, const char* num2, const bool minus);//����� �������� ���� �����
	char* Subtracting(char* num1, char* num2, const bool minus1, const bool minus2);//����� �������� ���� �����
	char* Multiplication(const char* num1, const char* num2, const bool minus1, const bool minus2);//����� ��������� ���� �����
	LongNumber DivisionRecursion(LongNumber num1, LongNumber num2, LongNumber result, int digit);//������� ����� ������
public:
	//����������� ����������� ���� �� ���������
	//���������� ������ ���� �� ���������
	void Print();//����� �����
	LongNumber(const char* valueNumber = "0");//����������� ������
	char* Get();//�������� �������� �����
	void Set(const char* valueNumber);//������ �����
	LongNumber& operator = (const LongNumber& numberObject);//�������� ������������
	bool operator == (const LongNumber& numberObject);//�������� ��������� � ���������
	bool operator != (const LongNumber& numberObject);//�������� ��������� � �����������
	bool operator > (const LongNumber& numberObject);//�������� ��������� � ������
	bool operator < (const LongNumber& numberObject);//�������� ��������� � ������
	bool operator >= (const LongNumber& numberObject);//�������� ��������� � ������ ��� �����
	bool operator <= (const LongNumber& numberObject);//�������� ��������� � ������ ��� �����
	LongNumber operator + (const LongNumber& numberObject);//�������� ��������
	LongNumber operator - (const LongNumber& numberObject);//�������� ���������
	LongNumber operator * (const LongNumber& numberObject);//�������� ���������
	LongNumber operator / (const LongNumber& numberObject);//�������� �������
	LongNumber& operator ++ ();//��������� � ���������� �����
	LongNumber& operator ++ (int dummy);//��������� � ����������� �����
	LongNumber& operator -- ();//��������� � ���������� �����
	LongNumber& operator -- (int dummy);//��������� � ����������� �����
	LongNumber& operator +=(const LongNumber& numberObject);//�������� ������������
	LongNumber& operator -=(const LongNumber& numberObject);//��������� ������������
};
#endif