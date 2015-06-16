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
  EXPECT_EQ(m_element_manager->countElements(), 0) << "countElement() != 0";
  EXPECT_EQ(m_element_manager->countNodes(), 0) << "countNodes() != 0";
  EXPECT_EQ(m_element_manager->countLinks(), 0) << "countLinks() != 0";
}

TEST_F(ElementManagerTest, addNode) {
  uint32_t elements_count = m_element_manager->countElements();
  uint32_t nodes_count = m_element_manager->countNodes();

  Node &reservoir = m_element_manager->addNode(NodeType::Reservoir, 1.0, 1.0);

  ASSERT_EQ(reservoir.type(), NodeType::Reservoir) << "reservoir.type() != NodeType::Reservoir";
  ASSERT_EQ(reservoir.latitude(), 1.0) << "node's latitude is different from what was specified";
  ASSERT_EQ(reservoir.longitude(), 1.0) << "node's longitude doesn't match with the specified longitude";

  EXPECT_EQ(m_element_manager->countNodes(), ++nodes_count) << "countNodes() is not correct!";
  EXPECT_GT(m_element_manager->countElements(), elements_count++) << "coutElements() is not correct!";

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

TEST_F(ElementManagerTest, getNode) {
  Node &reservoir = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);
  Node &demand = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);
  Node *node = nullptr;
  Node *aux = nullptr;

  ASSERT_TRUE(m_element_manager->getNode(demand.id(), node));
  ASSERT_FALSE(m_element_manager->getNode(reservoir.id() + demand.id() + 1, aux));
  ASSERT_EQ(aux, nullptr);
  EXPECT_EQ(demand.id(), node->id());
  EXPECT_EQ(demand.type(), node->type());
  EXPECT_EQ(demand.name(), node->name());
}

TEST_F(ElementManagerTest, getLink) {
  Node &reservoir = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);
  Node &demand = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);

  Link *link = nullptr;
  Link *aux = nullptr;

  ASSERT_TRUE(m_element_manager->addLink(reservoir.id(), demand.id(), link));
  ASSERT_TRUE(m_element_manager->getLink(link->id(), aux));
  ASSERT_FALSE(m_element_manager->getLink(reservoir.id(), aux));
  EXPECT_EQ(aux, link);
  EXPECT_NE(aux, nullptr);
  EXPECT_EQ(demand.id(), link->nodeDestiny().id());
  EXPECT_EQ(link->nodeOrigin().id(), reservoir.id());
}

TEST_F(ElementManagerTest, getElement) {
  Node &reservoir = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);
  Node &demand = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);
  Link *link = nullptr;
  Element *element = nullptr;

  ASSERT_TRUE(m_element_manager->addLink(reservoir.id(), demand.id(), link));

  ElementID id_high = reservoir.id() + demand.id() + link->id() + 9999;

  ASSERT_TRUE(m_element_manager->getElement(link->id(), element));
  EXPECT_EQ(element->elementType(), ElementType::Link);
  EXPECT_EQ(link->id(), element->id());
  EXPECT_TRUE( dynamic_cast< Link* >( element ) );

  ASSERT_FALSE(m_element_manager->getElement(id_high, element));
  EXPECT_EQ(link, element);

  ASSERT_TRUE(m_element_manager->getElement(reservoir.id(), element));
  EXPECT_EQ(element->elementType(), ElementType::Node);
  EXPECT_EQ(reservoir.id(), element->id());
  EXPECT_TRUE( dynamic_cast< Node* >( element ) );
}

TEST_F(ElementManagerTest, setNodeType) {
  Node &node = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);

  EXPECT_TRUE(m_element_manager->setNodeType(node, NodeType::Basin));
  EXPECT_FALSE(m_element_manager->setNodeType(node, NodeType::Basin));
  EXPECT_EQ(node.type(), NodeType::Basin);

  EXPECT_FALSE(m_element_manager->setNodeType(node.id(), NodeType::Basin));
  EXPECT_TRUE(m_element_manager->setNodeType(node.id(), NodeType::Lake));
  EXPECT_EQ(node.type(), NodeType::Lake);
}

TEST_F(ElementManagerTest, setLinkType) {
  Node &reservoir = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);
  Node &demand = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);
  Link *link = nullptr;

  ASSERT_TRUE(m_element_manager->addLink(reservoir.id(), demand.id(), link, LinkType::Default));
  EXPECT_TRUE(m_element_manager->setLinkType(link->id(), LinkType::Routing));
  EXPECT_EQ(LinkType::Routing, link->type());
  EXPECT_FALSE(m_element_manager->setLinkType(link->id(), LinkType::Routing));
  EXPECT_EQ(LinkType::Routing, link->type());
}

