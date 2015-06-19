#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_TRIANGLE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_TRIANGLE_H

#include "view/gui/draw_element/draw_primitive/draw_primitive.h"

class DrawTriangle : public DrawPrimitive {
public:
  DrawTriangle(long x, long y, QColor color, QColor border_color);
  virtual ~DrawTriangle();

  virtual bool hitTest(long screen_x, long screen_y);

protected:
  void calculateVertices();
};

#endif
