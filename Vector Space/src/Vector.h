//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_VECTOR_H
#define VECTOR_SPACE_VECTOR_H

#include <string>
#include <vector>
#include <cmath>
#include "VectorSpaceException.h"
#include "Eigen/Dense"

namespace VS
{
    class Vector {
    public:
        // - Attributes -
        unsigned int num_elements;
        // - Constructors -
        Vector() {
            this->num_elements = 0;
            this->m_Vect = Eigen::VectorXd(0);
        }
        explicit Vector(unsigned int n) {
            this->num_elements = n;
            this->m_Vect = Eigen::VectorXd(n);
        }
        explicit Vector(unsigned int n, double val) : Vector(n)
        {
            //
        }
        explicit Vector(std::vector<double> values)
            : m_Vect(values.size()), num_elements(values.size())
        {
            for (unsigned int i = 0; i < num_elements; i++)
            {
                m_Vect(i) = values[i];
            }
        }
        explicit Vector(Eigen::VectorXd vector)
            : m_Vect(std::move(vector)), num_elements(vector.size())
        {
            //
        }
        // - Methods -
        static Vector from_std_vector(std::vector<double> vector)
        {
            // cannot use "Vector({1,2})" because of two or more constructors matching the "{1,2}"
            return Vector(vector);
        }
        Eigen::VectorXd getVect() { return Eigen::VectorXd(m_Vect); }
        /*Vector matmult(Matrix M) {
            assert_multi_linear_compat(M);
            return M * (*this);
        }*/
        // Vector to Scalar
        double at_index(unsigned int i)
        {
            return this->m_Vect(i, 0);
        }
        double length() {
            double squared_length = 0;
            for (unsigned int i = 0; i < num_elements; i++)
            {
                double val = at_index(i);
                squared_length += val * val;
            }
            return sqrt(squared_length);
        }
        double distance(Vector other) {
            assert_linear_compat(other);
            double squared_distance = 0;
            for (unsigned int i = 0; i < num_elements; i++) {
                double distance = other[i] - at_index(i);
                squared_distance += distance * distance;
            }
            return sqrt(squared_distance);
        }
        double dot(Vector other) {
            assert_linear_compat(other);
            double dot_result = 0;
            for (unsigned int i = 0; i < num_elements; i++) {
                dot_result += at_index(i) * other[i];
            }
        }
        // Vector to Vector
        Vector normal_vector() {
            return resize(1);
        }
        Vector resize(double new_size) {
            double length_ = this->length();
            double ratio = new_size / length_;
            return (*this) * ratio;
        }
        // - Operator Overloading -
        // + operator
        Vector operator+(Vector other) {
            assert_linear_compat(other);
            return Vector(m_Vect + other.m_Vect);
        }
        Vector operator+=(Vector other) {
            assert_linear_compat(other);
            m_Vect += other.m_Vect;
            return *this;
        }
        // - operator
        Vector operator-(Vector other) {
            assert_linear_compat(other);
            return Vector(m_Vect - other.m_Vect);
        }
        Vector operator-=(Vector other) {
            assert_linear_compat(other);
            m_Vect -= other.m_Vect;
            return *this;
        }
        // * operator
        Vector operator*(Vector other) {
            assert_linear_compat(other);
            return Vector(m_Vect * other.m_Vect);
        }
        Vector operator*=(Vector other) {
            assert_linear_compat(other);
            m_Vect *= other.m_Vect;
            return *this;
        }
        Vector operator*(double x) {
            return Vector(m_Vect * x);
        }
        Vector operator*=(double x) {
            m_Vect *= x;
            return *this;
        }
        // / operator
        Vector operator/(double x) {
            return Vector(m_Vect / x);
        }
        Vector operator/=(double x) {
            m_Vect /= x;
            return *this;
        }
        // [] operator
        double operator[](int index) {
            return at_index(index);
        }
        // - Extra -
        std::string string_repr() {
            std::stringstream ss;
            ss << m_Vect;
            return ss.str();
        }
        void print() {
            std::cout << string_repr() << std::endl;
        }
    private:
        Eigen::VectorXd m_Vect;
        void assert_linear_compat(const Vector& other) const {
            if (num_elements != other.num_elements) {
                throw VS::VectorSpaceException("Vector linear algebra incompatibility: " + std::to_string(num_elements) + " != " + std::to_string(other.num_elements));
            }
        }
        /*void assert_multi_linear_compat(const Matrix& M) const {
            if (num_elements != M.columns) {
                throw VS::VectorSpaceException("Vector multi-linear algebra incompatibility (mat): " + std::to_string(num_elements) + " != " + std::to_string(M.columns));
            }
        }*/
    };
}

#endif //VECTOR_SPACE_VECTOR_H