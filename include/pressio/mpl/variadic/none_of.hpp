// Copyright (C) 2013, Ennio Barbaro.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://sbabbi.github.io/tinympl for documentation.
//
// You are welcome to contact the author at:
//  enniobarbaro@gmail.com
//

#ifndef PRESSIOOPS_MPL_VARIADIC_NONE_OF_HPP_
#define PRESSIOOPS_MPL_VARIADIC_NONE_OF_HPP_

namespace pressio{ namespace mpl{ namespace variadic {

/**
 * \class none_of
 * \brief Determines whether none of the elements in the sequence satisfy the given predicate
 * \param Predicate the predicate, `Predicate<T>::value` must be convertible to bool
 * \param Args... the input sequence
 * \return `none_of<...>::type` is a `std::integral_constant<bool,v>` where `v`
is true iff none of the elements in the sequence satisfy the predicate `Predicate`
 * \sa tinympl::none_of
 */
template< template<class ... T> class Predicate, class ... Args>
struct none_of;

template< template<class ... T> class Predicate, class Head, class ... Args>
struct none_of<Predicate, Head, Args...>
  : std::conditional <
  Predicate<Head>::value,
  std::integral_constant<bool, false>,
  typename none_of<Predicate, Args...>::type
  >::type
{};

template< template<class ... T> class Predicate>
struct none_of<Predicate>
  : std::integral_constant<bool, true>{};

template< template<class... T> class Predicate, class ... Args>
using none_of_t = typename none_of<Predicate, Args...>::type;


}}} // namespace pressio::mpl::variadic

#endif  // PRESSIOOPS_MPL_VARIADIC_NONE_OF_HPP_
