#include "view/gui/draw_element/draw_primitive/draw_triangle.h"

DrawTriangle::DrawTriangle(long x, long y, QColor color, QColor border_color)
  : DrawPrimitive(x, y, color, border_color)
{
  m_gl_primitive = GL_TRIANGLES;
  m_gl_border_primitive = GL_TRIANGLE_STRIP;
  m_vertex_vec.reserve(3);
}

bool DrawTriangle::hitTest(long screen_x, long screen_y) {
  return false;
}

void DrawTriangle::calculateVertices() {
  long inc = 1;

  long min_x = x() - inc;
  long max_x = x() + inc;
  long min_y = y() - inc;
  long max_y = y() + inc;

  long vertices[3][2] = {
    { min_x, min_y },
    { x(), max_y },
    { max_x, min_y}
  };

  m_vertex_vec[0] = std::make_pair(vertices[0][0], vertices[0][1]);
  m_vertex_vec[1] = std::make_pair(vertices[1][0], vertices[1][1]);
  m_vertex_vec[2] = std::make_pair(vertices[2][0], vertices[2][1]);
}
