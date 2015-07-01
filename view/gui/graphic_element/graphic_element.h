#ifndef VIEW_GUI_DRAW_ELEMENT_GRAPHIC_ELEMENT_H
#define VIEW_GUI_DRAW_ELEMENT_GRAPHIC_ELEMENT_H

#include <map>
#include <QVector>
#include <QVector3D>

#include "core/element/element_structs.h"

class DrawPrimitive;

class GraphicElement {
public:
  GraphicElement(ElementID id, ElementType type);
  virtual ~GraphicElement();

  //virtual bool hitTest(float x, float y) = 0; //!< verify if the point in world coords is within the element
  //virtual bool hitTest(QRect &rectangle) = 0;

  virtual void calculateVertices() = 0;
  virtual void calculateVertices(double screen_world_width_proportion, double screen_world_height_proportion) = 0;

  bool verticesUpdated();

  float scale();
  virtual void setScale(float value) = 0;

  float rotation();
  virtual void setRotation(float angle) = 0;

  ElementType elementType();
  ElementID id();

  virtual const std::vector< DrawPrimitive* >& primitives() = 0;

protected:
  bool m_has_to_calculate_primitives_vertices;

  ElementID m_id;
  ElementType m_element_type;

  float m_scale; //!< Defines element's draw proportion
  float m_rotation;
};

#endif
