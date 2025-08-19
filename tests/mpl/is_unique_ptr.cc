
#include <gtest/gtest.h>
#include "pressio/mpl.hpp"

// Compile-time consistency: value vs _v
template <typename T>
constexpr bool value_equals_v = (is_unique_ptr<T>::value == is_unique_ptr_v<T>);

TEST(IsUniquePtrTrait, ConsistencyBetweenValueAndVariableTemplate) {
  static_assert(value_equals_v<int>, "value and _v must agree");
  static_assert(value_equals_v<std::unique_ptr<int>>, "value and _v must agree");
  static_assert(value_equals_v<const std::unique_ptr<int>>, "value and _v must agree");
  static_assert(value_equals_v<volatile std::unique_ptr<int>>, "value and _v must agree");
  static_assert(value_equals_v<const volatile std::unique_ptr<int>>, "value and _v must agree");
  static_assert(value_equals_v<std::unique_ptr<int[]>>, "value and _v must agree");
  static_assert(value_equals_v<const std::unique_ptr<int[]>>, "value and _v must agree");
  SUCCEED();
}

TEST(IsUniquePtrTrait, Positive_ScalarVoidAndArrays) {
  // Scalars
  EXPECT_TRUE((is_unique_ptr_v<std::unique_ptr<int>>));
  EXPECT_TRUE((is_unique_ptr_v<std::unique_ptr<double>>));

  // void
  EXPECT_TRUE((is_unique_ptr_v<std::unique_ptr<void>>));

  // Arrays
  EXPECT_TRUE((is_unique_ptr_v<std::unique_ptr<int[]>>));
  EXPECT_TRUE((is_unique_ptr_v<std::unique_ptr<const int[]>>));
}

TEST(IsUniquePtrTrait, Positive_CvQualifiedUniquePtr) {
  using UPI = std::unique_ptr<int>;
  using UPA = std::unique_ptr<int[]>;

  EXPECT_TRUE((is_unique_ptr_v<const UPI>));
  EXPECT_TRUE((is_unique_ptr_v<volatile UPI>));
  EXPECT_TRUE((is_unique_ptr_v<const volatile UPI>));

  EXPECT_TRUE((is_unique_ptr_v<const UPA>));
  EXPECT_TRUE((is_unique_ptr_v<volatile UPA>));
  EXPECT_TRUE((is_unique_ptr_v<const volatile UPA>));
}

TEST(IsUniquePtrTrait, Negative_NonUniquePtrTypes_StillFalseUnderCv) {
  EXPECT_FALSE((is_unique_ptr_v<int>));
  EXPECT_FALSE((is_unique_ptr_v<const int>));     // forwards to is_unique_ptr<int> -> false
  EXPECT_FALSE((is_unique_ptr_v<volatile int>));
  EXPECT_FALSE((is_unique_ptr_v<int*>));
  EXPECT_FALSE((is_unique_ptr_v<const int*>));
  EXPECT_FALSE((is_unique_ptr_v<std::shared_ptr<int>>));
  EXPECT_FALSE((is_unique_ptr_v<std::weak_ptr<int>>));
}

TEST(IsUniquePtrTrait, Negative_PointersAndReferencesToUniquePtr) {
  using UPI = std::unique_ptr<int>;
  using CUPI = const std::unique_ptr<int>;

  // Pointers to unique_ptr (any cv) are not unique_ptr themselves
  EXPECT_FALSE((is_unique_ptr_v<UPI*>));
  EXPECT_FALSE((is_unique_ptr_v<const UPI*>));
  EXPECT_FALSE((is_unique_ptr_v<CUPI*>));

  // References (any cv) are not unique_ptr themselves
  EXPECT_FALSE((is_unique_ptr_v<UPI&>));
  EXPECT_FALSE((is_unique_ptr_v<const UPI&>));
  EXPECT_FALSE((is_unique_ptr_v<UPI&&>));
  EXPECT_FALSE((is_unique_ptr_v<const UPI&&>));
}

TEST(IsUniquePtrTrait, TypeIdentityChecks) {
  static_assert(std::is_base_of_v<std::true_type,  is_unique_ptr<std::unique_ptr<int>>>, "must be true_type");
  static_assert(std::is_base_of_v<std::true_type,  is_unique_ptr<const std::unique_ptr<int>>>, "cv-forwarding must preserve true");
  static_assert(std::is_base_of_v<std::false_type, is_unique_ptr<double>>,               "must be false_type");
  SUCCEED();
}

// Optional: compile-time examples
static_assert(is_unique_ptr<std::unique_ptr<int>>::value, "unique_ptr<int> should be true");
static_assert(is_unique_ptr<const std::unique_ptr<int>>::value, "const unique_ptr<int> should be true");
static_assert(!is_unique_ptr<const int>::value, "const int should be false");
