#pragma once

class Vector;
class Matrix;

// https://games-1312234642.cos.ap-guangzhou.myqcloud.com/course/GAMES001/GAMES001-Lecture13.pdf
class LUSolver
{
public:
	void Solve_Inplace(Matrix& A, const Vector& b, Vector& x);

	void Solve(const Matrix& A, const Vector& b, Vector& x);

	void LUDecomposition_Inplace(Matrix& A);

	void SolveLowerTriangular(const Matrix& L, const Vector& b, Vector& y);

	void SolveUpperTriangular(const Matrix& U, const Vector& y, Vector& x);
};
