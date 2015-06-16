#include "gtest/gtest.h"

#include"unit_tests/core/core_element/element_manager_test.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
