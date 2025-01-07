#include "LUSolver.h"
#include <vector>

void LUSolver::LUDecomposition_Inplace(std::vector<std::vector<float>>& A)
{
	const size_t n = A.size();
	for (size_t k = 0; k < n; ++k)
	{
		for (size_t i = k + 1; i < n; ++i)
		{
			A[i][k] /= A[k][k];
			for (size_t j = k + 1; j < n; ++j) { A[i][j] -= A[i][k] * A[k][j]; }
		}
	}
}

void LUSolver::SolveLowerTriangular(const std::vector<std::vector<float>>& L, const std::vector<float>& b, std::vector<float>& y)
{
	y.resize(b.size());
	const size_t n = L.size();
	for (size_t i = 0; i < n; ++i)
	{
		y[i] = b[i];
		for (size_t j = 0; j < i; ++j) { y[i] -= L[i][j] * y[j]; }
	}
}

void LUSolver::SolveUpperTriangular(const std::vector<std::vector<float>>& U, const std::vector<float>& y, std::vector<float>& x)
{
	x.resize(y.size());
	const size_t n = U.size();
	for (int i = n - 1; i >= 0; --i)
	{
		x[i] = y[i];
		for (size_t j = i + 1; j < n; ++j) { x[i] -= U[i][j] * x[j]; }
		x[i] /= U[i][i];
	}
}

void LUSolver::LUSolve_Inplace(std::vector<std::vector<float>>& A, const std::vector<float>& b, std::vector<float>& x)
{
	LUDecomposition_Inplace(A);
	std::vector<float> y;
	SolveLowerTriangular(A, b, y);
	SolveUpperTriangular(A, y, x);
}
