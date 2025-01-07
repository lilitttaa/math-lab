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
