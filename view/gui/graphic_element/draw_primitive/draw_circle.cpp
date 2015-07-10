#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

#include <cmath>
#include <QLineF>

DrawCircle::DrawCircle(double x, double y, QColor color, QColor border_color, int radius)
  : DrawPrimitive(x, y, color, border_color), m_radius(radius)
{
  m_gl_primitive = GL_TRIANGLE_FAN;
  m_gl_border_primitive = GL_TRIANGLE_STRIP;
}

DrawCircle::~DrawCircle() {

}

void DrawCircle::setRadius(int radius) {
  m_radius = radius;
}

int DrawCircle::radius() {
  return m_radius * m_scale;
}

bool DrawCircle::hitTest(double x, double y) {
  double radius_world = m_radius_world * m_scale;

  bool ret = QLineF(QPointF(m_x, m_y), QPointF(x, y)).length() <= radius_world;

  return ret;
}

bool DrawCircle::hitTest(QRect &rect) {
  return false;
}

void DrawCircle::computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  double pi = 3.14159265;
  m_radius_world = m_radius * (screen_world_width_proportion + screen_world_height_proportion) / 2.0;
  double delta_theta = 0.01;

  m_vertex_vec.clear();
  for (double angle = 0.0; angle < 2.0*pi; angle += delta_theta) {
    double x = cos(angle);
    double y = sin(angle);

    m_vertex_vec.push_back(QVector3D(x * m_radius_world + m_x, y * m_radius_world + m_y, 0.0));
  }
}

