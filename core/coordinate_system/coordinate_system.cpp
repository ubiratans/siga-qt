#include "core/coordinate_system/coordinate_system.h"

#include "core/coordinate_system/coordinate_system_strings.h"

CoordinateSystem::CoordinateSystem() {
}

std::string CoordinateSystem::name() {
  return m_name;
}

const std::string CoordinateSystem::xAxisName() const {
  return kTkCoordinateSystemWgs84XaxisName;
}

const std::string CoordinateSystem::yAxisName() const {
  return kTkCoordinateSystemWgs84YaxisName;
}

double CoordinateSystem::top() {
  return m_top;
}

double CoordinateSystem::bottom() {
  return m_bottom;
}

double CoordinateSystem::left() {
  return m_left;
}

double CoordinateSystem::right() {
  return m_right;
}

double CoordinateSystem::width() {
  double w = m_right - m_left;

  if (w < 0) {
    w *= -1.0;
  }

  return w;
}

double CoordinateSystem::height() {
  double h = m_top - m_bottom;

  if (h < 0) {
    h *= -1.0;
  }

  return h;
}
