//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_MATRIX_H
#define VECTOR_SPACE_MATRIX_H

#include "Vector.h"
#include <string>
#include <sstream>

class Matrix {
    public:
        // - Attributes -
        unsigned int rows;
        unsigned int columns;
        std::vector<Vector> values;
        // - Constructors -
        Matrix() {
            //
        }
        explicit Matrix(unsigned int a, unsigned int b) : Matrix(Matrix::init_matrix(a, b)) {
            //
        }
        explicit Matrix(unsigned int n) : Matrix(n, n) {
            //
        }
        explicit Matrix(const std::vector<Vector>& values) { // list of lines
            this->values = values;
            this->rows = values.size();
            this->columns = values[0].num_elements;
        }
        // - Methods -
        static Matrix init_matrix(unsigned int a, unsigned int b, double value = 0) {
            std::vector<Vector> values(a);
            for (int i = 0; i < a; i++) {
                values[i] = Vector(b);
                for (int j = 0; j < b; j++) {
                    values[i].values[j] = value;
                }
            }
            return Matrix(values);
        }
        static Matrix identity(unsigned int n) {
            Matrix Id(n);
            for (int i = 0; i < n; i++) {
                Id[i].values[i] = 1;
                std::cout << "Id: " << Id[i].values[i] << std::endl;
            }
            return Id;
        }
        Matrix pow(int n) {
            assert_multi_linear_compat(*this);
            if (n < 0) {
                return _pow(inverse(), -n);
            }
            return _pow(*this, n);
        }
        Matrix inverse() {
            return *this;
        }

        // - Operator Overloading -
        // + operator
        Matrix operator+(Matrix other) {
            assert_linear_compat(other);
            std::vector<Vector> new_values(rows);
            for (int i = 0; i < rows; i++) {
                new_values[i] = values[i] + other[i];
            }
            return Matrix(new_values);
        }
        Matrix operator+=(Matrix other) {
            assert_linear_compat(other);
            for (int i = 0; i < rows; i++) {
                values[i] += other[i];
            }
            return *this;
        }
        // - operator
        Matrix operator-(Matrix other) {
            assert_linear_compat(other);
            std::vector<Vector> new_values(rows);
            for (int i = 0; i < rows; i++) {
                new_values[i] = values[i] - other[i];
            }
            return Matrix(new_values);
        }
        Matrix operator-=(Matrix other) {
            assert_linear_compat(other);
            for (int i = 0; i < rows; i++) {
                values[i] -= other[i];
            }
            return *this;
        }
        // * operator (real matrix multiplication)
        Matrix operator*(Matrix other) {
            assert_multi_linear_compat(other);
            std::vector<Vector> new_values(rows);
            for (int i = 0; i < rows; i++) {
                new_values[i] = Vector(other.columns);
                for (int j = 0; j < other.columns; j++) {
                    new_values[i].values[j] = 0;
                    for (int k = 0; k < columns; k++) {
                        new_values[i].values[j] += values[i].values[k] * other[k].values[j];
                    }
                }
            }
            return Matrix(new_values);
        }
        Matrix operator*=(Matrix other) {
            Matrix new_(*this * other);
            this->values = new_.values;
            return *this;
        }
        // [] operator
        Vector& operator[](int index) {
            return values[index];
        }
        // - Extras -
        std::string string_repr() {
            std::string s;
            for (Vector u : values) {
                std::ostringstream buffer;
                buffer << " " << u.string_repr() << "\n";
                s += buffer.str();
            }
            return "[" + (rows > 0 ? s.substr(1, s.length() - 2) : "[]") + "]";
        }
        void print() {
            std::cout << string_repr() << std::endl;
        }
    private:
        void assert_linear_compat(const Matrix& other) const {
            if (rows != other.rows || columns != other.columns) {
                throw VectorSpaceException("Matrix linear algebra incompatibility");
            }
        }
        void assert_multi_linear_compat(const Matrix& other) const {
            if (columns != other.rows) {
                throw VectorSpaceException("Matrix multi-linear algebra incompatibility");
            }
        }
        Matrix _pow(Matrix M, unsigned int n) {
            if (n == 0) {
                return Matrix::identity(M.rows);
            }
            if (n == 1) {
                return M;
            }
            if (n % 2 == 0) {
                return _pow(M * M, n / 2);
            }
            return _pow(M * M, n / 2) * M;
        }
};


#endif //VECTOR_SPACE_MATRIX_H
