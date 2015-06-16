#ifndef CORE_ELEMENT_ELEMENT_STRUCTS_H
#define CORE_ELEMENT_ELEMENT_STRUCTS_H

#include <cstdint>

enum class Unit : char {
  NoUnit,
  Meter,
  Hectometer,
  HectometerCubic,
  MeterCubic,
  Millimiter
};

enum class ElementType {
  Link,
  Node
};

enum class ElementPropertyType {
  Bool = 0,
  Int,
  Double,
  String
};

enum class DemandType : int {
  AnimalConsume,
  HumanConsume,
  Industrial,
  Irrigation
};

enum class LinkType : int {
  Default = 0, //!< Trecho padrão
  Routing, //!< Trecho com propagação
  Pumping, //!< Trecho com bombeamento
  Separator //!< Trecho separador para resultados diferentes
};

enum class NodeType : int {
  Basin = 0,
  Demand,
  Junction,
  Lake,
  Reservoir
};

typedef uint64_t ElementID;

#endif
