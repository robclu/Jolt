//==--- Jolt/AVX1Params.hpp ------------------------------- -*- C++ -*- ---==//
//            
//                                  Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  AVX1Params.hpp
/// \brief This file defines parameters when the AVX1 instructions are
///        by the CPU.
//
//==-----------------------------------------------------------------------==//

#ifndef JOLT_AVX_1_PARAMS_H
#define JOLT_AVX_1_PARAMS_H

#include <immintrin.h>

namespace Jolt   {
namespace Params {

/// Defines the width of the SIMD lanes, in bytes.
static constexpr const uint16_t SimdWidth = 256;

}} // namespace Jolt::Params

#endif // JOLT_AVX_1_PARAMS_H

