#pragma once
#include <vector>
#include "../Vec3.h"

class matrix
{
public:
    matrix(const size_t rows, const size_t columns);

    matrix(const std::vector<std::vector<float>>& rows);
    matrix(const matrix& other);
    matrix(const size_t rows, const size_t columns,float* pRaw);
    size_t get_rows_count() const;
    matrix(const matrix&& other) noexcept;
    size_t get_columns_count() const;

    std::pair<size_t, size_t> get_size() const;

    float& at(const size_t iRow, const size_t iCol);

    float get_sum();
    matrix transpose();
    const float& at(const size_t iRow, const size_t iCol) const;

    matrix operator*(const matrix& other);
    matrix operator*(const float f) const;
    matrix operator*(const ImVec3& vec3);
    matrix& operator*=(const float f);
    void clear();

    void print();
    matrix& operator=(const matrix& other);
    matrix& operator=(matrix&& other) noexcept;
    matrix& operator/=(const float f);

    matrix operator/(const float f) const;
    ~matrix();
private:
    static float** Allocate2DArray(const size_t i, const size_t j);
    size_t m_iRows;
    size_t m_iColumns;
    float** m_ppData;
};
