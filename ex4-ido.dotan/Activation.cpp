//
// Created by idodo on 10/07/2024.
//
#include "Activation.h"
#include "Matrix.h"
#include "cmath"

Matrix activation::relu(const Matrix& m)
{
    Matrix m1(m);
    for (int i = 0; i < m1.get_rows(); i++)
    {
        for (int j = 0; j < m1.get_cols(); j++)
        {
            if (m1(i,j) < 0)
            {
                m1(i,j) = 0;
            }
        }
    }
    return m1;
}
Matrix activation::softmax(const Matrix& m)
{
    Matrix m1(m);
    float factor = 0;
    for (int i = 0; i < m1.get_rows()*m1.get_cols(); i++)
    {
        m1[i] = std::exp(m1[i]);
        factor += m1[i];
    }
    factor = 1 / factor;
    m1 = m1 * factor;
    return m1;
}