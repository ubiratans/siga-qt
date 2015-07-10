#include "view/gui/graphic_element/draw_node/draw_basin.h"

#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

DrawBasin::DrawBasin(double x, double y) : DrawNode(x, y), m_circle(nullptr) {
  initialize();
}

NodeType DrawBasin::type() {
  return NodeType::Basin;
}

int DrawBasin::height() {
  return m_circle->radius();
}

int DrawBasin::width() {
  return m_circle->radius();
}

void DrawBasin::initialize() {
    clearAndDeletePrimitives();

    m_circle = new DrawCircle(m_x, m_y, QColor(0, 0, 150, 255), QColor(Qt::black));

    DrawNodePrimitiveSt st;
    st.m_draw_primitive = m_circle;

    m_primitives_vector.push_back(m_circle);
    m_primitives_info.push_back(st);
}
