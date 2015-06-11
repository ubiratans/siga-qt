#ifndef CORE_ELEMENT_ELEMENT_H
#define CORE_ELEMENT_ELEMENT_H

#include <map>
#include <string>

#include "core/element/element_structs.h"

class ElementManager;

class Element {
  friend class ElementManager;

public:
  ElementID id(); //!< get element id

  double volume(); //!< get volume
  void setVolume(double volume);

  std::string name();
  void setName(std::string name);

  ElementType elementType(); //!< get element type

protected:
  Element(ElementID id, std::string name, double volume, ElementType type);
  virtual ~Element();

  void setID(ElementID id); //!< set element id

  ElementID m_id; //!< Element's identificator
  double m_volume; //!< Volume

  std::string m_name; //!< Element name
  ElementType m_element_type; //!< Element type
};

#endif
