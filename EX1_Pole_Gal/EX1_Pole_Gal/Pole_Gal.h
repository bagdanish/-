#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Pole_Gal
{
private:
	int degree_; // ������� ������������� ��������
	vector<unsigned char> elements; // ������ ��������� ����
	vector<int> irreducible_polynomial; // 30 ������������ ���������

	int getDegree(const int& value); // ����� ��� ������ ������� ������������ ������� 2
	int divide(int a, int b); // ���������� �������
public:
	Pole_Gal(int degree);

	unsigned char add(const unsigned char& a, const unsigned char& b);
	unsigned char multiply(const unsigned char& a, const unsigned char& b); 
	unsigned char inverse(const unsigned char& a); 

};
