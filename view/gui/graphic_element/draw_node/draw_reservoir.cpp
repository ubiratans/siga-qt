#include "view/gui/graphic_element/draw_node/draw_reservoir.h"

DrawReservoir::DrawReservoir(float x, float y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawReservoir::type() {
    return NodeType::Reservoir;
}

void DrawReservoir::initialize() {
    m_primitives_vector.clear();

    DrawTriangle *triangle = new DrawTriangle(m_x, m_y, QColor(Qt::blue), QColor(Qt::black));

    m_primitives_vector.push_back(triangle);
}
