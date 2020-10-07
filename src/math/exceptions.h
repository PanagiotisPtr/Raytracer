#ifndef MATH_EXCEPTIONS_H
#define MATH_EXCEPTIONS_H

#include <exception>

namespace math {

struct InitialiserListSizeException : public std::exception {
	const char * what () const throw () {
    	return "Initialiser list doesn't have the right size.";
    }
};

struct MatrixNotInvertableException : public std::exception {
	const char * what () const throw () {
    	return "The matrix cannot be inverted. It's determinant is 0.";
    }
};

} // namespace math

#endif