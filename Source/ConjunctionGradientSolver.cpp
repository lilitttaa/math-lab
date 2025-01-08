#include "ConjunctionGradientSolver.h"

#include "Matrix.h"
#include "Vector.h"

void ConjunctionGradientSolver::Solve(const Matrix& A, const Vector& b, Vector& x, const float tol, const int max_iter)
{
	x = Vector(A.Rows());
	Vector r = b - A * x;
	if(r.Norm() < tol)
		return;
	Vector p = r;
	for(int k=0; k<max_iter; ++k)
	{
		float alpha = r * r / (p * A * p);
		x = x + p * alpha;
		Vector new_r = r -  A * p * alpha;
		if(r.Norm() < tol)
			return;
		float beta = new_r * new_r / (r * r);
		p = new_r + p * beta;
		r = new_r;
	}
}
