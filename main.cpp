#include <iostream>
using namespace std;
#include "matrix.hpp"

matrix multiply(const matrix&, const matrix&);
matrix divideAndConquerMultiply(const matrix&, const matrix&);
matrix strassenMultiply(const matrix&, const matrix&);

int main()
{
    cout << "Program coming soon..." << endl;
    return 0;
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
