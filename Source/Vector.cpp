#include <iostream>
#include <stdexcept>
#include <string>
#include <Vector.h>

Vector::Vector()
{
	size_ = 0;
	data_.resize(0);
}

Vector::Vector(const size_t size)
{
	size_ = size;
	data_.resize(size);
}

Vector::Vector(std::initializer_list<float> list)
{
	size_ = list.size();
	data_ = list;
}

Vector::Vector(const Vector& other)
{
	size_ = other.size_;
	data_ = other.data_;
}

Vector& Vector::operator=(const Vector& other)
{
	if (this == &other) { return *this; }
	size_ = other.size_;
	data_ = other.data_;
	return *this;
}

Vector::~Vector() {}
float& Vector::operator()(const size_t i) { return data_[i]; }

const float& Vector::operator()(const size_t i) const { return data_[i]; }

Vector Vector::operator+(const Vector& other) const
{
	CheckSameSize(other);
	Vector result(size_);
	for (size_t i = 0; i < size_; ++i) { result(i) = data_[i] + other(i); }
	return result;
}

Vector Vector::operator-(const Vector& other) const
{
	CheckSameSize(other);
	Vector result(size_);
	for (size_t i = 0; i < size_; ++i) { result(i) = data_[i] - other(i); }
	return result;
}

Vector Vector::operator*(const float scalar) const
{
	Vector result(size_);
	for (size_t i = 0; i < size_; ++i) { result(i) = data_[i] * scalar; }
	return result;
}

float Vector::operator*(const Vector& other) const
{
	CheckSameSize(other);
	float result = 0.0f;
	for (size_t i = 0; i < size_; ++i) { result += data_[i] * other(i); }
	return result;
}

Vector Vector::operator/(const float scalar) const { return *this * (1.0f / scalar); }

float Vector::Norm() const
{
	return sqrt(*this * *this);
}

float Vector::SquaredNorm() const
{
	return *this * *this;
}

size_t Vector::Size() const { return size_; }

std::string Vector::ToString() const
{
	std::string str;
	for (size_t i = 0; i < size_; ++i) { str += std::to_string(data_[i]) + " "; }
	return str;
}

void Vector::CheckSameSize(const Vector& other) const
{
	if (size_ != other.size_) { throw std::invalid_argument("Vectors must have the same size."); }
}
