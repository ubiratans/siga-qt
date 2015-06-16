#include "core/element/link.h"

#include "core/element/node.h"
#include "core/element/link_properties_set.h"

Link::Link(
  ElementID id,
  std::string name,
  Node &node_origin,
  Node &node_destiny,
  LinkType type,
  bool bidirectional,
  bool lateral_inflow,
  bool artificial
  )
  : Element(id, name, 0.0, ElementType::Link),
    m_artificial(artificial), m_bidirectional(bidirectional), m_lateral_inflow(lateral_inflow),
    m_depth(0.0), m_length(0.0), m_has_div_point(false), m_type(type),
    m_node_origin(&node_origin), m_node_destiny(&node_destiny)
{
  m_properties_set = new LinkPropertiesSet(*this);
}

Link::~Link() {
  delete m_properties_set;
}

bool Link::isArtificial() {
  return m_artificial;
}
void Link::setArtificial(bool value) {
  m_artificial = value;
}

bool Link::isBidirectional() {
  return m_bidirectional;
}

void Link::setBidirectional(bool value) {
  m_bidirectional = value;
}

bool Link::hasLateralInflow() {
  return m_lateral_inflow;
}

void Link::setLateralInflow(bool value) {
  m_lateral_inflow = value;
}

double Link::length() {
  return m_length;
}

void Link::setLength(double value) {
  m_length = value;
}

double Link::depth() {
  return m_depth;
}

void Link::setDepth(double value) {
  m_depth = value;
}

double Link::divPointLongitude() {
  return m_div_point_longitude;
}

double Link::divPointLatitude() {
  return m_div_point_latitude;
}

bool Link::hasDivPoint() {
  return m_has_div_point;
}

void Link::removeDivPoint() {
  m_has_div_point = false;
}

void Link::setDivPoint(double longitude, double latitude) {
  m_has_div_point = true;

  m_div_point_longitude = longitude;
  m_div_point_latitude = latitude;
}

Node& Link::nodeDestiny() {
  return *m_node_destiny;
}

Node& Link::nodeOrigin() {
  return *m_node_origin;
}

bool Link::setNodes(Node &node_origin, Node &node_destiny) {
  bool ret = ( node_origin.id() != node_destiny.id() && (node_origin.id() != m_node_origin->id() || node_destiny.id() != m_node_destiny->id()) );

  if (ret) {
    m_node_destiny = &node_destiny;
    m_node_origin = &node_origin;
  }

  return ret;
}

LinkType Link::type() {
  return m_type;
}

bool Link::setType(LinkType type) {
  bool ret = type != m_type;

  if (ret) {
    m_type = type;
  }

  return ret;
}
