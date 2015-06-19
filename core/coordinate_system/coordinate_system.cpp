#include "core/coordinate_system/coordinate_system.h"

CoordinateSystem::CoordinateSystem() {
  initialize();
}

std::string CoordinateSystem::name() {
  return m_name;
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
