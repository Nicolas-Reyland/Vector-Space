//
// Created by Nicolas on 11/05/2021.
//

#ifndef VECTOR_SPACE_VECTORSPACEEXCEPTION_H
#define VECTOR_SPACE_VECTORSPACEEXCEPTION_H

#include <iostream>
#include <string>
#include <exception>

class VectorSpaceException : public std::exception {
public:
    std::string message;
    explicit VectorSpaceException(const std::string& message) {
        this->message = message;
        std::cout << "VectorSpaceException: " << message << std::endl;
    }
};


#endif //VECTOR_SPACE_VECTORSPACEEXCEPTION_H
