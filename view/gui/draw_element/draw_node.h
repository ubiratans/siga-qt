#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_NODE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_NODE_H

#include "view/gui/draw_element/draw_element.h"

class DrawNode : public DrawElement {
public:
  DrawNode(ElementID id, NodeType node_type, float x, float y, double scale = 1.0);
  void computeVertices(double screen_world_width_proportion, double screen_world_height_proportion);

protected:
  void initializePrimitives();

  float m_x;
  float m_y;
  NodeType m_type;
};

#endif
