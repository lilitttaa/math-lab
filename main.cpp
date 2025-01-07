#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "JacobiSolver.h"
#include "LUSolver.h"
#include "Matrix.h"
#include "Vector.h"

int TestNumber = 0;
int TestPassed = 0;

void EXPECT_EQ(const float actual, const float expect)
{
	TestNumber++;
	try
	{
		if (abs(actual - expect) > 1e-6)
		{
			throw std::runtime_error(
				"Actual value is not equal to expected value \nExpected: " + std::to_string(expect) + "\nActual: " + std::to_string(actual));
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
	TestPassed++;
}

void EXPECT_EQ_MATRIX_FLOAT(const Matrix& actual, const Matrix& expect)
{
	TestNumber++;
	try
	{
		const size_t n = actual.Rows();
		for (size_t i = 0; i < n; ++i)
		{
			const size_t m = actual.Cols();
			for (size_t j = 0; j < m; ++j)
			{
				if (abs(actual(i,j) - expect(i,j)) > 1e-6)
				{
					throw std::runtime_error(
						"Matrix A is not equal to matrix B \nExpected:\n" + expect.ToString() + "Actual:\n" + actual.ToString());
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

void EXPECT_EQ_VECTOR_FLOAT(const Vector& actual, const Vector& expect)
{
	TestNumber++;
	try
	{
		const size_t n = actual.Size();
		for (size_t i = 0; i < n; ++i)
		{
			if (abs(actual(i) - expect(i)) > 1e-6)
			{
				throw std::runtime_error(
					"Vector A is not equal to vector B \nExpected:\n" + expect.ToString() + "Actual:\n" + actual.ToString());
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

void EXPECT_EQ_VECTOR_FLOAT_TOLRANCE(const Vector& actual, const Vector& expect, const float tol)
{
	TestNumber++;
	try
	{
		const size_t n = actual.Size();
		for (size_t i = 0; i < n; ++i)
		{
			if (abs(actual(i) - expect(i)) > tol)
			{
				throw std::runtime_error(
					"Vector A is not equal to vector B \nExpected:\n" + expect.ToString() + "Actual:\n" + actual.ToString());
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

void TestLUSolver()
{
	Matrix OA = std::vector<std::vector<float>>{
		{2, 1, -1},
		{-3, -1, 2},
		{-2, 1, 2}
	};
	const Vector b = {8, -11, -3};
	{
		Matrix A = OA;
		LUSolver solver;

		solver.LUDecomposition_Inplace(A);
		EXPECT_EQ_MATRIX_FLOAT(A, std::vector<std::vector<float>>{
			{2, 1, -1},
			{-1.5, 0.5, 0.5},
			{-1, 4, -1}
		});

		Vector y;
		solver.SolveLowerTriangular(A, b, y);
		EXPECT_EQ_VECTOR_FLOAT(y, {8, 1, 1});

		Vector x;
		solver.SolveUpperTriangular(A, y, x);
		EXPECT_EQ_VECTOR_FLOAT(x, {2, 3, -1});
	}
	{
		Matrix A = OA;
		LUSolver solver;

		Vector x;
		solver.LUSolve_Inplace(A, b, x);
		EXPECT_EQ_VECTOR_FLOAT(x, {2, 3, -1});
	}
}

void TestJacobiSolver()
{
	Matrix A = std::vector<std::vector<float>>{
		{2, -1, 0},
		{-1, 2, -1},
		{0, -1, 2}
	};
	const Vector b = {8, -11, -3};
	{
		JacobiSolver solver;
		Vector x;
		solver.Solve(A, b, x, 1e-6, 100);
		EXPECT_EQ_VECTOR_FLOAT_TOLRANCE(x, {-0.25, -8.5, -5.75}, 1e-6);
	}
}

void TestMatrix()
{
	{
		// Matrix * Matrix
		Matrix A = std::vector<std::vector<float>>{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
		};
		Matrix B = std::vector<std::vector<float>>{
			{9, 8, 7},
			{6, 5, 4},
			{3, 2, 1}
		};
		EXPECT_EQ_MATRIX_FLOAT(A * B, std::vector<std::vector<float>>{
			{30, 24, 18},
			{84, 69, 54},
			{138, 114, 90}
		});
	}
	{
		// Matrix * Vector
		Matrix A = std::vector<std::vector<float>>{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
		};
		Vector b = {1, 2, 3};
		EXPECT_EQ_VECTOR_FLOAT(A * b, {14, 32, 50});
	}
	{
		// Matrix + Matrix
		Matrix A = std::vector<std::vector<float>>{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
		};
		Matrix B = std::vector<std::vector<float>>{
			{9, 8, 7},
			{6, 5, 4},
			{3, 2, 1}
		};
		EXPECT_EQ_MATRIX_FLOAT(A + B, std::vector<std::vector<float>>{
			{10, 10, 10},
			{10, 10, 10},
			{10, 10, 10}
		});
	}
	{
		// Matrix - Matrix
		Matrix A = std::vector<std::vector<float>>{
				{1, 2, 3},
				{4, 5, 6},
				{7, 8, 9}
		};
		Matrix B = std::vector<std::vector<float>>{
				{9, 8, 7},
				{6, 5, 4},
				{3, 2, 1}
		};
		EXPECT_EQ_MATRIX_FLOAT(A - B, std::vector<std::vector<float>>{
			{-8, -6, -4},
			{-2, 0, 2},
			{4, 6, 8}
		});
	}
}

void TestVector()
{
	{
		// Vector + Vector
		Vector a = {1, 2, 3};
		Vector b = {4, 5, 6};
		EXPECT_EQ_VECTOR_FLOAT(a + b, {5, 7, 9});
	}
	{
		// Vector - Vector
		Vector a = {1, 2, 3};
		Vector b = {4, 5, 6};
		EXPECT_EQ_VECTOR_FLOAT(a - b, {-3, -3, -3});
	}
	{
		// Vector * scalar
		Vector a = {1, 2, 3};
		EXPECT_EQ_VECTOR_FLOAT(a * 2, {2, 4, 6});
	}
	{
		// Vector / scalar
		Vector a = {2, 4, 6};
		EXPECT_EQ_VECTOR_FLOAT(a / 2, {1, 2, 3});
	}
	{
		// Vector * Vector
		Vector a = {1, 2, 3};
		Vector b = {4, 5, 6};
		EXPECT_EQ(a * b, 32);
	}
}

int main()
{
	TestVector();
	TestMatrix();
	TestLUSolver();
	TestJacobiSolver();
	std::cout << "Test passed: " << TestPassed << "/" << TestNumber << std::endl;
	return 0;
}
