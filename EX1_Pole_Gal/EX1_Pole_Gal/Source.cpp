#include "Pole_Gal.h"

int Pole_Gal::getDegree(const int& value)
{
	int number = 0;
	int one = 1;

	if (value == 0) return -1;

	for (int i = 0; i < degree_ * 2 - 1; i++) // ���� �� ���� ��������
	{
		if (one & value) { number = i; }
		one <<= 1;
	}

	return number;
}

unsigned char Pole_Gal::add(const unsigned char& a, const unsigned char& b)
{
	return a ^ b;
}

unsigned char Pole_Gal::multiply(const unsigned char& a, const unsigned char& b)
{
	int result = 0;
	int one_a = getDegree(int(a)); // ������ ������� ������� �����
	const int one_b_old = getDegree(int(b)); // ������ ������� ������� �����
	int one_b_new = one_b_old;

	while (one_a != -1)
	{
		if (a & (1 << one_a)) // ���� ��� ������� ����� �������
		{
			while (one_b_new != -1)
			{
				if (b & (1 << one_b_new)) // ���� ��� ������� ����� �������
				{
					if (result & (1 << (one_a + one_b_new))) { result &= (~(1 << (one_a + one_b_new))); } // ���� � ���������� ��� ���� ��� ������� -> ����� �������� ��
					else { result |= 1 << (one_a + one_b_new); }
				}

				--one_b_new;
			}
		}

		--one_a;
		one_b_new = one_b_old;
	}

	if (result > ((1 << degree_) - 1))
	{
		return unsigned char(divide(result, irreducible_polynomial.front())); // ����� ������ ������������ �������
	}
	else return unsigned char(result);
}

int Pole_Gal::divide(int a, int b)
{
	int value_new = 0;

	// ������� ����� ��� ������ 
	int degree_old = getDegree(b);
	int degree_new = getDegree(a);

	while (degree_old <= degree_new)
	{
		value_new = b << (degree_new - degree_old);
		a ^= value_new;
		degree_new = getDegree(a);
	}

	return a;
}

Pole_Gal::Pole_Gal(int degree) : degree_(degree)
{
	// ��������� �������� ����
	for (unsigned char i = 0; i < UCHAR_MAX; i++) { elements.push_back(i); }

	// ����� ������� ������������ �������� ��� ������� ����
	int value = 1 << degree_;
	vector<unsigned char>::iterator iter = elements.begin() + 2; // ���������� 0 � 1
	bool flag = true;

	while (!((1 << (degree_ + 1)) & value))
	{
		while (iter != elements.end())
		{
			if (!divide(value, int(*iter))) { flag = false; break; }
			++iter;
		}

		if (flag) { irreducible_polynomial.push_back(value); }
		++value; flag = true; iter = elements.begin() + 2;
	}

}


unsigned char Pole_Gal::inverse(const unsigned char& a)
{
	if (a == 0 || a == 1) { return a; }
	else
	{
		int result = 1;
		int step = (1 << degree_) - 2; // ������� � �������� �����
		int one = getDegree(step); // �������� ������ �������

		while (one != -1)
		{
			if ((1 << one) & step)
			{
				result = multiply(result, a);
				result = multiply(result, result);
			}
			else { result = multiply(result, result); }

			--one;
		}

		return unsigned char(result);
	}
}