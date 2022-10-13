#pragma once
#include <vector>
#include "../Vec3.h"

class matrix
{
public:
    matrix(const BYTE rows, const BYTE columns);

    matrix(const std::vector<std::vector<float>>& rows);
    matrix(const matrix& other);
    matrix(const BYTE rows, const BYTE columns,float* pRaw);
    BYTE GetRowsCount() const;
    matrix(const matrix&& other) noexcept;
    BYTE GetColumnsCount() const;

    std::pair<BYTE, BYTE> GetSize() const;

    float& At(const BYTE iRow, const BYTE iCol);

    float GetSumOfAllNumbers();

    const float& At(const BYTE iRow, const BYTE iCol) const;

    matrix operator*(const matrix& other);
    matrix operator*(const float f) const;
    matrix operator*(const ImVec3& vec3);
    matrix& operator*=(const float f);
    void Clear();

    void Print();
    matrix& operator=(const matrix& other);
    matrix& operator=(matrix&& other) noexcept;
    matrix& operator/=(const float f);

    matrix operator/(const float f) const;
    ~matrix();
private:
    static float** Allocate2DArray(const BYTE i, const BYTE j);
    BYTE m_iRows;
    BYTE m_iColumns;
    float** m_ppData;
};
