#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Pole_Gal
{
private:
	int degree_; // степень неприводимого полинома
	vector<unsigned char> elements; // вектор элементов поля
	vector<int> irreducible_polynomial; // 30 неприводимых полиномов

	int getDegree(const int& value); // метод для поиска позиции максимальной степени 2
	int divide(int a, int b); // возвращает остаток
public:
	Pole_Gal(int degree);

	unsigned char add(const unsigned char& a, const unsigned char& b);
	unsigned char multiply(const unsigned char& a, const unsigned char& b); 
	unsigned char inverse(const unsigned char& a); 

};
