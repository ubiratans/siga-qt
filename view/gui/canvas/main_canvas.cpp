#include "view/gui/canvas/main_canvas.h"

#include <QDesktopWidget>

#include "core/coordinate_system/wgs_84.h"
#include "view/gui/canvas/painter.h"
#include "view/gui/graphic_element/graphic_node.h"
#include "view/gui/canvas/shaders/fragment_shader.h"
#include "view/gui/canvas/shaders/vertex_shader.h"
#include "view/gui/graphic_element/graphic_element_manager.h"
#include "view/gui/graphic_element/command/command_manager.h"
#include "view/gui/graphic_element/command/command_add.h"

MainCanvas::MainCanvas(GraphicElementManager &manager, CoordinateSystem &coord_system, QWidget *parent)
  : QOpenGLWidget(parent), m_coordinate_system(&coord_system), m_graphic_element_manager(&manager)
{
  init();
}

void MainCanvas::init() {
  m_background_color = QColor(Qt::white);
  m_off_limits_background_color = QColor(Qt::gray);
  m_command_manager = new CommandManager(32);

  setMouseTracking(true);
  makeCurrent();

  initZoomAndMatrix();
  initWindowPositionAndSize();
  initTimer();
}

void MainCanvas::initWindowPositionAndSize() {
  m_pos_x = -10.0;
  m_pos_y = -10.0;

  // TODO: Improve the calculation of max width and height
  // Hint: perharps the screen resolution can be taken into account
  QRect rec = QApplication::desktop()->screenGeometry();
  int height = rec.height();
  int width = rec.width();

  m_max_width = std::max(width * 4.0, m_coordinate_system->width() * 10);
  m_max_height = std::max(height * 4.0, m_coordinate_system->height() * 10);
}

void MainCanvas::initZoomAndMatrix() {
  m_zoom = 1.0;
  m_projection_matrix.setToIdentity();
}

void MainCanvas::initTimer() {
  m_mouse_move_refresh_msecs = 4;

  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(emitMouseMoveSignal()));
}

MainCanvas::~MainCanvas() {
  delete m_timer;
  delete m_command_manager;
}

CoordinateSystem* MainCanvas::coordinateSystem() {
  return m_coordinate_system;
}

double MainCanvas::coordinateWidthPerPixel() {
  double value = (m_coordinate_system->width()) / (m_max_width * m_zoom);

  return value;
}

double MainCanvas::coordinateHeightPerPixel() {
  double value = (m_coordinate_system->height()) / (m_max_height * m_zoom);

  return value;
}

std::pair<double, double> MainCanvas::screenToCoordinateSystem(int x, int y) {
  double x_world = m_pos_x + coordinateWidthPerPixel()  * x;
  double y_world = m_pos_y + coordinateHeightPerPixel() * (height() - 1 - y);

  return std::make_pair(x_world, y_world);
}

std::pair<int, int> MainCanvas::coordinateSystemToScreen(double x, double y) {
  int x_screen = (x - m_pos_x) / coordinateWidthPerPixel();
  int y_screen = height() - ((y - m_pos_y) / coordinateHeightPerPixel());

  return std::make_pair(x_screen, y_screen);
}

QGLShaderProgram& MainCanvas::shaderProgram() {
  return m_shader_program;
}

double MainCanvas::zoom() {
  return m_zoom;
}

bool MainCanvas::setZoom(double value) {
  if (value != 0.0 && value >= maxZoomOut() && value <= maxZoomIn()) {
    m_zoom = value;

    m_has_to_recalculate_elements_vertices = true;

    emitZoomUpdateSignal();

    return true;
  }

  return false;
}

bool MainCanvas::zoomOut() {
  return setZoom(m_zoom / 1.1);
}

double MainCanvas::maxZoomOut() {
  return 0.125;
}

bool MainCanvas::zoomIn() {
  return setZoom(m_zoom * 1.1);
}

double MainCanvas::maxZoomIn() {
  return 10.0;
}

void MainCanvas::initializeGL() {
  if (initializeOpenGLFunctions()) {
    bool load_shaders = m_shader_program.addShaderFromSourceCode(QGLShader::Vertex, kCanvasVertexShader)
        && m_shader_program.addShaderFromSourceCode(QGLShader::Fragment, kCanvasFragmentShader)
        && m_shader_program.link();
  }
}

void MainCanvas::paintGL() {
  if (!isValid()) {
    return;
  }

  QPainter painter(this);

  drawElements(painter);

  /*QFont font;
  font.setPointSize(10);
  font.setFamily("Monospace");

  painter.setFont(font);

  std::pair< int, int > pos = coordinateSystemToScreen(node->x(), node->y());

  QRect rect(pos.first - node->width()*4,
             pos.second + node->height() + font.pixelSize() + font.pointSize(),
             node->width()*8,
             font.pointSize() + 4);

  painter.drawText(rect, Qt::AlignCenter, "N1");

  painter.end();*/
}

void MainCanvas::resizeGL(int width, int height) {
  calculateProjectionMatrix(width, height);
}

void MainCanvas::calculateProjectionMatrix(int width, int height) {
  m_projection_matrix.setToIdentity();

  double right = m_pos_x + (coordinateWidthPerPixel()) * (width - 1);
  double top = m_pos_y + (coordinateHeightPerPixel()) * (height - 1);

  m_projection_matrix.ortho(m_pos_x, right, m_pos_y, top, 0.0, 1.0);
}

