#include <iostream>
#include "VectorSpace.h"
#include "LinearMap.h"

int main() {



    VS::VectorSpace R3 = VS::VectorSpace::R(3);
    std::cout << R3.dimension << std::endl;
    VS::Projection proj = VS::Projection::SpaceToPlaneProjection(
        R3,
        VS::Vector::from_std_vector({1,0,1}),
        VS::Vector::from_std_vector({0,1,1}),
        VS::Vector::from_std_vector({-1,-1,1}));

    proj.M.print();

    VS::Vector vect = VS::Vector::from_std_vector({ 0,0,23 });
    vect.print();
    VS::Vector projected = proj(vect);

    proj.M.print();
    proj(VS::Vector::from_std_vector({-1,-1,1})).print();
    projected.print();

    VS::Matrix M = VS::Matrix::from_std_vector({ {10, -20, 30},{20, -30, 50},{10, 10, 0} });
    //VS::LinearMap f(M, R3);
    M.print();
    std::cout << "Rank: " << M.rank(true) << std::endl;

    return 0;
}
