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
  delete m_graphic_element_manager;

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

  const CoordinateSystem * const coord_system = m_main_canvas->coordinateSystem();

  m_mouse_x_position_widget = new StatusBarWidget(this);
  m_mouse_y_position_widget = new StatusBarWidget(this);
  m_zoom_widget = new StatusBarWidget(this);

  m_mouse_x_position_widget->setHeaderText(TranslationUtils::translate(kCoordinateSystemStringsContext, coord_system->xAxisName()));
  m_mouse_y_position_widget->setHeaderText(TranslationUtils::translate(kCoordinateSystemStringsContext, coord_system->yAxisName()));
  m_zoom_widget->setHeaderText("Zoom");
  m_zoom_widget->setContentText("1");

  m_status_bar->addWidget(m_mouse_x_position_widget, 0);
  m_status_bar->addWidget(m_mouse_y_position_widget, 0);
  m_status_bar->addWidget(m_zoom_widget, 0);

  m_status_bar->setContentsMargins(0, 0, 0, 0);

  //updateStatusbar(0.0, 0.0);
}

void MainWindow::connectEvents() {
  connect(m_main_canvas, SIGNAL(mouseMoved(double,double)), this, SLOT(updatePositionStatusbar(double,double)));
  connect(m_main_canvas, SIGNAL(zoomUpdated(double)), this, SLOT(updateZoomStatusbar(double)));
}

void MainWindow::init() {
  QIcon icon(":/image/app_icon.png");
  setWindowIcon(icon);

  TranslationUtils::loadDefaultTranslation();
  TranslationUtils::setDefaultContext(kMainWindowStringsContext);

  setWindowTitle(TranslationUtils::tr(kTkMainWindowStringWindowTitle));
  createMenu();
  createCanvas();
  createStatusBar();

  connectEvents();
}

void MainWindow::updatePositionStatusbar(double x, double y) {
  QCoreApplication::processEvents();

  if (x > m_main_canvas->coordinateSystem()->right() || x < m_main_canvas->coordinateSystem()->left()) {
    m_mouse_x_position_widget->setContentText("--");
  }

  else {
    m_mouse_x_position_widget->setContentText(QString::number(x, 'f', 2));
  }

  if (y > m_main_canvas->coordinateSystem()->top() || y < m_main_canvas->coordinateSystem()->bottom()) {
    m_mouse_y_position_widget->setContentText("--");
  }

  else {
    m_mouse_y_position_widget->setContentText(QString::number(y, 'f', 2));
  }
}

void MainWindow::updateZoomStatusbar(double zoom) {
  double x = zoom * 100.0;
  m_zoom_widget->setContentText(QString(QString::number(x, 'f', 2) + "%"));
}

void MainWindow::createCanvas() {
  m_graphic_element_manager = new GraphicElementManager(m_element_manager);
  m_main_canvas = new MainCanvas(*m_graphic_element_manager,
                                 *(CoordinateSystemUtils::instance().coordinateSystem(CoordinateSystemID::WGS_84)),
                                 this);

  setCentralWidget(m_main_canvas);
}
