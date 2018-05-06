#include <iostream>
using namespace std;
#include "matrix.hpp"

ostream& operator<<(ostream&, const matrix&);
matrix multiply(const matrix&, const matrix&);
matrix divideAndConquerMultiply(const matrix&, const matrix&);
matrix strassenMultiply(const matrix&, const matrix&);

int main()
{
    cout << "Program coming soon..." << endl;
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
