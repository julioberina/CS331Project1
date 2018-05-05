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

matrix matrix::subMatrix(int sub)
{
    matrix partialMatrix(size/2);
    int row = 0, col = 0; // row and col to start from, default sub 1
    int* rowVector = nullptr; // row vector to be inserted to matrix

    if (sub == 2)
        col = size/2;
    else if (sub == 3)
        row = size/2;
    else if (sub == 4)
    {
        row = size/2;
        col = size/2;
    }

    // fill in values of submatrix based on original matrix
    for (int r = row; r < (row + size/2); ++r)
    {
        rowVector = new int[size/2];

        for (int c = col; c < (col + size/2); ++c)
            rowVector[c] = mat[r][c];

        partialMatrix.insertRow(r, rowVector);
    }

    return partialMatrix;
}

ostream& matrix::operator<<(ostream& outs, const matrix& other)
{
    for (int i = 0; i < other.getSize(); ++i)
    {
        for (int j = 0; j < other.getSize(); ++j)
            outs << other.getMatrixValue(i, j) << " ";

        outs << endl;
    }

    return outs;
}