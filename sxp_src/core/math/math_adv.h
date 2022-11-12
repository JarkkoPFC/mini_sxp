//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_ADV_H
#define PFC_CORE_MATH_ADV_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "math.h"
namespace pfc
{

// new
template<typename T> vec3<T> eigenvalues_sym(const mat33<T>&);  // return eigenvalues of a symmetric 3x3 matrix
template<typename T> vec3<T> eigenvector_pow(const mat33<T>&);  // return maximum eigenvector for 3x3 matrix using power method
//----------------------------------------------------------------------------


//============================================================================
#include "math_adv.inl"
} // namespace pfc
#endif
