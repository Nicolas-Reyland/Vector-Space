//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_LINEARMAP_H
#define VECTOR_SPACE_LINEARMAP_H

#include <utility>

#include "Vector.h"
#include "Matrix.h"
#include "VectorSpace.h"

class LinearMap { // Application linéaire
    public:
        // - Attributes -
        Matrix M;
        VectorSpace E;
        VectorSpace F;
        // - Constructors -
        LinearMap() {
            //
        }
        explicit LinearMap(const Matrix& M, const VectorSpace& E, const VectorSpace& F) {
            this->M = M;
            this->E = E;
            this->F = F;
        }
        explicit LinearMap(const Matrix& M, const VectorSpace& E) : LinearMap(M, E, E) {
            //
        }
};

class Endomorphism : LinearMap { // Endomorphisme
    //
};

class Projection : Endomorphism { // Projecteur ou Projection
    //
};

#endif //VECTOR_SPACE_LINEARMAP_H
