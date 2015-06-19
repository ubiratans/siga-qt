#include "view/gui/draw_element/draw_element.h"

#include "view/gui/draw_element/draw_primitive/draw_primitive.h"

DrawElement::DrawElement(ElementID id, ElementType type, double scale) : m_id(id), m_element_type(type), m_scale(scale) {

}

DrawElement::~DrawElement() {
  for (auto primitive : m_primitives_vector) {
    delete primitive;
  }

  m_primitives_vector.clear();
}

double DrawElement::scale() {
  return m_scale;
}

void DrawElement::setScale(double value) {
  m_scale = value;

  for (auto primitive : m_primitives_vector) {
    primitive->setScale(value);
  }
}

ElementType DrawElement::elementType() {
  return m_element_type;
}

ElementID DrawElement::id() {
  return m_id;
}

const std::vector<DrawPrimitive *> &DrawElement::primitives() {
  return m_primitives_vector;
}
