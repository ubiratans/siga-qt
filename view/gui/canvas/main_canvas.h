#ifndef VIEW_CANVAS_MAIN_CANVAS_H
#define VIEW_CANVAS_MAIN_CANVAS_H

#include <QGLWidget>
#include <GL/gl.h>
#include <QGLShaderProgram>

#include "view/gui/graphic_element/graphic_element.h"
#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

class CoordinateSystem;
class CanvasElementManager;

class MainCanvas : public QGLWidget {
  Q_OBJECT

public:
  explicit MainCanvas(CoordinateSystem &coord_system, QWidget *parent = 0);
  virtual ~MainCanvas();

  const CoordinateSystem* const coordinateSystem(); //!< getter of canvas's coordinate system
  void setCoordinateSystem(CoordinateSystem &coord_system);


  QGLShaderProgram& shaderProgram();
  /*double zoom();
  bool setZoom(double value);

  bool zoomOut();
  double maxZoomOut();

  bool zoomIn();
  double maxZoomIn();

  bool fitNetwork();
  void redraw();*/

protected:
  void drawElement(GraphicElement &element, bool recalculate_vertices = false);
  void drawPrimitive(DrawPrimitive &primitive);

  virtual void initializeGL(); //!< initialize context
  virtual void paintGL(); //!< called when the widget needs to be redrawn
  virtual void resizeGL(int width, int height); //!< called when the widget is resized

  bool hasToUpdateVertices();

  QGLShaderProgram m_shader_program;

private:
  CoordinateSystem *m_coordinate_system;
  QMatrix4x4 m_projection_matrix;

  double m_pos_x; //!< Represents the coord. system axis X of the screen position (viewport) of x = 0 (in screen coordinates)
  double m_pos_y; //!< Represents the coord. system axis Y of the screen position (viewport) of y = 0 (in screen coordinates)
  double m_max_width;
  double m_max_height;

  double m_zoom;

  bool m_has_to_recalculate_elements_vertices;
};

#endif