void MainCanvas::mouseMoveEvent(QMouseEvent *event) {
  GLubyte data[4];
  std::pair< double, double > current_world_pos = screenToCoordinateSystem(event->x(), event->y());

  m_last_mouse_pos_x = current_world_pos.first;
  m_last_mouse_pos_y = current_world_pos.second;

  m_timer->start(m_mouse_move_refresh_msecs);

  for (auto it : m_graphic_element_manager->graphicElementsMap()) {
    GraphicElement *graphic_element = it.second;

    if (graphic_element->hitTest(current_world_pos.first, current_world_pos.second)) {
      if (!graphic_element->isSelected()) {
        // perform hit tests
        graphic_element->setSelected(true);

        update();
      }
    }

    else if (graphic_element->isSelected()) {
      graphic_element->setSelected(false);

      update();
    }
  }
}

void MainCanvas::mouseDoubleClickEvent(QMouseEvent *event) {
  std::pair<double, double> pos = screenToCoordinateSystem(event->x(), event->y());

  if (pos.first < m_coordinate_system->left() ||
      pos.first > m_coordinate_system->right() ||
      pos.second < m_coordinate_system->bottom() ||
      pos.second > m_coordinate_system->top())
  {
    return;
  }

  GraphicNodeStruct st(
        NodeType::Reservoir,
        pos.first,
        pos.second,
        coordinateWidthPerPixel(),
        coordinateHeightPerPixel()
        );

  if (m_command_manager->execute(new CommandAdd(*m_graphic_element_manager, st))) {
    update();
  }
}

void MainCanvas::wheelEvent(QWheelEvent *event) {
  // TODO: implement a special zoom when the mouse is over an element, that zoom should consider the distance from the center of the element to the current mouse position
  std::pair< double, double > current_world_pos = screenToCoordinateSystem(event->x(), event->y());

  if (event->delta() < 0) {
    if (zoomOut()) {
      std::pair< double, double > new_world_pos = screenToCoordinateSystem(event->x(), event->y());

      m_pos_x = m_pos_x + (current_world_pos.first - new_world_pos.first);
      m_pos_y = m_pos_y + (current_world_pos.second - new_world_pos.second);

      // TODO: Put the calculateProjectionMatrix inside setZoom
      calculateProjectionMatrix(width(), height());

      update();
    }
  }

  else if (zoomIn()) {
    std::pair< double, double > new_world_pos = screenToCoordinateSystem(event->x(), event->y());

    m_pos_x = m_pos_x + (current_world_pos.first - new_world_pos.first);
    m_pos_y = m_pos_y + (current_world_pos.second - new_world_pos.second);

    // TODO: Put the calculateProjectionMatrix inside setZoom
    calculateProjectionMatrix(width(), height());

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

void MainCanvas::emitZoomUpdateSignal() {
  emit(zoomUpdated(m_zoom));
}

void MainCanvas::drawElements(QPainter &painter) {
  painter.beginNativePainting();
    glViewport(0, 0, width()-1, height()-1);

    glClearColor(m_off_limits_background_color.redF(),
                 m_off_limits_background_color.greenF(),
                 m_off_limits_background_color.blueF(),
                 m_off_limits_background_color.alphaF());
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shader_program.bind();
    m_shader_program.setUniformValue("projection_matrix", m_projection_matrix);

    drawPaintArea();

    for (auto it : m_graphic_element_manager->graphicElementsMap()) {
      GraphicElement *graphic_element = it.second;

      if (m_has_to_recalculate_elements_vertices) {
        graphic_element->calculateVertices(coordinateWidthPerPixel(), coordinateHeightPerPixel());
      }

      drawElement(*graphic_element);
    }

    m_has_to_recalculate_elements_vertices = false;

    m_shader_program.release();

    glFlush();
  painter.endNativePainting();
}

void MainCanvas::drawElement(GraphicElement &element, bool recalculate_vertices) {
  if (recalculate_vertices || !element.verticesUpdated()) {
    element.calculateVertices();
  }

  for (auto primitive : element.primitives()) {
    drawPrimitive(*primitive, element.isSelected());
  }
}

void MainCanvas::drawPaintArea() {
  QVector< QVector3D > vertices;

  vertices.push_back(QVector3D(m_coordinate_system->left(), m_coordinate_system->bottom(), 0.0));
  vertices.push_back(QVector3D(m_coordinate_system->left(), m_coordinate_system->top(), 0.0));
  vertices.push_back(QVector3D(m_coordinate_system->right(), m_coordinate_system->top(), 0.0));
  vertices.push_back(QVector3D(m_coordinate_system->right(), m_coordinate_system->bottom(), 0.0));

  m_shader_program.setAttributeArray("vertex", vertices.constData());
  m_shader_program.enableAttributeArray("vertex");

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  m_shader_program.setUniformValue("color", m_background_color);

  // draw the vertices
  glDrawArrays(GL_QUADS, 0, vertices.size());

  m_shader_program.disableAttributeArray("vertex");
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

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  m_shader_program.disableAttributeArray("vertex");
}
