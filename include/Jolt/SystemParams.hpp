//==--- Jolt/SystemParams.hpp ----------------------------- -*- C++ -*- ---==//
//            
//                                  Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  SystemParams.hpp
/// \brief This file defines parameters of the system, which are determined
///        during the build process so that they are known at compile time.
///        This file converts the parameters to a nicer to used C++
///        representation.
//
//==-----------------------------------------------------------------------==//

#ifndef JOLT_SYSTEM_PARAMS_HPP
#define JOLT_SYSTEM_PARAMS_HPP

#ifdef SSE
#include "SSEParams.h"
#elif defined(SSE2)
#include "SSE2Params.h"
#elif defined(SSE3)
#include "SSE3Params.h"
#elif defined(SSE41)
#include "SSE41Params.h"
#elif defined(SSE42)
#include "SSE42Params.h"
#elif defined(AVX1)
#include "AVX1Params.h"
#elif defined(AVX2)
#include "AVX2Params.h"
#endif // SSE

namespace Jolt   {
namespace Params {

//==--- CPU Parameters ----------------------------------------------------==//

#ifdef CPU_DETECTED

/// Defines the number of cores in the system.
static constexpr const uint16_t CpuCores = CPU_CORES;

#endif // CPU_DETECTED

//==--- GPU Parameters ----------------------------------------------------==//

#ifdef GPU_DETECTED

#endif // GPU_DETECTED

}} // namespace Jolt::Params

#endif // JOLT_SYSTEM_PARAMS_HPP
