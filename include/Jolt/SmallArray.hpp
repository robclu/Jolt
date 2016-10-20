//==--- Jolt/SmallArray.hpp ------------------------------- -*- C++ -*- ---==//
//            
//                                  Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  SmallArray.hpp
/// \brief This file defines the interface of a small array class which stores
///        an array of elements of size equal to the vector width of the
///        CPU/GPU.
//
//==-----------------------------------------------------------------------==//

#ifndef JOLT_SMALL_ARRAY_HPP
#define JOLT_SMALL_ARRAY_HPP

#include "SystemParams.hpp"

namespace Jolt {

/// The small array class defines a class to store a specific number of
/// elements which is equal to the width of the vector instruction registers in
/// the CPU/GPU.
/// \tparam Type     The type of the elements in the array.
/// \tparam Elements The number of elements in the array.
template <typename Type, uint16_t Width = Params::SimdWidth>
class SmallArray {


};

} // namespace Jolt

#endif // JOLT_ARRAY_HPP
