#include "view/gui/graphic_element/draw_node/draw_basin.h"

#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

DrawBasin::DrawBasin(float x, float y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawBasin::type() {
    return NodeType::Basin;
}

void DrawBasin::initialize() {
    m_primitives_vector.clear();

    DrawCircle *circle = new DrawCircle(m_x, m_y, QColor(0, 0, 150, 255), QColor(Qt::black));

    m_primitives_vector.push_back(circle);
}
