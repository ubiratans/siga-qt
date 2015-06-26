#ifndef VIEW_GUI_DRAW_ELEMENT_GRAPHIC_ELEMENT_H
#define VIEW_GUI_DRAW_ELEMENT_GRAPHIC_ELEMENT_H

#include <vector>

#include "core/element/element_structs.h"

class DrawPrimitive;

class GraphicElement {
public:
  GraphicElement(ElementID id, ElementType type);
  virtual ~GraphicElement();

  float scale();
  void setScale(float value);

  float rotation();
  void setRotation(float angle);

  ElementType elementType();
  ElementID id();

  virtual const std::vector< DrawPrimitive* >& primitives() = 0;

protected:
  ElementID m_id;
  ElementType m_element_type;

  float m_scale; //!< Defines element's draw proportion
  float m_rotation;
};

#endif
