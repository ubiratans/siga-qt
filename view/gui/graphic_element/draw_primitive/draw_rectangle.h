#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class DrawRectangle : public DrawPrimitive {
public:
  DrawRectangle(double x, double y, QColor color, QColor border_color);
  virtual ~DrawRectangle();

  bool hitTest(double x, double y);
  bool hitTest(QRect &rect);

  int width();
  int height();

  void setDimensions(int width_pixels, int height_pixels);

private:
  virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

  int m_width;
  int m_height;
};

#endif
