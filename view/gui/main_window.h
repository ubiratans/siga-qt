#ifndef VIEW_GUI_MAIN_WINDOW_H
#define VIEW_GUI_MAIN_WINDOW_H

#include <QMainWindow>

#include "view/gui/canvas/main_canvas.h"
#include "view/gui/statusbar_widget.h"

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
  MainCanvas *m_main_canvas;

private slots:
  void updateStatusbar(double x, double y);
};

#endif
