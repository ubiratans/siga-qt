#ifndef CORE_ELEMENT_LINK_PROPERTIES_SET_H
#define CORE_ELEMENT_LINK_PROPERTIES_SET_H

#include "core/element/element_properties_set.h"

class Link;

class LinkPropertiesSet : public ElementPropertiesSet {
public:
  LinkPropertiesSet(Link &link);
  virtual ~LinkPropertiesSet();

  const std::map< std::string, ElementPropertyType >& mandatoryProperties();

private:
  static std::map< std::string, ElementPropertyType > m_empty_map;
  Link *m_link;
};

#endif
