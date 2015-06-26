#ifndef VIEW_GUI_CANVAS_DRAW_ELEMENT_DRAW_PRIMITIVE_H
#define VIEW_GUI_CANVAS_DRAW_ELEMENT_DRAW_PRIMITIVE_H

#include <QColor>
#include <QString>
#include <QtOpenGL>
#include <QVector2D>

class DrawPrimitive {
public:
  DrawPrimitive(float x, float y, QColor &color, QColor &border_color, QString label = "");
  virtual ~DrawPrimitive();

  QColor color();
  void setColor(int r, int g, int b, int alpha);
  void setColor(QColor &color);

  QColor borderColor();
  void setBorderColor(int r, int g, int b, int alpha);
  void setBorderColor(QColor &color);

  GLenum glPrimitive();
  GLenum glBorderPrimitive();

  virtual bool containBorder();
  virtual bool enableBorder(bool enable);

  const QVector< QVector3D >& borderVertexVector();

  float x();
  void setX(float x);

  float y();
  void setY(float y);

  void setPosition(float x, float y);

  double scale();
  void setScale(double scale);

  double rotation();
  void setRotation(double angle_degree);

  const QVector< QVector3D >& vertexVector();

 virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) = 0;

protected:
  QVector< QVector3D > m_vertex_vec;
  QVector< QVector3D > m_border_vertex_vec;

  GLenum m_gl_primitive;
  GLenum m_gl_border_primitive;

  float m_x;
  float m_y;

  double m_scale;
  double m_rotation_angle_degree;

  double m_last_zoom_factor;

  QColor m_color;
  QColor m_border_color;

  QString m_label;
  bool m_enable_border;
};

#endif
