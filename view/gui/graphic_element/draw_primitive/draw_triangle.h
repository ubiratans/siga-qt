#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_TRIANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_TRIANGLE_H

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class DrawTriangle : public DrawPrimitive {
public:
  DrawTriangle(double x, double y, QColor color, QColor border_color, double edge_size = 10.0);
  virtual ~DrawTriangle();

  bool hitTest(double x, double y);
  bool hitTest(QRect &rect);

  void setEdgeSize(double size);

private:
  double sign(QVector3D &point, QVector3D &triangle_vertex, QVector3D &triangle_vertex_2);
  virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

  double m_size;
};

#endif
