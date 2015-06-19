#ifndef VIEW_CANVAS_MAIN_CANVAS_H
#define VIEW_CANVAS_MAIN_CANVAS_H

#include <QGLWidget>
#include <QGLShaderProgram>

class CoordinateSystem;
class CanvasElementManager;

class MainCanvas : public QGLWidget {
  Q_OBJECT

public:
  explicit MainCanvas(CanvasElementManager &manager, QWidget *parent = 0);
  virtual ~MainCanvas();

  const CoordinateSystem* const coordinateSystem(); //!< getter of canvas's coordinate system
  void setCoordinateSystem(CoordinateSystem &coord_system);

/*  double zoom();
  bool setZoom(double value);

  bool zoomOut();
  double maxZoomOut();

  bool zoomIn();
  double maxZoomIn();

  bool fitNetwork();
  void redraw();*/

protected:
  virtual void initializeGL(); //!< initialize context
  virtual void paintGL(); //!< called when the widget needs to be redrawn
  virtual void resizeGL(int width, int height); //!< called when the widget is resized

  QGLShaderProgram m_shader_program;

private:
  CoordinateSystem *m_coordinate_system;
  double m_zoom;
};

#endif
