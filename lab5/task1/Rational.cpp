#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>
#include <limits>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
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

double CRational::ToDouble() const
{
	return m_numerator / static_cast<double>(m_denominator);
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
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

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator +() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const CRational::operator -() const
{
	if (m_numerator == std::numeric_limits<int>::min())
	{
		throw(std::out_of_range("Numenator out of range of int type"));
	}
	return CRational(-m_numerator, m_denominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator +(CRational const& rational2) const
{
	int denominatorsGCD = GCD(m_denominator, rational2.m_denominator);
	// overflow
	int newDenominator = m_denominator / denominatorsGCD * rational2.m_denominator;
	// overflow
	int newNumenator = m_numerator * (rational2.m_denominator / denominatorsGCD)
		+ rational2.m_numerator * (m_denominator / denominatorsGCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

CRational const operator +(CRational const& rational, int integer)
{
	return rational + CRational(integer, 1);
}

CRational const operator +(int integer, CRational const& rational)
{
	return CRational(integer, 1) + rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator -(CRational const& rational2) const
{
	int denominatorsGCD = GCD(m_denominator, rational2.m_denominator);
	// overflow
	int newDenominator = m_denominator / denominatorsGCD * rational2.m_denominator;
	// overflow
	int newNumenator = m_numerator * (rational2.m_denominator / denominatorsGCD)
		- rational2.m_numerator * (m_denominator / denominatorsGCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

CRational const operator -(CRational const& rational, int integer)
{
	return rational - CRational(integer, 1);
}

CRational const operator -(int integer, CRational const& rational)
{
	return CRational(integer, 1) - rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator +=(CRational const& rational2)
{
	*this = *this + rational2;
	return *this;
}
CRational& CRational::operator +=(int integer)
{
	*this = *this + integer;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator -=(CRational const& rational2)
{
	*this = *this - rational2;
	return *this;
}
CRational& CRational::operator -=(int integer)
{
	*this = *this - integer;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator *(CRational const& rational2) const
{
	int numerator1denominator2GCD = GCD(m_numerator, rational2.m_denominator);
	int denominator1numerator2GCD = GCD(m_denominator, rational2.m_numerator);
	// overflow
	int newDenominator = (m_denominator / denominator1numerator2GCD) 
		* (rational2.m_denominator / numerator1denominator2GCD);
	// overflow
	int newNumenator = (m_numerator / numerator1denominator2GCD) * (rational2.m_numerator / denominator1numerator2GCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

CRational const operator *(CRational const& rational, int integer)
{
	return rational * CRational(integer, 1);
}

CRational const operator *(int integer, CRational const& rational)
{
	return CRational(integer, 1) * rational;
}
//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator /(CRational const& rational2) const
{
	int numeratorsGCD = GCD(m_numerator, rational2.m_numerator);
	int denominatorsGCD = GCD(m_denominator, rational2.m_denominator);
	// overflow
	int newDenominator = (m_denominator / denominatorsGCD) * (rational2.m_numerator / numeratorsGCD);
	// overflow
	int newNumenator = (m_numerator / numeratorsGCD) * (rational2.m_denominator / denominatorsGCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

CRational const operator /(CRational const& rational, int integer)
{
	return rational / CRational(integer, 1);
}

CRational const operator /(int integer, CRational const& rational)
{
	return CRational(integer, 1) / rational;
}
//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////


