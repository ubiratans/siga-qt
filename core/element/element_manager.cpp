#include "core/element/element_manager.h"

#include <sstream>

#include "core/element/node/basin.h"
#include "core/element/node/demand.h"
#include "core/element/node/junction.h"
#include "core/element/node/lake.h"
#include "core/element/node/reservoir.h"

ElementManager::ElementManager() {
  m_id_counter = 1;

  m_link_map.clear();
  m_node_map.clear();
  m_element_map.clear();
}

ElementManager::~ElementManager() {

}

Node& ElementManager::addNode(NodeType type, double latitude, double longitude) {
  Node *node = nullptr;
  std::stringstream stream;

  stream << countNodes() + 1;

  std::string node_name = "N" + stream.str();

  node = instantiateNode(type, node_name, latitude, longitude);

  m_element_map[m_id_counter] = node;
  m_node_map[m_id_counter++] = node;

  return *node;
}

bool ElementManager::addLink(ElementID node_origin_id,
                             ElementID node_destiny_id,
                             Link *&result,
                             LinkType type,
                             bool bidirectional,
                             bool lateral_inflow,
                             bool artificial)
{
  Node *node_origin = nullptr;
  Node *node_destiny = nullptr;

  bool ret =  node_origin_id != node_destiny_id &&
              getNode(node_origin_id, node_origin) &&
              getNode(node_destiny_id, node_destiny) &&
              !(node_origin->hasOutgoingNode(node_destiny_id));

  if (ret) {
    std::stringstream stream;
    stream << countLinks() + 1;
    std::string name = "L" + stream.str();

    result = new Link(m_id_counter, name, *node_origin, *node_destiny, type, bidirectional, lateral_inflow, artificial);

    node_origin->insertOutgoingLink(node_destiny_id, *result);
    node_destiny->insertIngoingLink(node_origin_id, *result);

    m_element_map[m_id_counter] = result;
    m_link_map[m_id_counter++] = result;
  }

  return ret;
}

bool ElementManager::removeElement(ElementID id) {
  Element *element = nullptr;
  bool ret = getElement(id, element);

  if (ret) {
    if (element->elementType() == ElementType::Node) {
      removeNode(static_cast< Node* >( element ));
    }

    else {
      removeLink(static_cast< Link* >( element ));
    }
  }

  return ret;
}

bool ElementManager::getNode(ElementID id, Node *&result) {
  auto it = m_node_map.find(id);
  bool ret = it != m_node_map.end();

  if (ret) {
    result = (*it).second;
  }

  return ret;
}

bool ElementManager::getLink(ElementID id, Link *&result) {
  auto it = m_link_map.find(id);
  bool ret = it != m_link_map.end();

  if (ret) {
    result = (*it).second;
  }

  return ret;
}

bool ElementManager::getElement(ElementID id, Element *&result) {
  auto it = m_element_map.find(id);
  bool ret = it != m_element_map.end();

  if (ret) {
    result = (*it).second;
  }

  return ret;
}

bool ElementManager::getElementName(ElementID id, std::string &name) {
  Element *element = nullptr;
  bool ret = getElement(id, element);


  if (ret) {
    name = element->name();
  }

  return ret;
}

bool ElementManager::setNodeType(Node &node, NodeType new_type) {

}

std::map<ElementID, Node *>& ElementManager::nodesMap() {
  return m_node_map;
}

uint32_t ElementManager::countElements() {
  return m_element_map.size();
}

uint32_t ElementManager::countLinks() {
  return m_link_map.size();
}

uint32_t ElementManager::countNodes() {
  return m_node_map.size();
}

Node *ElementManager::instantiateNode(NodeType type, std::string name, double latitude, double longitude) {
  Node *node = nullptr;

  switch (type) {
    case NodeType::Basin:
      node = new Basin(m_id_counter, name, latitude, longitude);
      break;

    case NodeType::Demand:
      node = new Demand(m_id_counter, name, latitude, longitude);
      break;

    case NodeType::Junction:
      node = new Junction(m_id_counter, name, latitude, longitude);
      break;

    case NodeType::Lake:
      node = new Lake(m_id_counter, name, latitude, longitude);
      break;

    case NodeType::Reservoir:
    default:
      node = new Reservoir(m_id_counter, name, latitude, longitude);
      break;
  }

  return node;
}

Node *ElementManager::instantiateNode(NodeType type, Node &base_node) {
  Node *node = nullptr;

  switch (type) {
    case NodeType::Basin:
      node = new Basin(base_node);
      break;

    case NodeType::Demand:
      node = new Demand(base_node);
      break;

    case NodeType::Junction:
      node = new Junction(base_node);
      break;

    case NodeType::Lake:
      node = new Lake(base_node);
      break;

    case NodeType::Reservoir:
    default:
      node = new Reservoir(base_node);
      break;
  }

  return node;
}

bool ElementManager::removeNode(Node *node) {
  if (node != nullptr) {
    m_element_map.erase(node->id());
    m_node_map.erase(node->id());
    delete node;

    return true;
  }

  return false;
}

bool ElementManager::removeLink(Link *link) {
  if (link != nullptr) {
    m_element_map.erase(link->id());
    m_link_map.erase(link->id());
    delete link;

    return true;
  }

  return false;
}
