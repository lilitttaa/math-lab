#pragma once
#include <vector>

class Matrix;

class Vector
{
public:
	Vector();

	Vector(const size_t size);

	Vector(std::initializer_list<float> list);

	Vector(const Vector& other);

	Vector& operator=(const Vector& other);

	~Vector();

	float& operator()(const size_t i);

	const float& operator()(const size_t i) const;

	Vector operator+(const Vector& other) const;

	Vector operator-(const Vector& other) const;

	Vector operator*(const float scalar) const;

	float operator*(const Vector& other) const;

	Vector operator*(const Matrix& other) const;

	Vector operator/(const float scalar) const;

	float Norm() const;

	float SquaredNorm() const;

	size_t Size() const;

	std::string ToString() const;

protected:
	void CheckSameSize(const Vector& other) const;

	std::vector<float> data_;
	size_t size_;
};
