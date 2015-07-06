#include "view/gui/graphic_element/draw_node/draw_reservoir.h"

#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"

DrawReservoir::DrawReservoir(double x, double y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawReservoir::type() {
  return NodeType::Reservoir;
}

void DrawReservoir::initialize() {
    m_primitives_vector.clear();

    DrawTriangle *triangle = new DrawTriangle(m_x, m_y, QColor(70, 180, 255), QColor(Qt::black));
    DrawNodePrimitiveSt st;

    st.m_draw_primitive = triangle;

    m_primitives_vector.push_back(triangle);
    m_primitives_info.push_back(st);
}
