#ifndef VIEW_GUI_MAIN_WINDOW_H
#define VIEW_GUI_MAIN_WINDOW_H

#include <QMainWindow>

#include "view/gui/canvas/main_canvas.h"
#include "view/gui/statusbar_widget.h"
#include "view/gui/graphic_element/graphic_element_manager.h"

class ElementManager;
class GraphicElementManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void createCanvas();

private:
  void createMenu();
  void createStatusBar();
  void connectEvents();
  void init();

  Ui::MainWindow *m_ui;

  QMenu *m_menu_file;
  QMenu *m_menu_edit;
  QMenu *m_menu_tools;
  QMenu *m_menu_view;
  QStatusBar *m_status_bar;
  StatusBarWidget *m_mouse_x_position_widget;
  StatusBarWidget *m_mouse_y_position_widget;
  StatusBarWidget *m_zoom_widget;
  MainCanvas *m_main_canvas;

  ElementManager m_element_manager;
  GraphicElementManager *m_graphic_element_manager{nullptr};

private slots:
  void updatePositionStatusbar(double x, double y);
  void updateZoomStatusbar(double zoom);
};

#endif
