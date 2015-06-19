#ifndef VIEW_GUI_CANVAS_DRAW_ELEMENT_DRAW_PRIMITIVE_H
#define VIEW_GUI_CANVAS_DRAW_ELEMENT_DRAW_PRIMITIVE_H

#include <QColor>
#include <QString>
#include <QtOpenGL>

class DrawPrimitive {
public:
  DrawPrimitive(long x, long y, QColor &color, QColor &border_color, QString label = "");
  virtual ~DrawPrimitive();

  QString label();
  void setLabel(QString &label);

  QColor color();
  void setColor(int r, int g, int b, int alpha);
  void setColor(QColor &color);

  QColor borderColor();
  void setBorderColor(int r, int g, int b, int alpha);
  void setBorderColor(QColor &color);

  GLenum glPrimitive();
  GLenum glBorderPrimitive();

  long x();
  void setX(long x);

  long y();
  void setY(long y);

  void setPosition(long x, long y);

  double scale();
  void setScale(double scale);

  double rotation();
  void setRotation(double angle_degree);

  virtual bool hitTest(long screen_x, long screen_y) = 0;

  const std::vector< std::pair< long, long > >& vertexVector();

protected:
  virtual void calculateVertices() = 0;

  std::vector< std::pair< long, long > > m_vertex_vec;
  GLenum m_gl_primitive;
  GLenum m_gl_border_primitive;

  long m_x;
  long m_y;

  double m_scale;
  double m_rotation_angle_degree;

  QColor m_color;
  QColor m_border_color;

  QString m_label;
};

#endif
