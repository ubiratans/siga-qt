#include "core/element/node.h"

#include "core/element/node_properties_set.h"

Node::Node(ElementID id, std::string name, NodeType type, double latitude, double longitude) :
Element(id, name, 0.0, ElementType::Node), m_latitude(latitude), m_longitude(longitude), m_area(0.0), m_type(type)
{
  m_properties_set = new NodePropertiesSet(*this);
}

Node::Node(Node &node)
  : Element(node.id(), node.name(), node.volume(), ElementType::Node),
    m_latitude(node.latitude()), m_longitude(node.longitude()), m_area(node.area()),
    m_ingoing_links_map(node.ingoingLinks()), m_outgoing_links_map(node.outgoingLinks()), m_type(node.type())
{
  m_properties_set = new NodePropertiesSet(*this);
}

Node::~Node() {
  delete m_properties_set;
}

bool Node::setType(NodeType new_type) {
  if (m_type != new_type) {
    m_type = new_type;

    return true;
  }

  return false;
}

/*!
  * id -> Node id to be linked with
  * link -> the link between the two nodes
!*/
bool Node::insertIngoingLink(ElementID id, Link &link) {
  bool ret = hasIngoingNode(id);

  if (ret) {
    m_ingoing_links_map[id] = &link;
  }

  return ret;
}

/*!
* id -> Node id to be linked with
* link -> the link between the two nodes
!*/
bool Node::insertOutgoingLink(ElementID id, Link &link) {
  bool ret = !hasOutgoingNode(id);

  if (ret) {
    m_outgoing_links_map[id] = &link;
  }

  return ret;
}

void Node::stealLinks(Node &node) {
  for (auto it : node.ingoingLinks()) {
    if (it.first != m_id && !hasIngoingNode(it.first) && !hasOutgoingNode(it.first)) {
      node.removeIngoingLink(it.first);
      insertIngoingLink(it.first, *it.second);
    }
  }

  for (auto it : node.outgoingLinks()) {
    if (it.first != m_id && !hasIngoingNode(it.first) && !hasOutgoingNode(it.first)) {
      node.removeOutgoingLink(it.first);
      insertOutgoingLink(it.first, *it.second);
    }
  }
}

bool Node::removeIngoingLink(ElementID id) {
  auto it = m_ingoing_links_map.find(id);
  bool ret = (it != m_ingoing_links_map.end());

  if (ret) {
    m_ingoing_links_map.erase(it);
  }

  return ret;
}

bool Node::removeOutgoingLink(ElementID id) {
  auto it = m_outgoing_links_map.find(id);
  bool ret = (it != m_outgoing_links_map.end());

  if (ret) {
    m_outgoing_links_map.erase(it);
  }

  return ret;
}

std::map< ElementID, Link* >& Node::ingoingLinks() {
  return m_ingoing_links_map;
}

std::map<ElementID, Link* >& Node::outgoingLinks() {
  return m_outgoing_links_map;
}

NodeType Node::type() {
  return m_type;
}


double Node::longitude() {
  return m_longitude;
}

void Node::setLongitude(double value) {
  m_longitude = value;
}

double Node::latitude() {
  return m_latitude;
}

void Node::setLatitude(double value) {
  m_latitude = value;
}

double Node::area() {
  return m_area;
}

void Node::setArea(double area) {
  if (area >= 0.0) {
    m_area = area;
  }
}

bool Node::hasIngoingNode(ElementID node_id) {
  return m_ingoing_links_map.find(node_id) != m_ingoing_links_map.end();
}

bool Node::hasOutgoingNode(ElementID node_id) {
  return m_outgoing_links_map.find(node_id) != m_outgoing_links_map.end();
}
