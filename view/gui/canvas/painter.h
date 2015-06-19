#ifndef VIEW_GUI_CANVAS_PAINTER_H
#define VIEW_GUI_CANVAS_PAINTER_H

#include "view/gui/draw_element/draw_element.h"
#include "view/gui/draw_element/draw_primitive/draw_primitive.h"

class QGLWiget;

class Painter {
public:
  Painter(QGLWidget &widget);

  void drawElement(DrawElement &element);

protected:
  void drawPrimitive(DrawPrimitive &primitive);

  QGLWidget *m_gl_widget;
};

#endif
