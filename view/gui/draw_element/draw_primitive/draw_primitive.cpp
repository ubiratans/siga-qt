#include "view/gui/draw_element/draw_primitive/draw_primitive.h"

DrawPrimitive::DrawPrimitive(long x, long y, QColor &color, QColor &border_color, QString label)
  : m_x(x), m_y(y), m_color(color), m_border_color(border_color), m_label(label), m_scale(1.0), m_rotation_angle_degree(0.0)
{

}

DrawPrimitive::~DrawPrimitive() {
}

QString DrawPrimitive::label() {
  return m_label;
}

void DrawPrimitive::setLabel(QString &label) {
  m_label = label;
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

long DrawPrimitive::x() {
  return m_x;
}

void DrawPrimitive::setX(long x) {
  m_x = x;

  calculateVertices();
}

long DrawPrimitive::y() {
  return m_y;
}

void DrawPrimitive::setY(long y) {
  m_y = y;

  calculateVertices();
}

void DrawPrimitive::setPosition(long x, long y) {
  m_x = x;
  m_y = y;

  calculateVertices();
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

const std::vector<std::pair<long, long> > &DrawPrimitive::vertexVector() {
  return m_vertex_vec;
}
