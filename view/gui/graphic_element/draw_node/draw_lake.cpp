#include "view/gui/graphic_element/draw_node/draw_lake.h"

#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"
#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

DrawLake::DrawLake(double x, double y) : DrawNode(x, y) {
  initialize();
}

NodeType DrawLake::type() {
    return NodeType::Lake;
}

void DrawLake::initialize() {
    m_primitives_vector.clear();

    DrawTriangle *triangle = new DrawTriangle(m_x, m_y, QColor(70, 180, 255), QColor(Qt::black));
    DrawTriangle *triangle_intern = new DrawTriangle(m_x, m_y, QColor(90, 220, 255), QColor(Qt::black), 6);

    DrawNodePrimitiveSt st;
    DrawNodePrimitiveSt st_intern;

    st.m_draw_primitive = triangle;
    st_intern.m_draw_primitive = triangle_intern;

    m_primitives_info.push_back(st);
    m_primitives_info.push_back(st_intern);

    m_primitives_vector.push_back(triangle);
    m_primitives_vector.push_back(triangle_intern);
}
