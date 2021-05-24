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
        bool m_Null;

        std::vector<Vector> reduce_base(std::vector<Vector> base)
        {
            //
        }
    public:
        // - Attributes -
        unsigned int dimension;
        unsigned int vect_size;
        // - Constructors -
        VectorSpace() {};
        VectorSpace(std::vector<Vector> base)
            : m_Base(base), dimension(base.size())
        {
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
    };
}


#endif //VECTOR_SPACE_VECTORSPACE_H
