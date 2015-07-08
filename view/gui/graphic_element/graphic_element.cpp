#include "view/gui/graphic_element/graphic_element.h"

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

GraphicElement::GraphicElement(ElementID id, ElementType type) : m_id(id), m_element_type(type), m_scale(1.0), m_rotation(0.0) {
  m_has_to_calculate_primitives_vertices = true;
  m_selected = false;
}

GraphicElement::~GraphicElement() {
}

bool GraphicElement::verticesUpdated() {
  return !m_has_to_calculate_primitives_vertices;
}

void GraphicElement::setSelected(bool selected) {
  m_selected = selected;
}

bool GraphicElement::isSelected() {
  return m_selected;
}

double GraphicElement::scale() {
  return m_scale;
}

double GraphicElement::rotation() {
  return m_rotation;
}

ElementType GraphicElement::elementType() {
  return m_element_type;
}

ElementID GraphicElement::id() {
  return m_id;
}
