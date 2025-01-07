#pragma once
#include <vector>

// https://games-1312234642.cos.ap-guangzhou.myqcloud.com/course/GAMES001/GAMES001-Lecture13.pdf
class LUSolver
{
public:
	void LUSolve_Inplace(std::vector<std::vector<float>>& A, const std::vector<float>& b, std::vector<float>& x);

	void LUDecomposition_Inplace(std::vector<std::vector<float>>& A);

	void SolveLowerTriangular(const std::vector<std::vector<float>>& L, const std::vector<float>& b, std::vector<float>& y);

	void SolveUpperTriangular(const std::vector<std::vector<float>>& U, const std::vector<float>& y, std::vector<float>& x);
};
