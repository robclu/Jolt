//==--- Jolt/ExpressionTraits.hpp ------------------------- -*- C++ -*- ---==//
//            
//                                  Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  ExpressionTraits.hpp
/// \brief This file defines an traits for expressions.
//
//==-----------------------------------------------------------------------==//

#ifndef JOLT_VEC_TRAITS_HPP
#define JOLT_VEC_TRAITS_HPP

namespace Jolt   {

//==--- Forward declarations ----------------------------------------------==//

template <typename T>
class Vector;

namespace Traits {

/// The ExpressionTraits struct defines traits of an expression. The traits are
/// always defined by the expressions themselves, and the types decay into more
/// specialized version untill a concrete type is found.
/// \tparam Expresison The expression to get the traits of.
template <typename Expression>
struct ExpressionTraits {
  /// Alias for the data
  using Type = typename ExpressionTraits<Expression>::Type;
};

/// Specialization for an operation on two expressions.
template <template <typename, typename> class OP, typename E1, typename E2>
struct ExpressionTraits<OP<E1, E2>> {
  /// The type always decays to the type of the first expression.
  using Type = typename ExpressionTraits<E1>::Type;
};

/// Specialization for a Vector.
template <typename DT>
struct ExpressionTraits<Vector<DT>> {
  /// Alias for the data type of the vector.
  using Type = DT;
};

}} // namespace Jolt::Traits

#endif // JOLT_EXPRESSION_TRAITS_HPP

