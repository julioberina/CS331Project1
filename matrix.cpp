#include "matrix.hpp"

void matrix::copyMatrix(const matrix& other)
{
    if (mat == nullptr)
    {
        size = other.getSize();
        mat = new int[size];

        for (int i = 0; i < size; ++i)
        {
            mat[i] = new int[size];
            for (int j = 0; j < size; ++j)
                mat[i][j] = other.getMatrixValue(i, j);
        }
    }
}

matrix::matrix(int n)
{
    size = n;
    mat = new int[n];
}

matrix::matrix(const matrix& other)
{
    if (this != other)
        copyMatrix(other);
}

void matrix::operator=(const matrix& other)
{
    if (this != other)
        copyMatrix(other);
}

matrix::~matrix()
{
    for (int r = 0; r < n; ++r)
        delete [] mat[r];

    delete [] mat;
}

void matrix::insertRow(int rowIndex, int* row)
{
    mat[rowIndex] = row;
}
