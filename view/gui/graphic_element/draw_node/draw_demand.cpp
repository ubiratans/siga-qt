#include "view/gui/graphic_element/draw_node/draw_demand.h"

#include "view/gui/graphic_element/draw_primitive/draw_rectangle.h"

DrawDemand::DrawDemand(double x, double y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawDemand::type() {
    return NodeType::Basin;
}

void DrawDemand::initialize() {
    m_primitives_vector.clear();

    DrawRectangle *primitive = new DrawRectangle(m_x, m_y, QColor(200, 0, 0, 255), QColor(Qt::black));
    primitive->setRotation(45);

    DrawNodePrimitiveSt st;
    st.m_draw_primitive = primitive;
    st.m_rotation = 45.0;

    m_primitives_vector.push_back(primitive);
    m_primitives_info.push_back(st);
}
