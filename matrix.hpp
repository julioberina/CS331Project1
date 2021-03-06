#ifndef MATRIX_H
#define MATRIX_H

class matrix
{
private:
    int** mat;
    int size;
    void copyMatrix(const matrix& other);
public:
    matrix(int n);
    matrix(const matrix& other);
    void operator=(const matrix& other);
    ~matrix();
    int getSize() const { return size; }
    void insertRow(int rowIndex, int* row);
    int getMatrixValue(int r, int c) const { return mat[r][c]; }
    void setMatrixValue(int r, int c, int value) { mat[r][c] = value; }
    matrix subMatrix(int sub) const; // sub-matrix 1, 2, 3, 4
    void setSubMatrix(int sub, const matrix& sm);
};

#endif
