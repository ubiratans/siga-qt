#include "utils/coordinate_system/coordinate_system_utils.h"

#include "core/coordinate_system/wgs_84.h"

CoordinateSystemUtils* CoordinateSystemUtils::m_instance = nullptr;

CoordinateSystemUtils &CoordinateSystemUtils::instance() {
  if (m_instance == nullptr) {
    m_instance = new CoordinateSystemUtils;
  }

  return *m_instance;
}

CoordinateSystem* CoordinateSystemUtils::coordinateSystem(CoordinateSystemID id) {
  auto it = m_coord_system_map.find(id);
  CoordinateSystem *coord_system = (it == m_coord_system_map.end()? nullptr: it->second);

  return coord_system;
}

CoordinateSystemUtils::CoordinateSystemUtils() {
  initialize();
}

void CoordinateSystemUtils::initialize() {
  m_coord_system_map.clear();

  Wgs84 *wgs_coord_sys = new Wgs84();
  m_coord_system_map[CoordinateSystemID::WGS_84] = wgs_coord_sys;
}
