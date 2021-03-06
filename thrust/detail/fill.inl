/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file fill.inl
 *  \brief Inline file for fill.h.
 */

#include <thrust/fill.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/fill.h>
#include <thrust/system/detail/adl/fill.h>

namespace thrust
{


template<typename System, typename ForwardIterator, typename T>
  void fill(thrust::detail::dispatchable_base<System> &system,
            ForwardIterator first,
            ForwardIterator last,
            const T &value)
{
  using thrust::system::detail::generic::fill;
  return fill(system.derived(), first, last, value);
} // end fill()


template<typename System, typename OutputIterator, typename Size, typename T>
  OutputIterator fill_n(thrust::detail::dispatchable_base<System> &system,
                        OutputIterator first,
                        Size n,
                        const T &value)
{
  using thrust::system::detail::generic::fill_n;
  return fill_n(system.derived(), first, n, value);
} // end fill_n()


namespace detail
{


template<typename System, typename ForwardIterator, typename T>
  void strip_const_fill(const System &system,
                        ForwardIterator first,
                        ForwardIterator last,
                        const T &value)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::fill(non_const_system, first, last, value);
} // end fill()


template<typename System, typename OutputIterator, typename Size, typename T>
  OutputIterator strip_const_fill_n(const System &system,
                                    OutputIterator first,
                                    Size n,
                                    const T &value)
{
  System &non_const_system = const_cast<System&>(system);
  return fill_n(non_const_system, first, n, value);
} // end fill_n()


} // end detail


template<typename ForwardIterator, typename T>
  void fill(ForwardIterator first,
            ForwardIterator last,
            const T &value)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<ForwardIterator>::type System;

  System system;

  thrust::detail::strip_const_fill(select_system(system), first, last, value);
} // end fill()


template<typename OutputIterator, typename Size, typename T>
  OutputIterator fill_n(OutputIterator first,
                        Size n,
                        const T &value)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<OutputIterator>::type System;

  System system;

  return thrust::detail::strip_const_fill_n(select_system(system), first, n, value);
} // end fill()


} // end namespace thrust

