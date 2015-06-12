#include "unit_tests/core/core_element/element_manager_test.h"

void ElementManagerTest::SetUp() {
  m_element_manager = new ElementManager();
}

void ElementManagerTest::TearDown() {
  delete m_element_manager;
}

TEST_F(ElementManagerTest, isInitiallyEmpty) {
}
