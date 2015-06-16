#ifndef CORE_ELEMENT_ELEMENT_H
#define CORE_ELEMENT_ELEMENT_H

#include <map>
#include <string>
#include <vector>

#include "core/element/element_structs.h"
#include "core/element/element_properties_set.h"

class ElementManager;

class Element {
  friend class ElementManager;

public:
  ElementID id(); //!< get element id

  double volume(); //!< get volume
  void setVolume(double volume);

  std::string name();
  void setName(std::string name);

  ElementType elementType(); //!< get element type

  bool boolProperty(std::string key, bool &value);
  bool intProperty(std::string key, int &value);
  bool doubleProperty(std::string key, double &value);
  bool stringProperty(std::string key, std::string &value);

  const std::map< std::string, bool >& boolProperties();
  const std::map< std::string, int >& intProperties();
  const std::map< std::string, double >& doubleProperties();
  const std::map< std::string, std::string >& stringProperties();
  const std::map< std::string, ElementPropertyType >& mandatoryProperties();

  void setBoolProperty(std::string key, bool value);
  void setIntProperty(std::string key, int value);
  void setDoubleProperty(std::string key, double value);
  void setStringProperty(std::string key, std::string value);

  bool removeProperty(std::string key, ElementPropertyType property_type);

protected:
  Element(ElementID id, std::string name, double volume, ElementType type);
  virtual ~Element();

  void setID(ElementID id); //!< set element id

  ElementID m_id; //!< Element's identificator
  double m_volume; //!< Volume

  ElementType m_element_type; //!< Element type
  std::string m_name; //!< Element name

  ElementPropertiesSet *m_properties_set;
};

#endif
