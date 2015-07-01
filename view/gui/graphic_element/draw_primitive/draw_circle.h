#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class DrawCircle : public DrawPrimitive {
public:
  DrawCircle(double x, double y, QColor color, QColor border_color, double radius = 10.0);
  virtual ~DrawCircle();

  void setRadius(double radius);

  bool hitTest(double x, double y);
  bool hitTest(QRect &rect);

private:
  virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

  double m_radius;
  double m_radius_world;
};

#endif
