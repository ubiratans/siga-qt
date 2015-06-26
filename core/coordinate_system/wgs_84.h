#ifndef CORE_COORDINATE_SYSTEM_WGS_84_H
#define CORE_COORDIANTE_SYSTEM_WGS_84_H

#include "core/coordinate_system/coordinate_system.h"

class Wgs84 : public CoordinateSystem {
public:
  Wgs84();

  std::pair< double, double > origin();

protected:
  void initialize();
};

#endif
