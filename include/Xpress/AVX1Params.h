//==--- Xpress/AVX1Params.hpp ----------------------------- -*- C++ -*- ---==//
//            
//                                  Xpress
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

#ifndef XPRESS_AVX_1_PARAMS_H
#define XPRESS_AVX_1_PARAMS_H

#include <immintrin.h>

namespace Xpress {
namespace Params {
namespace Cpu    {

/// Defines the width of the SIMD lanes, in bits,
/// which we define as the width of the parallel space.
static constexpr const uint16_t ParaWidth = 256;

/// Defines the number of parallel registers per node,
/// which we define as the depth of the memory space.
static constexpr const uint16_t MemDepth = 16;

}} // namespace Xpress::Params::Cpu

#endif // XPRESS_AVX_1_PARAMS_H

