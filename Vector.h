//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_VECTOR_H
#define VECTOR_SPACE_VECTOR_H

#include <string>
#include <vector>
#include <cmath>
#include "VectorSpaceException.h"

class Vector {
    public:
        // - Attributes -
        unsigned int num_elements;
        std::vector<double> values;
        // - Constructors -
        Vector() {
            this->num_elements = 0;
            this->values = {};
        }
        explicit Vector(int n) {
            this->num_elements = n;
            this->values = std::vector<double>(n);
        }
        explicit Vector(const std::vector<double>& values) {
            this->values = values;
            this->num_elements = values.size();
        }
        // - Methods -
        // Vector to Scalar
        double length() {
            double squared_length = 0;
            for (double coord : this->values) {
                squared_length += coord;
            }
            return sqrt(squared_length);
        }
        double distance(Vector other) {
            assert_linear_compat(other);
            double squared_distance = 0;
            for (int i = 0; i < num_elements; i++) {
                double distance = other[i] - values[i];
                squared_distance += distance * distance;
            }
            return sqrt(squared_distance);
        }
        double dot(Vector other) {
            assert_linear_compat(other);
            double dot_result = 0;
            for (int i = 0; i < num_elements; i++) {
                dot_result += values[i] * other[i];
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
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = values[i] + other[i];
            }
            return Vector(new_values);
        }
        Vector operator+(double x) {
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = (values[i]) + x;
            }
            return Vector(new_values);
        }
        Vector operator+=(Vector other) {
            assert_linear_compat(other);
            for (int i = 0; i < num_elements; i++) {
                values[i] += other[i];
            }
            return *this;
        }
        Vector operator+=(double x) {
            for (int i = 0; i < num_elements; i++) {
                values[i] += x;
            }
            return *this;
        }
        // - operator
        Vector operator-(Vector other) {
            assert_linear_compat(other);
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = values[i] - other[i];
            }
            return Vector(new_values);
        }
        Vector operator-(double x) {
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = (values[i]) - x;
            }
            return Vector(new_values);
        }
        Vector operator-=(Vector other) {
            assert_linear_compat(other);
            for (int i = 0; i < num_elements; i++) {
                values[i] -= other[i];
            }
            return *this;
        }
        Vector operator-=(double x) {
            for (int i = 0; i < num_elements; i++) {
                values[i] -= x;
            }
            return *this;
        }
        // * operator
        Vector operator*(Vector other) {
            assert_linear_compat(other);
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = values[i] * other[i];
            }
            return Vector(new_values);
        }
        Vector operator*(double x) {
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = (values[i]) * x;
            }
            return Vector(new_values);
        }
        Vector operator*=(Vector other) {
            assert_linear_compat(other);
            for (int i = 0; i < num_elements; i++) {
                values[i] *= other[i];
            }
            return *this;
        }
        Vector operator*=(double x) {
            for (int i = 0; i < num_elements; i++) {
                values[i] *= x;
            }
            return *this;
        }
        // / operator
        Vector operator/(Vector other) {
            assert_linear_compat(other);
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = values[i] / other[i];
            }
            return Vector(new_values);
        }
        Vector operator/(double x) {
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = (values[i]) / x;
            }
            return Vector(new_values);
        }
        Vector operator/=(Vector other) {
            assert_linear_compat(other);
            for (int i = 0; i < num_elements; i++) {
                values[i] /= other[i];
            }
            return *this;
        }
        Vector operator/=(double x) {
            for (int i = 0; i < num_elements; i++) {
                values[i] /= x;
            }
            return *this;
        }
        // % operator
        Vector operator%(Vector other) {
            assert_linear_compat(other);
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = std::fmod(values[i], other[i]);
            }
            return Vector(new_values);
        }
        Vector operator%(double x) {
            std::vector<double> new_values(num_elements);
            for (int i = 0; i < num_elements; i++) {
                new_values[i] = std::fmod(values[i], x);
            }
            return Vector(new_values);
        }
        Vector operator%=(Vector other) {
            assert_linear_compat(other);
            for (int i = 0; i < num_elements; i++) {
                values[i] = std::fmod(values[i], other[i]);
            }
            return *this;
        }
        Vector operator%=(double x) {
            for (int i = 0; i < num_elements; i++) {
                values[i] = std::fmod(values[i], x);
            }
            return *this;
        }
        // [] operator
        double operator[](int index) {
            return values[index];
        }
        // - Extra -
        std::string string_repr() {
            std::string s;
            for (double coord : values) {
                s += std::to_string(coord) + ", ";
            }
            return "[" + (num_elements > 0 ? s.substr(0, s.length() - 2) : "") + "]";
        }
        void print() {
            std::cout << string_repr() << std::endl;
        }
    private:
        void assert_linear_compat(const Vector& other) const {
            if (num_elements != other.num_elements) {
                throw VectorSpaceException("Vector algebra incompatibility");
            }
        }
};

#endif //VECTOR_SPACE_VECTOR_H