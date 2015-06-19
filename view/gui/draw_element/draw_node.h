#ifndef VIEW_GUI_DRAW_ELEMENT_DRAW_NODE_H
#define VIEW_GUI_DRAW_ELEMENT_DRAW_NODE_H

#include "view/gui/draw_element/draw_element.h"

class DrawNode : public DrawElement {
public:
  DrawNode(ElementID id, NodeType node_type, long x, long y, double scale = 1.0);

protected:
  void initializePrimitives();

  long m_x;
  long m_y;
  NodeType m_type;
};

#endif
