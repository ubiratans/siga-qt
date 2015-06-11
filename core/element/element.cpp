#include "core/element/element.h"

Element::Element(ElementID id, std::string name, double volume, ElementType type)
  : m_id(id), m_volume(volume), m_element_type(type), m_name(name)
{

}

Element::~Element(void) {
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
