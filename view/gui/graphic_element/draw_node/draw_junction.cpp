#include "view/gui/graphic_element/draw_node/draw_junction.h"

#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

DrawJunction::DrawJunction(float x, float y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawJunction::type() {
    return NodeType::Junction;
}

void DrawJunction::initialize() {
    m_primitives_vector.clear();

    DrawCircle *circle = new DrawCircle(m_x, m_y, QColor(0, 0, 255, 255), QColor(Qt::black), 6.0);

    DrawNodePrimitiveSt st;
    st.m_draw_primitive = circle;

    m_primitives_vector.push_back(circle);
    m_primitives_info.push_back(st);
}
