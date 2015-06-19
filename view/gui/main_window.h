#ifndef VIEW_GUI_MAIN_WINDOW_H
#define VIEW_GUI_MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void createMenu();
  void init();

  Ui::MainWindow *m_ui;

  QMenu *m_menu_file;
  QMenu *m_menu_edit;
  QMenu *m_menu_tools;
  QMenu *m_menu_view;
};

#endif
