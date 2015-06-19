#include "view/gui/main_window.h"
#include "view/gui/main_window_ui.h"

#include "view/gui/main_window_strings.h"
#include "view/gui/translation_utils.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  init();
}

void MainWindow::createMenu() {
  m_menu_file = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuFile));
  m_menu_edit = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuEdit));
  m_menu_view = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuView));
  m_menu_tools = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuTools));
}

void MainWindow::init() {
  TranslationUtils::loadDefaultTranslation();
  TranslationUtils::setDefaultContext(kMainWindowStringsContext);

  setWindowTitle(TranslationUtils::tr(kTkMainWindowStringWindowTitle));
  createMenu();
}

MainWindow::~MainWindow() {
  delete m_ui;
}
