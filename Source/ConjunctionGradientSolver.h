#pragma once

class Vector;
class Matrix;

// https://games-1312234642.cos.ap-guangzhou.myqcloud.com/course/GAMES001/GAMES001-Lecture13.pdf
class ConjunctionGradientSolver
{
public:
	void Solve(const Matrix& A, const Vector& b, Vector& x, const float tol = 1e-6, const int max_iter = 1000);
};
