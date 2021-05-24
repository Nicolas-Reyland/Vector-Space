//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_MATRIX_H
#define VECTOR_SPACE_MATRIX_H

#include "Vector.h"
#include <string>
#include <sstream>
#include <utility>
#include <Eigen/Dense>

const double EPSILON = 1.0e-14;

namespace VS
{
    unsigned int rankOfMatrix(std::vector<std::vector<double>> mat, int rows, int columns);
    void swap(std::vector<std::vector<double>> mat, int row1, int row2, int col);

    class Matrix {
    public:
        // - Attributes -
        unsigned int rows;
        unsigned int columns;
        // - Constructors -
        Matrix() {
            //
        }
        explicit Matrix(const unsigned int a, const unsigned int b) : Matrix(Matrix::init_matrix(a, b)) {
            //
        }
        explicit Matrix(const unsigned int n) : Matrix(n, n) {
            //
        }
        explicit Matrix(const Eigen::MatrixXd m)
            : m_Matrix(std::move(m))
        {
            // cannot do this in ":"
            columns = m_Matrix.cols();
            rows = m_Matrix.rows();
        }
        explicit Matrix(std::vector<Vector> vectors)
        {
            rows = vectors.size();
            if (rows != 0)
            {
                columns = vectors[0].num_elements;
                m_Matrix = Eigen::MatrixXd(columns, rows);
                for (unsigned int i = 0; i < columns; i++) {
                    for (unsigned int j = 0; j < rows; j++) {
                        m_Matrix(i, j) = vectors[j][i];
                    }
                }
            }
            else
            {
                columns = 0;
                m_Matrix = Eigen::MatrixXd(rows, columns);
            }
        }
        explicit Matrix(std::vector<std::vector<double>> matrix_vect)
        {
            *this = from_std_vector(matrix_vect);
        }
        // - Methods -
        static Matrix from_std_vector(std::vector<std::vector<double>> matrix_vect)
        {
            // this methods makes it easier to create matrixes. Cannot do this in a constructor bc there would be risks of uncertainty when adding overloads
            int cols = matrix_vect.size();
            if (cols == 0) return Matrix();
            int rows = matrix_vect[0].size();
            std::vector<Vector> useable(cols);
            for (int i = 0; i < cols; i++) {
                useable[i] = Vector(matrix_vect[i]);
            }
            return Matrix(useable);
        }
        static Matrix init_matrix(unsigned int a, unsigned int b, double value = 0) {
            Eigen::MatrixXd m(a, b);
            for (unsigned int i = 0; i < a; i++) {
                for (unsigned int j = 0; j < b; j++) {
                    m(i, j) = value;
                }
            }
            return Matrix(m);
        }
        static Matrix identity(unsigned int n) {
            return Matrix(Eigen::MatrixXd::Identity(n, n));
        }
        static bool IsZero(double x) { return x < EPSILON; }
        Eigen::MatrixXd getMatrix() { return Eigen::MatrixXd(m_Matrix); }
        Matrix pow(int n) {
            assert_multi_linear_compat(*this);
            if (n < 0) {
                return Matrix(pow_(m_Matrix.inverse(), -n));
            }
            return Matrix(pow_(m_Matrix, n));
        }
        Matrix inverse() {
            return Matrix(m_Matrix.inverse());
        }
        Matrix transpose() {
            return Matrix(m_Matrix.transpose());
        }
        std::vector<std::vector<double>> convert_to_std_vect() {
            std::vector<std::vector<double>> vect_vect(columns);
            for (unsigned int i = 0; i < columns; i++) {
                vect_vect[i] = std::vector<double>(rows);
                for (unsigned int j = 0; j < rows; j++) {
                    vect_vect[i][j] = m_Matrix.col(i)(j);
                }
            }

            return vect_vect;
        }
        unsigned int rank(bool force_calculation = false)
        {
            if (!force_calculation && m_RankCalculated) return m_Rank;
            Matrix M2 = transpose();
            std::vector<std::vector<double>> vect_vect = M2.convert_to_std_vect();
            m_Rank = rankOfMatrix(vect_vect, M2.rows, M2.columns);
            m_RankCalculated = true;
            return m_Rank;
        }

        // - Operator Overloading -
        // + operator (Matrix only)
        Matrix operator+(Matrix other) {
            assert_linear_compat(other);
            return Matrix(m_Matrix + other.m_Matrix);
        }
        Matrix operator+=(Matrix other) {
            assert_linear_compat(other);
            m_Matrix += other.m_Matrix;
            return *this;
        }
        // - operator (Matrix only)
        Matrix operator-(Matrix other) {
            assert_linear_compat(other);
            return Matrix(m_Matrix - other.m_Matrix);
        }
        Matrix operator-=(Matrix other) {
            assert_linear_compat(other);
            m_Matrix -= other.m_Matrix;
            return *this;
        }
        // * operator (all) (real matrix multiplication for Matrix)
        Matrix operator*(Matrix other) {
            assert_multi_linear_compat(other);
            return Matrix(m_Matrix * other.m_Matrix);
        }
        Matrix operator*=(Matrix other) {
            assert_multi_linear_compat(other);
            m_Matrix *= other.m_Matrix;
            return *this;
        }
        Vector operator*(Vector vect) {
            assert_multi_linear_compat(vect);
            return Vector(m_Matrix * vect.getVect());
        }
        Matrix operator*(double x) {
            return Matrix(m_Matrix * x);
        }
        // / operatrion (scalar only)
        Matrix operator/(double x) {
            return Matrix(m_Matrix / x);
        }
        // [] operator
        Vector operator[](unsigned int index) {
            return Vector(m_Matrix.col(index));
        }
        // = operator
        Matrix& operator=(Matrix other) {
            m_Matrix = Eigen::MatrixXd(other.m_Matrix);
            columns = other.columns;
            rows = other.rows;
            m_Rank = other.m_Rank;
            m_RankCalculated = other.m_RankCalculated;
            return *this;
        };

        // - Extras -
        std::string string_repr() {
            std::stringstream ss;
            ss << m_Matrix;
            return ss.str();
        }
        void print() {
            std::cout << string_repr() << std::endl;
        }
    private:
        //
        Eigen::MatrixXd m_Matrix;
        unsigned int m_Rank;
        bool m_RankCalculated = false;
        //
        static Eigen::MatrixXd pow_(const Eigen::MatrixXd& M, const unsigned int n)
        {
            if (n == 0) {
                return Matrix::identity(M.rows()).m_Matrix;
            }
            if (n == 1) {
                return M;
            }
            if (n % 2 == 0) {
                return pow_(M * M, n / 2);
            }
            return pow_(M * M, n / 2) * M;
        }
        void assert_linear_compat(const Matrix& other) const {
            if (rows != other.rows || columns != other.columns) {
                throw VS::VectorSpaceException("Matrix linear algebra incompatibility: " + std::to_string(rows) + " != " + std::to_string(other.rows) + " || " + std::to_string(columns) + " != " + std::to_string(other.columns));
            }
        }
        void assert_multi_linear_compat(const Matrix& other) const {
            if (columns != other.rows) {
                throw VS::VectorSpaceException("Matrix multi-linear algebra incompatibility: " + std::to_string(columns) + " != " + std::to_string(other.rows));
            }
        }
        void assert_multi_linear_compat(const Vector& other) const {
            if (columns != other.num_elements) {
                throw VS::VectorSpaceException("Matrix multi-linear algebra incompatibility (vect): " + std::to_string(columns) + " != " + std::to_string(other.num_elements));
            }
        }
    };
}

#endif //VECTOR_SPACE_MATRIX_H
