#ifndef UTILS_COORDINATE_SYSTEM_COORDINATE_SYSTEM_UTILS_H
#define UTILS_COORDINATE_SYSTEM_COORDINATE_SYSTEM_UTILS_H

#include <map>

#include "core/coordinate_system/coordinate_system.h"
#include "utils/coordinate_system/coordinate_system_utils_structs.h"

class CoordinateSystemUtils {
public:
  static CoordinateSystemUtils& instance();
  CoordinateSystem* coordinateSystem(CoordinateSystemID id);

private:
  CoordinateSystemUtils();

  void initialize();
  static CoordinateSystemUtils *m_instance;
  std::map< CoordinateSystemID, CoordinateSystem* > m_coord_system_map;
};

#endif
