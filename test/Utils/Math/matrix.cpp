#include "matrix.h"
#include <iostream>
#include <utility>


matrix::matrix(const size_t rows, const size_t columns)
{
	if (rows == 0 and columns == 0)
		throw std::runtime_error("Matrix cannot be 0x0");

	m_iRows = rows;
	m_iColumns = columns;

	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			m_ppData[i][j] = 0;
}

matrix::matrix(const std::vector<std::vector<float>>& rows)
{
	m_iRows    = rows.size();
	m_iColumns = rows[0].size();


	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			m_ppData[i][j] = rows[i][j];
}

matrix::matrix(const matrix& other)
{
	m_iRows    = other.m_iRows;
	m_iColumns = other.m_iColumns;


	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			at(i, j) = other.at(i, j);
}

matrix::matrix(const size_t rows, const size_t columns,float* pRaw)
{
	m_iRows    = rows;
	m_iColumns = columns;


	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (size_t i = 0; i < m_iRows; ++i)
	{
		memcpy(*(m_ppData+i), pRaw, sizeof(float) * m_iColumns);
		pRaw += m_iColumns;
	}
		
}

size_t matrix::get_rows_count() const
{
	return m_iRows;
}

matrix::matrix(const matrix&& other) noexcept
{
	m_iRows    = other.m_iRows;
	m_iColumns = other.m_iColumns;

	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			m_ppData[i][j] = other.m_ppData[i][j];

	m_ppData = nullptr;
}

size_t matrix::get_columns_count() const
{
	return m_iColumns;
}

std::pair<size_t, size_t> matrix::get_size() const
{
	return { get_rows_count(), get_columns_count() };
}

float& matrix::at(const size_t iRow, const size_t iCol)
{
	return m_ppData[iRow][iCol];
}

float matrix::get_sum()
{
	float sum = 0;

	for (size_t i = 0; i < get_rows_count(); i++)
		for (size_t j = 0; j < get_columns_count(); j++)
			sum += at(i, j);

	return  sum;
}

const float& matrix::at(const size_t iRow, const size_t iCol) const
{
	return m_ppData[iRow][iCol];
}

matrix matrix::operator*(const matrix& other)
{
	if (m_iColumns != other.m_iRows)
		throw std::runtime_error("n != m");

	auto outMat = matrix(m_iRows, other.m_iColumns);

	for (size_t d = 0; d < m_iRows; ++d)
		for (size_t i = 0; i < other.m_iColumns; ++i)
			for (size_t j = 0; j < other.m_iRows; ++j)
				outMat.at(d, i) += at(d, j) * other.at(j, i);


	return outMat;
}

matrix matrix::operator*(const float f) const
{
	auto out = *this;
	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			out.at(i, j) *= f;

	return out;
}

matrix matrix::operator*(const ImVec3& vec3)
{
	auto vecmatrix = matrix(4, 1);
	vecmatrix.at(0, 0) = vec3.x;
	vecmatrix.at(1, 0) = vec3.y;
	vecmatrix.at(2, 0) = vec3.z;
	vecmatrix.at(3, 0) = 1;

	return *this * vecmatrix;

}

matrix& matrix::operator*=(const float f)
{
	for (size_t i = 0; i < get_rows_count(); i++)
		for (size_t j = 0; j < get_columns_count(); j++)
			at(i, j) *= f;

	return *this;
}

void matrix::clear()
{
	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			at(i, j) = 0.f;
}

void matrix::print()
{
	for (size_t i = 0; i < get_rows_count(); i++)
	{
		for (size_t j = 0; j < get_columns_count(); j++)
		{
			printf("%.f ", at(i, j));
		}
		printf("\n");

	}
}

matrix& matrix::operator=(const matrix& other)
{
	if (this == &other)
		return *this;

	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			at(i, j) = other.at(i, j);

	return *this;

}

matrix& matrix::operator=(matrix&& other) noexcept
{
	m_iRows    = other.m_iRows;
	m_iColumns = other.m_iColumns;
	m_ppData   = other.m_ppData;

	return *this;

}

matrix& matrix::operator/=(const float f)
{
	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			at(i, j) /= f;

	return *this;
}

matrix matrix::operator/(const float f) const
{
	auto out = *this;
	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			out.at(i, j) /= f;

	return out;
}

matrix matrix::transpose()
{
	matrix transposed = { m_iColumns, m_iRows };

	for (size_t i = 0; i < m_iRows; ++i)
		for (size_t j = 0; j < m_iColumns; ++j)
			transposed.at(j, i) = at(i, j);

	return transposed;
}

matrix::~matrix()
{
	// If move constructor moved pointer to another class
	// so we must NOT delete this memory
	if (!m_ppData) return;

	for (size_t i = 0; i < m_iRows; i++)
		delete[] m_ppData[i];
	delete[] m_ppData;
}

float** matrix::Allocate2DArray(const size_t i, const size_t j)
{
	const auto pArr = new float* [i];

	for (size_t x = 0; x < i; ++x)
		pArr[x] = new float[j];

	return pArr;
}