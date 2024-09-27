
#ifndef PRESSIOOPS_MPL_NONE_OF_HPP_
#define PRESSIOOPS_MPL_NONE_OF_HPP_

#include "./variadic/none_of.hpp"

namespace pressio{ namespace mpl{

template< template<class ... T> class F, class ... Args>
struct none_of : variadic::none_of<F, Args...>{};

template< template<class... T> class F, class ... Args>
using none_of_t = typename none_of<F, Args...>::type;

}}
#endif  // PRESSIOOPS_MPL_NONE_OF_HPP_
