#include <JacobiSolver.h>

#include "Matrix.h"
#include "Vector.h"

void JacobiSolver::SolveDAndN(const Matrix& A, Matrix& InvD, Matrix& N)
{
	InvD = A;
	N = A;
	for (size_t i = 0; i < A.Rows(); ++i)
	{
		for (size_t j = 0; j < A.Cols(); ++j)
		{
			if (i == j)
			{
				InvD(i, j) = 1.0f / A(i, j);
				N(i, j) = 0.0f;
			}
			else
			{
				InvD(i, j) = 0.0f;
				N(i, j) = A(i, j);
			}
		}
	}
}

void JacobiSolver::Solve(const Matrix& A, const Vector& b, Vector& x, const float tol, const int max_iter)
{
	Matrix InvD(A.Rows(), A.Cols());
	Matrix N(A.Rows(), A.Cols());
	x = Vector(b.Size());

	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		SolveDAndN(A, InvD, N);
		x = InvD * b - InvD * N * x;
		if ((A * x - b).SquaredNorm() < tol * tol) { break; }
	}
}
