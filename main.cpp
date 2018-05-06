#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "matrix.hpp"

ostream& operator<<(ostream&, const matrix&);
matrix multiply(const matrix&, const matrix&);
matrix divideAndConquerMultiply(const matrix&, const matrix&);
matrix strassenMultiply(const matrix&, const matrix&);

void fillMatrix(matrix& m)
{
    int* rowVector = nullptr;

    for (int i = 0; i < m.getSize(); ++i)
    {
        rowVector = new int[m.getSize()];

        for (int j = 0; j < m.getSize(); ++j)
            rowVector[j] = rand() % 5 + 1;

        m.insertRow(i, rowVector);
    }
}

int main(int argc, char** argv)
{
    srand(time(0));

    matrix m1(4);
    fillMatrix(m1);

    cout << m1 << endl;
    cout << m1 << endl;
    cout << multiply(m1, m1) << endl;
    return 0;
}

ostream& operator<<(ostream& outs, const matrix& other)
{
    for (int i = 0; i < other.getSize(); ++i)
    {
        for (int j = 0; j < other.getSize(); ++j)
            outs << other.getMatrixValue(i, j) << " ";

        outs << endl;
    }

    return outs;
}

matrix multiply(const matrix& m1, const matrix& m2)
{
    int n = m1.getSize();
    int* rowVector = nullptr;

    matrix result(n);

    for (int i = 0; i < n; ++i)
    {
        rowVector = new int[n];

        for (int j = 0; j < n; ++j)
        {
            rowVector[j] = 0;

            for (int k = 0; k < n; ++k)
                rowVector[j] += (m1.getMatrixValue(i, k) * m2.getMatrixValue(k, j));
        }

        result.insertRow(i, rowVector);
    }

    return result;
}
