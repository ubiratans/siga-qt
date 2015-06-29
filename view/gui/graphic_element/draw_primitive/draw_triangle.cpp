#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"

DrawTriangle::DrawTriangle(float x, float y, QColor color, QColor border_color)
  : DrawPrimitive(x, y, color, border_color)
{
  m_gl_primitive = GL_TRIANGLES;
  m_gl_border_primitive = GL_TRIANGLES;
  m_vertex_vec.resize(3);
  m_border_vertex_vec.resize(3);
}

DrawTriangle::~DrawTriangle() {

}

void DrawTriangle::computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  long inc = 10;

  float y_inc = inc * screen_world_height_proportion;
  float x_inc = inc * screen_world_width_proportion;

  float min_x = -1 * x_inc + x();
  float max_x = x_inc + x();

  float min_y = -1 * y_inc + y();
  float max_y = y_inc + y();

  y_inc = ++inc * screen_world_height_proportion;
  x_inc = inc * screen_world_width_proportion;

  float border_min_x = -1 * x_inc + x();
  float border_max_x = x_inc + x();

  float border_min_y = -1 * y_inc + y();
  float border_max_y = y_inc + y();

  float vertices[3][2] = {
    { min_x, min_y },
    { x(), max_y },
    { max_x, min_y}
  };

  float border_vertices[3][2] = {
    { border_min_x, border_min_y },
    { x(), border_max_y },
    { border_max_x, border_min_y}
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
