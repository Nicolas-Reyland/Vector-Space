//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_VECTORSPACE_H
#define VECTOR_SPACE_VECTORSPACE_H

#include "Vector.h"
#include "Matrix.h"

namespace VS
{
    class VectorSpace {
    private:
        std::vector<Vector> m_Base;
        Matrix m_M;
        bool m_Null;
    public:
        // - Attributes -
        unsigned int dimension; // e.g. = 2 in a plane, even if the plane is in R^3
        unsigned int vect_size; // e.g. = 3 in a plane, when the plane is in R^3
        // - Constructors -
        VectorSpace() {};
        VectorSpace(std::vector<Vector> base)
        {
            m_Base = base;
            m_M = VS::Matrix(m_Base);
            dimension = m_M.rank();
            if (dimension > 0) {
                vect_size = base[0].num_elements;
                m_Null = false;
            }
            else {
                vect_size = 0;
                m_Null = true;
            }
        }
        // - Methods -
        static VectorSpace R(unsigned int dim)
        {
            // generate R^dim with its canonical base
            if (dim == 0) {
                return VectorSpace(std::vector<Vector>(0));
            }
            std::vector<Vector> base(dim);
            Matrix Id = Matrix::identity(dim);
            for (unsigned int i = 0; i < dim; i++) {
                base[i] = Id[i];
            }
            return VectorSpace(base);
        }
        bool isNull() { return m_Null; }
        unsigned int rank() {
            return m_M.rank();
        }
    };
}


#endif //VECTOR_SPACE_VECTORSPACE_H
