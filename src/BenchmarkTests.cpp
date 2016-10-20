//==--- Pronto/src/BenchmarkTests.cpp --------------------- -*- C++ -*- ---==//
//            
//                                  Pronto
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  BenchmarkTests.cpp
/// \brief This file provides benchmark tests for various array manipulation
///        libraries agains Pronto's implementation.
//
//==-----------------------------------------------------------------------==//

#include <blitz/array.h>
#include <Pronto/Timer.hpp>

int main(int argc, char** argv) {
  Pronto::Time::Timer<3> timer;
  auto startPoint = timer.setTimepoint();

  blitz::Array<float, 1> A(1000000), B(1000000), C(1000000);
  A = 1.0f; B = 2.0f; C = 0.0f;

  auto createdPoint = timer.setTimepoint();

  C = A + B;

  auto finishedPoint = timer.setTimepoint();

  std::cout << "Creation time : "; timer.printDuration(startPoint  , 
                                                       createdPoint);
  std::cout << "Addition time : "; timer.printDuration(createdPoint ,
                                                       finishedPoint);

  return 0;
}
