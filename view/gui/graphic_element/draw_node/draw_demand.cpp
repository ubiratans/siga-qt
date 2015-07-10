#include "view/gui/graphic_element/draw_node/draw_demand.h"

#include "view/gui/graphic_element/draw_primitive/draw_rectangle.h"

DrawDemand::DrawDemand(double x, double y) : DrawNode(x, y), m_rectangle(nullptr) {
  initialize();
}

NodeType DrawDemand::type() {
  return NodeType::Basin;
}

int DrawDemand::height() {
  return m_rectangle->height();
}

int DrawDemand::width() {
  return m_rectangle->width();
}

void DrawDemand::initialize() {
  clearAndDeletePrimitives();

  m_rectangle = new DrawRectangle(m_x, m_y, QColor(200, 0, 0, 255), QColor(Qt::black));
  m_rectangle->setRotation(45);

  DrawNodePrimitiveSt st;
  st.m_draw_primitive = m_rectangle;
  st.m_rotation = 45.0;

  m_primitives_vector.push_back(m_rectangle);
  m_primitives_info.push_back(st);
}
