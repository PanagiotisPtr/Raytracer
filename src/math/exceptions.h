#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace math {

struct InitialiserListSizeException : public std::exception {
	const char * what () const throw () {
    	return "Initialiser list doesn't have the right size.";
    }
};

} // namespace math

#endif