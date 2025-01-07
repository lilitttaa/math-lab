
#include <Matrix.h>
#include <stdexcept>
#include <string>

#include "Vector.h"

Matrix::Matrix(const size_t rows, const size_t cols)
{
	rows_ = rows;
	cols_ = cols;
	data_.resize(rows);
	for (size_t i = 0; i < rows; ++i) { data_[i].resize(cols); }
}

Matrix::Matrix(const std::vector<std::vector<float>>& data)
{
	rows_ = data.size();
	cols_ = data[0].size();
	data_ = data;
}

Matrix::Matrix(const Matrix& other)
{
	rows_ = other.rows_;
	cols_ = other.cols_;
	data_ = other.data_;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this == &other) { return *this; }
	rows_ = other.rows_;
	cols_ = other.cols_;
	data_ = other.data_;
	return *this;
}

Matrix::~Matrix() {}

float& Matrix::operator()(const size_t row, const size_t col) { return data_[row][col]; }

const float& Matrix::operator()(const size_t row, const size_t col) const { return data_[row][col]; }

Matrix Matrix::operator+(const Matrix& other) const
{
	CheckSameDimensions(other);
	Matrix result(rows_, cols_);
	for (size_t i = 0; i < rows_; ++i) { for (size_t j = 0; j < cols_; ++j) { result(i, j) = data_[i][j] + other(i, j); } }
	return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
	CheckSameDimensions(other);
	Matrix result(rows_, cols_);
	for (size_t i = 0; i < rows_; ++i) { for (size_t j = 0; j < cols_; ++j) { result(i, j) = data_[i][j] - other(i, j); } }
	return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	if (cols_ != other.Rows()) { throw std::runtime_error("Matrix dimensions do not match"); }
	Matrix result(rows_, other.Cols());
	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < other.Cols(); ++j)
		{
			result(i, j) = 0;
			for (size_t k = 0; k < cols_; ++k) { result(i, j) += data_[i][k] * other(k, j); }
		}
	}
	return result;
}

Vector Matrix::operator*(const Vector& other) const
{
	if (cols_ != other.Size()) { throw std::runtime_error("Matrix dimensions do not match"); }
	Vector result(rows_);
	for (size_t i = 0; i < rows_; ++i)
	{
		result(i) = 0;
		for (size_t j = 0; j < cols_; ++j) { result(i) += data_[i][j] * other(j); }
	}
	return result;
}

Matrix Matrix::operator*(const float scalar) const
{
	Matrix result(rows_, cols_);
	for (size_t i = 0; i < rows_; ++i) { for (size_t j = 0; j < cols_; ++j) { result(i, j) = data_[i][j] * scalar; } }
	return result;
}

Matrix Matrix::operator/(const float scalar) const { return *this * (1 / scalar); }

Matrix Matrix::Transpose() const
{
	Matrix result(cols_, rows_);
	for (size_t i = 0; i < rows_; ++i) { for (size_t j = 0; j < cols_; ++j) { result(j, i) = data_[i][j]; } }
	return result;
}

size_t Matrix::Rows() const { return rows_; }

size_t Matrix::Cols() const { return cols_; }

std::string Matrix::ToString() const
{
	std::string result;
	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j) { result += std::to_string(data_[i][j]) + " "; }
		result += "\n";
	}
	return result;
}

void Matrix::CheckSameDimensions(const Matrix& other) const
{
	if (rows_ != other.Rows() || cols_ != other.Cols()) { throw std::runtime_error("Matrix dimensions do not match"); }
}
