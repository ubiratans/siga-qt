#ifndef VIEW_GUI_CANVAS_DRAW_ELEMENT_DRAW_PRIMITIVE_H
#define VIEW_GUI_CANVAS_DRAW_ELEMENT_DRAW_PRIMITIVE_H

#include <QColor>
#include <QString>
#include <QtOpenGL>
#include <QVector2D>
#include <QRect>

class DrawPrimitive {
public:
  DrawPrimitive(double x, double y, QColor &color, QColor &border_color, QString label = "");
  virtual ~DrawPrimitive();

  QColor color();
  void setColor(int r, int g, int b, int alpha);
  void setColor(QColor &color);

  QColor borderColor();
  void setBorderColor(int r, int g, int b, int alpha);
  void setBorderColor(QColor &color);

  QColor selectionColor();
  void setSelectionColor(int r, int g, int b, int alpha);
  void setSelectionColor(QColor &color);

  QColor selectionBorderColor();
  void setSelectionBorderColor(int r, int g, int b, int alpha);
  void setSelectionBorderColor(QColor &color);

  virtual bool hitTest(double x, double y) = 0;
  virtual bool hitTest(QRect &rect) = 0;

  GLenum glPrimitive();
  GLenum glBorderPrimitive();

  virtual bool containBorder();
  virtual void enableBorder(bool enable);

  double x();
  void setX(double x);

  double y();
  void setY(double y);

  void setPosition(double x, double y);

  double scale();
  void setScale(double scale);

  double rotation();
  void setRotation(double angle_degree);

  const QVector< QVector3D >& vertexVector();

  void calculateVertices(double screen_world_width_proportion, double screen_world_height_proportion);

  void applyTransformations();

protected:
    virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) = 0;

  QMatrix4x4 m_model_view_matrix;

  QVector< QVector3D > m_vertex_vec;

  GLenum m_gl_primitive;
  GLenum m_gl_border_primitive;

  double m_x;
  double m_y;

  double m_scale;
  double m_rotation_angle_degree;

  double m_last_zoom_factor;

  QColor m_color;
  QColor m_border_color;

  QColor m_color_selection;
  QColor m_border_color_selection;

  QString m_label;
  bool m_enable_border;
};

#endif
