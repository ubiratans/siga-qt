#include "unit_tests/core/core_element/element_manager_test.h"

#include "core/element/node.h"
#include "core/element/link.h"

void ElementManagerTest::SetUp() {
  m_element_manager = new ElementManager();
}

void ElementManagerTest::TearDown() {
  delete m_element_manager;
}

TEST_F(ElementManagerTest, isInitiallyEmpty) {
  EXPECT_EQ(m_element_manager->countElements(), 0);
  EXPECT_EQ(m_element_manager->countNodes(), 0);
  EXPECT_EQ(m_element_manager->countLinks(), 0);
}

TEST_F(ElementManagerTest, addNode) {
  uint32_t elements_count = m_element_manager->countElements();
  uint32_t nodes_count = m_element_manager->countNodes();

  Node &reservoir = m_element_manager->addNode(NodeType::Reservoir, 1.0, 1.0);

  ASSERT_EQ(reservoir.type(), NodeType::Reservoir);
  ASSERT_EQ(reservoir.latitude(), 1.0);
  ASSERT_EQ(reservoir.longitude(), 1.0);

  EXPECT_EQ(m_element_manager->countNodes(), ++nodes_count);
  EXPECT_GT(m_element_manager->countElements(), elements_count++);

  ASSERT_EQ(m_element_manager->addNode(NodeType::Demand, 5.0, 10.0).type(), NodeType::Demand);
  ASSERT_EQ(m_element_manager->addNode(NodeType::Junction, 5.0, 5.0).type(), NodeType::Junction);
  ASSERT_EQ(m_element_manager->addNode(NodeType::Basin, 90.0, 100.0).type(), NodeType::Basin);
  ASSERT_EQ(m_element_manager->addNode(NodeType::Lake, 30.0, 90.0).type(), NodeType::Lake);

  ASSERT_EQ(m_element_manager->countNodes(), nodes_count + 4);
  EXPECT_EQ(m_element_manager->countElements(), elements_count + 4);
}

TEST_F(ElementManagerTest, addLink) {
  uint32_t first_node_id = 0;
  uint32_t second_node_id = 0;

  std::map< ElementID, Node* > &nodes_map = m_element_manager->nodesMap();
  Link *link = nullptr;

  ASSERT_EQ(m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0).type(), NodeType::Reservoir);
  ASSERT_EQ(m_element_manager->addNode(NodeType::Reservoir, 5.0, 5.0).type(), NodeType::Reservoir);

  ASSERT_EQ(nodes_map.size(), 2);

  first_node_id = nodes_map.begin()->first;
  second_node_id = nodes_map.rbegin()->first;

  ASSERT_FALSE(m_element_manager->addLink(1000, 1001, link));
  ASSERT_FALSE(m_element_manager->addLink(first_node_id, first_node_id, link));
  ASSERT_FALSE(m_element_manager->addLink(first_node_id, 1000, link));
  ASSERT_TRUE(m_element_manager->addLink(first_node_id, second_node_id, link));
  ASSERT_FALSE(m_element_manager->addLink(first_node_id, second_node_id, link));

  ASSERT_EQ(m_element_manager->countLinks(), 1);
  ASSERT_EQ(m_element_manager->countElements(), m_element_manager->countNodes() + m_element_manager->countLinks());
}
