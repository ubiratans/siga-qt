#include "core/element/element_manager.h"

#include <sstream>

ElementManager::ElementManager() {
  m_id_counter = 1;

  m_link_map.clear();
  m_node_map.clear();
  m_element_map.clear();
}

ElementManager::~ElementManager() {
  clear();
}

Node& ElementManager::addNode(NodeType type, double latitude, double longitude) {
  Node *node = nullptr;
  std::stringstream stream;

  stream << countNodes() + 1;

  std::string node_name = "N" + stream.str();

  node = new Node(m_id_counter, node_name, type, latitude, longitude);

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
      removeNode(id);
    }

    else {
      removeLink(id);
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
  return node.setType(new_type);
}

bool ElementManager::setNodeType(ElementID node_id, NodeType new_type) {
  Node *node = nullptr;

  if (getNode(node_id, node)) {
    return setNodeType(*node, new_type);
  }

  return false;
}

bool ElementManager::setLinkType(Link &link, LinkType new_type) {
  return link.setType(new_type);
}

bool ElementManager::setLinkType(ElementID link_id, LinkType new_type) {
  Link *link= nullptr;

  if (getLink(link_id, link)) {
    return setLinkType(*link, new_type);
  }

  return false;
}

bool ElementManager::setLinkNodes(ElementID link_id, ElementID node_origin_id, ElementID node_destiny_id) {
  Link *link = nullptr;

  if (!getLink(link_id, link)) {
    return false;
  }

  Node *node_origin = nullptr;
  Node *node_destiny = nullptr;

  if (!getNode(node_origin_id, node_origin) || !getNode(node_destiny_id, node_destiny)) {
    return false;
  }

  ElementID old_node_origin_id = link->nodeOrigin().id();
  ElementID old_node_destiny_id = link->nodeDestiny().id();

  if (node_origin->id() != old_node_origin_id && node_origin->outgoingLinks().find(node_destiny->id()) != node_origin->outgoingLinks().end()) {
    return false;
  }

  if (node_destiny->id() != old_node_destiny_id && node_destiny->ingoingLinks().find(node_origin->id()) != node_destiny->ingoingLinks().end()) {
    return false;
  }

  link->nodeOrigin().removeOutgoingLink(link->nodeDestiny().id());
  link->nodeDestiny().removeIngoingLink(link->nodeOrigin().id());
  link->setNodes(*node_origin, *node_destiny);

  node_origin->insertOutgoingLink(node_destiny->id(), *link);
  node_destiny->insertIngoingLink(node_origin->id(), *link);

  return true;
}

bool ElementManager::setElementID(ElementID old_id, ElementID new_id) {
  Element *element = nullptr;
  Element *element_aux = nullptr;

  bool ret = false;

  if (old_id != new_id && getElement(old_id, element) && !getElement(new_id, element_aux)) {
    ret = true;

    if (element->elementType() == ElementType::Link) {
      Link *link = static_cast< Link* >( element );

      setLinkID(*link, new_id);
    }

    else {
      Node *node = static_cast< Node* >(element);

      setNodeID(*node, new_id);
    }

    if (new_id >= m_id_counter) {
      m_id_counter = new_id + 1;
    }
  }

  return ret;
}

bool ElementManager::attachNode(Node &node) {
  bool ret = m_element_map.find(node.id()) == m_element_map.end();

  if (ret) {
    m_node_map[node.id()] = &node;
    m_element_map[node.id()] = &node;
  }

  return ret;
}

Node* ElementManager::detachNode(ElementID id) {
  Node *node = nullptr;

  if (getNode(id, node)) {
    for (auto entry : node->ingoingLinks()) {
      Link *link = entry.second;
      Node &parent_node = link->nodeOrigin();

      parent_node.removeOutgoingLink(node->id());

      m_link_map.erase(link->id());
      m_element_map.erase(link->id());
    }

    for (auto entry : node->outgoingLinks()) {
      Link *link = entry.second;
      Node &parent_node = link->nodeDestiny();

      parent_node.removeIngoingLink(node->id());

      m_link_map.erase(link->id());
      m_element_map.erase(link->id());
    }

    m_node_map.erase(id);
    m_element_map.erase(id);
  }

  return node;
}

bool ElementManager::attachLink(Link &link) {
  Node &node_origin = link.nodeOrigin();
  Node &node_destiny = link.nodeDestiny();
  ElementID node_origin_id = link.nodeOrigin().id();
  ElementID node_destiny_id = link.nodeDestiny().id();

  bool ret = m_element_map.find(link.id()) == m_element_map.end() && (node_origin_id != node_destiny_id);

  if (ret && node_origin.insertOutgoingLink(node_destiny_id, link) && node_destiny.insertIngoingLink(node_origin_id, link)) {
    m_link_map[link.id()] = &link;
    m_element_map[link.id()] = &link;

    return true;
  }

  return false;
}

Link* ElementManager::detachLink(ElementID id) {
  Link* link = nullptr;

  if (getLink(id, link)) {
    Node &node_origin = link->nodeOrigin();
    Node &node_destiny = link->nodeDestiny();

    node_origin.removeOutgoingLink(node_destiny.id());
    node_destiny.removeIngoingLink(node_origin.id());

    m_link_map.erase(link->id());
    m_element_map.erase(link->id());
  }

  return link;
}

std::map<ElementID, Node *>& ElementManager::nodesMap() {
  return m_node_map;
}

bool ElementManager::deleteExternalElement(Element *element) {
  Element *aux_element = nullptr;

  if (element != nullptr && !getElement(element->id(), aux_element)) {
    delete element;
    return true;
  }

  return false;
}

void ElementManager::clear() {
  for (auto it : m_node_map) {
    delete it.second;
  }

  for (auto it : m_link_map) {
    delete it.second;
  }

  m_node_map.clear();
  m_link_map.clear();
  m_element_map.clear();

  m_id_counter = 1;
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

bool ElementManager::removeNode(ElementID id) {
  Node *node = detachNode(id);
  bool ret = node != nullptr;

  if (ret) {
    for (auto it : node->outgoingLinks()) {
      delete it.second;
    }

    for (auto it : node->ingoingLinks()) {
      delete it.second;
    }

    delete node;
  }

  return ret;
}

bool ElementManager::removeLink(ElementID id) {
  Link *link = detachLink(id);
  bool ret = link != nullptr;

  if (ret) {
    delete link;
  }

  return ret;
}

void ElementManager::setLinkID(Link &link, ElementID new_id) {
  ElementID old_id = link.id();

  if (new_id != old_id) {
    link.setID(new_id);

    m_link_map[new_id] = &link;
    m_element_map[new_id] = &link;

    m_link_map.erase(old_id);
    m_element_map.erase(old_id);
  }
}

void ElementManager::setNodeID(Node &node, ElementID new_id) {
  ElementID old_id = node.id();
  node.setID(new_id);

  for (auto it : node.outgoingLinks()) {
    Link &link = *it.second;
    Node &neighbor = link.nodeDestiny();

    neighbor.removeIngoingLink(old_id);
    neighbor.insertIngoingLink(new_id, link);
  }

  for (auto it : node.ingoingLinks()) {
    Link &link = *it.second;
    Node &neighbor = link.nodeOrigin();

    neighbor.removeOutgoingLink(old_id);
    neighbor.insertOutgoingLink(new_id, link);
  }

  auto it = m_node_map.find(old_id);
  m_node_map.erase(it);
  m_element_map.erase(old_id);

  m_node_map[new_id] = &node;
  m_element_map[new_id] = &node;
}
