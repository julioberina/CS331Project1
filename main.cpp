#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "matrix.hpp"

ostream& operator<<(ostream&, const matrix&);
matrix operator+(const matrix&, const matrix&);
matrix operator-(const matrix&, const matrix&);
matrix multiply(const matrix&, const matrix&);
matrix divideAndConquerMultiply(const matrix&, const matrix&);
matrix strassenMultiply(const matrix&, const matrix&);

void fillMatrix(matrix& m, bool zero = false)
{
    int* rowVector = nullptr;

    for (int i = 0; i < m.getSize(); ++i)
    {
        rowVector = new int[m.getSize()];

        for (int j = 0; j < m.getSize(); ++j)
            rowVector[j] = (zero ? 0 : rand() % 5 + 1);

        m.insertRow(i, rowVector);
    }
}

int main(int argc, char** argv)
{
    srand(time(0));
    matrix m1(atoi(argv[1]));
    fillMatrix(m1);

    /*
    cout << "Matrix M:" << endl;
    cout << m1 << endl;
    cout << "M * M by ";
    */

    switch (atoi(argv[2]))
    {
        case 1:
            // cout << "classical matrix multiplication:" << endl;
            multiply(m1, m1);
        break;
        case 2:
            // cout << "divide and conquer matrix multiplication:" << endl;
            divideAndConquerMultiply(m1, m1);
        break;
        case 3:
            // cout << "Strassen's algorithm:" << endl;
            strassenMultiply(m1, m1);
        break;
    }

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

matrix operator+(const matrix& m1, const matrix& m2)
{
    int n = m1.getSize();
    matrix result(n);
    fillMatrix(result, true);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            result.setMatrixValue(i, j,
                (m1.getMatrixValue(i, j) + m2.getMatrixValue(i, j)));
        }
    }

    return result;
}

matrix operator-(const matrix& m1, const matrix& m2)
{
    int n = m1.getSize();
    matrix result(n);
    fillMatrix(result, true);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            result.setMatrixValue(i, j,
                (m1.getMatrixValue(i, j) - m2.getMatrixValue(i, j)));
        }
    }

    return result;
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

matrix divideAndConquerMultiply(const matrix& m1, const matrix& m2)
{
    int n = m1.getSize();
    matrix result(n);
    fillMatrix(result, true);

    if (n == 1)
    {
        result.setMatrixValue(0, 0,
            (m1.getMatrixValue(0, 0) * m2.getMatrixValue(0, 0)));
    }
    else
    {
        result.setSubMatrix(1,
            divideAndConquerMultiply(m1.subMatrix(1), m2.subMatrix(1)) +
            divideAndConquerMultiply(m1.subMatrix(2), m2.subMatrix(3)));
        result.setSubMatrix(2,
            divideAndConquerMultiply(m1.subMatrix(1), m2.subMatrix(2)) +
            divideAndConquerMultiply(m1.subMatrix(2), m2.subMatrix(4)));
        result.setSubMatrix(3,
            divideAndConquerMultiply(m1.subMatrix(3), m2.subMatrix(1)) +
            divideAndConquerMultiply(m1.subMatrix(4), m2.subMatrix(3)));
        result.setSubMatrix(4,
            divideAndConquerMultiply(m1.subMatrix(3), m2.subMatrix(2)) +
            divideAndConquerMultiply(m1.subMatrix(4), m2.subMatrix(4)));
    }

    return result;
}

matrix strassenMultiply(const matrix& m1, const matrix& m2)
{
    int n = m1.getSize();
    matrix result(n);
    fillMatrix(result, true);

    if (n == 2)
    {
        int p1, p2, p3, p4, p5, p6, p7;

        p1 = m1.getMatrixValue(0, 0) * (m2.getMatrixValue(0, 1) - m2.getMatrixValue(1, 1));
        p2 = m2.getMatrixValue(1, 1) * (m1.getMatrixValue(0, 0) + m1.getMatrixValue(0, 1));
        p3 = m2.getMatrixValue(0, 0) * (m1.getMatrixValue(1, 0) + m1.getMatrixValue(1, 1));
        p4 = m1.getMatrixValue(1, 1) * (m2.getMatrixValue(1, 0) - m2.getMatrixValue(0, 0));
        p5 = ((m1.getMatrixValue(0, 0) + m1.getMatrixValue(1, 1)) *
              (m2.getMatrixValue(0, 0) + m2.getMatrixValue(1, 1)));
        p6 = ((m1.getMatrixValue(0, 1) - m1.getMatrixValue(1, 1)) *
              (m2.getMatrixValue(1, 0) + m2.getMatrixValue(1, 1)));
        p7 = ((m1.getMatrixValue(0, 0) - m1.getMatrixValue(1, 0)) *
              (m2.getMatrixValue(0, 0) + m2.getMatrixValue(0, 1)));

        result.setMatrixValue(0, 0, p6 + p5 + p4 - p2);
        result.setMatrixValue(0, 1, p1 + p2);
        result.setMatrixValue(1, 0, p3 + p4);
        result.setMatrixValue(1, 1, p1 + p5 - p3 - p7);
    }
    else
    {
        matrix p1(strassenMultiply(m1.subMatrix(1),
                    (m2.subMatrix(2) - m2.subMatrix(4))));
        matrix p2(strassenMultiply((m1.subMatrix(1) + m1.subMatrix(2)),
                    m2.subMatrix(4)));
        matrix p3(strassenMultiply((m1.subMatrix(3) + m1.subMatrix(4)),
                    m2.subMatrix(1)));
        matrix p4(strassenMultiply(m1.subMatrix(4),
                    (m2.subMatrix(3) - m2.subMatrix(1))));
        matrix p5(strassenMultiply((m1.subMatrix(1) + m1.subMatrix(4)),
                    (m2.subMatrix(1) + m2.subMatrix(4))));
        matrix p6(strassenMultiply((m1.subMatrix(2) - m1.subMatrix(4)),
                    (m2.subMatrix(3) + m2.subMatrix(4))));
        matrix p7(strassenMultiply((m1.subMatrix(1) - m1.subMatrix(3)),
                    (m2.subMatrix(1) + m2.subMatrix(2))));

        result.setSubMatrix(1, p6 + p5 + p4 - p2);
        result.setSubMatrix(2, p1 + p2);
        result.setSubMatrix(3, p3 + p4);
        result.setSubMatrix(4, p1 + p5 - p3 - p7);
    }

    return result;
}
