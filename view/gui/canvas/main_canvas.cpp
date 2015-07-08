#include "view/gui/canvas/main_canvas.h"

#include <QDesktopWidget>

#include "core/coordinate_system/wgs_84.h"
#include "view/gui/canvas/painter.h"
#include "view/gui/graphic_element/graphic_node.h"
#include "view/gui/canvas/shaders/fragment_shader.h"
#include "view/gui/canvas/shaders/vertex_shader.h"

MainCanvas::MainCanvas(/*CanvasElementManager &manager,*/CoordinateSystem &coord_system, QWidget *parent)
  : QOpenGLWidget(parent), m_coordinate_system(&coord_system)
{
  m_background_color = QColor(Qt::white);

  setMouseTracking(true);
  makeCurrent();

  m_pos_x = -10.0;
  m_pos_y = -10.0;

  // TODO: Improve the calculation of max width and height
  // Hint: maybe the screen resolution can be taken into account
  m_max_width = m_coordinate_system->width() * 10;
  m_max_height = m_coordinate_system->height() * 10;

  m_zoom = 1.0;
  m_projection_matrix.setToIdentity();

  m_mouse_move_refresh_msecs = 4;

  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(emitMouseMoveSignal()));

  node = new GraphicNode(
        0,
        GraphicNodeStruct(NodeType::Reservoir,
                          0.0,
                          2.0,
                          m_coordinate_system->width() / (m_max_width * m_zoom),
                          m_coordinate_system->height() / (m_max_height * m_zoom),
                          0.0,
                          1.0
                          )
        );

  node->calculateVertices();
}

MainCanvas::~MainCanvas() {
  delete m_timer;
}

const CoordinateSystem * const MainCanvas::coordinateSystem() {
  return m_coordinate_system;
}

std::pair<double, double> MainCanvas::screenToCoordinateSystem(int x, int y) {
  double x_world = m_pos_x + m_coordinate_system->width() / (m_max_width * m_zoom) * x;
  double y_world = m_pos_y + m_coordinate_system->height() / (m_max_height * m_zoom) * (height() - 1 - y);

  return std::make_pair(x_world, y_world);
}

QGLShaderProgram& MainCanvas::shaderProgram() {
  return m_shader_program;
}

void MainCanvas::initializeGL() {
  if (initializeOpenGLFunctions()) {
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool load_shaders = m_shader_program.addShaderFromSourceCode(QGLShader::Vertex, kCanvasVertexShader)
        && m_shader_program.addShaderFromSourceCode(QGLShader::Fragment, kCanvasFragmentShader)
        && m_shader_program.link();

    if (load_shaders) {
      glClearColor(m_background_color.redF(), m_background_color.greenF(), m_background_color.blueF(), m_background_color.alphaF());
    }
  }
}

void MainCanvas::paintGL() {
  if (!isValid()) {
    return;
  }

  glClear(GL_COLOR_BUFFER_BIT);

  m_shader_program.bind();
  m_shader_program.setUniformValue("projection_matrix", m_projection_matrix);

  drawElement(*node);

  m_shader_program.release();

  glFlush();
}

void MainCanvas::resizeGL(int width, int height) {
  m_projection_matrix.setToIdentity();

  double right = m_pos_x + (m_coordinate_system->width() / (m_max_width * m_zoom)) * (width - 1);
  double top = m_pos_y + (m_coordinate_system->height() / (m_max_height * m_zoom)) * (height - 1);

  m_projection_matrix.ortho(m_pos_x, right, m_pos_y, top, 0.0, 1.0);

  glViewport(0, 0, width-1, height-1);
}

void MainCanvas::mouseMoveEvent(QMouseEvent *event) {
  GLubyte data[4];
  std::pair< double, double > current_world_pos = screenToCoordinateSystem(event->x(), event->y());

  m_last_mouse_pos_x = current_world_pos.first;
  m_last_mouse_pos_y = current_world_pos.second;

  m_timer->start(m_mouse_move_refresh_msecs);

  QColor color_pos = QColor(data[0], data[1], data[2]);

  if (node->hitTest(current_world_pos.first, current_world_pos.second)) {
    if (!node->isSelected()) {
      // perform hit tests
      node->setSelected(true);

      update();
    }
  }

  else if (node->isSelected()) {
    node->setSelected(false);

    update();
  }
}

bool MainCanvas::hasToUpdateVertices() {
  return m_has_to_recalculate_elements_vertices;
}

void MainCanvas::emitMouseMoveSignal() {
  emit(mouseMoved(m_last_mouse_pos_x, m_last_mouse_pos_y));
  m_timer->stop();
}

void MainCanvas::drawElement(GraphicElement &element, bool recalculate_vertices) {
  if (recalculate_vertices || !element.verticesUpdated()) {
    element.calculateVertices();
  }

  for (auto primitive : element.primitives()) {
    drawPrimitive(*primitive, element.isSelected());
  }
}

void MainCanvas::drawPrimitive(DrawPrimitive &primitive, bool selected) {
  m_shader_program.setAttributeArray("vertex", primitive.vertexVector().constData());
  m_shader_program.enableAttributeArray("vertex");

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  QColor color = (!selected? primitive.color(): primitive.selectionColor());
  m_shader_program.setUniformValue("color", color);

  // draw the vertices
  glDrawArrays(primitive.glPrimitive(), 0, primitive.vertexVector().size());

  if (primitive.containBorder()) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float line_width;
    glGetFloatv(GL_LINE_WIDTH, &line_width);

    // TODO: Add the border_width to DrawPrimitive
    glLineWidth(line_width + 0.5);
    color = (!selected? primitive.borderColor(): primitive.selectionBorderColor());
    m_shader_program.setUniformValue("color", color);
    glDrawArrays(primitive.glBorderPrimitive(), 0, primitive.vertexVector().size());

    glLineWidth(line_width);
  }

  m_shader_program.disableAttributeArray("vertex");
}
