//
// Created by idodo on 10/07/2024.
//
#include <sstream>
#include "Matrix.h"
#include "iostream"
#include "cmath"
#define MIN_VAL 0.1

Matrix:: Matrix(int rows, int cols):_rows(rows),_cols(cols),_matrix(new
float[rows*cols])
{
    if (rows < 0 || cols < 0)
    {
        throw std::invalid_argument("Not valid dimensions");
    }
    for (int i = 0; i < _rows*_cols;i++)
    {
        _matrix[i] = 0;
    }
}
Matrix:: Matrix(): Matrix(1,1) {}
Matrix:: Matrix(const Matrix& m):_rows(m._rows),_cols(m._cols),_matrix(new
float[m._rows*m._cols])
{
    for (int i = 0; i < _rows*_cols;i++)
    {
        _matrix[i] = m._matrix[i];
    }
}
Matrix:: ~Matrix()
{
    delete[] _matrix;
}
int Matrix:: get_rows() const
{
    return _rows;
}
int Matrix:: get_cols() const
{
    return _cols;
}
Matrix& Matrix:: transpose()
{
    Matrix temp(*this);
    for (int i = 0; i < _rows;i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            _matrix[j * _rows + i] = temp._matrix[i * _cols + j];
        }
    }
    std::swap(_rows,_cols);
    return *this;
}

Matrix& Matrix::vectorize()
{
    _rows = _rows * _cols;
    _cols = 1;
    return *this;
}

void Matrix::plain_print() const
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            std::cout << _matrix[i * _cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::dot(const Matrix& second) const
{
    if (second._cols != _cols || second._rows!=_rows)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    Matrix new_matrix(_rows,_cols);
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            new_matrix._matrix[i * _cols + j] = _matrix[i*_cols +j] * second
                    ._matrix[i*_cols + j];
        }
    }
    return new_matrix;
}
float Matrix::norm() const
{
    float norm = 0;
    for (int i = 0; i < _rows * _cols; i++)
    {
        norm += (_matrix[i]*_matrix[i]);
    }
    return std::sqrt(norm);
}
void Matrix::swap_rows(int row1, int row2)
{
    float* current_row = new float[_cols];
    for (int i = 0; i < _cols; i++)
    {
        current_row[i] = _matrix[row1*_cols+i];
    }
    for (int i = 0; i < _cols; i++)
    {
         _matrix[row1*_cols+i] = _matrix[row2*_cols+i];
         _matrix[row2*_cols+i] = current_row[i];
    }
    delete[] current_row;
}
void Matrix::add_row(int row1, int row2, float mult)
{
    for (int i = 0; i < _cols; i++)
    {
        _matrix[row1*_cols+i] += (_matrix[row2*_cols+i] * mult);
    }
}
void Matrix::mult_row(int row, float mult)
{
    for (int i = 0; i < _cols; i++)
    {
        _matrix[row*_cols+i] *= mult;
    }
}
Matrix Matrix::rref() const
{
    Matrix rref_mat(*this);
    int current_pivot = 0;
    for (int i = 0; i < _cols; i++)
    {
        if (current_pivot >= _cols)
        {
            break;
        }
        int pivot = current_pivot;
        while (pivot < _rows && (rref_mat._matrix[pivot*_cols +i] ==0))
        {
            pivot++;
        }
        if (pivot == _rows)
        {
            continue; // Skip this column, move to the next one
        }
        rref_mat.swap_rows(current_pivot,pivot);
        float normalize_fact = 1 / rref_mat._matrix[current_pivot*_cols+i];
        rref_mat.mult_row(current_pivot,normalize_fact);
        for (int j = 0; j < _rows; j++)
        {
            if (j != current_pivot)
            {
                float lead = rref_mat._matrix[j * _cols + i];
                if (lead != 0)
                {
                    rref_mat.add_row(j, current_pivot, -lead);
                }
            }
        }
        current_pivot++;
    }
    return rref_mat;
}

