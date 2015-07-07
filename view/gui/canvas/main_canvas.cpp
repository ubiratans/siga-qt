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

  node = new GraphicNode(
        0,
        GraphicNodeStruct(NodeType::Basin,
                          0.0,
                          2.0,
                          m_coordinate_system->width() / (m_max_width * m_zoom),
                          m_coordinate_system->height() / (m_max_height * m_zoom),
                          0.0,
                          1.0
                          )
        );

  node->setScale(5.0);


  GraphicNode *node2 = new GraphicNode(
        0,
        GraphicNodeStruct(NodeType::Basin,
                          8.0,
                          2.0,
                          m_coordinate_system->width() / (m_max_width * m_zoom),
                          m_coordinate_system->height() / (m_max_height * m_zoom),
                          0.0,
                          1.0
                          )
        );

  GraphicNode *node3 = new GraphicNode(
        0,
        GraphicNodeStruct(NodeType::Demand,
                          16.0,
                          2.0,
                          m_coordinate_system->width() / (m_max_width * m_zoom),
                          m_coordinate_system->height() / (m_max_height * m_zoom),
                          0.0,
                          1.0
                          )
        );

  node3->setScale(3.0);

  GraphicNode *node4 = new GraphicNode(
        0,
        GraphicNodeStruct(NodeType::Junction,
                          24.0,
                          2.0,
                          m_coordinate_system->width() / (m_max_width * m_zoom),
                          m_coordinate_system->height() / (m_max_height * m_zoom),
                          0.0,
                          1.0
                          )
        );

  GraphicNode *node5 = new GraphicNode(
        0,
        GraphicNodeStruct(NodeType::Lake,
                          32.0,
                          2.0,
                          m_coordinate_system->width() / (m_max_width * m_zoom),
                          m_coordinate_system->height() / (m_max_height * m_zoom),
                          0.0,
                          1.0
                          )
        );

  node->calculateVertices();
  node2->calculateVertices();
  node3->calculateVertices();
  node4->calculateVertices();
  node5->calculateVertices();

  drawElement(*node);
  drawElement(*node2);
  drawElement(*node3);
  drawElement(*node4);
  drawElement(*node5);

  m_shader_program.release();

  glFlush();
  //
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
    // perform hit tests
    int x = 10;
    x = 11;
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
    drawPrimitive(*primitive);
  }
}

void MainCanvas::drawPrimitive(DrawPrimitive &primitive) {
  m_shader_program.setAttributeArray("vertex", primitive.vertexVector().constData());
  m_shader_program.enableAttributeArray("vertex");

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  m_shader_program.setUniformValue("color", primitive.color());

  // draw the vertices
  glDrawArrays(primitive.glPrimitive(), 0, primitive.vertexVector().size());

  if (primitive.containBorder()) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float line_width;
    glGetFloatv(GL_LINE_WIDTH, &line_width);

    // TODO: Add the border_width to DrawPrimitive
    glLineWidth(line_width /*+ 0.5*/);
    m_shader_program.setUniformValue("color", primitive.borderColor());
    glDrawArrays(primitive.glBorderPrimitive(), 0, primitive.vertexVector().size());

    glLineWidth(line_width);
  }

  m_shader_program.disableAttributeArray("vertex");
}
