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
    VS::Vector projected = proj(vect);

    std::cout << proj.M.rank() << std::endl;

    return 0;
}
