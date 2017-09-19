/* en_util_make_unique.h */
// ===================================80 chars=================================|

// Version by Stephan T. Lavavej (also known by STL)
// who originally proposed adding this function to C++14
// source: https://stackoverflow.com/a/17902439
//
// '__cplusplus == 201103L' based on Keiji's comment
// source: https://stackoverflow.com/users/4093728/keiji

#ifndef EN_UTIL_MAKE_UNIQUE_H
#define EN_UTIL_MAKE_UNIQUE_H

#if __cplusplus == 201103L

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

namespace std
{
template<class T> struct _Unique_if {
	typedef unique_ptr <T> _Single_object;
};

template<class T> struct _Unique_if <T []> {
	typedef unique_ptr <T []> _Unknown_bound;
};

template<class T, size_t N> struct _Unique_if <T [ N ]> {
	typedef void _Known_bound;
};

template<class T, class ... Args>
typename _Unique_if <T>::_Single_object
make_unique( Args && ... args ) {
	return unique_ptr <T> ( new T( std::forward <Args> (
				args ) ... ) );
}

template<class T>
typename _Unique_if <T>::_Unknown_bound
make_unique( size_t n ) {
	typedef typename remove_extent <T>::type U;

	return unique_ptr <T> ( new U [ n ] () );
}

template<class T, class ... Args>
typename _Unique_if <T>::_Known_bound
make_unique( Args && ... ) = delete;
}

// __cplusplus == 201103L
#endif

// EN_UTIL_MAKE_UNIQUE_H
#endif

// ===================================80 chars=================================|
/* EOF */

