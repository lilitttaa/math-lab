#pragma once
#include <string>
#include <vector>

class Vector;

class Matrix
{
public:
	Matrix(const size_t rows, const size_t cols);

	Matrix(const std::vector<std::vector<float>>& data);

	Matrix(const Matrix& other);

	Matrix& operator=(const Matrix& other);

	~Matrix();

	float& operator()(const size_t row, const size_t col);

	const float& operator()(const size_t row, const size_t col) const;

	Matrix operator+(const Matrix& other) const;

	Matrix operator-(const Matrix& other) const;

	Matrix operator*(const Matrix& other) const;

	Vector operator*(const Vector& other) const;

	Matrix operator*(const float scalar) const;

	Matrix operator/(const float scalar) const;

	Matrix Transpose() const;

	size_t Rows() const;

	size_t Cols() const;

	std::string ToString() const;

protected:
	void CheckSameDimensions(const Matrix& other) const;

	std::vector<std::vector<float>> data_;
	size_t rows_;
	size_t cols_;
};
