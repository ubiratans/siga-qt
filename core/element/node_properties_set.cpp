#include "core/element/node_properties_set.h"

#include "core/element/node.h"
#include "core/element/element_constants.h"

std::map< std::string, ElementPropertyType > NodePropertiesSet::m_demand_mandatory_properties_map = {
  {kElementPropertyDemandType.first, kElementPropertyDemandType.second}
};

std::map< std::string, ElementPropertyType > NodePropertiesSet::m_empty_map;

NodePropertiesSet::NodePropertiesSet(Node &node) : m_node(&node) {

}

const std::map<std::string, ElementPropertyType>& NodePropertiesSet::mandatoryProperties() {
  if (m_node->type() == NodeType::Demand) {
    return m_demand_mandatory_properties_map;
  }

  return m_empty_map;
}
