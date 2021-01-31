#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath>

// Helper class to allow for [][] usage
template <class E> class MatrixRow;

template <class T>
class Matrix {
private:
    T** data;
    uint rows, cols;

public:
    Matrix(): data(nullptr), rows(0), cols(0) {}
    Matrix(uint _rows, uint _cols): rows(_rows), cols(_cols) {
        this->data = new T*[_rows];
        for(int r = 0 ; r < _rows; r++)
            this->data[r] = new T[_cols];
    }
    Matrix(int _rows, int _cols): rows(_rows), cols(_cols) {
        this->data = new T*[_rows];
        for(int r = 0 ; r < _rows; r++) {
            this->data[r] = new T[_cols];
            for(int c = 0; c < _cols; c++)
                this->data[r][c] = 0;
        }
    }

    // Copy constructor and assignment
    Matrix(const Matrix<T> &m) {
        rows = m.rows;
        cols = m.cols;

        data = new T*[rows];
        for(int r = 0; r < rows; r++) {
            data[r] = new T[cols];

            for(int c = 0; c < cols; c++)
                data[r][c] = m.data[r][c];
        }
    }
    Matrix& operator=(const Matrix<T> &m) {
        if(this == &m)
            return *this;

        rows = m.rows;
        cols = m.cols;

        data = new T*[rows];
        for(int r = 0; r < rows; r++) {
            data[r] = new T[cols];

            for(int c = 0; c < cols; c++)
                data[r][c] = m.data[r][c];
        }
    }

    // Deconstructor
    ~Matrix() {
        if(empty())
            return;

        for(int r = 0; r < this->rows; r++)
            delete[] this->data[r];
        delete[] this->data;
    }

    // Returns new matrix obj that's transpose of original
    Matrix transpose() {
        Matrix<T> t(cols, rows);

        // Allocate new data table
        for(int r = 0; r < t.rows; r++)
            for(int c = 0; c < t.cols; c++)
                t[r][c] = data[c][r];

        return t;
    }

    // Returns the dot product of x and y
    T dot(Matrix<T>& y) {
        // Ensure valid inputs
        if((this->rows != 1 && this->cols != 1) || this->rows == 0 || this->cols == 0) {
            std::cerr << "X[" << this->rows << ','<< this->cols << "] is not a vector.\n";
            return (T) -1;
        }
        if((y.rows != 1 && y.cols != 1) || y.rows == 0 || y.cols == 0) {
            std::cerr << "Y[" << y.rows << ','<< y.cols << "] is not a vector.\n";
            return (T) -1;
        }

        // If one is a column vector and one is a row, still do calculation
        bool xIsRowVector = this->rows > 1;
        uint xLength = xIsRowVector ? this->rows : this->cols;
        bool yIsRowVector = y.rows > 1;
        uint yLength = yIsRowVector ? y.rows : y.cols;
        if(xLength != yLength) {
            std::cerr << "X and Y do not have same dimensions.\n";
            return -1;
        }

        // Make sure x and y are both row or col vectors
        // Here temp = y or the transpose of y
        Matrix<T> temp = y;
        if(xIsRowVector ^ yIsRowVector)
            temp = y.transpose();

        // Perform calculation
        T sum = 0;
        if(this->rows > 1)
            for(int r = 0; r < rows; r++)
                sum += this->data[r][0] * temp[r][0];
        else
            for(int c = 0; c < cols; c++)
                sum += this->data[0][c] * temp[0][c];

        return sum;
    }

    // Returns cross product of x and y
    Matrix cross(Matrix<T>& y) {
        if(cols != y.rows)
            return Matrix<T>();

        Matrix<T> product(rows, y.cols);
        for(int r = 0; r < rows; r++)
            for(int c = 0; c < y.cols; c++) {
                Matrix<T> xRow = row(r);
                Matrix<T> yCol = y.column(c);

                product[r][c] = xRow.dot(yCol);
            }
        
        return product;
    }

    // Returns matrix object of column c 
    Matrix column(int c) {
        Matrix<T> col( (int) rows, 1);

        for(int r = 0; r < rows; r++)
            col[r][0] = data[r][c];
        
        return col;
    }

    // Returns matrix object of row r 
    Matrix row(int r) {
        Matrix<T> rowMatrix(1, (int) cols);

        for(int c = 0; c < cols; c++)
            rowMatrix[0][c] = data[r][c];
        
        return rowMatrix;
    }

    // Returns true if matrix is empty (have no table)
    bool empty() { return data == nullptr; }

    // data[r][c] = val
    void set(int r, int c, T val) { this->data[r][c] = val; }
    // data[r][c]
    T at(int r, int c) { return this->data[r][c]; }

    // Getters
    uint numRows() { return this->rows; }
    uint numCols() { return this->cols; }

    // Allows the use of the operator [][] to read/write table data
    template <class E>
    class MatrixRow {
    private:
        E* array;
        int length;
    public:
        MatrixRow(E* _array, int my_length): array(_array), length(my_length) {}

