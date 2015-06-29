#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_RECTANGLE_H

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class DrawRectangle : public DrawPrimitive {
public:
  DrawRectangle(float x, float y, QColor color, QColor border_color);
  virtual ~DrawRectangle();

  void setDimensions(float width_pixels, float height_pixels);

  virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

private:
  float m_width;
  float m_height;
};

#endif
