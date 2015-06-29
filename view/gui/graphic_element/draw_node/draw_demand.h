#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_DEMAND_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_DEMAND_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawDemand : public DrawNode {
public:
  DrawDemand(float x, float y);

  NodeType type();

protected:
  void initialize();
};

#endif
