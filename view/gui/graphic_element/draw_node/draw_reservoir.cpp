#include "view/gui/graphic_element/draw_node/draw_reservoir.h"

#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"

DrawReservoir::DrawReservoir(float x, float y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawReservoir::type() {
    return NodeType::Reservoir;
}

void DrawReservoir::initialize() {
    m_primitives_vector.clear();

    DrawTriangle *triangle = new DrawTriangle(m_x, m_y, QColor(70, 180, 255), QColor(Qt::black));

    m_primitives_vector.push_back(triangle);
}
