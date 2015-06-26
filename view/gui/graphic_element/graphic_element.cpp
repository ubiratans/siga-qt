#include "view/gui/graphic_element/graphic_element.h"

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

GraphicElement::GraphicElement(ElementID id, ElementType type) : m_id(id), m_element_type(type), m_scale(1.0), m_rotation(0.0) {
}

GraphicElement::~GraphicElement() {
}

float GraphicElement::scale() {
  return m_scale;
}

void GraphicElement::setScale(float value) {
  m_scale = value;
}

float GraphicElement::rotation() {
  return m_rotation;
}

void GraphicElement::setRotation(float angle) {
  m_rotation = angle;
}

ElementType GraphicElement::elementType() {
  return m_element_type;
}

ElementID GraphicElement::id() {
  return m_id;
}
