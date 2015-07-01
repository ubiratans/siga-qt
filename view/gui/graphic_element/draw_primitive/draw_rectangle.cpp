#include "view/gui/graphic_element/draw_primitive/draw_rectangle.h"

DrawRectangle::DrawRectangle(double x, double y, QColor color, QColor border_color)
  : DrawPrimitive(x, y, color, border_color)
{
  m_gl_primitive = GL_QUADS;
  m_gl_border_primitive = GL_QUADS;
  m_vertex_vec.resize(4);

  m_width = m_height = 6.0;
}

DrawRectangle::~DrawRectangle() {

}

bool DrawRectangle::hitTest(double x, double y) {
  return false;
}

bool DrawRectangle::hitTest(QRect &rect) {
  return false;
}

void DrawRectangle::setDimensions(double width_pixels, double height_pixels) {
  m_width = width_pixels;
  m_height = height_pixels;
}

void DrawRectangle::computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  double y_inc = m_height * screen_world_height_proportion;
  double x_inc = m_width * screen_world_width_proportion;

  double min_x = -1 * x_inc + x();
  double max_x = x_inc + x();

  double min_y = -1 * y_inc + y();
  double max_y = y_inc + y();

  y_inc = (m_height) * screen_world_height_proportion;
  x_inc = (m_width) * screen_world_width_proportion;

  double vertices[4][2] = {
    { max_x, max_y },
    { max_x, min_y },
    { min_x, min_y},
    { min_x, max_y }
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
  m_vertex_vec[3].setX(vertices[3][0]);
  m_vertex_vec[3].setY(vertices[3][1]);
  m_vertex_vec[3].setZ(0.0);
}
