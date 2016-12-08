// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"
#include <limits>

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}



/*
  Рациональное число:
	равно нулю по умолчанию (0/1)
	может быть созданно из целого в формате (n / 1)
	может быть задано с указанием числителя и знаменателя
	хранится в нормализованном виде
	*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}
void VerifyRational(const CRational & r, const CRational & expectedR)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedR.GetNumerator());
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedR.GetDenominator());
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}




//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE(ToDouble_function)
	
		BOOST_AUTO_TEST_CASE(work_for_0)
		{
			BOOST_CHECK_CLOSE_FRACTION(CRational(0, 1).ToDouble(), 0.0, DBL_EPSILON);
		}
		BOOST_AUTO_TEST_CASE(work_for_finite_fraction)
		{
			BOOST_CHECK_CLOSE_FRACTION(CRational(3, 5).ToDouble(), 0.6, DBL_EPSILON);
			BOOST_CHECK_CLOSE_FRACTION(CRational(-4, 25).ToDouble(), -0.16, DBL_EPSILON);
		}
		BOOST_AUTO_TEST_CASE(work_for_unfinite_fraction)
		{
			BOOST_CHECK_CLOSE_FRACTION(CRational(1, 3).ToDouble(), 1.0 / 3.0, DBL_EPSILON);
			BOOST_CHECK_CLOSE_FRACTION(CRational(-11, 7).ToDouble(), - 11.0 / 7.0, DBL_EPSILON);
		}

	BOOST_AUTO_TEST_SUITE_END()
//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE(Unary_plus_operator)

		BOOST_AUTO_TEST_CASE(gives_the_same_number)
		{
			const CRational rational(3, 5);
			CRational rationalUnaryPlus = + rational; // r2 также равно 3/5
			VerifyRational(rationalUnaryPlus, 3, 5);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Unary_minus_operator)

		BOOST_AUTO_TEST_CASE(gives_the_additive_inverse)
		{
			const CRational rational(3, 5);
			CRational rationalUnaryMinus = - rational; // r3 равно -3/5
			VerifyRational(rationalUnaryMinus, -3, 5);
		}
		//BOOST_AUTO_TEST_CASE(throw_exeption_if_numerator_has_minimum_possible_value)
		//{
		//	const CRational minRational(std::numeric_limits<int>::min());
		//	BOOST_REQUIRE_THROW( (-minRational), std::out_of_range );
		//}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////

static const int MAXINT = std::numeric_limits<int>::max();
static const int MININT = std::numeric_limits<int>::min();

	BOOST_AUTO_TEST_SUITE(Two_arguments_plus_operator)

		BOOST_AUTO_TEST_SUITE(give_correct_value)

			BOOST_AUTO_TEST_CASE(for_simple_rational)
			{
				VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);//	(1/2) + (1/6) = (2/3)
				VerifyRational(CRational(1, 2) + 1, 3, 2);	//	(1/2) + 1     = (3/2)
				VerifyRational(1 + CRational(1, 2), 3, 2);	//	1 + (1/2)     = (3/2)
			}
			BOOST_AUTO_TEST_CASE(for_close_to_limits_values)
			{
				VerifyRational(CRational(1, MAXINT / 6 * 2) + CRational(1, MAXINT / 6 * 3), CRational(5, MAXINT / 6 * 6));
				VerifyRational(CRational(MAXINT - 1, MAXINT) + CRational(1, MAXINT), 1, 1);
				VerifyRational(CRational(MININT, MAXINT) + CRational(1, 1), -1, MAXINT);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE(Two_arguments_minus_operator)

		BOOST_AUTO_TEST_SUITE(give_correct_value)

			BOOST_AUTO_TEST_CASE(for_simple_rational)
			{
				VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);//	(1/2) - (1/6) = (1/3)
				VerifyRational(CRational(1, 2) - 1, -1, 2);	//	(1/2) - 1     = - (1/2)
				VerifyRational(1 - CRational(1, 2), 1, 2);	//	1 - (1/2)     = (1/2)
			}
			BOOST_AUTO_TEST_CASE(for_close_to_limits_values)
			{
				VerifyRational(CRational(1, MAXINT / 6 * 2) - CRational(1, MAXINT / 6 * 3), CRational(1, MAXINT / 6 * 6));
				VerifyRational(CRational(1, 1) - CRational(MAXINT - 1, MAXINT), 1, MAXINT);
				VerifyRational(CRational(-1, MAXINT) - CRational(MININT, MAXINT) , 1, 1);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE(Appropriating_plus_operator)

		BOOST_AUTO_TEST_SUITE(give_correct_value)

			BOOST_AUTO_TEST_CASE(for_simple_rational)
			{
				CRational rational = CRational(1, 2);
				rational += CRational(1, 6);
				VerifyRational(rational, 2, 3);//	(1/2) + (1/6) = (2/3)
				rational += 1;
				VerifyRational(rational, 5, 3);	//	(2/3) + 1     = (5/3)
			}
			BOOST_AUTO_TEST_CASE(for_close_to_limits_values)
			{
				CRational rational = CRational(1, MAXINT / 6 * 2);
				rational += CRational(1, MAXINT / 6 * 3);
				VerifyRational(rational, CRational(5, MAXINT / 6 * 6));
				rational = CRational(-1, MAXINT);
				rational += 1;
				VerifyRational(rational, MAXINT - 1, MAXINT);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE(Appropriating_minus_operator)

		BOOST_AUTO_TEST_SUITE(give_correct_value)

			BOOST_AUTO_TEST_CASE(for_simple_rational)
			{
				CRational rational = CRational(1, 2);
				rational -= CRational(1, 6);
				VerifyRational(rational, 1, 3);
				rational -= 1;
				VerifyRational(rational, -2, 3);
			}
			BOOST_AUTO_TEST_CASE(for_close_to_limits_values)
			{
				CRational rational = CRational(1, MAXINT / 6 * 2);
				rational -= CRational(1, MAXINT / 6 * 3);
				VerifyRational(rational, 1, MAXINT / 6 * 6);
				rational = CRational(MAXINT - 1, MAXINT);
				rational -= 1;
				VerifyRational(rational, -1, MAXINT);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	7 * (2/3)     = (14/3)
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(Two_arguments_product_operator)

	BOOST_AUTO_TEST_SUITE(give_correct_value)

		BOOST_AUTO_TEST_CASE(for_simple_rational)
		{
			VerifyRational(CRational(1, 2) * CRational(1, 3), 1, 6);
			VerifyRational(CRational(1, 3) * -3, -1, 1);
			VerifyRational(7 * CRational(2, 3), 14, 3);
		}
		BOOST_AUTO_TEST_CASE(for_close_to_limits_values)
		{
			int bigOdd = MAXINT / 2;
			int bigEven = bigOdd - 1;
			VerifyRational(CRational(bigEven, 2 * bigOdd) * CRational(bigOdd, 2 * bigEven), 1, 4);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE(Two_arguments_devide_operator)

		BOOST_AUTO_TEST_SUITE(give_correct_value)

			BOOST_AUTO_TEST_CASE(for_simple_rational)
			{
				VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
				VerifyRational(CRational(1, 2) / 5, 1, 10);
				VerifyRational(7 / CRational(2, 3), 21, 2);
			}
			BOOST_AUTO_TEST_CASE(for_close_to_limits_values)
			{
				int bigOdd = MAXINT / 2;
				int bigEven = bigOdd - 1;
				VerifyRational(CRational(bigEven, 2 * bigOdd) / CRational(2 * bigEven, bigOdd), 1, 4);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(throw_if_devide_on_zero)
		{
			BOOST_REQUIRE_THROW(CRational(1, 2) / CRational(0, 1), std::invalid_argument);
			BOOST_REQUIRE_THROW(CRational(1, 2) / 0, std::invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(3/4) /= (3/8) → (2/1)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_SUITE_END()
