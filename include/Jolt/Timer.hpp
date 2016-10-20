//==--- Jolt/Timer.hpp ------------------------------------ -*- C++ -*- ---==//
//            
//                                  Jolt
//
//                       Copyright (c) 2016 Rob Clucas
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  Timer.hpp
/// \brief This file provides the definition of a timer class, for which
///        timepoints can be added, and the time between various timepoints 
///        can be returned.
//
//==-----------------------------------------------------------------------==//

#ifndef JOLT_TIMER_HPP
#define JOLT_TIMER_HPP

#include <array>
#include <chrono>
#include <iostream>

namespace Jolt {
namespace Time {

/// Converts the resolution to a human readable format.
/// \tparam Resolution The resolution to convert to human readable format.
template <typename Resolution>
constexpr const char* humanReadableResolution();

template <>
constexpr const char* humanReadableResolution<std::chrono::nanoseconds>() {
  return "ns";
}

/// The timer class provides basic, high resolution timing functionality. The
/// resolution is sufficient for the timer to be used to benchmark high
/// performance code. The timer allocates a pool of timepoints, so that adding
/// timepoints does not result in inacurate measurements.
/// \tparam MaxTimepoints The number of timepoints to store.
template <size_t MaxTimepoints>
class Timer {
 public:
  /// The type of timepoint used.
  using TimepointType      = std::chrono::high_resolution_clock::time_point;
  /// The type of timepoint used.
  using TimepointContainer = std::array<TimepointType, MaxTimepoints>;

  /// Constructor -- creates the timepoints.
  Timer();

  /// Sets a new timepoint at the back of the container, and 
  /// returns the index of the timepoint in the container.
  size_t setTimepoint();

  /// Sets a timepoint at a specific index in the container.
  /// \param[in] timepointIndex The index of the timepoint to set.
  void setTimepoint(size_t timepointIndex);

  /// Returns the amount of time which has passed between 
  /// two timepoints, at a resolution of Resolution.
  /// \param[in] startTimepoint The index of the starting point in the duration.
  /// \param[in] endTimepoint   The index of the timepoint which ends the
  ///                           duration.
  /// \tparam    Resolution     The resolution for the timing.
  template <typename Resolution = std::chrono::nanoseconds>
  decltype(auto) duration(size_t startTimepoint, size_t endTimepoint) const;

  /// Prints a duration in a readable format: <duration> <resolution> <\n>
  /// \param[in] startTimepoint The index of the starting point in the duration.
  /// \param[in] endTimepoint   The index of the timepoint which ends the
  ///                           duration.
  /// \tparam    Resolution     The resolution for the timing.
  template <typename Resolution = std::chrono::nanoseconds>
  void printDuration(size_t startTimepoint, size_t endTimepoint) const;
 private:
  /// Timepoints to store.
  TimepointContainer Timepoints; //!< The timepoints to store.
  size_t             NewIndex;   //!< The index of the next timepoint to set.
};

//==--- Implementation ----------------------------------------------------==//

template <size_t MT>
Timer<MT>::Timer() {}

template <size_t MT>
size_t Timer<MT>::setTimepoint() {
  Timepoints[NewIndex] = std::chrono::high_resolution_clock::now();
  return NewIndex++;
}

template <size_t MT>
void Timer<MT>::setTimepoint(size_t timepointIndex) {
  Timepoints[timepointIndex] = std::chrono::high_resolution_clock::now();
}

template <size_t MT> template <typename Res>
decltype(auto) Timer<MT>::duration(size_t startTimepoint, 
                                   size_t endTimepoint  ) const {
  return std::chrono::duration_cast<Res>(Timepoints[endTimepoint] - 
                                         Timepoints[startTimepoint]).count();
}

template <size_t MT> template <typename Res>
void Timer<MT>::printDuration(size_t startTimepoint, 
                              size_t endTimepoint  ) const {
  std::cout << duration<Res>(startTimepoint, endTimepoint) << " " 
            << humanReadableResolution<Res>()              << "\n";
}

}} // namespace Jolt::Time

#endif // JOLT_TIMER_HPP

