#ifndef PRIMITIVES_EXCEPTIONS_H
#define PRIMITIVES_EXCEPTIONS_H

#include <exception>

namespace primitives {

struct NoIntersectionsException : public std::exception {
	const char * what () const throw () {
    	return "There are no intersections in front of the ray.";
    }
};

} // namespace math

#endif