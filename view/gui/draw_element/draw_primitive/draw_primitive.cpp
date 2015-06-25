#include "view/gui/draw_element/draw_primitive/draw_primitive.h"

DrawPrimitive::DrawPrimitive(float x, float y, QColor &color, QColor &border_color, QString label)
  : m_x(x), m_y(y), m_color(color), m_border_color(border_color), m_label(label),
    m_scale(1.0), m_rotation_angle_degree(0.0), m_enable_border(true)
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

bool DrawPrimitive::containBorder() {
  return m_enable_border;
}

bool DrawPrimitive::enableBorder(bool enable) {
  m_enable_border = enable;
}

const QVector<QVector3D> &DrawPrimitive::borderVertexVector() {
  return m_border_vertex_vec;
}

float DrawPrimitive::x() {
  return m_x;
}

void DrawPrimitive::setX(float x) {
  m_x = x;

  calculateVertices();
}

float DrawPrimitive::y() {
  return m_y;
}

void DrawPrimitive::setY(float y) {
  m_y = y;

  calculateVertices();
}

void DrawPrimitive::setPosition(float x, float y) {
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

const QVector<QVector3D> &DrawPrimitive::vertexVector() {
  return m_vertex_vec;
}
