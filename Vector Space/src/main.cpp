#include <iostream>
#include "VectorSpace.h"
#include "LinearMap.h"

int main() {

    VS::VectorSpace R3 = VS::VectorSpace::R(3);
    VS::Projection proj = VS::Projection::SpaceToPlaneProjection(
        R3,
        VS::Vector::from_std_vector({1,0,1}),
        VS::Vector::from_std_vector({0,1,1}),
        VS::Vector::from_std_vector({-1,-1,1}));

    VS::Vector vect = VS::Vector::from_std_vector({ 0,0,23 });
    VS::Vector projected = proj(vect);

    proj.M.print();
    proj(VS::Vector::from_std_vector({-1,-1,1})).print();
    projected.print();

    VS::Matrix M = VS::Matrix::from_std_vector({ {10, -20, 30},{20, -30, 50},{10, 10, 0} });
    VS::LinearMap f(M, R3);
    std::cout << "Rank: " << f.CalculateRank() << std::endl;

    return 0;
}
