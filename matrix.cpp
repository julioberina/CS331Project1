#include "matrix.hpp"

void matrix::copyMatrix(const matrix& other)
{
    size = other.getSize();
    mat = new int*[size];

    for (int i = 0; i < size; ++i)
    {
        mat[i] = new int[size];
        for (int j = 0; j < size; ++j)
            mat[i][j] = other.getMatrixValue(i, j);
    }
}

matrix::matrix(int n)
{
    size = n;
    mat = new int*[n];
}

matrix::matrix(const matrix& other)
{
    copyMatrix(other);
}

void matrix::operator=(const matrix& other)
{
    copyMatrix(other);
}

matrix::~matrix()
{
    for (int r = 0; r < size; ++r)
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
    int rv_row = 0, rv_col = 0; // row vector rows and columns

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
        rv_col = 0;

        for (int c = col; c < (col + size/2); ++c)
        {
            rowVector[rv_col] = mat[r][c];
            ++rv_col;
        }

        partialMatrix.insertRow(rv_row, rowVector);
        ++rv_row;
    }

    return partialMatrix;
}

void matrix::setSubMatrix(int sub, const matrix& sm)
{
    int row = 0, col = 0; // row and col to start from, default sub 1
    int sm_row = 0, sm_col = 0; // for sm matrix

    if (sub == 2)
        col = size/2;
    else if (sub == 3)
        row = size/2;
    else if (sub == 4)
    {
        row = size/2;
        col = size/2;
    }

    // fill in values of submatrix with sm
    for (int r = row; r < (row + size/2); ++r)
    {
        sm_col = 0;

        for (int c = col; c < (col + size/2); ++c)
        {
            mat[r][c] = sm.getMatrixValue(sm_row, sm_col);
            ++sm_col;
        }

        ++sm_row;
    }
}
