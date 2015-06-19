#include "core/coordinate_system/wgs_84.h"

void Wgs84::initialize() {
  m_name = "WGS-84";

  m_top = 90.0;
  m_bottom = -90.0;
  m_left = -180.0;
  m_right = 180.0;
}
