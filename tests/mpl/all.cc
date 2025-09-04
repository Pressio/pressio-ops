
#include <gtest/gtest.h>
#include "pressio/mpl.hpp"

TEST(mpl, isDefaultConstructible){
  using namespace pressio;

  class A{
  public:
    A() = default;
  };
  EXPECT_EQ( std::is_default_constructible<A>::value, true);

  class B{
  public:
    B(){}
  };
  EXPECT_EQ( std::is_default_constructible<B>::value, true);

  class C{
  public:
    C() = delete;
  };
  EXPECT_EQ( std::is_default_constructible<C>::value, false);
}

TEST(mpl, all_of)
{
  namespace pmpl = pressio::mpl;
  static_assert
    (pmpl::all_of<std::is_floating_point, double, float>::value, "" );
}

TEST(mpl, any_of)
{
  namespace pmpl = pressio::mpl;
  static_assert
    (pmpl::any_of<std::is_integral, int, float>::value, "" );
}

TEST(mpl, none_of)
{
  namespace pmpl = pressio::mpl;
  static_assert
    (pmpl::none_of<std::is_integral, double, float>::value, "" );
}


TEST(mpl, size)
{
  namespace pmpl = pressio::mpl;
  static_assert(pmpl::size<double, float>::value==2, "" );
  static_assert(pmpl::size<double, float>::value!=3, "" );
  static_assert(pmpl::size<double, float>::value!=0, "" );
}
