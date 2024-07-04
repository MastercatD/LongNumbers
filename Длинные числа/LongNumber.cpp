#include "LongNumber.h"
using namespace std;


int LongNumber::Comparing(const char* num1, const char* num2, bool abs)
{
	bool minus1 = false, minus2 = false;//����� �����
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
		minus2 = true;
	if (abs == false)//���������� �������� �����, � �� �� ������
	{
		if (minus1 > minus2)//����������� �������� ����� ���������� ������
			return 1;
		if (minus1 < minus2)
			return -1;
	}
	int size1 = strlen(num1);//������� 1 ����� 
	int size2 = strlen(num2);//������� 2 ����� 
	if (size1 - minus1 > size2 - minus2)//����������� �������� ����� ���������� �� �����
		return 1;
	if (size1 - minus1 < size2 - minus2)
		return -1;
	for (int i = minus1, j = minus2; num1[i] != '\0'; i++, j++)//��������� �������� �����
	{
		if (num1[i] > num2[j])
			return 1;
		if (num1[i] < num2[j])
			return -1;
	}
	return 0;//����� �����
}
char* LongNumber::Adding(const char* num1, const char* num2, const bool minus)
{
	int remains = 0;//�������
	int digit = 0, digit1, digit2;//������������ ������� �����, ������� ������� � ������� �����
	char result[255];//��������� ��������
	digit1 = strlen(num1);//�������� 1 �����
	digit2 = strlen(num2);//�������� 2 �����
	digit1--; digit2--;
	int beg = 0;//������ �����
	if (minus == true)
		beg = 1;//��� ������� ������ ������ ����� ��������� � ����� �� �����������
	while (digit1 >= beg && digit2 >= beg)
	{
		//����������� ����� ���������� �� �������� �������� � �������
		remains += (num1[digit1] - '0') + (num2[digit2] - '0');
		result[digit] = (remains % 10 + '0');
		remains /= 10;
		digit1--; digit2--; digit++;
	}
	if (digit1 < beg)
	{
		while (remains != 0 && digit2 >= beg)//���� ������� �� ��� ������������, ��������� ���
		{
			remains += (num2[digit2] - '0');
			result[digit] = (remains % 10 + '0');
			remains /= 10;
			digit++; digit2--;
		}
		while (digit2 >= beg)//����� ������� ���, ������ ��������� ������� ������� �����
		{
			result[digit] = num2[digit2];
			digit++; digit2--;
		}
	}
	if (digit2 < beg)
	{
		while (remains != 0 && digit1 >= beg)//���� ������� �� ��� ������������, ��������� ���
		{
			remains += (num1[digit1] - '0');
			result[digit] = (remains % 10 + '0');
			remains /= 10;
			digit++; digit1--;
		}
		while (digit1 >= beg)//����� ������� ���, ������ ��������� ������� ������� �����
		{
			result[digit] = num1[digit1];
			digit++; digit1--;
		}
	}
	if (remains != 0)
	{
		result[digit] = remains + '0';//��� ������� ������� ��������� �� ����� ������� ������
		if (minus)
		{
			digit++;
			result[digit] = '-';//������ ����� ��� �������� ���� ������������� �����
		}
		result[digit + 1] = '\0';//�������� ������
	}
	else//����� ������ ������ ����� � �������� ������
	{
		if (minus)
		{
			result[digit] = '-';//������ ����� ��� �������� ���� ������������� �����
			digit++;
		}
		result[digit] = '\0';
		digit--;
	}
	for (int inversdig = 0; inversdig < digit; digit--, inversdig++)//����������� �����, ��� ��� ����� � �� ��������� � �������� �������
	{
		char container = result[inversdig];//��������� ���������
		result[inversdig] = result[digit];
		result[digit] = container;
	}
	return result;
}
char* LongNumber::Subtracting(char* num1, char* num2, const bool minus1, const bool minus2)
{
	int remains = 0;//��������� ��������� ���� ����
	int digit, digit1, digit2;//������������ ������� �����, ������� ������� � ������� �����
	char result[255];//��������� ���������
	bool minus;//���� ����������
	if (Comparing(num1, num2, true) == 0)
	{//���� ����� ��������� �� ����������� �� ��������� ����� ����
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	if (Comparing(num1, num2, true) == -1)
	{
		char container[255];//��������� ���������
		strcpy(container, num2);
		strcpy(num2, num1);
		strcpy(num1, container);
		minus = minus2;
	}//num1 ������� �����, num2 ������� �����
	else minus = minus1;//��������� ����� �� ������ �������� �����
	digit1 = strlen(num1);//�������� 1 �����
	digit2 = strlen(num2);//�������� 2 �����
	digit1--; digit2--;
	int beg1 = 0, beg2 = 0;//������ ������� � ������� ����� � ������
	if (minus == true)
		beg1 = 1;
	else beg2 = 1;
	digit = beg1;//��������� ������ � ����������� �� ������� ������
	while (digit2 >= beg2)
	{
		//�������� ����� ��������� ���������� � �������
		remains += (num1[digit1] - '0') - (num2[digit2] - '0');
		if (remains < 0)
		{
			num1[digit1 - 1] = ((num1[digit1 - 1] - '0') - 1) + '0';//�������� ������� �� ������ ����
			remains += 10;
		}
		result[digit] = remains + '0';
		remains = 0;
		digit1--; digit2--; digit++;
	}
	while (digit1 >= beg1)//���������� ������� ��������� ������� ������ num1
	{
		result[digit] = num1[digit1];
		digit++; digit1--;
	}
	int diff = 0;//�����������, �� ������� �������� ����������� ���������� �����
	for (int digitcopy = digit - 1; result[digitcopy] == '0'; digitcopy--, diff++);
	result[digit - diff] = '\0';//�������� ����� ������
	digit--;
	for (int inversdig = beg1; inversdig < digit - diff; digit--, inversdig++)//����������� �����, ��� ��� ����� � �� ��������� � �������� �������
	{
		char container = result[inversdig];//��������� ���������
		result[inversdig] = result[digit - diff];
		result[digit - diff] = container;
	}
	if (minus)
		result[0] = '-';//������ ����� ���� ��������� ���������� �������������

	return result;
}
char* LongNumber::Multiplication(const char* num1, const char* num2, const bool minus1, const bool minus2)
{
	int remains = 0;//������� �� ��������� ���� ����
	int digit = 0, digit1, digit2;//������������ ������� �����, ������� ������� � ������� �����
	char result[255];//��������� ���������
	result[0] = '0';
	result[1] = '\0';
	bool minus = false;//���� ����������
	digit1 = strlen(num1);//�������� 1 �����
	digit2 = strlen(num2);//�������� 2 �����
	digit1--; digit2--;
	if (minus1 != minus2)//���� ���������� ������� �� ������ ����������
		minus = true;//��� ������� ������ ������ �������
	for (int digadd = 0; digit2 >= (int)minus2; digadd++, digit2--)//��������� ����� �� �����
	{
		char addresult[255];//��������� ��������� �� ���� �� ��������
		//��������� � ������� 
		digit = 0;
		while (digit < digadd)
		{
			addresult[digit] = '0';
			digit++;//��������� ������ �������� �����
		}

		for (int digit1copy = digit1; digit1copy >= (int)minus1; digit1copy--, digit++)
		{
			remains += (num2[digit2] - '0') * (num1[digit1copy] - '0');
			addresult[digit] = remains % 10 + '0';
			remains /= 10;
		}
		while (remains != 0)//����������� �� �������
		{
			addresult[digit] = remains % 10 + '0';
			remains /= 10;
			digit++;
		}
		addresult[digit] = '\0';//�������� ������
		digit--;
		for (int inversdig = 0; inversdig < digit; digit--, inversdig++)//����������� �����, ��� ��� ����� � �� ��������� � �������� �������
		{
			char container = addresult[inversdig];//��������� ���������
			addresult[inversdig] = addresult[digit];
			addresult[digit] = container;
		}
		strcpy(result, Adding(result, addresult, false));//���������� � ��������� �����������
	}
	if (minus)//��������� ����� � �����
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
	LongNumber curdigit = "1";//������� ������
	for (int i = 1; i < digit; i++)
		curdigit = curdigit * (LongNumber)"10";
	while (num1 < result * num2)
	{
		result = result - curdigit;
	}
	digit--;//��������� ������
	if (digit > 0)
	{
		result = result + curdigit;
		result = DivisionRecursion(num1, num2, result, digit);//���� ����� ���������� �������� ������ �����
	}
	return result;
}
void LongNumber::Print()
{
	cout << number;
}
LongNumber::LongNumber(const char* valueNumber)
{
	strcpy(number, valueNumber);//��������� �������� ����� ��� �������������
		//�� ��������� ��������� �������� ����� ����
	int digit = strlen(number);
	for (int i = 1; i < digit; i++)
		if (number[i] > 57 || number[i] < 48)
			throw MyException("������� ����������� ��������");
	if ((number[0] > 57 || number[0] < 48) && number[0] != '-')
		throw MyException("������� ����������� ��������");
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
			throw MyException("������������� ������� ����������� ��������");
	if ((numberObject.number[0] > 57 || numberObject.number[0] < 48) && number[0] == '-')
		throw MyException("������������� ������� ����������� ��������");
	strcpy(this->number, numberObject.number);
	return *this;//������������ ������ �� ��������� �������, � �������� ��������� ������������
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
	char num1[255], num2[255];//����� ����� �������� ���������� ��������
	strcpy(num1, this->number);
	strcpy(num2, numberObject.number);
	char result[255];//��������� ��������
	bool minus1 = false, minus2 = false;//����� �����
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
		minus2 = true;
	if (minus1 == minus2)//���� � ����� ���������� �����, �� �� ����������
		strcpy(result, Adding(num1, num2, minus1));//��������� �������� ����� �� ������ �����
	else//���� ����� ������ �������� ���������
		strcpy(result, Subtracting(num1, num2, minus1, minus2));//��������� ��������� ����� �� ������ �������� �����
	LongNumber Number = result;//��������� ��������
	return Number;//���������� ���������� �������� � ����� ���� ������
}
LongNumber LongNumber::operator-(const LongNumber& numberObject)
{
	char num1[255], num2[255];//����� ����� �������� ���������� ���������
	strcpy(num1, this->number);
	strcpy(num2, numberObject.number);
	char result[255];//��������� ��������
	bool minus1 = false, minus2 = true;//����� �����
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
	{
		minus2 = false;//����� �� ����� ��� ����, ������� ������ ���� �����
		for (int i = 0; num2[i] != '\0'; i++)
			num2[i] = num2[i + 1];
	}
	else//����� ���� ����� ���� �������� � �����
	{
		for (int i = strlen(num2) + 1; i > 0; i--)
		{
			num2[i] = num2[i - 1];
		}
		num2[0] = '-';
	}
	if (minus1 == minus2)//���� � ����� ���������� �����, �� �� ����������
		strcpy(result, Adding(num1, num2, minus1));//��������� �������� ����� �� ������ �����
	else//���� ����� ������ �������� ���������
		strcpy(result, Subtracting(num1, num2, minus1, minus2));//��������� ��������� ����� �� ������ �������� �����
	LongNumber Number = result;//��������� ��������
	return Number;//����� ����� � ��������� ��������� ����� ����
}
LongNumber LongNumber::operator*(const LongNumber& numberObject)
{
	char num1[255], num2[255];//����� ����� �������� ���������� ���������
	strcpy(num1, this->number);
	strcpy(num2, numberObject.number);
	if (num1[0] == '0' || num2[0] == '0')
	{
		LongNumber Number = "0";
		return Number;//����������� ��������� �� 0 ����� 0
	}
	char result[255];//��������� ���������
	bool minus1 = false, minus2 = false;//����� �����
	if (num1[0] == '-')
		minus1 = true;
	if (num2[0] == '-')
		minus2 = true;
	LongNumber Number = Multiplication(num1, num2, minus1, minus2);
	return Number;//���������� ��������� ��������� � ����� ���� ������
}
LongNumber LongNumber::operator/(const LongNumber& numberObject)
{
	LongNumber num1, num2;//������� � ��������
	num1.Set(this->number);
	num2.Set(numberObject.number);
	if (num2 == (LongNumber)"0")
		throw MyException("�������� ����� ����");
	//������� ������������ �� ���������� ������� � ��������� ����� �������� �������
	bool minus1 = false, minus2 = false;//����� �����
	if (num1.number[0] == '-')
	{
		minus1 = true;
		num1 = num1 * (LongNumber)"-1";//����������� �� ������
	}
	if (num2.number[0] == '-')
	{
		minus2 = true;
		num2 = num2 * (LongNumber)"-1";//����������� �� ������
	}
	if (num1 < num2)
	{
		LongNumber Number = "0";
		return Number;//���� �������� ������ ��������, �� ����� ����� ���������� ������ ����� ����� ����
	}
	int digit1 = strlen(num1.Get());//�������� � ������ �����
	int digit2 = strlen(num2.Get());//�������� �� ������ �����
	int difdigit = digit1 - digit2;//������� � �������� ����� �������
	LongNumber result = "1";//��������� �������
	for (int i = 0; i < difdigit; i++)
		result = result * (LongNumber)"10";//����� �������� � ����������
	result = DivisionRecursion(num1, num2, result, difdigit);
	if (minus1 != minus2)
		result = result * (LongNumber)"-1";//���� ����� �������� � �������� ��������, �� ��������� ����� �������������
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
