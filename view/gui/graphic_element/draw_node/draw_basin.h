#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_BASIN_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_BASIN_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawBasin : public DrawNode {
public:
  DrawBasin(double x, double y);

  NodeType type();

protected:
  void initialize();
};

#endif
