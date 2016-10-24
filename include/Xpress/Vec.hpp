//==--- Xpress/Vec.hpp ------------------------------------ -*- C++ -*- ---==//
//            
//                                  Xpress
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  Vec.hpp
/// \brief This file defines a basic Vector class for Xpress.
//
//==-----------------------------------------------------------------------==//

#ifndef XPRESS_VEC_HPP
#define XPRESS_VEC_HPP

#include "VecExpression.hpp"
#include <vector>

namespace Xpress {

/// The Vector class defines a container to store a 
/// dynamic number of a certain type of elements.
/// \tparam DT The type of the vector elements.
template <typename DT>
class Vector : public VecExpression<Vector<DT>> {
 public:
  /// The type of the vector elements.
  using Type = DT;

  Vector(size_t n) : Elements(n) {}

  template <typename Expression>
  Vector(const VecExpression<Expression>& vecExpr) : Elements(vecExpr.size()) {
    // ADD static assert on Expression::Type
    for (size_t i = 0; i < vecExpr.size(); ++i) {
      Elements[i] = vecExpr[i];
    }
  }

  size_t size() const { return Elements.size(); }

  Type operator[](size_t i) const {
    return Elements[i];
  }
  
  Type& operator[](size_t i) {
    return Elements[i];
  }

 private:
  std::vector<Type> Elements; //!< The elements being stored.
};

} // namespace Xpress

#endif // XPRESS_VEC_HPP
