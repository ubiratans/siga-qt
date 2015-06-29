#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_TRIANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_TRIANGLE_H

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class DrawTriangle : public DrawPrimitive {
public:
  DrawTriangle(float x, float y, QColor color, QColor border_color);
  virtual ~DrawTriangle();

  virtual void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);
};

#endif
