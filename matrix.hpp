#pragma once

class matrix
{
private:
    int** mat
    int size;
    void copyMatrix(const matrix& other);
public:
    matrix(int n); // square matrix
    matrix(const matrix& other);
    void operator=(const matrix& other);
    ~matrix();
    int getSize() { return size; }
    int** getMatrix() { return mat; }
};
