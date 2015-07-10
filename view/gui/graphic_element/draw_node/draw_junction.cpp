#include "view/gui/graphic_element/draw_node/draw_junction.h"

#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

DrawJunction::DrawJunction(double x, double y) : DrawNode(x, y), m_circle(nullptr) {
  initialize();
}

int DrawJunction::height() {
  return m_circle->radius();
}

int DrawJunction::width() {
  return m_circle->radius();
}

NodeType DrawJunction::type() {
  return NodeType::Junction;
}

void DrawJunction::initialize() {
  clearAndDeletePrimitives();

  m_circle = new DrawCircle(m_x, m_y, QColor(0, 0, 255, 255), QColor(Qt::black), 6.0);

  DrawNodePrimitiveSt st;
  st.m_draw_primitive = m_circle;

  m_primitives_vector.push_back(m_circle);
  m_primitives_info.push_back(st);
}
