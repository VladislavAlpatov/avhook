#pragma once
#include <vector>
#include "../Vec3.h"

class matrix
{
public:
    matrix(size_t rows, size_t columns);

    explicit matrix(const std::vector<std::vector<float>>& rows);
    matrix(const matrix& other);
    matrix(size_t rows, size_t columns,float* pRaw);
    matrix(matrix&& other) noexcept;
    size_t get_rows_count() const;
    size_t get_columns_count() const;

    std::pair<size_t, size_t> get_size() const;

    float& at(size_t iRow, size_t iCol);

    float get_sum();
    matrix transpose();
	void set(const float val);
    const float& at(size_t iRow, size_t iCol) const;

    matrix operator*(const matrix& other);
    matrix operator*(float f) const;
    matrix operator*(const ImVec3& vec3);
    matrix& operator*=(float f);


    void clear();
	matrix strip(size_t row, size_t column) const;
	float  minor(const size_t i,const  size_t j) const;
	float alg_complement(const size_t i, const size_t j) const;
	float det() const;
    void print() const;

    matrix& operator=(const matrix& other);
    matrix& operator=(matrix&& other) noexcept;
    matrix& operator/=(float f);

    matrix operator/(float f) const;
    ~matrix();
private:
    static float** Allocate2DArray(size_t i, size_t j);
    size_t m_iRows = 0;
    size_t m_iColumns = 0;
    float** m_ppData = nullptr;
};
