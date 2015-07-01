#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

DrawPrimitive::DrawPrimitive(double x, double y, QColor &color, QColor &border_color, QString label)
  : m_x(x), m_y(y), m_color(color), m_border_color(border_color), m_label(label),
    m_scale(1.0), m_rotation_angle_degree(0.0), m_enable_border(true)
{

}

DrawPrimitive::~DrawPrimitive() {
}

QColor DrawPrimitive::color() {
  return m_color;
}

void DrawPrimitive::setColor(int r, int g, int b, int alpha) {
  m_color = QColor(r, g, b, alpha);
}

void DrawPrimitive::setColor(QColor &color) {
  m_color = color;
}

QColor DrawPrimitive::borderColor() {
  return m_border_color;
}

void DrawPrimitive::setBorderColor(int r, int g, int b, int alpha) {
  m_border_color = QColor(r, g, b, alpha);
}

void DrawPrimitive::setBorderColor(QColor &color) {
  m_border_color = color;
}

GLenum DrawPrimitive::glPrimitive() {
  return m_gl_primitive;
}

GLenum DrawPrimitive::glBorderPrimitive() {
  return m_gl_border_primitive;
}

bool DrawPrimitive::containBorder() {
  return m_enable_border;
}

void DrawPrimitive::enableBorder(bool enable) {
  m_enable_border = enable;
}

double DrawPrimitive::x() {
  return m_x;
}

void DrawPrimitive::setX(double x) {
  m_x = x;
}

double DrawPrimitive::y() {
  return m_y;
}

void DrawPrimitive::setY(double y) {
  m_y = y;
}

void DrawPrimitive::setPosition(double x, double y) {
  m_x = x;
  m_y = y;
}

double DrawPrimitive::scale() {
  return m_scale;
}

void DrawPrimitive::setScale(double scale) {
  m_scale = scale;
}

double DrawPrimitive::rotation() {
  return m_rotation_angle_degree;
}

void DrawPrimitive::setRotation(double angle_degree) {
  m_rotation_angle_degree = angle_degree;
}

const QVector<QVector3D> &DrawPrimitive::vertexVector() {
  return m_vertex_vec;
}

void DrawPrimitive::calculateVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  computeVertices(screen_world_width_proportion, screen_world_height_proportion);

  applyTransformations();
}

void DrawPrimitive::applyTransformations() {
  QMatrix4x4 model_view_matrix;
  model_view_matrix.setToIdentity();

  bool execute_rotation = (int(m_rotation_angle_degree / 360) * 360.0 == m_rotation_angle_degree? false: true);
  bool execute_scale = (m_scale != 1.0? true: false);

  if (execute_scale) {
    model_view_matrix.translate(-1.0 * x(), -1.0 * y(), 0.0);

    model_view_matrix.scale(m_scale, m_scale);
  }

  if (execute_rotation) {
    model_view_matrix.translate(x(), y(), 0.0);

    model_view_matrix.rotate(rotation(), 0.0, 0.0, 1.0);

    model_view_matrix.translate(-x(), -y(), 0.0);
  }

  int i = 0;

  for (auto vertex : vertexVector()) {
    m_vertex_vec[i++] = model_view_matrix * vertex;
  }
}
