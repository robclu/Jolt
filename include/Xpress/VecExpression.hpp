//==--- Xpress/VecExpression.hpp -------------------------- -*- C++ -*- ---==//
//            
//                                  Xpress
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  VecExpression.hpp
/// \brief This file defines an expression on a vector.
//
//==-----------------------------------------------------------------------==//

#ifndef XPRESS_VEC_EXPRESSION_HPP
#define XPRESS_VEC_EXPRESSION_HPP

#include "ExpressionTraits.hpp"

namespace Xpress {

/// The VecExpression class represents any expression on a vector, where the
/// actual expression implementation is defined by the template. Expressions
/// are evaluated lazily.
/// \tparam Type       The type on which the expression operates.
/// \tparam Expression The expression to abstract.
template <typename Expression>
class VecExpression {
 public:
  using Type = typename Traits::ExpressionTraits<Expression>::Type;

  /// Overload of the access operator to return the 
  /// result of the expression at a certain index.
  /// \param[in] i The index of result of the evaluated expression to get.
  Type operator[](size_t i) const {
    return static_cast<const Expression&>(*this)[i];
  }

  size_t size() const { return static_cast<const Expression&>(*this).size(); }

  /// Define operators to convert this abstract representation 
  /// of an expression into the expression itself.
  operator Expression&() { return static_cast<Expression&>(*this); }
  operator Expression const&() const { 
    return static_cast<const Expression&>(*this);
  }
};

} // namespace Xpress

#endif // XPRESS_VEC_EXPRESSION_HPP
