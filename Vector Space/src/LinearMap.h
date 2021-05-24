//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_LINEARMAP_H
#define VECTOR_SPACE_LINEARMAP_H

#include <utility>

#include "Vector.h"
#include "Matrix.h"
#include "VectorSpace.h"

namespace VS
{
    class LinearMap { // Application linéaire
    public:
        // - Attributes -
        Matrix M;
        VectorSpace E;
        VectorSpace F;
        int rank; // rang
        // - Constructors -
        LinearMap() {
            //
        }
        explicit LinearMap(Matrix M, VectorSpace E, VectorSpace F) {
            this->M = M; // maybe do it with the ":" thing ?
            this->E = E;
            this->F = F;
        }
        explicit LinearMap(Matrix M, VectorSpace E) : LinearMap(M, E, E) {
            //
        }
        // - Methods -
        int CalculateRank();

        // - Operator Overloading -
        Vector operator()(Vector u) {
            return M * u;
        }

    };

    class Endomorphism : public LinearMap { // Endomorphisme
    public:
        explicit Endomorphism(Matrix M, VectorSpace E) : LinearMap(M, E)
        {
            //
        }
    };

    class Projection : public Endomorphism { // Projecteur ou Projection
    public:
        explicit Projection(Matrix M, VectorSpace E) : Endomorphism(M, E)
        {
            //
        }

        static Projection SpaceToPlaneProjection(VectorSpace space, Vector plane_vector1, Vector plane_vector2, Vector projection_axes)
        {
            // make all the necessary checks
            if (space.dimension != 3) {
                throw VectorSpaceException("Space dimension is not 3 but " + std::to_string(space.dimension));
            }
            if (plane_vector1.num_elements != 3) {
                throw VectorSpaceException("Plane Vector 1 has " + std::to_string(plane_vector1.num_elements) + " values but should have 3");
            }
            if (plane_vector2.num_elements != 3) {
                throw VectorSpaceException("Plane Vector 2 has " + std::to_string(plane_vector2.num_elements) + " values but should have 3");
            }
            if (projection_axes.num_elements != 3) {
                throw VectorSpaceException("Projection Axes has " + std::to_string(projection_axes.num_elements) + " but should have 3");
            }
            // we implicitly define space2, where the axes is defined as (0,0,1) (basically the plane projected on the X-Y axes)
            // calculate the Transfer function matrix 'P' from the space to space2
            Matrix P({ plane_vector1, plane_vector2, projection_axes });
            // A is the projection from any point in space2 so that (x,y,z) -> (x,y,0)
            Matrix A = VS::Matrix::from_std_vector({ {1,0,0},{0,1,0},{0,0,0} });
            // calculate the inverse of P (P^-1)
            Matrix inverse_P = P.inverse();
            // return P * A * P^-1
            Matrix M = P * A;
            M *= inverse_P;
            // return the corresponding linear map
            return Projection(M, space);
        }
    };
}


#endif //VECTOR_SPACE_LINEARMAP_H
