#include "view/gui/graphic_element/draw_primitive/draw_triangle.h"

DrawTriangle::DrawTriangle(double x, double y, QColor color, QColor border_color, double edge_size)
  : DrawPrimitive(x, y, color, border_color), m_size(edge_size)
{
  m_gl_primitive = GL_TRIANGLES;
  m_gl_border_primitive = GL_TRIANGLES;
  m_vertex_vec.resize(3);
}

DrawTriangle::~DrawTriangle() {

}

bool DrawTriangle::hitTest(double x, double y) {
  QVector3D point(x, y, 0.0);

  bool b1 = sign(point, m_vertex_vec[0], m_vertex_vec[1]) < 0.0;
  bool b2 = sign(point, m_vertex_vec[1], m_vertex_vec[2]) < 0.0;
  bool b3 = sign(point, m_vertex_vec[2], m_vertex_vec[0]) < 0.0;

  return ((b1 == b2) && (b2 == b3));
}

bool DrawTriangle::hitTest(QRect &rect) {
  return false;
}

void DrawTriangle::setEdgeSize(double size) {
  m_size = size;
}

double DrawTriangle::sign(QVector3D &point, QVector3D &triangle_vertex, QVector3D &triangle_vertex_2) {
  return (point.x() - triangle_vertex_2.x()) *
      (triangle_vertex.y() - triangle_vertex_2.y()) - (triangle_vertex.x() - triangle_vertex_2.x()) *
      (point.y() - triangle_vertex_2.y());
}

void DrawTriangle::computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  long inc = m_size;

  double y_inc = inc * screen_world_height_proportion;
  double x_inc = inc * screen_world_width_proportion;

  double min_x = -1 * x_inc + x();
  double max_x = x_inc + x();

  double min_y = -1 * y_inc + y();
  double max_y = y_inc + y();

  double vertices[3][2] = {
    { min_x, min_y },
    { x(), max_y },
    { max_x, min_y}
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
}
