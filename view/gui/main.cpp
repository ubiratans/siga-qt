#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>

#include "view/gui/main_window.h"
#include "core/core_strings.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow *main_window = new MainWindow();
  main_window->show();

  return app.exec();
}
