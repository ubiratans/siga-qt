#include "view/gui/canvas/main_canvas.h"

#include <QDesktopWidget>

#include "core/coordinate_system/wgs_84.h"
#include "view/gui/canvas/painter.h"
#include "view/gui/draw_element/draw_node.h"
#include "view/gui/canvas/shaders/fragment_shader.h"
#include "view/gui/canvas/shaders/vertex_shader.h"

MainCanvas::MainCanvas(/*CanvasElementManager &manager,*/CoordinateSystem &coord_system, QWidget *parent)
  : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent), m_coordinate_system(&coord_system)
{
  m_pos_x = -30.0;
  m_pos_y = -15.0;
  m_max_width = m_coordinate_system->width() * 10;
  m_max_height = m_coordinate_system->height() * 10;
  m_zoom = 1.0;
  m_projection_matrix.setToIdentity();
}

MainCanvas::~MainCanvas() {
}

const CoordinateSystem * const MainCanvas::coordinateSystem() {
  return m_coordinate_system;
}

QGLShaderProgram& MainCanvas::shaderProgram() {
  return m_shader_program;
}

void MainCanvas::initializeGL() {
  bool load_shaders = m_shader_program.addShaderFromSourceCode(QGLShader::Vertex, kCanvasVertexShader)
                     && m_shader_program.addShaderFromSourceCode(QGLShader::Fragment, kCanvasFragmentShader)
                      && m_shader_program.link();

  if (load_shaders) {
    qglClearColor(QColor(Qt::white));
  }
}

void MainCanvas::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);

  bool x = m_shader_program.bind();
  m_shader_program.setUniformValue("projection_matrix", m_projection_matrix);

  DrawNode *node = new DrawNode(0, NodeType::Reservoir, 0.0, 0.0, 1.5);
  node->computeVertices((m_coordinate_system->width() / (m_max_width * m_zoom)), (m_coordinate_system->height() / (m_max_height * m_zoom)));

  drawElement(*node);

  m_shader_program.release();


  glFlush();
  //
}

void MainCanvas::resizeGL(int width, int height) {
  m_projection_matrix.setToIdentity();

  double right = m_pos_x + (m_coordinate_system->width() / (m_max_width * m_zoom)) * (width - 1);
  double top = m_pos_y + (m_coordinate_system->height() / (m_max_height * m_zoom)) * (height - 1);

  /*glOrtho(
              m_pos_x,
              right,
              m_pos_y,
              top,
              0.0,
              1.0
          );*/

  //m_projection_matrix.translate(5.0, 0.5, 0.0);
  m_projection_matrix.ortho(m_pos_x, right, m_pos_y, top, 0.0, 1.0);

  glViewport(0, 0, width-1, height-1);
}


void MainCanvas::drawElement(DrawElement &element) {
  for (auto primitive : element.primitives()) {
    drawPrimitive(*primitive);
  }
}

void MainCanvas::drawPrimitive(DrawPrimitive &primitive) {
  QMatrix4x4 model_view_matrix;
  model_view_matrix.setToIdentity();

  m_shader_program.setAttributeArray("vertex", primitive.vertexVector().constData());
  m_shader_program.enableAttributeArray("vertex");

  bool rotate = (int(primitive.rotation() / 360) * 360 == primitive.rotation()? false: true);
  bool scale = (primitive.scale() != 1.0? true: false);

  if (rotate) {
    model_view_matrix.translate(primitive.x(), primitive.y(), 0.0);
    model_view_matrix.rotate(primitive.rotation(), 0.0, 0.0, 1.0);
    model_view_matrix.translate(-primitive.x(), -primitive.y(), 0.0);
  }

  if (scale) {
    model_view_matrix.translate(-primitive.x(), -primitive.y(), 0.0);
    model_view_matrix.scale(primitive.scale(), primitive.scale(), 1.0);
    model_view_matrix.translate(primitive.x(), primitive.y(), 0.0);
  }

  model_view_matrix.translate(primitive.x(), primitive.y(), 0.0);

  m_shader_program.setUniformValue("model_view_matrix", model_view_matrix);

  if (primitive.containBorder()) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_shader_program.setUniformValue("color", primitive.borderColor());
    glDrawArrays(primitive.glBorderPrimitive(), 0, primitive.borderVertexVector().size());
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  m_shader_program.setUniformValue("color", primitive.color());
  glDrawArrays(primitive.glPrimitive(), 0, primitive.vertexVector().size());

  m_shader_program.disableAttributeArray("vertex");

}
