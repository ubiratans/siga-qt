#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class DrawRectangle : public DrawPrimitive {
public:
  DrawRectangle(double x, double y, QColor color, QColor border_color);
  virtual ~DrawRectangle();

  bool hitTest(double x, double y);
  bool hitTest(QRect &rect);

  void setDimensions(double width_pixels, double height_pixels);

private:
    virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

  double m_width;
  double m_height;
};

#endif
