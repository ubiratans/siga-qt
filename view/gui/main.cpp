#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include "view/gui/main_screen.h"
#include "core/core_strings.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  int x = 0;
  long y = 1;

  if (x > y) {

  }

  MainScreen *main_screen = new MainScreen();
  main_screen->show();

  return app.exec();
}
