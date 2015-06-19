#ifndef CORE_ELEMENT_NODE_PROPERTIES_SET_H
#define CORE_ELEMENT_NODE_PROPERTIES_SET_H

#include "core/element/element_properties_set.h"

class Node;

class NodePropertiesSet : public ElementPropertiesSet {
public:
  NodePropertiesSet(Node &node);
  virtual ~NodePropertiesSet();

  const std::map< std::string, ElementPropertyType >& mandatoryProperties();

private:
  static std::map< std::string, ElementPropertyType > m_demand_mandatory_properties_map;
  static std::map< std::string, ElementPropertyType > m_empty_map;

  Node *m_node;
};

#endif
