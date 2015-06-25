#include "view/gui/draw_element/draw_primitive/draw_triangle.h"

DrawTriangle::DrawTriangle(float x, float y, QColor color, QColor border_color)
  : DrawPrimitive(x, y, color, border_color)
{
  m_gl_primitive = GL_TRIANGLES;
  m_gl_border_primitive = GL_TRIANGLES;
  m_vertex_vec.resize(3);
  m_border_vertex_vec.resize(3);

  calculateVertices();
}

DrawTriangle::~DrawTriangle() {

}

void DrawTriangle::calculateVertices() {
  long inc = 1;

  float min_x = -1 * inc;
  float max_x = inc;
  float min_y = min_x;
  float max_y = inc;

  float vertices[3][2] = {
    { min_x, min_y },
    { x(), max_y },
    { max_x, min_y}
  };

  float border_vertices[3][2] = {
    { --min_x, --min_y },
    { x(), ++max_y },
    { ++max_x, min_y}
  };

  m_vertex_vec[0].setX(vertices[0][0]);
  m_vertex_vec[0].setY(vertices[0][1]);
  m_vertex_vec[0].setZ(0.0);
  m_vertex_vec[1].setX(vertices[1][0]);
  m_vertex_vec[1].setY(vertices[1][1]);
  m_vertex_vec[1].setZ(0.0);
  m_vertex_vec[2].setX(vertices[2][0]);
  m_vertex_vec[2].setY(vertices[2][1]);
  m_vertex_vec[2].setZ(0.0);

  m_border_vertex_vec[0].setX(border_vertices[0][0]);
  m_border_vertex_vec[0].setY(border_vertices[0][1]);
  m_border_vertex_vec[0].setZ(0.0);
  m_border_vertex_vec[1].setX(border_vertices[1][0]);
  m_border_vertex_vec[1].setY(border_vertices[1][1]);
  m_border_vertex_vec[1].setZ(0.0);
  m_border_vertex_vec[2].setX(border_vertices[2][0]);
  m_border_vertex_vec[2].setY(border_vertices[2][1]);
  m_border_vertex_vec[2].setZ(0.0);
}
