#include "LUSolver.h"

#include "Matrix.h"
#include "Vector.h"

void LUSolver::Solve_Inplace(Matrix& A, const Vector& b, Vector& x)
{
	LUDecomposition_Inplace(A);
	Vector y(b.Size());
	SolveLowerTriangular(A, b, y);
	SolveUpperTriangular(A, y, x);
}

void LUSolver::Solve(const Matrix& A, const Vector& b, Vector& x)
{
	Matrix AA = A;
	Solve_Inplace(AA, b, x);
}

void LUSolver::LUDecomposition_Inplace(Matrix& A)
{
	const size_t n = A.Rows();
	for (size_t k = 0; k < n; ++k)
	{
		for (size_t i = k + 1; i < n; ++i)
		{
			A(i, k) /= A(k, k);
			for (size_t j = k + 1; j < n; ++j)
			{
				A(i, j) -= A(i, k) * A(k, j);
			}
		}
	}
}

void LUSolver::SolveLowerTriangular(const Matrix& L, const Vector& b, Vector& y)
{
	y = Vector(b.Size());
	const size_t n = L.Rows();
	for (size_t i = 0; i < n; ++i)
	{
		y(i) = b(i);
		for (size_t j = 0; j < i; ++j)
		{
			y(i) -= L(i, j) * y(j);
		}
	}
}

void LUSolver::SolveUpperTriangular(const Matrix& U, const Vector& y, Vector& x)
{
	x = Vector(y.Size());
	const size_t n = U.Rows();
	for (int i = n - 1; i >= 0; --i)
	{
		x(i) = y(i);
		for (size_t j = i + 1; j < n; ++j)
		{
			x(i) -= U(i, j) * x(j);
		}
		x(i) /= U(i, i);
	}
}
