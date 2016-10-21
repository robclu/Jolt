//==--- Jolt/VecSum.hpp ----------------------------------- -*- C++ -*- ---==//
//            
//                                  Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  VecSum.hpp
/// \brief This file defines an expression to sum two vectors.
//
//==-----------------------------------------------------------------------==//

#ifndef JOLT_VEC_SUM_HPP
#define JOLT_VEC_SUM_HPP

#include "VecExpression.hpp"

namespace Jolt {

/// The VecSum class sums the elements of two vectors.
/// \tparam Exp1 The first vector expression in the sum.
/// \tparam Exp2 The second vector expression in the sum.
template <typename Exp1, typename Exp2>
class VecSum : public VecExpression<VecSum<Exp1, Exp2>> {
 public:
  /// Constructor -- Ensures that the expressions being 
  /// added have the same number of elements.
  /// \param[in] a A reference to the first expression.
  /// \param[in] b A reference to the second expression.
  VecSum(const VecExpression<Exp1>& a, const VecExpression<Exp2>& b)
  :   A(a), B(b) {
    assert(a.size() == b.size() && "Expressions have different size!");
    
    // TODO: Add static assert on Expr1::Type, Expr2::Type and ensure they are
    // convertible!!
  }

  decltype(auto) operator[](size_t i) const {
    return A[i] + B[i];
  };

  size_t size() const { return A.size(); }

 private:
  const Exp1& A;  //!< The first vector expression in the sum.
  const Exp2& B;  //!< The second vector expression in the sum.
};

} // namespace Jolt

// Overload of operator+ for two vector expression.
template <typename Expr1, typename Expr2>
Jolt::VecSum<Expr1, Expr2> operator+(const Jolt::VecExpression<Expr1>& a,
                                     const Jolt::VecExpression<Expr2>& b) {
  return Jolt::VecSum<Expr1, Expr2>(a, b);
};

#endif // JOLT_VEC_SUM_HPP
