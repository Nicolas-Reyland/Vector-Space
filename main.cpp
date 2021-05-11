#include <iostream>
#include "VectorSpace.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Vector u({3, 4});
    Vector v({1, -2});

    Matrix Id = Matrix::identity(2);
    Matrix M({Vector(std::vector<double>({4})), Vector(std::vector<double>({-3}))});
    Id.print();
    M.print();

    Matrix R = Matrix({Vector({1, 1}), Vector({1, 1})});
    R.print();
    R = R.pow(12);
    R.print();

    return 0;
}
