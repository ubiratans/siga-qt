#include "view/gui/canvas/main_canvas.h"

#include "core/coordinate_system/wgs_84.h"

MainCanvas::MainCanvas(CanvasElementManager &manager, QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

}

const CoordinateSystem * const MainCanvas::coordinateSystem() {
  return m_coordinate_system;
}

void MainCanvas::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  qglClearColor(QColor(Qt::white));
  m_shader_program.addShaderFromSourceFile(QGLShader::Vertex, "shaders/vertex_shader.h");
  m_shader_program.addShaderFromSourceFile(QGLShader::Fragment, "shaders/fragment_shader.h");
  m_shader_program.link();

  //QMatrix4x4::ortho()
}
