//==--- Jolt/src/BenchmarkTests.cpp ----------------------- -*- C++ -*- ---==//
//            
//                                   Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  BenchmarkTests.cpp
/// \brief This file provides benchmark tests for various array manipulation
///        libraries agains Jolt's implementation.
//
//==-----------------------------------------------------------------------==//

#include <blitz/array.h>
#include <Jolt/Timer.hpp>
#include <Jolt/SystemParams.hpp>

int main(int argc, char** argv) {
  Jolt::Time::Timer<3> timer;
  auto startPoint = timer.setTimepoint();

  blitz::Array<float, 1> A(1000000), B(1000000), C(1000000);
  A = 1.0f; B = 2.0f; C = 0.0f;

  auto createdPoint = timer.setTimepoint();

  C = A + B;

  auto finishedPoint = timer.setTimepoint();

  std::cout << "CPU Cores     : " << Jolt::Params::CpuCores  << "\n";
  std::cout << "SIMD Width    : " << Jolt::Params::SimdWidth << "\n";
  std::cout << "Creation time : "; timer.printDuration(startPoint  , 
                                                       createdPoint);
  std::cout << "Addition time : "; timer.printDuration(createdPoint ,
                                                       finishedPoint);

  return 0;
}
