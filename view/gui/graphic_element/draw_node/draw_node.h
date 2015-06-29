#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_NODE_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_NODE_H

#include <QString>
#include <vector>

#include "core/element/element_structs.h"

class DrawPrimitive;

class DrawNode {
public:
  DrawNode(float x, float y);
  virtual ~DrawNode();

  float x();
  void setX(float x);

  float y();
  void setY(float y);

  void setPosition(float x, float y);

  virtual NodeType type() = 0;

  bool verticesUpdated();

  std::vector< DrawPrimitive* >& primitives();

  //!< The main intent of this method is to compute all the primitives vertices, but it also calls the initialize() if is needed.
  void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

protected:
  //!< This method will instantiate the primitives and fill the primitives vector, it SHALL not calculate the primitive vertices.
  virtual void initialize() = 0;
  QString m_label;

  float m_x;
  float m_y;

  bool m_has_to_compute_vertices;
  bool m_initialized;

  std::vector< DrawPrimitive* > m_primitives_vector;
};

#endif
