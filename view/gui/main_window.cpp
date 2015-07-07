#include "view/gui/main_window.h"
#include "view/gui/main_window_ui.h"

#include "core/coordinate_system/coordinate_system_strings.h"
#include "view/gui/main_window_strings.h"
#include "view/gui/translation_utils.h"
#include "utils/coordinate_system/coordinate_system_utils.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  init();
}

MainWindow::~MainWindow() {
  delete m_ui;
}

void MainWindow::createMenu() {
  m_menu_file = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuFile));
  m_menu_edit = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuEdit));
  m_menu_view = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuView));
  m_menu_tools = menuBar()->addMenu(TranslationUtils::tr(kTkMainWindowStringMenuTools));
}

void MainWindow::createStatusBar() {
  m_status_bar = new QStatusBar(this);
  setStatusBar(m_status_bar);

  updateStatusbar(0.0, 0.0);
}

void MainWindow::connectEvents() {
  connect(m_main_canvas, SIGNAL(mouseMoved(double,double)), this, SLOT(updateStatusbar(double,double)));
}

void MainWindow::init() {
  TranslationUtils::loadDefaultTranslation();
  TranslationUtils::setDefaultContext(kMainWindowStringsContext);

  setWindowTitle(TranslationUtils::tr(kTkMainWindowStringWindowTitle));
  createMenu();
  createCanvas();
  createStatusBar();

  connectEvents();
}

void MainWindow::updateStatusbar(double x, double y) {
  QCoreApplication::processEvents();
  const CoordinateSystem * const coord_system = m_main_canvas->coordinateSystem();

  QString message = QString(
        TranslationUtils::translate(kCoordinateSystemStringsContext, coord_system->xAxisName()) +
        ": %1 @ " +
        TranslationUtils::translate(kCoordinateSystemStringsContext, coord_system->yAxisName()) +
        ": %2"
        ).arg(QString::number(x), QString::number(y));

  m_status_bar->showMessage(message, 0);
}

void MainWindow::createCanvas() {
  m_main_canvas = new MainCanvas(*(CoordinateSystemUtils::instance().coordinateSystem(CoordinateSystemID::WGS_84)), this);
  setCentralWidget(m_main_canvas);
}
