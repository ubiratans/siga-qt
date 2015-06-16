#ifndef CORE_ELEMENT_ELEMENT_CONSTANTS_H
#define CORE_ELEMENT_ELEMENT_CONSTANTS_H

#include <string>
#include <utility>

#include "core/element/element_structs.h"

// Element Properties pairs
const std::pair< std::string, ElementPropertyType > kElementPropertyDemandType = std::make_pair("DEMAND_TYPE", ElementPropertyType::Int);

#endif
