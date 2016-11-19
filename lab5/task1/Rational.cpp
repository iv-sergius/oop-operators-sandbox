#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>
#include <cassert>

CRational::CRational(int numerator, int denominator)
{
	Assign(numerator, denominator);
}

void CRational::Assign(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	m_numerator = numerator;
	m_denominator = denominator;
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

double CRational::ToDouble() const
{
	assert(m_denominator != 0);
	return static_cast<double>(m_numerator) / m_denominator;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

unsigned LCM(unsigned a, unsigned b)
{
	return a / GCD(a, b) * b;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////
const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	int k = (m_denominator < 0 || m_denominator < 0) ? +1 : -1;
	return CRational(k * m_numerator, m_denominator);
}




//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////
const CRational operator+(const CRational & lhs, const CRational & rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
	int denominator = lhs.GetDenominator() * rhs.GetDenominator();
	return CRational(numerator, denominator);
}




//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////
const CRational operator-(const CRational & lhs, const CRational & rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator();
	int denominator = lhs.GetDenominator() * rhs.GetDenominator();
	return CRational(numerator, denominator);
}




//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator+=(const CRational & summand)
{
	if (summand.GetNumerator() == 0)
	{
		return *this;
	}
	auto lcm = LCM(GetDenominator(), summand.GetDenominator());
	Assign(
		GetNumerator() * (lcm / summand.GetDenominator()) +
			summand.GetNumerator() * (lcm / GetDenominator()),
		lcm);
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator-=(const CRational & subtrahend)
{
	if (subtrahend.GetNumerator() == 0)
	{
		return *this;
	}
	auto lcm = LCM(GetDenominator(), subtrahend.GetDenominator());
	Assign(
		subtrahend.GetNumerator() * (lcm / GetDenominator()) - 
			GetNumerator() * (lcm / subtrahend.GetDenominator()), 
		lcm);
	return *this;
}




//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////
const CRational operator*(const CRational & lhs, const CRational & rhs)
{
	return CRational(lhs.GetNumerator() * rhs.GetNumerator(),
	                 lhs.GetDenominator() * rhs.GetDenominator());
}



//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////
const CRational operator/(const CRational & dividend, const CRational & divider)
{
	return CRational(dividend.GetNumerator() * divider.GetDenominator(),
	                 dividend.GetDenominator() * divider.GetNumerator());
}




//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator*=(const CRational & multiplier)
{
	Assign(m_numerator * multiplier.GetNumerator(), m_denominator * multiplier.GetDenominator());
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator/=(const CRational & divider)
{
	Assign(m_numerator * divider.GetDenominator(), m_denominator * divider.GetNumerator());
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////
const bool operator<(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator());
}

const bool operator>(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() > rhs.GetNumerator() * lhs.GetDenominator());
}

const bool operator<=(const CRational & lhs, const CRational & rhs)
{
	return !(lhs > rhs);
}

const bool operator>=(const CRational & lhs, const CRational & rhs)
{
	return !(lhs < rhs);
}




//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & output, const CRational & rat)
{
	output << rat.GetNumerator() << '/' << rat.GetDenominator();
	return output;
}





//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////


