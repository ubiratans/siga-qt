#ifndef CORE_ELEMENT_ELEMENT_PROPERTIES_SET
#define CORE_ELEMENT_ELEMENT_PROPERTIES_SET

#include <map>
#include <string>

#include "core/element/element_structs.h"

class Element;

class ElementPropertiesSet {
public:
  bool boolProperty(std::string &key, bool &value);
  bool intProperty(std::string &key, int &value);
  bool doubleProperty(std::string &key, double &value);
  bool stringProperty(std::string &key, std::string &value);

  const std::map< std::string, bool >& boolProperties();
  const std::map< std::string, int >& intProperties();
  const std::map< std::string, double >& doubleProperties();
  const std::map< std::string, std::string >& stringProperties();

  void setBoolProperty(std::string &key, int value);
  void setIntProperty(std::string &key, int value);
  void setDoubleProperty(std::string &key, double value);
  void setStringProperty(std::string &key, std::string value);

  bool removeProperty(std::string &key, ElementPropertyType property_type);

  virtual const std::map< std::string, ElementPropertyType >& mandatoryProperties() = 0;

protected:
  bool removeBoolProperty(std::string &key);
  bool removeIntProperty(std::string &key);
  bool removeDoubleProperty(std::string &key);
  bool removeStringProperty(std::string &key);

  bool isKeyPropertyMandatory(std::string &key, ElementPropertyType);

  std::map< std::string, bool > m_bool_property_map;
  std::map< std::string, int > m_int_property_map;
  std::map< std::string, double > m_double_property_map;
  std::map< std::string, std::string > m_string_property_map;
};

#endif
