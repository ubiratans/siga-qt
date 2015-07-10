#include "view/gui/graphic_element/draw_node/draw_reservoir.h"

#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"

DrawReservoir::DrawReservoir(double x, double y) : DrawNode(x, y), m_triangle(nullptr) {
  initialize();
}

int DrawReservoir::height() {
  return m_triangle->height();
}

int DrawReservoir::width() {
  return m_triangle->edgeSize();
}

NodeType DrawReservoir::type() {
  return NodeType::Reservoir;
}

void DrawReservoir::initialize() {
  clearAndDeletePrimitives();

  m_triangle = new DrawTriangle(m_x, m_y, QColor(70, 180, 255), QColor(Qt::black));
  DrawNodePrimitiveSt st;

  st.m_draw_primitive = m_triangle;

  m_primitives_vector.push_back(m_triangle);
  m_primitives_info.push_back(st);
}
