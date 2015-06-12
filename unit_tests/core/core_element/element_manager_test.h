#ifndef UNIT_TESTS_CORE_ELEMENT_MANAGER_TEST_H
#define UNIT_TESTS_CORE_ELEMENT_MANAGER_TEST_H

#include "gtest/gtest.h"
#include "core/element/element_manager.h"

class ElementManagerTest : public ::testing::Test {
public:
  //!< This method does the initialization of the Test Fixture (It's called right after an instance be created - at the begin of each test)
  virtual void SetUp();
  //!< This method does a clean up of the class, it will be called at the end of each test right before the Test Fixture instance be deleted
  virtual void TearDown(); //!<

protected:
  ElementManager *m_element_manager;
};

#endif
