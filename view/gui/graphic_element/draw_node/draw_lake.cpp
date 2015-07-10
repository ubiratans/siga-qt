#include "view/gui/graphic_element/draw_node/draw_lake.h"

#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"
#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

DrawLake::DrawLake(double x, double y) : DrawNode(x, y), m_main_triangle(nullptr) {
  initialize();
}

NodeType DrawLake::type() {
  return NodeType::Lake;
}

int DrawLake::height() {
  return m_main_triangle->height();
}

int DrawLake::width() {
  return m_main_triangle->edgeSize();
}

void DrawLake::initialize() {
    clearAndDeletePrimitives();

    m_main_triangle = new DrawTriangle(m_x, m_y, QColor(70, 180, 255), QColor(Qt::black));
    DrawTriangle *triangle_intern = new DrawTriangle(m_x, m_y, QColor(110, 240, 255), QColor(Qt::black), 7);

    DrawNodePrimitiveSt st;
    DrawNodePrimitiveSt st_intern;

    st.m_draw_primitive = m_main_triangle;
    st_intern.m_draw_primitive = triangle_intern;

    m_primitives_info.push_back(st);
    m_primitives_info.push_back(st_intern);

    m_primitives_vector.push_back(m_main_triangle);
    m_primitives_vector.push_back(triangle_intern);
}
