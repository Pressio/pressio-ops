
#ifndef PRESSIOOPS_MPL_ANY_OF_HPP_
#define PRESSIOOPS_MPL_ANY_OF_HPP_

#include "./variadic/any_of.hpp"

namespace pressio{ namespace mpl{

template< template<class ... T> class F, class ... Args>
struct any_of : variadic::any_of<F, Args...>{};

template< template<class... T> class F, class ... Args>
using any_of_t = typename any_of<F, Args...>::type;

}}
#endif  // PRESSIOOPS_MPL_ANY_OF_HPP_
