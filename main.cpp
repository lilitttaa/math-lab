#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "LUSolver.h"

int TestNumber = 0;
int TestPassed = 0;

std::string Matrix2String(const std::vector<std::vector<float>>& A)
{
	std::string str;
	const size_t n = A.size();
	for (size_t i = 0; i < n; ++i)
	{
		const size_t m = A[i].size();
		for (size_t j = 0; j < m; ++j) { str += std::to_string(A[i][j]) + " "; }
		str += "\n";
	}
	return str;
}

void EXPECT_EQ_MATRIX_FLOAT(const std::vector<std::vector<float>>& actual, const std::vector<std::vector<float>>& expect)
{
	TestNumber++;
	try
	{
		const size_t n = actual.size();
		for (size_t i = 0; i < n; ++i)
		{
			const size_t m = actual[i].size();
			for (size_t j = 0; j < m; ++j)
			{
				if (abs(actual[i][j] - expect[i][j]) > 1e-6)
				{
					throw std::runtime_error(
						"Matrix A is not equal to matrix B \nExpected:\n" + Matrix2String(expect) + "Actual:\n" + Matrix2String(actual));
				}
			}
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
	TestPassed++;
}

void Test()
{
	std::vector<std::vector<float>> A = {
		{2, 1, -1},
		{-3, -1, 2},
		{-2, 1, 2}
	};
	std::vector<float> b = {8, -11, -3};
	LUSolver solver;
	std::vector<float> x;
	solver.LUDecomposition_Inplace(A);
	EXPECT_EQ_MATRIX_FLOAT(A, {
		{2, 1, -1},
		{-1.5, 0.5, 0.5},
		{-1, 4, -1}
	});
	std::cout << "Test passed: " << TestPassed << "/" << TestNumber << std::endl;
}

int main()
{
	Test();
	return 0;
}
