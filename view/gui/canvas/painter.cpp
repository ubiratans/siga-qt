#include "view/gui/canvas/painter.h"

Painter::Painter(QGLWidget &widget) : m_gl_widget(&widget) {

}

void Painter::drawElement(DrawElement &element) {
  for (auto primitive : element.primitives()) {
    drawPrimitive(*primitive);
  }
}

void Painter::drawPrimitive(DrawPrimitive &primitive) {

}
