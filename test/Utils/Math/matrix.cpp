#include "matrix.h"
#include <iostream>
#include <utility>


matrix::matrix(const BYTE rows, const BYTE columns)
{
	m_iRows = rows;
	m_iColumns = columns;

	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			m_ppData[i][j] = 0;
}

matrix::matrix(const std::vector<std::vector<float>>& rows)
{
	m_iRows    = rows.size();
	m_iColumns = rows[0].size();


	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			m_ppData[i][j] = rows[i][j];
}

matrix::matrix(const matrix& other)
{
	m_iRows    = other.m_iRows;
	m_iColumns = other.m_iColumns;


	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			At(i, j) = other.At(i, j);
}

matrix::matrix(const BYTE rows, const BYTE columns,float* pRaw)
{
	m_iRows    = rows;
	m_iColumns = columns;


	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (BYTE i = 0; i < m_iRows; ++i)
	{
		memcpy(*(m_ppData+i), pRaw, sizeof(float) * m_iColumns);
		pRaw += m_iColumns;
	}
		
}

BYTE matrix::GetRowsCount() const
{
	return m_iRows;
}

matrix::matrix(const matrix&& other) noexcept
{
	m_iRows    = other.m_iRows;
	m_iColumns = other.m_iColumns;

	m_ppData = Allocate2DArray(m_iRows, m_iColumns);

	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			m_ppData[i][j] = other.m_ppData[i][j];

	m_ppData = nullptr;
}

BYTE matrix::GetColumnsCount() const
{
	return m_iColumns;
}

std::pair<BYTE, BYTE> matrix::GetSize() const
{
	return { GetRowsCount(), GetColumnsCount() };
}

float& matrix::At(const BYTE iRow, const BYTE iCol)
{
	return m_ppData[iRow][iCol];
}

float matrix::GetSumOfAllNumbers()
{
	float sum = 0;

	for (BYTE i = 0; i < GetRowsCount(); i++)
		for (BYTE j = 0; j < GetColumnsCount(); j++)
			sum += At(i, j);

	return  sum;
}

const float& matrix::At(const BYTE iRow, const BYTE iCol) const
{
	return m_ppData[iRow][iCol];
}

matrix matrix::operator*(const matrix& other)
{
	if (m_iColumns != other.m_iRows)
		throw std::runtime_error("n != m");

	auto outMat = matrix(m_iRows, other.m_iColumns);

	for (BYTE d = 0; d < m_iRows; ++d)
		for (BYTE i = 0; i < other.m_iColumns; ++i)
			for (BYTE j = 0; j < other.m_iRows; ++j)
				outMat.At(d, i) += At(d, j) * other.At(j, i);


	return outMat;
}

matrix matrix::operator*(const float f) const
{
	auto out = *this;
	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			out.At(i, j) *= f;

	return out;
}

matrix matrix::operator*(const ImVec3& vec3)
{
	auto vecmatrix = matrix(4, 1);
	vecmatrix.At(0, 0) = vec3.x;
	vecmatrix.At(1, 0) = vec3.y;
	vecmatrix.At(2, 0) = vec3.z;
	vecmatrix.At(3, 0) = 1;

	return *this * vecmatrix;

}

matrix& matrix::operator*=(const float f)
{
	for (BYTE i = 0; i < GetRowsCount(); i++)
		for (BYTE j = 0; j < GetColumnsCount(); j++)
			At(i, j) *= f;

	return *this;
}

void matrix::Clear()
{
	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			At(i, j) = 0.f;
}

void matrix::Print()
{
	for (BYTE i = 0; i < GetRowsCount(); i++)
	{
		for (BYTE j = 0; j < GetColumnsCount(); j++)
		{
			printf("%.f ", At(i, j));
		}
		printf("\n");

	}
}

matrix& matrix::operator=(const matrix& other)
{
	if (this == &other)
		return *this;

	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			At(i, j) = other.At(i, j);

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
	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			At(i, j) /= f;

	return *this;
}

matrix matrix::operator/(const float f) const
{
	auto out = *this;
	for (BYTE i = 0; i < m_iRows; ++i)
		for (BYTE j = 0; j < m_iColumns; ++j)
			out.At(i, j) /= f;

	return out;
}

matrix::~matrix()
{
	// If move constructor moved pointer to another class
	// so we must NOT delete this memory
	if (!m_ppData) return;

	for (BYTE i = 0; i < m_iRows; i++)
		delete[] m_ppData[i];
	delete[] m_ppData;
}

float** matrix::Allocate2DArray(const BYTE i, const BYTE j)
{
	const auto pArr = new float* [i];

	for (BYTE x = 0; x < i; ++x)
		pArr[x] = new float[j];

	return pArr;
}