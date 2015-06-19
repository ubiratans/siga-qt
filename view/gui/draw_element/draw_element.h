#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_ELEMENT_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_ELEMENT_H

#include <vector>

#include "core/element/element_structs.h"

class DrawPrimitive;

class Painter;

class DrawElement {
public:
  DrawElement(ElementID id, ElementType type, double scale);
  virtual ~DrawElement();

  double scale();
  void setScale(double value);

  ElementType elementType();
  ElementID id();

  const std::vector< DrawPrimitive* >& primitives();

protected:
  virtual void initializePrimitives() = 0;
  std::vector< DrawPrimitive* > m_primitives_vector;

  ElementID m_id;
  ElementType m_element_type;

  double m_scale; //!< Defines element's draw proportion
};

#endif
