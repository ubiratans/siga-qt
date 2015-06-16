#include "core/element/link_properties_set.h"

std::map< std::string, ElementPropertyType > LinkPropertiesSet::m_empty_map;

LinkPropertiesSet::LinkPropertiesSet(Link &link) : m_link(&link) {

}

LinkPropertiesSet::~LinkPropertiesSet() {

}

const std::map<std::string, ElementPropertyType>& LinkPropertiesSet::mandatoryProperties() {
  return m_empty_map;
}
