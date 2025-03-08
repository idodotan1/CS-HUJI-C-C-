// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};
/**
 * The class used for representing a matrix. Each matrix have the attributes
 * that represent the number of rows, number of columns and a 1-D array
 * representing the matrix itself.
 */
class Matrix
{
private:
    int _rows;
    int _cols;
    float* _matrix;
    /*
     * Used for swapping row1 and row2 in the matrix.
     */
    void swap_rows(int row1, int row2);
    /*
     * Used for adding row2 multiplied by mult factor to row1.
     */
    void add_row(int row1, int row2, float mult);
    /*
     * Used for multiplying a row for a factor mult.
     */
    void mult_row(int row, float mult);

public:
    /*
     * Basic constructor of a Matrix with number of row and number of
     * columns, default values of all elements is 0.
     */
    Matrix(int rows, int cols);
    /*
     * Default constructor used to initialize a 1X1 Matrix with value 0.
     */
    Matrix();
    ~Matrix();
    /*
     * Copy constructor
     */
    Matrix(const Matrix& other);

    int get_rows() const;

    int get_cols() const;
    /*
     * The function that transposes a matrix. Returns a reference for
     * chaining.
     */
    Matrix& transpose();
    /*
     * The function to turn a Matrix into a 1D vector.
     */
    Matrix& vectorize();
    /*
     * Used to print the matrix.
     */
    void plain_print() const;
    /*
     * This function returns a new matrix that each element is the
     * multiplying product of the elements in the same place in the original
     * matrix and the input matrix. If matrices are not the same size raises
     * an exception.
     */
    Matrix dot(const Matrix& second) const;
    /*
     * Returns the norm of the matrix.
     */
    float norm() const;
    /*
     * Returns a matrix that is the reduced row echelon form of the original
     * matrix.
     */
    Matrix rref() const;
    /*
     * Returns the index of the largest element.
     */
    int argmax() const;
    /*
     * Returns the sum of all elements in the matrix.
     */
    float sum() const;
    /*
     * Adds each element of the input matrix the original matrix. If
     * matrices are not the same size raises an exception.
     */
    Matrix& operator+=(const Matrix& m);
    /*
    * Assigns all the data from the input matrix to the original.
    */
    Matrix& operator=(const Matrix& m);
    /*
    * A read only operator for accessing an element
    */
    float operator()(int row, int col) const;
    /*
    * A writing operator for accessing an element
    */
    float& operator()(int row, int col);
    /*
    * A read only operator for accessing an element
    */
    float operator[](int loc) const;
    /*
    * A writing operator for accessing an element
    */
    float& operator[](int loc);

    friend Matrix operator*(float mult,const Matrix& m);
    friend Matrix operator*(const Matrix& m, float mult);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);

};
/*
* Adds each element of the first matrix the second matrix. and returns
* a new matrix. If matrices are not the same size raises an exception.
*/
Matrix operator+(const Matrix& m1, const Matrix& m2);
/*
* Multiplies matrices. If matrices are not the valid size raises an exception.
*/
Matrix operator*(const Matrix& m1, const Matrix& m2);
/*
* Multiplies a matrix by a scalar on the right.
*/
Matrix operator*(const Matrix& m, float mult);
/*
* Multiplies a matrix by a scalar on the left.
*/
Matrix operator*(float mult, const Matrix& m);
/*
* Creates an output stream for printing.
*/
std::ostream& operator<<(std::ostream& os, const Matrix& m);
/*
* Creates a matrix from an input stream.
*/
std::istream& operator>>(std::istream& is, Matrix& m);




#endif //MATRIX_H