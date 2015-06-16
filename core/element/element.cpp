#include "core/element/element.h"

Element::Element(ElementID id, std::string name, double volume, ElementType type)
  : m_id(id), m_volume(volume), m_element_type(type), m_name(name)
{

}

Element::~Element(void) {
}

void Element::setBoolProperty(std::string key, bool value) {
  m_properties_set->setBoolProperty(key, value);
}

void Element::setIntProperty(std::string key, int value) {
  m_properties_set->setIntProperty(key, value);
}

void Element::setDoubleProperty(std::string key, double value) {
  m_properties_set->setDoubleProperty(key, value);
}

void Element::setStringProperty(std::string key, std::string value) {
  m_properties_set->setStringProperty(key, value);
}

bool Element::removeProperty(std::string key, ElementPropertyType property_type) {
 return  m_properties_set->removeProperty(key, property_type);
}

ElementID Element::id() {
  return m_id;
}

void Element::setID(ElementID id) {
  m_id = id;
}

double Element::volume() {
  return m_volume;
}

void Element::setVolume(double volume) {
  m_volume = volume;
}

std::string Element::name() {
  return m_name;
}

void Element::setName(std::string name) {
  m_name = name;
}

ElementType Element::elementType() {
  return m_element_type;
}

bool Element::boolProperty(std::string key, bool &value) {
  return m_properties_set->boolProperty(key, value);
}

bool Element::intProperty(std::string key, int &value) {
  return m_properties_set->intProperty(key, value);
}

bool Element::doubleProperty(std::string key, double &value) {
  return m_properties_set->doubleProperty(key, value);
}

bool Element::stringProperty(std::string key, std::string &value) {
  return m_properties_set->stringProperty(key, value);
}

const std::map<std::string, bool> &Element::boolProperties() {
  return m_properties_set->boolProperties();
}

const std::map<std::string, int>& Element::intProperties() {
  return m_properties_set->intProperties();
}

const std::map<std::string, double> &Element::doubleProperties() {
  return m_properties_set->doubleProperties();
}

const std::map<std::string, std::string> &Element::stringProperties() {
  return m_properties_set->stringProperties();
}

const std::map<std::string, ElementPropertyType> &Element::mandatoryProperties() {
  return m_properties_set->mandatoryProperties();
}
