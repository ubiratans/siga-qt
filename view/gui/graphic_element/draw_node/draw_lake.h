#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_LAKE_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_LAKE_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawLake : public DrawNode {
public:
  DrawLake(float x, float y);

  NodeType type();

protected:
  void initialize();
};

#endif
