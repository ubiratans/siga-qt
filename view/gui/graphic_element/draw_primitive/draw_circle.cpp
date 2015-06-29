#include "view/gui/graphic_element/draw_primitive/draw_circle.h"

#include <cmath>

DrawCircle::DrawCircle(float x, float y, QColor color, QColor border_color)
  : DrawPrimitive(x, y, color, border_color)
{
  m_gl_primitive = GL_TRIANGLE_FAN;
  m_gl_border_primitive = GL_TRIANGLE_STRIP;
}

DrawCircle::~DrawCircle() {

}

void DrawCircle::computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  float pi = 3.14159265;
  float radius_x = 10.0 * screen_world_width_proportion;
  float radius_y = 10.0 * screen_world_height_proportion;
  float delta_theta = 0.01;

  m_vertex_vec.clear();
  m_border_vertex_vec.clear();

  for (float angle = 0.0; angle < 2.0*pi; angle += delta_theta) {
    float x = m_x + cos(angle);
    float y = m_y + sin(angle);

    m_vertex_vec.push_back(QVector3D(x * radius_x, y * radius_y, 0.0));
    m_border_vertex_vec.push_back(QVector3D(x * (radius_x +1), y * (radius_y+1), 0.0));
  }
}

