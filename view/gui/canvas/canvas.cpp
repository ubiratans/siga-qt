#include "view/gui/canvas/canvas.h"

Canvas::Canvas(CanvasElementManager &manager, QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

}
