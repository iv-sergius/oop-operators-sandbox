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

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integralPart = m_numerator / m_denominator;
	CRational fractionalPart(m_numerator % m_denominator, m_denominator);
	return std::pair<int, CRational>(integralPart, fractionalPart);
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

double CRational::ToDouble() const
{
	return m_numerator / static_cast<double>(m_denominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator +() const
{
	return *this;
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

CRational const operator +(CRational const& rational1, CRational const& rational2)
{
	int denominatorsGCD = GCD(rational1.GetDenominator(), rational2.GetDenominator());
	// overflow
	int newDenominator = rational1.GetDenominator() / denominatorsGCD * rational2.GetDenominator();
	// overflow
	int newNumenator = rational1.GetNumerator() * (rational2.GetDenominator() / denominatorsGCD)
		+ rational2.GetNumerator() * (rational1.GetDenominator() / denominatorsGCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////

CRational const operator -(CRational const& rational1, CRational const& rational2)
{
	int denominatorsGCD = GCD(rational1.GetDenominator(), rational2.GetDenominator());
	// overflow
	int newDenominator = rational1.GetDenominator() / denominatorsGCD * rational2.GetDenominator();
	// overflow
	int newNumenator = rational1.GetNumerator() * (rational2.GetDenominator() / denominatorsGCD)
		- rational2.GetNumerator() * (rational1.GetDenominator() / denominatorsGCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
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

CRational const operator *(CRational const& rational1, CRational const& rational2)
{
	int numerator1denominator2GCD = GCD(rational1.GetNumerator(), rational2.GetDenominator());
	int denominator1numerator2GCD = GCD(rational1.GetDenominator(), rational2.GetNumerator());
	// overflow
	int newDenominator = (rational1.GetDenominator() / denominator1numerator2GCD)
		* (rational2.GetDenominator() / numerator1denominator2GCD);
	// overflow
	int newNumenator = (rational1.GetNumerator() / numerator1denominator2GCD) * (rational2.GetNumerator() / denominator1numerator2GCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////

CRational const operator /(CRational const& rational1, CRational const& rational2)
{
	int numeratorsGCD = GCD(rational1.GetNumerator(), rational2.GetNumerator());
	int denominatorsGCD = GCD(rational1.GetDenominator(), rational2.GetDenominator());
	// overflow
	int newDenominator = (rational1.GetDenominator() / denominatorsGCD) * (rational2.GetNumerator() / numeratorsGCD);
	// overflow
	int newNumenator = (rational1.GetNumerator() / numeratorsGCD) * (rational2.GetDenominator() / denominatorsGCD);

	CRational resultRational = CRational(newNumenator, newDenominator);
	return resultRational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator *=(CRational const& rational2)
{
	*this = *this * rational2;
	return *this;
}
CRational& CRational::operator *=(int integer)
{
	*this = *this * integer;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////

CRational& CRational::operator /=(CRational const& rational2)
{
	*this = *this / rational2;
	return *this;
}
CRational& CRational::operator /=(int integer)
{
	*this = *this / integer;
	return *this;
}
//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////

bool const operator ==(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() == rational2.GetNumerator() && rational1.GetDenominator() == rational2.GetDenominator();
}

bool const operator !=(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() != rational2.GetNumerator() || rational1.GetDenominator() != rational2.GetDenominator();
}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////

bool const operator <(CRational const& rational1, CRational const& rational2)
{
	CRational difference = rational1 - rational2;
	return difference.GetNumerator() < 0;
}

bool const operator >(CRational const& rational1, CRational const& rational2)
{
	CRational difference = rational1 - rational2;
	return difference.GetNumerator() > 0;
}

bool const operator <=(CRational const& rational1, CRational const& rational2)
{
	CRational difference = rational1 - rational2;
	return difference.GetNumerator() <= 0;
}

bool const operator >=(CRational const& rational1, CRational const& rational2)
{
	CRational difference = rational1 - rational2;
	return difference.GetNumerator() >= 0;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & strm, const CRational & rational)
{
	strm << rational.GetNumerator() << '/' << rational.GetDenominator();
	return strm;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////

std::istream & operator >> (std::istream & strm, CRational & rational)
{
	int numerator, denominator;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		strm.setstate(std::ios_base::failbit);
	}
	return strm;
}