int Matrix::argmax() const
{
    float max_arg = _matrix[0];
    int max_index = 0;
    for (int i = 1; i < _rows*_cols;i++)
    {
        if (_matrix[i] > max_arg)
        {
            max_arg = _matrix[i];
            max_index = i;
        }
    }
    return max_index;
}
float Matrix::sum() const
{
    float sum = 0;
    for (int i = 0; i < _rows*_cols;i++)
    {
        sum += _matrix[i];
    }
    return sum;
}
Matrix& Matrix::operator+=(const Matrix& m)
{
    if (m._cols != _cols || m._rows != _rows)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    for (int i = 0; i < _cols*_rows; i++)
    {
        _matrix[i] += m._matrix[i];
    }
    return *this;
}
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    if (m1._cols != m2._cols || m1._rows != m2._rows)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    Matrix m(m1);
    m+= m2;
    return m;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m) {
        return *this;
    }
    delete[] _matrix;
    _rows = m._rows;
    _cols = m._cols;
    _matrix = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++) {
        _matrix[i] = m._matrix[i];
    }
    return *this;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    if (m1._cols != m2._rows)
    {
        throw std::invalid_argument("Matrices are not the valid size");
    }
    Matrix m(m1._rows,m2._cols);
    for (int i = 0; i < m1._rows; i++)
    {
        for (int j = 0; j < m2._cols; j++)
        {
            float sum = 0;
            for (int k = 0; k < m1._cols; k++)
            {
                sum += m1._matrix[i * m1._cols + k] *
                        m2._matrix[k * m2._cols + j];
            }
            m._matrix[i * m._cols + j] = sum;
        }
    }
    return m;
}

Matrix operator*(const Matrix& m, float mult)
{
    Matrix m1(m);
    for(int i = 0; i < m1._cols*m1._rows;i++)
    {
        m1._matrix[i]*= mult;
    }
    return m1;
}
Matrix operator*(float mult, const Matrix& m)
{
    Matrix m1 = m * mult;
    return m1;
}
float Matrix::operator()(int row, int col) const
{
    if (row >= _rows || col >= _cols || row < 0 || col < 0)
    {
        throw std::out_of_range("Row and column indexes not valid");
    }
    return _matrix[row*_cols+col];
}
float& Matrix::operator()(int row, int col)
{
    if (row >= _rows || col >= _cols || row < 0 || col < 0)
    {
        throw std::out_of_range("Row and column indexes not valid");
    }
    return _matrix[row*_cols+col];
}
float Matrix::operator[](int loc) const
{
    if (loc >= _rows*_cols || loc < 0)
    {
        throw std::out_of_range("Index not valid");
    }
    return _matrix[loc];
}

float& Matrix::operator[](int loc)
{
    if (loc >= _rows*_cols || loc < 0)
    {
        throw std::out_of_range("Index not valid");
    }
    return _matrix[loc];
}
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i = 0; i < m._rows; ++i) {
        for (int j = 0; j < m._cols; ++j)
        {
            if (m(i, j) > MIN_VAL)
            {
                os << "**";
            } else
            {
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    int total_elements = m.get_rows() * m.get_cols();
    int index = 0;
    float value;
    if (is.read(reinterpret_cast<char*>(&value), sizeof(float)))
    {
        m._matrix[index++] = value;
        while (index < total_elements &&
        is.read(reinterpret_cast<char*>(&value), sizeof(float)))
        {
            m._matrix[index++] = value;
        }
    } else
    {
        is.clear();
        is.seekg(0, std::ios::beg);
        while (index < total_elements && is >> value) {
            if (is.fail())
            {
                throw std::invalid_argument("Not a number.");
            }
            m._matrix[index++] = value;
        }
    }

    if (index < total_elements)
    {
        throw std::invalid_argument("Not enough data to fill the matrix.");
    }

    return is;
}
