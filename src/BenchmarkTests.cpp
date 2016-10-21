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
#include <Jolt/Vector.hpp>

int main(int argc, char** argv) {
  Jolt::Time::Timer<6> timer;
  auto startPoint = timer.setTimepoint();

  blitz::Array<float, 1> A(1000000), B(1000000), C(1000000);
  A = 1.0f; B = 2.0f; C = 0.0f;

  auto createdPoint = timer.setTimepoint();

  C = A + B;

  auto finishedPoint = timer.setTimepoint();

  Jolt::Vector<float> D(1000000), E(1000000), F(1000000);

  auto createdPointJ = timer.setTimepoint();

  D = E + F;

  auto finishedPointJ = timer.setTimepoint();

  std::cout << "CPU Nodes       : " << Jolt::Params::Cpu::Nodes     << "\n";
  std::cout << "CPU Par Width   : " << Jolt::Params::Cpu::ParaWidth << "\n";
  std::cout << "CPU Mem Depth   : " << Jolt::Params::Cpu::MemDepth  << "\n";
  std::cout << "Creation time B : "; timer.printDuration(startPoint  , 
                                                         createdPoint);
  std::cout << "Addition time B : "; timer.printDuration(createdPoint ,
                                                         finishedPoint);
  std::cout << "Creation time J : "; timer.printDuration(finishedPoint , 
                                                         createdPointJ);
  std::cout << "Addition time J : "; timer.printDuration(createdPointJ ,
                                                         finishedPointJ);

  return 0;
}
