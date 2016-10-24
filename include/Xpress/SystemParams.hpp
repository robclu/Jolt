//==--- Xpress/SystemParams.hpp --------------------------- -*- C++ -*- ---==//
//            
//                                  Xpress
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

#ifndef XPRESS_SYSTEM_PARAMS_HPP
#define XPRESS_SYSTEM_PARAMS_HPP

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

namespace Xpress {
namespace Params {

//==--- CPU Functionality: ------------------------------------------------==//

namespace Cpu    {

#ifdef CPU_DETECTED

/// Defines the number of nodes in the system, where a node is essentially a
/// separate computational unit. We use the node as an abstraction to allow the 
/// interface to operate on nodes rather than CPU/CPU computational units.
static constexpr const uint16_t Nodes = CPU_CORES;

#endif // CPU_DETECTED

} // namespace Cpu

//==--- GPU Functionality: ------------------------------------------------==//

namespace Gpu {

#ifdef GPU_DETECTED

#endif // GPU_DETECTED

} // namespace Gpu

}} // namespace Xpress::Params

#endif // XPRESS_SYSTEM_PARAMS_HPP