        E& operator[](int index) { 
            if(index >= length || index < 0)
                return *(E*) -1;
            return array[index]; 
        }
    };
    MatrixRow<T> operator[](int index) {
        if(index >= rows || index < 0)
            return MatrixRow<T>(new T[0], 0);
        return MatrixRow<T>(data[index], cols);
    }
};




///////////////////////////////
// OPERATORS
///////////////////////////////

// Returns the sum of two matrices (x and y) with same dimensions, else returns empty Matrix
template <class T>
Matrix<T> operator+(Matrix<T>& x, Matrix<T>& y) {
    if(x.numRows() != y.numRows() || x.numCols() != y.numCols())
        return Matrix<T>();
            
    Matrix<T> sum(x.numRows(), x.numCols());

    for(int r = 0; r < x.numRows(); r++)
        for(int c = 0; c < x.numCols(); c++)
            sum[r][c] = x[r][c] + y[r][c];
            
    return sum;
}

// Returns the difference of two matrices (x and y) with same dimensions, else returns empty Matrix
template <class T>
Matrix<T> operator-(Matrix<T>& x, Matrix<T>& y) {
    Matrix<T> negY = -y;
    return x + negY;
 }

// CROSS PRODUCT
template <class T>
Matrix<T> operator*(Matrix<T>& LHS, Matrix<T>& RHS) {
    return LHS.cross(RHS);
}

// NEGATION: Returns the product of matrix m and -1
template <class T>
Matrix<T> operator-(Matrix<T>& m) {
    return (T) -1 * m;
} 

// SCALAR MULTIPLICATION: Returns a Matrix object that is the product of a Matrix and scalar
template <class T>
Matrix<T> operator*(T a, Matrix<T>& m) {
    Matrix<T> product(m.numRows(), m.numCols());

    for(int r = 0; r < m.numRows(); r++)
        for(int c = 0; c < m.numCols(); c++)
            product[r][c] = a * m[r][c];
        
    return product;
} 
template <class T>
Matrix<T> operator*(Matrix<T>& m, T a) {
    Matrix<T> product(m.numRows(), m.numCols());

    for(int r = 0; r < m.numRows(); r++)
        for(int c = 0; c < m.numCols(); c++)
            product[r][c] = a * m[r][c];
        
    return product;
} 

template <class T>
std::ostream& operator<<(std::ostream& os, Matrix<T> &m) {
    // Find longest number length for formatting
    int maxLength = -1, curLength;
    for(int r = 0; r < m.numRows(); r++) {
        for(int c = 0; c < m.numCols(); c++) {
            curLength = std::to_string(m[r][c]).length();

            if(curLength > maxLength)
                maxLength = curLength;
        }
    }

    os << '(';
    for(uint r = 0; r < m.numRows(); r++) {
        os << (r == 0 ? "" : " ");
        for(uint c = 0; c < m.numCols(); c++)
            os << std::setw((int) maxLength) << m[r][c] << (c < m.numCols() - 1 ? ", " : "");
        os << (r == m.numRows()-1 ? "" : "\n");
    }
    os << ")\n";

    return os;
}

std::ostream& operator<<(std::ostream& os, Matrix<char> &m) {
    os << '(';
    for(uint r = 0; r < m.numRows(); r++) {
        os << (r == 0 ? "" : " ");
        for(uint c = 0; c < m.numCols(); c++)
            os << m.at(r, c) << (c < m.numCols() - 1 ? ", " : "");
        os << (r == m.numRows()-1 ? "" : "\n");
    }
    os << ")\n";

    return os;
}

std::ostream& operator<<(std::ostream& os, Matrix<double> &m) {
    // Find longest number length for formatting
    int maxLength = -1, curLength;
    for(int r = 0; r < m.numRows(); r++) {
        for(int c = 0; c < m.numCols(); c++) {
            curLength = std::to_string( (int) m.at(r, c) ).length();

            if(curLength > maxLength)
                maxLength = curLength;
        }
    }

    os << '(';
    for(uint r = 0; r < m.numRows(); r++) {
        os << (r == 0 ? "" : " ");
        for(uint c = 0; c < m.numCols(); c++) {
            // Round to 2 decimal points
            double rounded = round(m.at(r, c) * 100) / 100;

            // force printing of 2 decimal places if number is whole or in tenths
            if(floor(rounded) == rounded) // Is whole number
                os << std::setw(maxLength) << rounded << ".00" << (c < m.numCols() - 1 ? ", " : "");
            else if( floor(rounded*10) == rounded*10 ) // Decimal is multiple of 0.1
                os << std::setw(maxLength + 2) << rounded << '0' << (c < m.numCols() - 1 ? ", " : "");
            else // Both round decimal places are used
                os << std::setw(maxLength + 3) << rounded << (c < m.numCols() - 1 ? ", " : "");
        }
        os << (r == m.numRows()-1 ? "" : "\n");
    }
    os << ")\n";

    return os;
}

#endif
