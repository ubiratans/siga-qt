#include "core/element/element_properties_set.h"

bool ElementPropertiesSet::boolProperty(std::string &key, bool &value) {
  auto it = m_bool_property_map.find(key);
  bool ret = m_bool_property_map.end() != it;

  if (ret) {
    value = it->second;
  }

  return ret;
}

bool ElementPropertiesSet::intProperty(std::string &key, int &value) {
  auto it = m_int_property_map.find(key);
  bool ret = m_int_property_map.end() != it;

  if (ret) {
    value = it->second;
  }

  return ret;
}

bool ElementPropertiesSet::doubleProperty(std::string &key, double &value) {
  auto it = m_double_property_map.find(key);
  bool ret = m_double_property_map.end() != it;

  if (ret) {
    value = it->second;
  }

  return ret;
}

bool ElementPropertiesSet::stringProperty(std::string &key, std::string &value) {
  auto it = m_string_property_map.find(key);
  bool ret = m_string_property_map.end() != it;

  if (ret) {
    value = it->second;
  }

  return ret;
}

const std::map<std::string, bool> &ElementPropertiesSet::boolProperties() {
  return m_bool_property_map;
}

const std::map<std::string, int> &ElementPropertiesSet::intProperties() {
  return m_int_property_map;
}

const std::map<std::string, double> &ElementPropertiesSet::doubleProperties() {
  return m_double_property_map;
}

const std::map<std::string, std::string> &ElementPropertiesSet::stringProperties() {
  return m_string_property_map;
}

void ElementPropertiesSet::setBoolProperty(std::string &key, int value) {
  auto &map = m_bool_property_map;

  map[key] = value;
}

void ElementPropertiesSet::setIntProperty(std::string &key, int value) {
  auto &map = m_int_property_map;

  map[key] = value;
}

void ElementPropertiesSet::setDoubleProperty(std::string &key, double value) {
  auto &map = m_double_property_map;

  map[key] = value;
}

void ElementPropertiesSet::setStringProperty(std::string &key, std::string value) {
  auto &map = m_string_property_map;

  map[key] = value;
}

bool ElementPropertiesSet::removeProperty(std::string &key, ElementPropertyType property_type) {
  switch (property_type) {
    case ElementPropertyType::Bool:
      return removeBoolProperty(key);

    case ElementPropertyType::Double:
      return removeDoubleProperty(key);

    case ElementPropertyType::Int:
      return removeIntProperty(key);

    case ElementPropertyType::String:
      return removeStringProperty(key);

    default:
      return false;
  }
}

bool ElementPropertiesSet::removeBoolProperty(std::string &key) {
  return (!isKeyPropertyMandatory(key, ElementPropertyType::Bool)
              && m_int_property_map.erase(key) > 0);
}

bool ElementPropertiesSet::removeIntProperty(std::string &key) {
  return (!isKeyPropertyMandatory(key, ElementPropertyType::Int)
              && m_int_property_map.erase(key) > 0);
}

bool ElementPropertiesSet::removeDoubleProperty(std::string &key) {
  return (!isKeyPropertyMandatory(key, ElementPropertyType::Double)
              && m_double_property_map.erase(key) > 0);
}

bool ElementPropertiesSet::removeStringProperty(std::string &key) {
  return (!isKeyPropertyMandatory(key, ElementPropertyType::String)
              && m_string_property_map.erase(key) > 0);
}

bool ElementPropertiesSet::isKeyPropertyMandatory(std::string &key, ElementPropertyType prop_type) {
  auto it = mandatoryProperties().find(key);
  bool ret = false;

  if (it != mandatoryProperties().end()) {
    ret = (prop_type == it->second);
  }

  return ret;
}