TEST_F(ElementManagerTest, setLinkNodes) {
  Node &node_1 = m_element_manager->addNode(NodeType::Basin, 5.0, 10.0);
  Node &node_2 = m_element_manager->addNode(NodeType::Basin, 5.0, 10.0);
  Node &node_3 = m_element_manager->addNode(NodeType::Basin, 5.0, 10.0);
  Link *link = nullptr;

  ASSERT_TRUE(m_element_manager->addLink(node_1.id(), node_2.id(), link, LinkType::Default)) << "addLink() error!";
  EXPECT_TRUE(node_1.hasOutgoingNode(node_2.id())) << "node_1.hasOutgoingNode(node_2) == false";
  EXPECT_TRUE(node_2.hasIngoingNode(node_1.id())) << "node_2.hasIngoingNode(node_1) == false";

  ASSERT_TRUE(m_element_manager->setLinkNodes(link->id(), node_2.id(), node_3.id())) << "setLinkNodes() error";
  EXPECT_FALSE(node_1.hasOutgoingNode(node_2.id())) << "node_1 outgoing link to node_2 wasn't removed";
  EXPECT_FALSE(node_2.hasIngoingNode(node_1.id())) << "node_2 ingoing link to node_1 wasn't removed";
  EXPECT_TRUE(node_2.hasOutgoingNode(node_3.id())) << "node_2 outgoing link to node_3 was not setted";
  EXPECT_TRUE(node_3.hasIngoingNode(node_2.id())) << "node_3 ingoing link to node_2 was not setted";
  EXPECT_EQ(link->nodeDestiny().id(), node_3.id()) << "the new destiny node of the link was not setted";
  EXPECT_EQ(link->nodeOrigin().id(), node_2.id())<< "the new origin node of the link was not setted";
}

TEST_F(ElementManagerTest, setElementID) {
  Node &node_1 = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);
  Node &node_2 = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);
  Link *link = nullptr;

  ASSERT_TRUE(m_element_manager->addLink(node_1.id(), node_2.id(), link, LinkType::Default)) << "addLink() error!";

  ElementID new_id = node_1.id() + 10 + link->id() + node_2.id();
  ElementID old_id = node_1.id();

  EXPECT_TRUE(node_1.hasOutgoingNode(node_2.id())) << "node_1.hasOutgoingNode(node_2) == false";
  EXPECT_TRUE(node_2.hasIngoingNode(node_1.id())) << "node_2.hasIngoingNode(node_1) == false";

  ASSERT_TRUE(m_element_manager->setElementID(node_1.id(), new_id));
  ASSERT_FALSE(m_element_manager->setElementID(node_1.id(), link->id())) << "The ID of the node was changed by the id of an existing element";
  ASSERT_TRUE(m_element_manager->setElementID(link->id(), old_id));

  ASSERT_EQ(node_1.id(), new_id);
  ASSERT_EQ(link->id(), old_id);
  EXPECT_TRUE(node_2.hasIngoingNode(node_1.id()));
  EXPECT_EQ(link->nodeOrigin().id(), new_id);
}

TEST_F(ElementManagerTest, removeElement) {
  Node &node_1 = m_element_manager->addNode(NodeType::Reservoir, 5.0, 10.0);
  Node &node_2 = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);
  Node &node_3 = m_element_manager->addNode(NodeType::Demand, 5.0, 10.0);
  Link *link = nullptr;

  ASSERT_TRUE(m_element_manager->addLink(node_1.id(), node_2.id(), link, LinkType::Default)) << "addLink() error!";
  ASSERT_TRUE(m_element_manager->addLink(node_2.id(), node_3.id(), link, LinkType::Default)) << "addLink() error!";
  ASSERT_TRUE(m_element_manager->removeElement(node_1.id()));
  EXPECT_EQ(m_element_manager->countElements(), 3);
  EXPECT_EQ(m_element_manager->countLinks(), 1);

  ASSERT_TRUE(m_element_manager->removeElement(link->id()));
  EXPECT_EQ(node_3.ingoingLinks().size(), 0);
  EXPECT_EQ(node_2.outgoingLinks().size(), 0);
  EXPECT_EQ(m_element_manager->countLinks(), 0);
  EXPECT_EQ(m_element_manager->countNodes(), 2);
  EXPECT_EQ(m_element_manager->countElements(), 2);
}
